#include "radio.h"

#define FXTAL						16000000	//Xtal Frequency in Hz

void RadioUHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_U, cs);
}

void RadioVHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_V, cs);
}

void RadioInterfacesInit() {
	//Initialize Radio Interfaces
	AX5043InterfaceStruct radioInterfaces[2];
	radioInterfaces[RADIO_UHF].SPICS = RadioUHFCS;
	radioInterfaces[RADIO_UHF].SPIReadWrite = SPI1ReadWrite;
	radioInterfaces[RADIO_VHF].SPICS = RadioVHFCS;
	radioInterfaces[RADIO_VHF].SPIReadWrite = SPI2ReadWrite;
	AX5043InterfacesInit(radioInterfaces, 2);
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
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE0, &data, 1);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE12, 0x00, 1);
	data = 0x03;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE13, &data, 1);
	data = 0x04;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE16, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE17, &data, 1);
	data = 0x06;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE24, &data, 1);
	data = 0x07;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE28, &data, 1);
	data = 0x5C;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE33, &data, 1);
	data = 0x53;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE34, &data, 1);
	data = 0x76;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE35, &data, 1);
	data = 0x92;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE38, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE48, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE49, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE50, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE51, &data, 1);
	data = 0x08;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE52, &data, 1);
	data = 0x10;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE53, &data, 1);
	data = 0x24;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE68, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE114, &data, 1);

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_VHF, PLLLoop_Filter500kHz);
	AX5043SynthSetPLLChargePumpCurrent(RADIO_VHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_VHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCO2Internal(RADIO_VHF, 1);	//Use VCO 2 with external inductor
//	AX5043SynthSetPLLRefDivider(RADIO_VHF, PllCodiv_fXtal_div1);	//Set refrence divider
	AX5043SynthSetFrequencyA(RADIO_VHF, 0x091E51EC);
//	AX5043SynthSetFrequencyB(RADIO_VHF, 0x08B22E58);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_VHF);
	while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete
//	AX5043SynthStartAutoRangingB(RADIO_VHF);
//	while(AX5043SynthGetAutoRangingB(RADIO_VHF));	//Wait for Auto Ranging Complete

	//Set PLL/VCO Parameters
	//AX5043PLLParamSetVCOBias(RADIO_VHF, 0x07);
	//AX5043PLLParamIsManualVCOIEnabled(RADIO_VHF);
	//AX5043PLLParamSetLockDetectDelay(RADIO_VHF, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(RADIO_VHF, PLLRangingClock_11);	//Default

	//Set Modulation
	AX5043GeneralSetModulation(RADIO_VHF, AFSK);
	AX5043TXParamSetTXDatarate(RADIO_VHF, 0x04EB);	//Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, 0x0A8E); //Set FSK deviation to 3000 Hz
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x14);	//Set AFSK Space freq. of 1200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x25);		//Set AFSK Mark freq. of 2200 Hz
}

void RadioUHFInit() {
	//Reset Radio
	AX5043PwrReset(RADIO_UHF);

	//Power Down
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);

	//Set GPIOs
	AX5043GPIOCnfgSysClk(RADIO_UHF, SysClk_Low, 0);
	AX5043GPIOCnfgDCLK(RADIO_UHF, DCLK_Modem_Data_Clk_Output, 0, 0);
	AX5043GPIOCnfgDATA(RADIO_UHF, DATA_Modem_Data_Output, 0, 0);
	//AX5043GPIOCnfgIRQ(RADIO_UHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_UHF, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(RADIO_UHF, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(RADIO_UHF, DACInput_SampleRotI);
	AX5043GPIOSetDACInputShift(RADIO_UHF, 0x0C);

	//Set Performance Tuning Registers
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE0, &data, 1);		//F00
	data = 0x04;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE8, &data, 1);		//F08: Power Control 1??
	data = 0x03;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE13, &data, 1);	//F0D: Ref ??
	data = 0x04;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE16, &data, 1);	//F10: XTALOSC ??
	data = 0x00;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE17, &data, 1);	//F11: XTALAMPL ??
//	data = 0x06;	//For TX
	data = 0x02;	//For RX
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE24, &data, 1);	//F18
	data = 0x07;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE28, &data, 1);	//F1C
	data = 0x68;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE33, &data, 1);	//F21
	data = 0xFF;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE34, &data, 1);	//F22
	data = 0x84;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE35, &data, 1);	//F23
	data = 0x98;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE38, &data, 1);	//F26
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE48, &data, 1);	//F30
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE49, &data, 1);	//F31
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE50, &data, 1);	//F32
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE51, &data, 1);	//F33
	data = 0x28;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE52, &data, 1);	//F34
	data = 0x10;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE53, &data, 1);	//F35
	data = 0x25;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE68, &data, 1);	//F44
	data = 0xE7;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE95, &data, 1);	//F5F: MODCFGP ??
	data = 0x06;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE114, &data, 1);	//F72

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_UHF, PLLLoop_Filter500kHz);
//	AX5043SynthSetPLLChargePumpCurrent(RADIO_UHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_UHF, 0);	//Use VCO 1
//	AX5043SynthSetPLLVCO2Internal(RADIO_UHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCOEnableRefDivider(RADIO_UHF, 1);
	AX5043SynthSetFrequencyA(RADIO_UHF, (0x1B474335 + 0x0419));	//For 436.45MHz is 0x1B473334 calculated but calibrated value is 0x1B474335
