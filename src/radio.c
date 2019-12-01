#include "radio.h"

#define RADIO_UHF					0
#define RADIO_VHF					1

void RadioUHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_U, cs);
}

void RadioVHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_V, cs);
}

void RadioVHFInit();

void RadioInit() {
	//Initialize Radio Interfaces
	AX5043InterfaceStruct radioInterfaces[2];
	radioInterfaces[RADIO_UHF].SPICS = RadioUHFCS;
	radioInterfaces[RADIO_UHF].SPIReadWrite = SPI1ReadWrite;
	radioInterfaces[RADIO_VHF].SPICS = RadioVHFCS;
	radioInterfaces[RADIO_VHF].SPIReadWrite = SPI2ReadWrite;
	AX5043InterfacesInit(radioInterfaces, 2);

	RadioVHFInit();

	//Reset Radios
	AX5043PwrReset(RADIO_UHF);

	//Powerdown Radios
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);

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

void RadioVHFInit() {
	//Reset Radio
	AX5043PwrReset(RADIO_VHF);

	//Power Down
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_Powerdown);

	//Set GPIOs
	AX5043GPIOCnfgSysClk(RADIO_VHF, SysClk_Low, 0);
	AX5043GPIOCnfgDCLK(RADIO_VHF, DCLK_Low, 0, 0);
	AX5043GPIOCnfgDATA(RADIO_VHF, DATA_Low, 0, 0);
	//AX5043GPIOCnfgIRQ(RADIO_VHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_VHF, AntSel_Low, 0, 0);
	//AX5043GPIOCnfgPwrRamp(RADIO_VHF, PwrRamp_Low, 0, 0);	//Default

	//Set Performance Tuning Registers
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE0, 0x0F);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE12, 0x00);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE13, 0x03);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE16, 0x04);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE17, 0x00);	//Default
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE24, 0x06);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE28, 0x07);	//Default
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE33, 0x68);
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE34, 0xFF);
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE35, 0x84);
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE38, 0x98);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE48, 0x3F);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE49, 0xF0);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE50, 0x3F);	//Default
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE51, 0xF0);	//Default
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE52, 0x08);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE53, 0x10);	//Default
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE68, 0x25);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE114, 0x00);	//Default

	//Set PLL Parameters
	AX5043PLLParamSetVCOBias(RADIO_VHF, 0x07);
	AX5043PLLParamIsManualVCOIEnabled(RADIO_VHF);
	//AX5043PLLParamSetLockDetectDelay(RADIO_VHF, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(RADIO_VHF, PLLRangingClock_11);	//Default

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_VHF, PLLLoop_ExtLoopFilter);
	AX5043SynthSetPLLLoopEnableExtFilter(RADIO_VHF, 1);
	AX5043SynthSetPLLChargePumpCurrent(RADIO_VHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_VHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCO2Internal(RADIO_VHF, 1);	//Use VCO 2 with external inductor
}
