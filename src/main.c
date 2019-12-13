#include "main.h"

#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "usb_vcp.h"

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

	//Initialize the VHF and UHF Radio Interfaces, set the SPI and CS
	RadioInterfacesInit();

	//Init VHF Radio
	RadioUHFInit();

	//Initializations done, VUHFRadio Powered Up
	GPIOWrite(GPIO_OUT_LED5, 1);

	volatile uint8_t diversity = AX5043GeneralGetAntennaDiversity(RADIO_UHF);

	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_RXEN);

	uint8_t rxTestData[300];
	while(1) {
		uint8_t fifoCnt = AX5043FIFOGetFIFOCount(RADIO_UHF);
		if(fifoCnt > 0) {
			AX5043FIFOGetFIFO(fifoCnt, rxTestData, fifoCnt);
			USBVCPWrite(rxTestData, fifoCnt);
		}

		char str[200];
		uint8_t rssiAGC = AX5043GeneralGetAGCCurrentGain(RADIO_UHF);
		uint8_t rssi = AX5043GeneralGetRSSI(RADIO_UHF);
		uint16_t trackAmp = AX5043RXTrackingAmplitude(RADIO_UHF);
		uint8_t len = sprintf(str, "Amp: %u; RSSI AGC: %u; RSSI: %u\n", trackAmp, rssiAGC, rssi);
		USBVCPWrite(str, len);

		uint16_t trackFreq = AX5043RXTrackingGetFrequency(RADIO_UHF);
		int32_t trackRFFreq = ((int32_t)AX5043RXTrackingGetRFFrequency(RADIO_UHF) << 12) >> 12;
		uint32_t trackDatarate = AX5043RXTrackingDatarate(RADIO_UHF);
		len = sprintf(str, "RFFreq: %d; Freq: %u; Datarate: %u\n", trackRFFreq, trackFreq, trackDatarate);
		USBVCPWrite(str, len);

		Delay(100);
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

	RadioState radioState = AX5043GeneralRadioState(RADIO_UHF);
	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(RADIO_UHF);
	RadioUHFEnterTX();
	while(1) {
		RadioUHFEnterTX();
		RadioUHFWritePreamble(0x55, 10);
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
	}

//	volatile uint8_t revisionV = AX5043GeneralRevision(RADIO_VHF);
//	volatile uint8_t revisionU = AX5043GeneralRevision(RADIO_UHF);
//	volatile uint8_t scratchV = AX5043GeneralScratch(RADIO_VHF);
//	volatile uint8_t scratchU = AX5043GeneralScratch(RADIO_UHF);
//	volatile RadioState statusV = AX5043GeneralRadioState(RADIO_VHF);
//	volatile RadioState statusU = AX5043GeneralRadioState(RADIO_UHF);

	uint8_t isVCPConnected = 0;
	uint8_t rxData[256];
	uint16_t rxLength;
	uint8_t* framed;
	uint8_t framedLength;
	while (1) {
		if(USBVCPRead(rxData, &rxLength) == 1) {
			if(ATCmdFraming(rxData, rxLength, &framed, &framedLength) == 0) {
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
				USBVCPWrite("Software Version: 0.1, Nov 2019 \n", 33);
				USBVCPWrite("This Module uses AT Commands, for more info write AT+LIST \n", 59);

				isVCPConnected = 1;
			}
		}
		else {
			isVCPConnected = 0;
		}
		GPIOWrite(GPIO_OUT_LED4, USBVCPIsConnected());
	}
}

void Error_Handler(void) {

}