//	AX5043SynthSetFrequencyB(RADIO_UHF, 0x1B474335);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_UHF);
	while(AX5043SynthGetAutoRangingA(RADIO_UHF));	//Wait for Auto Ranging Complete
//	AX5043SynthStartAutoRangingB(RADIO_UHF);
//	while(AX5043SynthGetAutoRangingB(RADIO_UHF));	//Wait for Auto Ranging Complete

	//Set PLL/VCO Parameters
	//AX5043PLLParamSetVCOBias(RADIO_UHF, 0x07);
	//AX5043PLLParamIsManualVCOIEnabled(RADIO_UHF);
	//AX5043PLLParamSetLockDetectDelay(RADIO_UHF, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(RADIO_UHF, PLLRangingClock_11);	//Default

	//Set Modulation for TX Mode
	AX5043GeneralSetModulation(RADIO_UHF, AFSK);
	AX5043TXParamSetTXDatarate(RADIO_UHF, 0x04EB);	//Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_UHF, 0x0A8E);	//Set FSK deviation to 3000 Hz
//	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x13);		//Set TX AFSK Space freq. of 2200 Hz
//	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x0A);			//Set TX AFSK Mark freq. of 1200 Hz

	//Set Demodulation for RX Mode
//	RadioUHFSetIF(20000);
//	RadioUHFSetBandwidth(125000);
//	RadioUHFSetRXBitrate(1200);

	AX5043RXParamSetIFFrequency(RADIO_UHF, 0x099A);		//~37498Hz
	AX5043RXParamSetDecimation(RADIO_UHF, 0x04);		//~250kHz
	AX5043RXParamSetRXDatarate(RADIO_UHF, 0x0682AB);	//~1200 bits/s
	AX5043RXParamSetRXMaximumDatarateOffset(RADIO_UHF, 0x00);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_UHF, 0x28F6);	//Set to 10kHz
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_UHF, 1);
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x25);	//Set RX AFSK Space freq. of 2200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x14);		//Set RX AFSK Mark freq. of 1200 Hz
	AX5043RXParamSetAFSKDetBandwitdh(RADIO_UHF, 0x0E);
