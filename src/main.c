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

	//Initialize the VHF and UHF Radio
	RadioInit();

	volatile uint8_t revision = AX5043GeneralRevision(RADIO_VHF);
	volatile uint8_t scratch = AX5043GeneralScratch(RADIO_VHF);
	volatile RadioState status = AX5043GeneralRadioState(RADIO_VHF);

	//Initializations done, VUHFRadio Powered Up
	GPIOWrite(GPIO_OUT_LED4, 1);

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
		GPIOWrite(GPIO_OUT_LED5, USBVCPIsConnected());
	}
}

void Error_Handler(void) {

}
