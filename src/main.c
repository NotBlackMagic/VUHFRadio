#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "usb_vcp.h"

#include "ax25.h"
#include "radio.h"

#include "atCmdInter.h"
#include "commandHandler.h"

int main(void) {
	//Configure the system clock
	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	USBVCPInit();
	ADC1Init();
	SPI1Init();
	SPI2Init();
//	PWM1Init();
//	PWM2Init();

	//Initialize Global Variables
	GlobalVariablesInit();

	//Initialize the VHF and UHF Radio Interfaces, set the SPI and CS
	RadioInterfacesInit();

	//Init VHF Radio
	RadioVHFInit();

	//Config VHF Radio
	RadioConfigStruct radioVHFConfig;
	radioVHFConfig.frequency = 145895000;
	radioVHFConfig.datarate = 1200;
	radioVHFConfig.afcRange = 2000;
	radioVHFConfig.fskDeviation = 3000;
	radioVHFConfig.modulation = AFSK;
	RadioVHFModConfig(radioVHFConfig);

	//Init UHF Radio
	RadioUHFInit();

	//Config UHF Radio
	RadioConfigStruct radioUHFConfig;
	radioUHFConfig.frequency = 436450000 + 4600;
	radioUHFConfig.datarate = 1200;
	radioUHFConfig.afcRange = 2000;
	radioUHFConfig.fskDeviation = 3000;
	radioUHFConfig.modulation = AFSK;
	RadioUHFModConfig(radioUHFConfig);

	//Initializations done, VUHFRadio Powered Up
	GPIOWrite(GPIO_OUT_LED5, 1);

	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_RXEN);
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_RXEN);

	uint32_t time = GetSysTick();

	//Variables for USB/AT Commands
	uint8_t isVCPConnected = 0;
	uint8_t rxUSBData[512];
	uint16_t rxLength;
	uint8_t* framed;
	uint16_t framedLength;

	//Variables for RX data
	uint8_t rxTestData[300];
	uint8_t rxAX25Data[300];
	while(1) {
		//USB/AT Command Interpreter
		if(USBVCPRead(rxUSBData, &rxLength) == 1) {
			if(ATCmdFraming(rxUSBData, rxLength, &framed, &framedLength) == 0) {
				ATCmdStruct atCmdstr;
				if(ATCmdParse(framed, framedLength, &atCmdstr) == 0) {
					CommandHandler(atCmdstr.cmd, atCmdstr.args, (CommandTypeEnum)atCmdstr.type);
				}
			}
		}

		//This Sets the LED1 to the Virtual COM Connection state, LED is ON if connected
		if(USBVCPIsConnected()) {
			if(isVCPConnected == 0) {
				//First Connection, write welcome message
				USBVCPWrite("Welcome to VUHFRadio V1! \n", 26);
				USBVCPWrite("Hardware Version: 1.2, Nov 2019 \n", 33);
				USBVCPWrite("Software Version: 0.7, Jan 2020 \n", 33);
				USBVCPWrite("This Module uses AT Commands, for more info write AT+LIST \n", 59);

				isVCPConnected = 1;
			}
		}
		else {
			isVCPConnected = 0;
		}
		GPIOWrite(GPIO_OUT_LED4, USBVCPIsConnected());

		uint8_t fifoCnt = AX5043FIFOGetFIFOCount(RADIO_UHF);
		if(fifoCnt > 0) {
			AX5043FIFOGetFIFO(RADIO_UHF, rxTestData, fifoCnt);
			uint8_t fifoOpcode = rxTestData[0];
			uint8_t fifoLength = rxTestData[1];
			uint8_t fifoStatus = rxTestData[2];

			uint8_t crc = (fifoStatus & DATA_CRCFAIL) >> 3;

			if(fifoCnt > 20) {
				AX25Struct ax25Struct;
				ax25Struct.payload = rxAX25Data;

				AX25Decode(&rxTestData[3], fifoCnt - 3, &ax25Struct);

				//AX25 Filtering, except CRC (CRC is part of HDLC frame)
				if(AX25Filter(ax25Struct, uhfAX25FltStruct) == 0x00) {
					uint8_t dspInfo = 0;
					uint16_t len = 0;
					char str[400];

					uint8_t hour, min, sec;
					uint16_t ms;
					GetSysTickAsTime(&hour, &min, &sec, &ms);
					len += sprintf(&str[len], "%03d:%02d:%02d ", hour, min, sec);

					len += sprintf(&str[len], "RX UHF: ");
					//Add Source, destination, control and PID only if not filtered on those!
					if(uhfAX25FltStruct.onSourceAddress == 0x00) {
						len += sprintf(&str[len], "Src: %s; ", ax25Struct.sourceAddress);
						dspInfo = 1;
					}
					if(uhfAX25FltStruct.onDestinationAddress == 0x00) {
						len += sprintf(&str[len], "Dst: %s; ", ax25Struct.destinationAddress);
						dspInfo = 1;
					}
					if(uhfAX25FltStruct.onControlField == 0x00) {
						len += sprintf(&str[len], "Ctrl: %d; ", ax25Struct.control);
						dspInfo = 1;
					}
					if(uhfAX25FltStruct.onPIDField == 0x00) {
						len += sprintf(&str[len], "PID: %d; ", ax25Struct.pid);
						dspInfo = 1;
					}

					//Check if any Info was added, to be displayed
					if(dspInfo == 0x01) {
						len += sprintf(&str[len], "\n");
					}
					else {
						//No Info to display so reset len (string index counter)
						len = 0;
					}

					//Add payload, on new line
					len += sprintf(&str[len], "%03d:%02d:%02d ", hour, min, sec);
					len += sprintf(&str[len], "RX UHF: %s \n", ax25Struct.payload);
					USBVCPWrite(str, len);
				}
			}
			GPIOWrite(GPIO_OUT_LED1, 1);
		}
		else {
			GPIOWrite(GPIO_OUT_LED1, 0);
		}

		fifoCnt = AX5043FIFOGetFIFOCount(RADIO_VHF);
		if(fifoCnt > 0) {
			AX5043FIFOGetFIFO(RADIO_VHF, rxTestData, fifoCnt);
			uint8_t fifoOpcode = rxTestData[0];
			uint8_t fifoLength = rxTestData[1];
			uint8_t fifoStatus = rxTestData[2];

			uint8_t crc = (fifoStatus & DATA_CRCFAIL) >> 3;

			if(fifoCnt > 20) {
				AX25Struct ax25Struct;
				ax25Struct.payload = rxAX25Data;

				AX25Decode(&rxTestData[3], fifoCnt - 3, &ax25Struct);

				//AX25 Filtering, except CRC (CRC is part of HDLC frame)
				if(AX25Filter(ax25Struct, vhfAX25FltStruct) == 0x00) {
					uint8_t dspInfo = 0;
					uint16_t len = 0;
					char str[400];

					uint8_t hour, min, sec;
					uint16_t ms;
					GetSysTickAsTime(&hour, &min, &sec, &ms);		//Get Local Timestamp
					len += sprintf(&str[len], "%03d:%02d:%02d ", hour, min, sec);	//Add local Timestamp

					len += sprintf(&str[len], "RX VHF: ");
					//Add Source, destination, control and PID only if not filtered on those!
					if(vhfAX25FltStruct.onSourceAddress == 0x00) {
						len += sprintf(&str[len], "Src: %s; ", ax25Struct.sourceAddress);
						dspInfo = 1;
					}
					if(vhfAX25FltStruct.onDestinationAddress == 0x00) {
						len += sprintf(&str[len], "Dst: %s; ", ax25Struct.destinationAddress);
						dspInfo = 1;
					}
					if(vhfAX25FltStruct.onControlField == 0x00) {
						len += sprintf(&str[len], "Ctrl: %d; ", ax25Struct.control);
						dspInfo = 1;
					}
					if(vhfAX25FltStruct.onPIDField == 0x00) {
						len += sprintf(&str[len], "PID: %d; ", ax25Struct.pid);
						dspInfo = 1;
					}

					//Check if any Info was added, to be displayed
					if(dspInfo == 0x01) {
						len += sprintf(&str[len], "\n");
					}
					else {
						//No Info to display so reset len (string index counter)
						len = 0;
					}

					//Add payload, on new line
					len += sprintf(&str[len], "%03d:%02d:%02d ", hour, min, sec);	//Add local Timestamp
					len += sprintf(&str[len], "RX VHF: %s \n", ax25Struct.payload);
					USBVCPWrite(str, len);
				}
			}
			GPIOWrite(GPIO_OUT_LED3, 1);
		}
		else {
			GPIOWrite(GPIO_OUT_LED3, 0);
		}

//		if(time + 1000 < GetSysTick()) {
//			time = GetSysTick();
//
//			int8_t uhfRSSI = AX5043GeneralGetRSSI(RADIO_UHF);
//			int8_t vhfRSSI = AX5043GeneralGetRSSI(RADIO_VHF);
//			uint8_t vhfGain = AX5043GeneralGetAGCCurrentGain(RADIO_VHF);
//			char str[200];
//			uint8_t len = sprintf(str, "RSSI VHF: %4d; UHF: %4d; AGC: %3d \n", vhfRSSI, uhfRSSI, vhfGain);
//			USBVCPWrite(str, len);
//
//			int32_t vhfFreqRF = AX5043RXTrackingGetRFFrequency(RADIO_VHF);
//			int32_t uhfFreqRF = AX5043RXTrackingGetRFFrequency(RADIO_UHF);
//			len = sprintf(str, "RF Deviation VHF: %d; UHF: %d \n", vhfFreqRF, uhfFreqRF);
//			USBVCPWrite(str, len);
//		}
	}

	//Send Test Frame
	uint8_t testData[200];
	uint8_t testDataLen = 0;
	testData[testDataLen++] = 'I' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = 'T' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = 'A' << 1;
	testData[testDataLen++] = 'T' << 1;
	testData[testDataLen++] = '1' << 1;
	testData[testDataLen++] = 'C' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = '5' << 1;
	testData[testDataLen++] = 'C' << 1;
	testData[testDataLen++] = 'E' << 1;
	testData[testDataLen++] = 'P' << 1;
	testData[testDataLen++] = ('1' << 1) | 0x01;
	testData[testDataLen++] = 0x03;
	testData[testDataLen++] = 0x00;
	testData[testDataLen++] = '0';
	testData[testDataLen++] = '1';
	testData[testDataLen++] = '2';
	testData[testDataLen++] = '3';
	testData[testDataLen++] = '4';
	testData[testDataLen++] = '5';
	testData[testDataLen++] = '6';
	testData[testDataLen++] = '7';
	testData[testDataLen++] = '8';
	testData[testDataLen++] = '9';
	testData[testDataLen++] = '\n';

	//Random generator
	uint8_t i;
	for(i = 0; i < 200; i++) {
		testData[i] = rand();
	}
	testDataLen = i;

	RadioState radioState = AX5043GeneralRadioState(RADIO_UHF);
<<<<<<< HEAD
	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(RADIO_UHF);
	RadioUHFEnterTX();
	while(1) {
		RadioUHFEnterTX();
//		RadioUHFWritePreamble(0x55, 200);
=======
	while(1) {
		RadioUHFEnterTX();
//		RadioUHFWritePreamble(0x55, 20);
>>>>>>> 9f74b69e9f1cd2293367f60158a7a850cfd3cb66
		RadioUHFWriteFrame(testData, testDataLen);
		AX5043FIFOSetFIFOStatCommand(RADIO_UHF, FIFOStat_Commit);

		do {
			radioState = AX5043GeneralRadioState(RADIO_UHF);

			if(radioState == RadioState_TX || radioState == RadioState_TXTail) {
				GPIOWrite(GPIO_OUT_LED0, 1);
			}
			else {
				GPIOWrite(GPIO_OUT_LED0, 0);
			}

		} while(radioState != RadioState_Idle);

		AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);

//		Delay(1000);
	}
}

void Error_Handler(void) {

}