//	AX5043RXParamSetRXFSKMaxDeviation(RADIO_UHF, 0x43C0);
//	AX5043RXParamSetRXFSKMinDeviation(RADIO_UHF, 0xDC40);
	AX5043RXParamSetRXParameterNumber0(RADIO_UHF, 0);
	AX5043RXParamSetRXParameterNumber1(RADIO_UHF, 1);
	AX5043RXParamSetRXParameterNumber2(RADIO_UHF, 3);
	AX5043RXParamSetRXParameterNumber3(RADIO_UHF, 3);
	//RX Parameter 0
	AX5043RXParamSetAGCReleaseSpeed0(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed0(RADIO_UHF, 0x08);
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_UHF, 0x84);
	AX5043RXParamSetAGCTargetHysteresis0(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset0(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset0(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery0(RADIO_UHF, 0x0D, 0x0E);
	AX5043PacketSetGainDatarateRecovery0(RADIO_UHF, 0x0D, 0x08);
	AX5043RXParamSetRXPhaseGain0(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter0(RADIO_UHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA0(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB0(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC0(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD0(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain0(RADIO_UHF, 0x06);
	AX5043RXParamSetRXAmplitudeAGCJump0(RADIO_UHF, 0x01);
	AX5043RXParamSetRXFrequencyDeviation0(RADIO_UHF, 0x00);
	AX5043RXParamSetDeviationDecay0(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate0(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(RADIO_UHF, 0x00);
	//RX Parameter 1
	AX5043RXParamSetAGCReleaseSpeed1(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed1(RADIO_UHF, 0x08);
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_UHF, 0x84);
	AX5043RXParamSetAGCTargetHysteresis1(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset1(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset1(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery1(RADIO_UHF, 0x0D, 0x0C);
	AX5043PacketSetGainDatarateRecovery1(RADIO_UHF, 0x0D, 0x07);
	AX5043RXParamSetRXPhaseGain1(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter1(RADIO_UHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA1(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB1(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC1(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD1(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain1(RADIO_UHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation1(RADIO_UHF, 0x01C0);
	AX5043RXParamSetDeviationDecay1(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate1(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_UHF, 0x00);
	//RX Parameter 3
	AX5043RXParamSetAGCReleaseSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCAttackSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_UHF, 0x84);
	AX5043RXParamSetAGCTargetHysteresis3(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset3(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset3(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery3(RADIO_UHF, 0x0D, 0x0B);
	AX5043PacketSetGainDatarateRecovery3(RADIO_UHF, 0x0D, 0x06);
	AX5043RXParamSetRXPhaseGain3(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter3(RADIO_UHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA3(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB3(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC3(RADIO_UHF, 0x0D);
	AX5043RXParamSetRXFrequencyGainD3(RADIO_UHF, 0x0D);
	AX5043RXParamSetRXAmplitudeGain3(RADIO_UHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation3(RADIO_UHF, 0x01C0);
	AX5043RXParamSetDeviationDecay3(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate3(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(RADIO_UHF, 0x00);

	//Set Packet, encoding and framing
	AX5043PacketSetMSBFirst(RADIO_UHF, 0);
	AX5043PacketEnableEncodeBitInversion(RADIO_UHF, 1);
	AX5043PacketEnableEncodeDifferential(RADIO_UHF, 1);
	AX5043PacketSetFrameMode(RADIO_UHF, FrmMode_Raw);
	AX5043PacketSetCRCMode(RADIO_UHF, CRCMode_Off);
//	AX5043PacketSetPacketChunkSize(RADIO_UHF, PacketChunkSize_240byte);
	AX5043PacketSetMaxLength(RADIO_UHF, 0xC8);

	//Set Pattern Matching
	AX5043PacketSetPaternLength0(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_UHF, 0x1F);
	AX5043PacketSetPaternMatch0(RADIO_UHF, 0xAAAAAAAA);
	AX5043PacketSetPaternMatch0Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_UHF, 0x0A);
	AX5043PacketSetPaternLength1(RADIO_UHF, 0x8A);
	AX5043PacketSetPaternMatch1(RADIO_UHF, 0x7E7E);

	//Set packet control
	AX5043PacketSetTXPLLBoostTime(RADIO_UHF, 0x02, 0x03);
	AX5043PacketSetTXPLLSettlingTime(RADIO_UHF, 0x14, 0x00);
	AX5043PacketSetRXPLLBoostTime(RADIO_UHF, 0x02, 0x03);
	AX5043PacketSetRXPLLSettlingTime(RADIO_UHF, 0x14, 0x00);
	AX5043PacketSetRXDCOffsetAcquisitionTime(RADIO_UHF, 0x00, 0x00);
	AX5043PacketSetRXCoarseAGCTime(RADIO_UHF, 0x13, 0x03);
	AX5043PacketSetRXAGCSettlingTime(RADIO_UHF, 0x00, 0x00);
	AX5043PacketSetRXRSSISettlingTime(RADIO_UHF, 0x03, 0x00);
	AX5043PacketSetRXPreamble1Timeout(RADIO_UHF, 0x00, 0x00);
	AX5043PacketSetRXPreamble2Timeout(RADIO_UHF, 0x17, 0x00);
	AX5043PacketSetRXPreamble3Timeout(RADIO_UHF, 0x00, 0x00);
}

void RadioVHFEnterTX() {
	PwrStatus status = AX5043PwrStats(RADIO_VHF);
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_VHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_VHF);
	}
}

void RadioUHFEnterTX() {
	PwrStatus status = AX5043PwrStats(RADIO_UHF);
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_UHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_UHF);
	}
}

void RadioUHFSetBandwidth(uint32_t bandwidth) {
	uint8_t decimation = FXTAL / (bandwidth << 4);
	AX5043RXParamSetDecimation(RADIO_UHF, decimation);
}

void RadioUHFSetIF(uint32_t ifFreq) {
	uint16_t ifF = (uint16_t)(ifFreq * (1048576.f / FXTAL) + 0.5f);
	AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
}

void RadioUHFSetRXBitrate(uint32_t bitrate) {
	uint8_t decimation = AX5043RXParamGetDecimation(RADIO_UHF);
	uint32_t dr = (FXTAL << 7) / (bitrate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_UHF, dr);
}

void RadioVHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength; //FIFO Data Length
	fifoData[i++] = 0x2B;		//Bypass encoder and framing, bypass CRC, set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_VHF, fifoData, i);
}

void RadioUHFWritePreamble(uint8_t symbol, uint8_t length) {
	uint8_t fifoData[4];
	fifoData[0] = 0x62;
	fifoData[1] = 0x18;
	fifoData[2] = length;
	fifoData[3] = symbol;

	AX5043FIFOSetFIFO(RADIO_UHF, fifoData, 4);
}

void RadioUHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength + 1;	//FIFO Data Length + 1 (info/flag byte, the next byte)
	fifoData[i++] = 0x03;		//Bypass encoder and framing, bypass CRC, set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_UHF, fifoData, i);
}
