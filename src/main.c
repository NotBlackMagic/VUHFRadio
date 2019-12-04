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


	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_RXEN);

	uint8_t rxTestData[300];
	while(1) {
		uint8_t fifoCnt = AX5043FIFOGetFIFOCount(RADIO_UHF);
		if(fifoCnt > 0) {
			AX5043FIFOGetFIFO(fifoCnt, rxTestData, fifoCnt);
			USBVCPWrite(rxTestData, fifoCnt);
		}

		char str[100];
		uint8_t rssi = AX5043GeneralRSSI(RADIO_UHF);
		uint8_t len = sprintf(str, "RSSI: %u\n", rssi);
		USBVCPWrite(str, len);

		Delay(100);
	}

	//Send Test Frame
	uint8_t testData[200];
	uint8_t i;
	for(i = 0; i < 20; i++) {
		testData[i] = 0x7E;
	}
	for(i = 20; i < 180; i++) {
		testData[i] = i << 1;
	}
	for(i = 180; i < 200; i++) {
		testData[i] = 0x7E;
	}

	RadioState radioState = AX5043GeneralRadioState(RADIO_UHF);
	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(RADIO_UHF);
	while(1) {
		RadioUHFEnterTX();
		RadioUHFWriteFrame(testData, 200);
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
