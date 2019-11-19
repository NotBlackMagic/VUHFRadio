#include "radio.h"

#define RADIO_UHF					0
#define RADIO_VHF					1

void RadioUHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_U, cs);
}

void RadioVHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_V, cs);
}

void RadioInit() {
	//Initialize Radio Interfaces
	AX5043InterfaceStruct radioInterfaces[2];
	radioInterfaces[RADIO_UHF].SPICS = RadioUHFCS;
	radioInterfaces[RADIO_UHF].SPIReadWrite = SPI1ReadWrite;
	radioInterfaces[RADIO_VHF].SPICS = RadioVHFCS;
	radioInterfaces[RADIO_VHF].SPIReadWrite = SPI2ReadWrite;
	AX5043InterfacesInit(radioInterfaces, 2);

	//Reset Radios
	AX5043PwrReset(RADIO_UHF);
	AX5043PwrReset(RADIO_VHF);

	//Powerdown Radios
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_Powerdown);

	//Set basic parameters

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_UHF);
	while(AX5043SynthGetAutoRangingA(RADIO_UHF));	//Wait for Auto Ranging Complete
	AX5043SynthStartAutoRangingB(RADIO_UHF);
	while(AX5043SynthGetAutoRangingB(RADIO_UHF));	//Wait for Auto Ranging Complete
	AX5043SynthStartAutoRangingA(RADIO_VHF);
	while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete
	AX5043SynthStartAutoRangingB(RADIO_VHF);
	while(AX5043SynthGetAutoRangingB(RADIO_VHF));	//Wait for Auto Ranging Complete

}
