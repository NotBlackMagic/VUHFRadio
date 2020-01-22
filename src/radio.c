#include "radio.h"

RadioConfigStruct uhfRadioConfiguration;
RadioConfigStruct vhfRadioConfiguration;

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
	AX5043GPIOCnfgDCLK(RADIO_VHF, DCLK_Modem_Data_Clk_Output, 0, 0);
	AX5043GPIOCnfgDATA(RADIO_VHF, DATA_Modem_Data_Output, 0, 0);
	//AX5043GPIOCnfgIRQ(RADIO_VHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_VHF, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(RADIO_VHF, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(RADIO_VHF, DACInput_SampleRotI);
	AX5043GPIOSetDACInputShift(RADIO_VHF, 0x0C);

	//Set IRQ
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifothrcnt = 1;
	irqMask.irqmfifothrfree = 1;
	AX5043IrqSetIRQMask(RADIO_VHF, irqMask);

	//Set Events
	RadioEventMask radioEvenMask;
	radioEvenMask.raw = 0x00;
	radioEvenMask.revmdone = 1;
	AX5043IrqSetRadioEventMask(RADIO_VHF, radioEvenMask);

	//Set Performance Tuning Registers
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE0, &data, 1);		//F00
	data = 0x04;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE8, &data, 1);		//F08: Power Control 1??
	data = 0x03;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE13, &data, 1);	//F0D: Ref ??
	data = 0x04;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE16, &data, 1);	//F10: XTALOSC ??
	data = 0x00;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE17, &data, 1);	//F11: XTALAMPL ??
//	data = 0x06;	//For TX
	data = 0x02;	//For RX
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE24, &data, 1);	//F18
	data = 0x07;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE28, &data, 1);	//F1C
	data = 0x68;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE33, &data, 1);	//F21
	data = 0xFF;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE34, &data, 1);	//F22
	data = 0x84;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE35, &data, 1);	//F23
	data = 0x98;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE38, &data, 1);	//F26
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE48, &data, 1);	//F30
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE49, &data, 1);	//F31
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE50, &data, 1);	//F32
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE51, &data, 1);	//F33
	data = 0x08;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE52, &data, 1);	//F34
	data = 0x10;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE53, &data, 1);	//F35
	data = 0x25;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE68, &data, 1);	//F44
	data = 0xE7;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE95, &data, 1);	//F5F: MODCFGP ??
	data = 0x00;	//Set to 0x06 if "Raw, Soft Bits"
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE114, &data, 1);	//F72

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_VHF, PLLLoop_Filter500kHz);
//	AX5043SynthSetPLLChargePumpCurrent(RADIO_VHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_VHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCO2Internal(RADIO_VHF, 1);	//Use VCO 2 with external inductor
//	AX5043SynthSetPLLVCOEnableRefDivider(RADIO_VHF, 1);
	AX5043SynthSetFrequencyA(RADIO_VHF, (0x091E51EC));	//For 145.895MHz is 0x091E51EC calculated value
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

	//Set Modulation for TX Mode
	AX5043GeneralSetModulation(RADIO_VHF, FSK);
	AX5043TXParamSetTXDatarate(RADIO_VHF, 0x2752);	//AFSK: 0x04EB; Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, 0x09D5);	//AFSK: 0x0A8E; Set FSK deviation to 3000 Hz

//	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x13);		//Set TX AFSK Space freq. of 2200 Hz
//	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x0A);			//Set TX AFSK Mark freq. of 1200 Hz

	//Set Demodulation for RX Mode
//	RadioUHFSetIF(20000);
//	RadioUHFSetBandwidth(125000);
//	RadioUHFSetRXBitrate(1200);

	AX5043RXParamSetIFFrequency(RADIO_VHF, 0x0666);		//AFSK: 0x099A; ~37498Hz
	AX5043RXParamSetDecimation(RADIO_VHF, 0x05);		//AFSK: 0x04; ~250kHz
	AX5043RXParamSetRXDatarate(RADIO_VHF, 0x00A6AA);	//AFSK: 0x0682AB; ~1200 bits/s
	AX5043RXParamSetRXMaximumDatarateOffset(RADIO_VHF, 0x00);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_VHF, 0x0831);	//0x28F6: Set to 10kHz
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_VHF, 1);
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x25);	//Set RX AFSK Space freq. of 2200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x14);		//Set RX AFSK Mark freq. of 1200 Hz
	AX5043RXParamSetAFSKDetBandwitdh(RADIO_VHF, 0x0E);
	AX5043RXParamSetRXFSKMaxDeviation(RADIO_VHF, 0x0395);		//AFSK: 0x43C0
	AX5043RXParamSetRXFSKMinDeviation(RADIO_VHF, 0xFC6B);		//AFSK: 0xDC40
	AX5043RXParamSetRXParameterNumber0(RADIO_VHF, 0);
	AX5043RXParamSetRXParameterNumber1(RADIO_VHF, 1);
	AX5043RXParamSetRXParameterNumber2(RADIO_VHF, 3);
	AX5043RXParamSetRXParameterNumber3(RADIO_VHF, 3);
	//RX Parameter 0
	AX5043RXParamSetAGCReleaseSpeed0(RADIO_VHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed0(RADIO_VHF, 0x08);
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_VHF, 0x80);
	AX5043RXParamSetAGCTargetHysteresis0(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset0(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset0(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery0(RADIO_VHF, 0x0A, 0x0A);		//AFSK: 0x0D, 0x0E; FSK-9600: 0x0A, 0x0A
	AX5043PacketSetGainDatarateRecovery0(RADIO_VHF, 0x0A, 0x04);	//AFSK: 0x0D, 0x08; FSK-9600: 0x0A, 0x04
	AX5043RXParamSetRXPhaseGain0(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter0(RADIO_VHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA0(RADIO_VHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB0(RADIO_VHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC0(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD0(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain0(RADIO_VHF, 0x06);
	AX5043RXParamSetRXAmplitudeAGCJump0(RADIO_VHF, 0x00);
	AX5043RXParamSetRXFrequencyDeviation0(RADIO_VHF, 0x00);
	AX5043RXParamSetDeviationDecay0(RADIO_VHF, 0x06);
	AX5043RXParamEnableDeviationUpdate0(RADIO_VHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(RADIO_VHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(RADIO_VHF, 0x00);
	//RX Parameter 1
	AX5043RXParamSetAGCReleaseSpeed1(RADIO_VHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed1(RADIO_VHF, 0x08);
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_VHF, 0x80);
	AX5043RXParamSetAGCTargetHysteresis1(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset1(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset1(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery1(RADIO_VHF, 0x0A, 0x08);		//AFSK: 0x0D, 0x0C; FSK-9600: 0x0A, 0x08
	AX5043PacketSetGainDatarateRecovery1(RADIO_VHF, 0x0A, 0x03);	//AFSK: 0x0D, 0x07; FSK-9600: 0x0A, 0x03
	AX5043RXParamSetRXPhaseGain1(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter1(RADIO_VHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA1(RADIO_VHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB1(RADIO_VHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC1(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD1(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain1(RADIO_VHF, 0x06);
	AX5043RXParamSetRXAmplitudeAGCJump1(RADIO_VHF, 0x00);
	AX5043RXParamSetRXFrequencyDeviation1(RADIO_VHF, 0x002D);	//AFSK: 0x01C0
	AX5043RXParamSetDeviationDecay1(RADIO_VHF, 0x06);
	AX5043RXParamEnableDeviationUpdate1(RADIO_VHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_VHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_VHF, 0x00);
	//RX Parameter 3
	AX5043RXParamSetAGCReleaseSpeed3(RADIO_VHF, 0x0F);
	AX5043RXParamSetAGCAttackSpeed3(RADIO_VHF, 0x0F);
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_VHF, 0x80);
	AX5043RXParamSetAGCTargetHysteresis3(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset3(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset3(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery3(RADIO_VHF, 0x0A, 0x07);		//AFSK: 0x0D, 0x0B; FSK-9600: 0x0A, 0x07
	AX5043PacketSetGainDatarateRecovery3(RADIO_VHF, 0x0A, 0x02);	//AFSK: 0x0D, 0x06; FSK-9600: 0x0A, 0x02
	AX5043RXParamSetRXPhaseGain3(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter3(RADIO_VHF, 0x01);
	AX5043RXParamSetRXFrequencyGainA3(RADIO_VHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB3(RADIO_VHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC3(RADIO_VHF, 0x0D);
	AX5043RXParamSetRXFrequencyGainD3(RADIO_VHF, 0x0D);
	AX5043RXParamSetRXAmplitudeGain3(RADIO_VHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation3(RADIO_VHF, 0x002D);	//AFSK: 0x01C0
	AX5043RXParamSetDeviationDecay3(RADIO_VHF, 0x06);
	AX5043RXParamEnableDeviationUpdate3(RADIO_VHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(RADIO_VHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(RADIO_VHF, 0x00);

	//Set Packet, encoding and framing
	AX5043PacketSetMSBFirst(RADIO_VHF, 0);
	AX5043PacketEnableEncodeBitInversion(RADIO_VHF, 1);
	AX5043PacketEnableEncodeDifferential(RADIO_VHF, 1);
	AX5043PacketEnableEncodeScramble(RADIO_VHF, 1);
	AX5043PacketSetFrameMode(RADIO_VHF, FrmMode_HDLC);
	AX5043PacketSetCRCMode(RADIO_VHF, CRCMode_CCITT);
	AX5043PacketSetPacketChunkSize(RADIO_VHF, PacketChunkSize_240byte);
	AX5043PacketSetLengthByteSignificantBits(RADIO_VHF, 0x0F);	//Enable arbitrary packet length
	AX5043PacketSetMaxLength(RADIO_VHF, 0xFF);
	AX5043PacketSetAcceptPacketsMultiChuck(RADIO_VHF, 1);
	AX5043PacketSetAcceptPacketsCRCFailed(RADIO_VHF, 1);

	//Set Pattern Matching
	AX5043PacketSetPaternMatch0(RADIO_VHF, 0xAACCAACC);
	AX5043PacketSetPaternLength0(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch0Raw(RADIO_VHF, 0);
	AX5043PacketSetPaternMatch0Min(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_VHF, 0x1F);

	AX5043PacketSetPaternMatch1(RADIO_VHF, 0x5555);
	AX5043PacketSetPaternLength1(RADIO_VHF, 0x0A);
	AX5043PacketSetPaternMatch1Raw(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch1Min(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch1Max(RADIO_VHF, 0x0A);

	//Set packet control
	AX5043PacketSetTXPLLBoostTime(RADIO_VHF, 0x02, 0x03);
	AX5043PacketSetTXPLLSettlingTime(RADIO_VHF, 0x14, 0x00);
	AX5043PacketSetRXPLLBoostTime(RADIO_VHF, 0x02, 0x03);
	AX5043PacketSetRXPLLSettlingTime(RADIO_VHF, 0x14, 0x00);
	AX5043PacketSetRXDCOffsetAcquisitionTime(RADIO_VHF, 0x00, 0x00);
	AX5043PacketSetRXCoarseAGCTime(RADIO_VHF, 0x13, 0x03);
	AX5043PacketSetRXAGCSettlingTime(RADIO_VHF, 0x00, 0x00);
	AX5043PacketSetRXRSSISettlingTime(RADIO_VHF, 0x03, 0x00);
	AX5043PacketSetRXPreamble1Timeout(RADIO_VHF, 0x00, 0x00);
	AX5043PacketSetRXPreamble2Timeout(RADIO_VHF, 0x17, 0x00);
	AX5043PacketSetRXPreamble3Timeout(RADIO_VHF, 0x00, 0x00);
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

	//Set IRQ
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifothrcnt = 1;
	irqMask.irqmfifothrfree = 1;
	AX5043IrqSetIRQMask(RADIO_UHF, irqMask);

	//Set Events
	RadioEventMask radioEvenMask;
	radioEvenMask.raw = 0x00;
	radioEvenMask.revmdone = 1;
	AX5043IrqSetRadioEventMask(RADIO_UHF, radioEvenMask);

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
	data = 0x00;	//Set to 0x06 if "Raw, Soft Bits"
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
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_UHF, 0x8C);
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
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_UHF, 0x8C);
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
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_UHF, 0x8C);
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
	AX5043PacketSetFrameMode(RADIO_UHF, FrmMode_HDLC);
	AX5043PacketSetCRCMode(RADIO_UHF, CRCMode_CCITT);
	AX5043PacketSetPacketChunkSize(RADIO_UHF, PacketChunkSize_240byte);
	AX5043PacketSetLengthByteSignificantBits(RADIO_UHF, 0x0F);	//Enable arbitrary packet length
	AX5043PacketSetMaxLength(RADIO_UHF, 0xFF);
	AX5043PacketSetAcceptPacketsMultiChuck(RADIO_UHF, 1);
	AX5043PacketSetAcceptPacketsCRCFailed(RADIO_UHF, 1);

	//Set Pattern Matching
	AX5043PacketSetPaternLength0(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_UHF, 0x1F);
	AX5043PacketSetPaternMatch0(RADIO_UHF, 0xAACCAACC);

	AX5043PacketSetPaternMatch1Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch1Max(RADIO_UHF, 0x0A);
	AX5043PacketSetPaternLength1(RADIO_UHF, 0x0A);
	AX5043PacketSetPaternMatch1Raw(RADIO_UHF, 0x01);
	AX5043PacketSetPaternMatch1(RADIO_UHF, 0xAAAA);

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

uint8_t RadioVHFConfig(RadioConfigStruct configuration) {
	//Save configuration
	vhfRadioConfiguration = configuration;

	//Set Central Frequency
	if(vhfRadioConfiguration.frequency > RADIO_VHF_FREQ_MAX || vhfRadioConfiguration.frequency < RADIO_VHF_FREQ_MIN) {
		return 1;
	}
	uint32_t freq = (uint32_t)((vhfRadioConfiguration.frequency * (16777216.f / FXTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(RADIO_VHF, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_VHF);
	while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete

	//Set Modulation/Demodulation
	AX5043GeneralSetModulation(RADIO_VHF, vhfRadioConfiguration.modulation);

	//Set RX Bandwidth and IF Frequency
	uint32_t minBandwithAFC = vhfRadioConfiguration.afcRange * 4;
	uint32_t minBandwithDeviation = vhfRadioConfiguration.fskDeviation * 2;
	if(minBandwithAFC > minBandwithDeviation) {
		uint8_t decimation = (uint8_t)(FXTAL / ((float)(minBandwithAFC << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_VHF, decimation);
		uint16_t ifF = (uint16_t)(((minBandwithAFC >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_VHF, ifF);
	}
	else {
		uint8_t decimation = (uint8_t)(FXTAL / ((float)(minBandwithDeviation << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_VHF, decimation);
		uint16_t ifF = (uint16_t)(((minBandwithDeviation >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_VHF, ifF);
	}

	//Set RX AFC Range
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_VHF, 1);
	uint32_t afc = (uint32_t)((vhfRadioConfiguration.afcRange * (16777216.f / FXTAL)) + 0.5f);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_VHF, afc);

	//Set Datarates
	if(vhfRadioConfiguration.datarate > 250000 || vhfRadioConfiguration.datarate < 1000) {
		return 1;
	}
	uint8_t decimation = AX5043RXParamGetDecimation(RADIO_VHF);
	uint32_t dr = (FXTAL << 7) / (vhfRadioConfiguration.datarate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_VHF, dr);
	dr = (uint16_t)((vhfRadioConfiguration.datarate * (16777216.f / FXTAL)) + 0.5f);
	AX5043TXParamSetTXDatarate(RADIO_VHF, dr);

	//Set frequency deviation
	if(vhfRadioConfiguration.fskDeviation < (vhfRadioConfiguration.datarate >> 1)) {
		return 1;
	}
	if(vhfRadioConfiguration.modulation != AFSK) {
		uint16_t df = (uint16_t)(((vhfRadioConfiguration.fskDeviation >> 1) * (16777216.f / FXTAL)) + 0.5f);
		AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, df);
	}
	else {
		AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, 0x0A8E);	//Set FSK deviation to 3000 Hz

		//Save configuration for AFSK RX
		vhfRadioConfiguration.afskSpaceRX = (uint16_t)((2200 * decimation << 16) / (float)FXTAL + 0.5f);
		vhfRadioConfiguration.afskMarkRX = (uint16_t)((1200 * decimation << 16) / (float)FXTAL + 0.5f);
		uint16_t afskBW = (uint16_t)(2.f * log2f((float)FXTAL / (32 * vhfRadioConfiguration.datarate * decimation)) + 1.5f);

		//Save configuration for AFSK TX
		vhfRadioConfiguration.afskSpaceTX = (uint16_t)(2200 * (262144.f / FXTAL) + 0.5f);
		vhfRadioConfiguration.afskMarkTX = (uint16_t)(1200 * (262144.f / FXTAL) + 0.5f);

		AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, vhfRadioConfiguration.afskSpaceRX);		//Set RX AFSK Space freq. of 2200 Hz
		AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, vhfRadioConfiguration.afskMarkRX);			//Set RX AFSK Mark freq. of 1200 Hz
		AX5043RXParamSetAFSKDetBandwitdh(RADIO_VHF, afskBW);
	}

	return 0;
}

uint8_t RadioUHFConfig(RadioConfigStruct configuration) {
	//Save configuration
	uhfRadioConfiguration = configuration;

	//Set Central Frequency
	if(uhfRadioConfiguration.frequency > RADIO_UHF_FREQ_MAX || uhfRadioConfiguration.frequency < RADIO_UHF_FREQ_MIN) {
		return 1;
	}
	uint32_t freq = (uint32_t)((uhfRadioConfiguration.frequency * (16777216.f / FXTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(RADIO_UHF, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_UHF);
	while(AX5043SynthGetAutoRangingA(RADIO_UHF));	//Wait for Auto Ranging Complete

	//Set Modulation/Demodulation
	AX5043GeneralSetModulation(RADIO_UHF, uhfRadioConfiguration.modulation);

	//Set RX Bandwidth and IF Frequency
	uint32_t minBandwithAFC = uhfRadioConfiguration.afcRange * 4;
	uint32_t minBandwithDeviation = uhfRadioConfiguration.fskDeviation * 2;
	if(minBandwithAFC > minBandwithDeviation) {
		uint8_t decimation = (uint8_t)(FXTAL / ((float)(minBandwithAFC << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_UHF, decimation);
		uint16_t ifF = (uint16_t)(((minBandwithAFC >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
	}
	else {
		uint8_t decimation = (uint8_t)(FXTAL / ((float)(minBandwithDeviation << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_UHF, decimation);
		uint16_t ifF = (uint16_t)(((minBandwithDeviation >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
	}

	//Set RX AFC Range
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_UHF, 1);
	uint32_t afc = (uint32_t)((uhfRadioConfiguration.afcRange * (16777216.f / FXTAL)) + 0.5f);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_UHF, afc);

	//Set Datarates
	if(uhfRadioConfiguration.datarate > 250000 || uhfRadioConfiguration.datarate < 1000) {
		return 1;
	}
	uint8_t decimation = AX5043RXParamGetDecimation(RADIO_UHF);
	uint32_t dr = (FXTAL << 7) / (uhfRadioConfiguration.datarate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_UHF, dr);
	dr = (uint16_t)((uhfRadioConfiguration.datarate * (16777216.f / FXTAL)) + 0.5f);
	AX5043TXParamSetTXDatarate(RADIO_UHF, dr);

	//Set frequency deviation
	if(uhfRadioConfiguration.fskDeviation < (uhfRadioConfiguration.datarate >> 1)) {
		return 1;
	}
	if(uhfRadioConfiguration.modulation != AFSK) {
		uint16_t df = (uint16_t)(((uhfRadioConfiguration.fskDeviation >> 1) * (16777216.f / FXTAL)) + 0.5f);
		AX5043TXParamSetFSKFrequencyDeviation(RADIO_UHF, df);
	}
	else {
		AX5043TXParamSetFSKFrequencyDeviation(RADIO_UHF, 0x0A8E);	//Set FSK deviation to 3000 Hz

		//Save configuration for AFSK RX
		uhfRadioConfiguration.afskSpaceRX = (uint16_t)((2200 * decimation << 16) / (float)FXTAL + 0.5f);
		uhfRadioConfiguration.afskMarkRX = (uint16_t)((1200 * decimation << 16) / (float)FXTAL + 0.5f);
		uint16_t afskBW = (uint16_t)(2.f * log2f((float)FXTAL / (32 * uhfRadioConfiguration.datarate * decimation)) + 1.5f);

		//Save configuration for AFSK TX
		uhfRadioConfiguration.afskSpaceTX = (uint16_t)(2200 * (262144.f / FXTAL) + 0.5f);
		uhfRadioConfiguration.afskMarkTX = (uint16_t)(1200 * (262144.f / FXTAL) + 0.5f);

		AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, uhfRadioConfiguration.afskSpaceRX);		//Set RX AFSK Space freq. of 2200 Hz
		AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, uhfRadioConfiguration.afskMarkRX);			//Set RX AFSK Mark freq. of 1200 Hz
		AX5043RXParamSetAFSKDetBandwitdh(RADIO_UHF, afskBW);
	}

	return 0;
}

void RadioVHFEnterTX() {
	//Set Radio Up for TX
	if(vhfRadioConfiguration.modulation == AFSK) {
		AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, vhfRadioConfiguration.afskSpaceTX);
		AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, vhfRadioConfiguration.afskMarkTX);
	}

	PwrStatus status = AX5043PwrStats(RADIO_VHF);
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_VHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_VHF);
	}
}

void RadioUHFEnterTX() {
	//Set Radio Up for TX
	if(vhfRadioConfiguration.modulation == AFSK) {
		AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, uhfRadioConfiguration.afskSpaceTX);
		AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, uhfRadioConfiguration.afskMarkTX);
	}

	PwrStatus status = AX5043PwrStats(RADIO_UHF);
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_UHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_UHF);
	}
}

void RadioUHFEnterRX() {
	//Set Radio Up for RX
	if(vhfRadioConfiguration.modulation == AFSK) {
		AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, uhfRadioConfiguration.afskSpaceRX);
		AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, uhfRadioConfiguration.afskMarkRX);
	}

	PwrStatus status = AX5043PwrStats(RADIO_UHF);
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_RXEN);
	status = AX5043PwrStats(RADIO_UHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_UHF);
	}
}

void RadioVHFWritePreamble(uint8_t symbol, uint8_t length) {
	uint8_t fifoData[4];
	fifoData[0] = 0x62;
	fifoData[1] = 0x18;
	fifoData[2] = length;
	fifoData[3] = symbol;

	AX5043FIFOSetFIFO(RADIO_VHF, fifoData, 4);
}

void RadioUHFWritePreamble(uint8_t symbol, uint8_t length) {
	uint8_t fifoData[4];
	fifoData[0] = 0x62;
	fifoData[1] = 0x18;
	fifoData[2] = length;
	fifoData[3] = symbol;

	AX5043FIFOSetFIFO(RADIO_UHF, fifoData, 4);
}

void RadioVHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength; //FIFO Data Length
	fifoData[i++] = 0x03;		//Set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_VHF, fifoData, i);
}

void RadioUHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength + 1;	//FIFO Data Length + 1 (info/flag byte, the next byte)
	fifoData[i++] = 0x03;		//Set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_UHF, fifoData, i);
}
