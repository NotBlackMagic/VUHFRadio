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
	AX5043GPIOCnfgDATA(RADIO_VHF, DATA_Modem_Data_Output, 0, 0);			//DATA_IO_Modem_Data
	AX5043GPIOCnfgIRQ(RADIO_VHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_VHF, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(RADIO_VHF, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(RADIO_VHF, DACInput_RSSI);
	AX5043GPIOSetDACInputShift(RADIO_VHF, 0x0C);
	AX5043GPIOSetDACOutputMode(RADIO_VHF, 0x00);
	AX5043GPIOSetDACClockDoubling(RADIO_VHF, 0x01);

	//Set IRQ
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifonotempty = 1;
	AX5043IrqSetIRQMask(RADIO_VHF, irqMask);

	//Set Events
	RadioEventMask radioEvenMask;
	radioEvenMask.raw = 0x00;
//	radioEvenMask.revmdone = 1;
	AX5043IrqSetRadioEventMask(RADIO_VHF, radioEvenMask);

	//Calibrate RSSI: Compensate for Board effects
	AX5043PacketSetRSSIOffset(RADIO_VHF, 0xF5);		//Offset: -11dBm

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
	data = 0x08;	//Set to 0x28 if RFDIV is set, 0x08 otherwise
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
//	AX5043SynthSetPLLLoopFilter(RADIO_VHF, PLLLoop_Filter100kHz);
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
	AX5043TXParamSetTXDatarate(RADIO_VHF, 0x2752);				//AFSK: 0x04EB; Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, 0x09D5);	//AFSK: 0x0A8E; Set FSK deviation to 3000 Hz

//	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x13);		//Set TX AFSK Space freq. of 2200 Hz
//	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x0A);			//Set TX AFSK Mark freq. of 1200 Hz

	//Set TX Power, Pout = TXPWRCOEFFB / (2^12 - 1) * Pmax; Pmax = 16 dBm
	uint8_t txPower = 16;
	uint16_t powerCoef = (txPower * 4095) >> 4;
	AX5043TXParamSetTXPredistortionCoeffB(RADIO_VHF, powerCoef);	//With no predistortion (default) this sets the output power

	//Set Demodulation for RX Mode
//	RadioUHFSetIF(20000);
//	RadioUHFSetBandwidth(125000);
//	RadioUHFSetRXBitrate(1200);

	AX5043RXParamSetIFFrequency(RADIO_VHF, 0x0276);		//AFSK: 0x099A -> ~37498Hz; FSK-9600: 0x0276 -> ~9600Hz
	AX5043RXParamSetDecimation(RADIO_VHF, 0x04);		//AFSK: 0x04 -> ~250kHz; FSK-9600: 0x05; Needs to be > 2 * Signal Bandwidth
	AX5043RXParamSetRXDatarate(RADIO_VHF, 0x099A);		//AFSK: 0x0682AB -> ~1200 bits/s; FSK-9600: 0xA6AA
	AX5043RXParamSetRXMaximumDatarateOffset(RADIO_VHF, 0x00);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_VHF, 0xCCCC);	//0x28F6: Set to 10kHz; FSK-9600: 0x0831
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_VHF, 1);
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x25);	//Set RX AFSK Space freq. of 2200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x14);		//Set RX AFSK Mark freq. of 1200 Hz
	AX5043RXParamSetAFSKDetBandwitdh(RADIO_VHF, 0x0E);
	AX5043RXParamSetRXFSKMaxDeviation(RADIO_VHF, 0x43C0);		//AFSK: 0x43C0; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXFSKMinDeviation(RADIO_VHF, 0xDC40);		//AFSK: 0xDC40; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXParameterNumber0(RADIO_VHF, 0);
	AX5043RXParamSetRXParameterNumber1(RADIO_VHF, 0);		//1
	AX5043RXParamSetRXParameterNumber2(RADIO_VHF, 0);		//3
	AX5043RXParamSetRXParameterNumber3(RADIO_VHF, 0);		//3
	//RX Parameter 0
	AX5043RXParamSetAGCReleaseSpeed0(RADIO_VHF, 0x0E);				//Original: 0x0E; Calculated FSK-9600: 0x07
	AX5043RXParamSetAGCAttackSpeed0(RADIO_VHF, 0x08);				//Original: 0x08; Calculated FSK-9600: 0x04
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
	AX5043RXParamSetAGCTargetHysteresis0(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset0(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset0(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery0(RADIO_VHF, 0x0D, 0x0E);		//AFSK: 0x0D, 0x0E; FSK-9600: 0x0A, 0x0A
	AX5043PacketSetGainDatarateRecovery0(RADIO_VHF, 0x0D, 0x08);	//AFSK: 0x0D, 0x08; FSK-9600: 0x0A, 0x04
	AX5043RXParamSetRXPhaseGain0(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter0(RADIO_VHF, 0x03);
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
	AX5043RXParamSetAGCReleaseSpeed1(RADIO_VHF, 0x07);				//Original: 0x0E; Calculated FSK-9600: 0x07
	AX5043RXParamSetAGCAttackSpeed1(RADIO_VHF, 0x04);				//Original: 0x08; Calculated FSK-9600: 0x04
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
	AX5043RXParamSetAGCTargetHysteresis1(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset1(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset1(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery1(RADIO_VHF, 0x0A, 0x0A);		//AFSK: 0x0D, 0x0C; FSK-9600: 0x0A, 0x08
	AX5043PacketSetGainDatarateRecovery1(RADIO_VHF, 0x0A, 0x06);	//AFSK: 0x0D, 0x07; FSK-9600: 0x0A, 0x03
	AX5043RXParamSetRXPhaseGain1(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter1(RADIO_VHF, 0x03);
	AX5043RXParamSetRXFrequencyGainA1(RADIO_VHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB1(RADIO_VHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC1(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD1(RADIO_VHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain1(RADIO_VHF, 0x06);
	AX5043RXParamSetRXAmplitudeAGCJump1(RADIO_VHF, 0x00);
	AX5043RXParamSetRXFrequencyDeviation1(RADIO_VHF, 0x00);			//AFSK: 0x01C0; FSK-9600: 0x002D; Not needed, maybe improves performance?
	AX5043RXParamSetDeviationDecay1(RADIO_VHF, 0x06);
	AX5043RXParamEnableDeviationUpdate1(RADIO_VHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_VHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_VHF, 0x00);
	//RX Parameter 3
	AX5043RXParamSetAGCReleaseSpeed3(RADIO_VHF, 0x0F);
	AX5043RXParamSetAGCAttackSpeed3(RADIO_VHF, 0x0F);
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
	AX5043RXParamSetAGCTargetHysteresis3(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMaximumReset3(RADIO_VHF, 0x00);
	AX5043RXParamSetAGCMinimumReset3(RADIO_VHF, 0x00);
	AX5043PacketSetGainTimingRecovery3(RADIO_VHF, 0x0A, 0x0A);		//AFSK: 0x0D, 0x0B; FSK-9600: 0x0A, 0x07
	AX5043PacketSetGainDatarateRecovery3(RADIO_VHF, 0x0A, 0x06);	//AFSK: 0x0D, 0x06; FSK-9600: 0x0A, 0x02
	AX5043RXParamSetRXPhaseGain3(RADIO_VHF, 0x03);
	AX5043RXParamSetRXDecimationFilter3(RADIO_VHF, 0x03);
	AX5043RXParamSetRXFrequencyGainA3(RADIO_VHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB3(RADIO_VHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC3(RADIO_VHF, 0x0D);
	AX5043RXParamSetRXFrequencyGainD3(RADIO_VHF, 0x0D);
	AX5043RXParamSetRXAmplitudeGain3(RADIO_VHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation3(RADIO_VHF, 0x00);			//AFSK: 0x01C0; FSK-9600: 0x002D; Not needed, maybe improves performance?
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

	//Append RX tracking data in FIFO
//	AX5043PacketEnableStoreRFFrequencyValue(RADIO_VHF, 0x01);	//Append/save RF frequency offset
//	AX5043PacketEnableStoreDatarateValue(RADIO_VHF, 0x01);		//Append/save RX datarate
	AX5043PacketEnableStoreRSSI(RADIO_VHF, 0x01);				//Append/save RSSI value

	//Set Pattern Matching
	AX5043PacketSetPaternMatch0(RADIO_VHF, 0x7E7E7E7E);
	AX5043PacketSetPaternLength0(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch0Raw(RADIO_VHF, 0);
	AX5043PacketSetPaternMatch0Min(RADIO_VHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_VHF, 0x1F);

	AX5043PacketSetPaternMatch1(RADIO_VHF, 0x7E7E);
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
	AX5043PacketSetRXCoarseAGCTime(RADIO_VHF, 0x13, 0x03);				//19*2^3 us = 152 us
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
	AX5043GPIOCnfgDATA(RADIO_UHF, DATA_Modem_Data_Output, 0, 0);			//DATA_IO_Modem_Data
	AX5043GPIOCnfgIRQ(RADIO_UHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_UHF, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(RADIO_UHF, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(RADIO_UHF, DACInput_TRKAmplitude);
	AX5043GPIOSetDACInputShift(RADIO_UHF, 0x0C);
	AX5043GPIOSetDACOutputMode(RADIO_UHF, 0x00);
	AX5043GPIOSetDACClockDoubling(RADIO_UHF, 0x01);

	//Set IRQ
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifonotempty = 1;
	AX5043IrqSetIRQMask(RADIO_UHF, irqMask);

	//Set Events
	RadioEventMask radioEvenMask;
	radioEvenMask.raw = 0x00;
//	radioEvenMask.revmdone = 1;
	AX5043IrqSetRadioEventMask(RADIO_UHF, radioEvenMask);

	//Calibrate RSSI: Compensate for Board effects
	AX5043PacketSetRSSIOffset(RADIO_UHF, 0xF5);		//Offset: -11dBm

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
	data = 0x28;	//Set to 0x28 if RFDIV is set, 0x08 otherwise
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
	AX5043SynthSetFrequencyA(RADIO_UHF, 0x1B473334);	//For 436.45MHz is 0x1B473334 calculated but calibrated value is 0x1B474335
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
	AX5043GeneralSetModulation(RADIO_UHF, FSK);					//AFSK
	AX5043TXParamSetTXDatarate(RADIO_UHF, 0x04EB);				//Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_UHF, 0x0A8E);	//Set FSK deviation to 3000 Hz

//	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x13);		//Set TX AFSK Space freq. of 2200 Hz
//	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x0A);			//Set TX AFSK Mark freq. of 1200 Hz

	//Set TX Power, Pout = TXPWRCOEFFB / (2^12 - 1) * Pmax; Pmax = 16 dBm
	uint8_t txPower = 16;
	uint16_t powerCoef = ((uint32_t)txPower * 4095) >> 4;
	AX5043TXParamSetTXPredistortionCoeffB(RADIO_UHF, powerCoef);	//With no predistortion (default) this sets the output power

	//Set Demodulation for RX Mode
//	RadioUHFSetIF(20000);
//	RadioUHFSetBandwidth(125000);
//	RadioUHFSetRXBitrate(1200);

	AX5043RXParamSetIFFrequency(RADIO_UHF, 0x0667);		//~25kHz
	AX5043RXParamSetDecimation(RADIO_UHF, 0x14);		//~50kHz (0x32)

	AX5043RXParamSetRXDatarate(RADIO_UHF, 0x0200);		//~200000 bits/s (0xCD)
	AX5043RXParamSetRXMaximumDatarateOffset(RADIO_UHF, 0x00);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_UHF, 0x00);	//Set to 10kHz (0x28F6)
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_UHF, 1);
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x25);	//Set RX AFSK Space freq. of 2200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x14);		//Set RX AFSK Mark freq. of 1200 Hz
	AX5043RXParamSetAFSKDetBandwitdh(RADIO_UHF, 0x0E);
	AX5043RXParamSetRXFSKMaxDeviation(RADIO_UHF, 0x43C0);	//AFSK: 0x43C0; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXFSKMinDeviation(RADIO_UHF, 0xDC40);	//AFSK: 0x43C0; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXParameterNumber0(RADIO_UHF, 0);
	AX5043RXParamSetRXParameterNumber1(RADIO_UHF, 0);
	AX5043RXParamSetRXParameterNumber2(RADIO_UHF, 0);
	AX5043RXParamSetRXParameterNumber3(RADIO_UHF, 0);
	//RX Parameter 0
	AX5043RXParamSetAGCReleaseSpeed0(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed0(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_UHF, 0x79);	//Target: 192
	AX5043RXParamSetAGCTargetHysteresis0(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset0(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset0(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery0(RADIO_UHF, 0x0D, 0x0E);
	AX5043PacketSetGainDatarateRecovery0(RADIO_UHF, 0x0D, 0x08);
	AX5043RXParamSetRXPhaseGain0(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter0(RADIO_UHF, 0x03);
	AX5043RXParamSetRXFrequencyGainA0(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB0(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC0(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD0(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain0(RADIO_UHF, 0x04);
	AX5043RXParamSetRXAmplitudeAGCJump0(RADIO_UHF, 0x00);
	AX5043RXParamSetRXAmplitudeRecoveryByAverage0(RADIO_UHF, 0x00);
	AX5043RXParamSetRXFrequencyDeviation0(RADIO_UHF, 0x00);
	AX5043RXParamSetDeviationDecay0(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate0(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(RADIO_UHF, 0x00);
	//RX Parameter 1
	AX5043RXParamSetAGCReleaseSpeed1(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCAttackSpeed1(RADIO_UHF, 0x08);
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_UHF, 0x89);
	AX5043RXParamSetAGCTargetHysteresis1(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset1(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset1(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery1(RADIO_UHF, 0x0D, 0x0C);
	AX5043PacketSetGainDatarateRecovery1(RADIO_UHF, 0x0D, 0x07);
	AX5043RXParamSetRXPhaseGain1(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter1(RADIO_UHF, 0x03);
	AX5043RXParamSetRXFrequencyGainA1(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB1(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC1(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXFrequencyGainD1(RADIO_UHF, 0x0A);
	AX5043RXParamSetRXAmplitudeGain1(RADIO_UHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation1(RADIO_UHF, 0x00);
	AX5043RXParamSetDeviationDecay1(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate1(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_UHF, 0x00);
	//RX Parameter 3
	AX5043RXParamSetAGCReleaseSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCAttackSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_UHF, 0x89);
	AX5043RXParamSetAGCTargetHysteresis3(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMaximumReset3(RADIO_UHF, 0x00);
	AX5043RXParamSetAGCMinimumReset3(RADIO_UHF, 0x00);
	AX5043PacketSetGainTimingRecovery3(RADIO_UHF, 0x0D, 0x0B);
	AX5043PacketSetGainDatarateRecovery3(RADIO_UHF, 0x0D, 0x06);
	AX5043RXParamSetRXPhaseGain3(RADIO_UHF, 0x03);
	AX5043RXParamSetRXDecimationFilter3(RADIO_UHF, 0x03);
	AX5043RXParamSetRXFrequencyGainA3(RADIO_UHF, 0x0F);
	AX5043RXParamSetRXFrequencyGainB3(RADIO_UHF, 0x1F);
	AX5043RXParamSetRXFrequencyGainC3(RADIO_UHF, 0x0D);
	AX5043RXParamSetRXFrequencyGainD3(RADIO_UHF, 0x0D);
	AX5043RXParamSetRXAmplitudeGain3(RADIO_UHF, 0x06);
	AX5043RXParamSetRXFrequencyDeviation3(RADIO_UHF, 0x00);
	AX5043RXParamSetDeviationDecay3(RADIO_UHF, 0x06);
	AX5043RXParamEnableDeviationUpdate3(RADIO_UHF, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(RADIO_UHF, 0x00);

	//Set Packet, encoding and framing
	AX5043PacketSetMSBFirst(RADIO_UHF, 0);
	AX5043PacketEnableEncodeBitInversion(RADIO_UHF, 1);
	AX5043PacketEnableEncodeDifferential(RADIO_UHF, 1);
	AX5043PacketEnableEncodeScramble(RADIO_UHF, 1);
	AX5043PacketSetFrameMode(RADIO_UHF, FrmMode_HDLC);
	AX5043PacketSetCRCMode(RADIO_UHF, CRCMode_CCITT);
	AX5043PacketSetPacketChunkSize(RADIO_UHF, PacketChunkSize_240byte);
	AX5043PacketSetLengthByteSignificantBits(RADIO_UHF, 0x0F);	//Enable arbitrary packet length
	AX5043PacketSetMaxLength(RADIO_UHF, 0xFF);
	AX5043PacketSetAcceptPacketsMultiChuck(RADIO_UHF, 1);
	AX5043PacketSetAcceptPacketsCRCFailed(RADIO_UHF, 1);

	//Append RX tracking data in FIFO
//	AX5043PacketEnableStoreRFFrequencyValue(RADIO_UHF, 0x01);	//Append/save RF frequency offset
//	AX5043PacketEnableStoreDatarateValue(RADIO_UHF, 0x01);		//Append/save RX datarate
	AX5043PacketEnableStoreRSSI(RADIO_UHF, 0x01);				//Append/save RSSI value

	//Set Pattern Matching
	AX5043PacketSetPaternMatch0(RADIO_UHF, 0x7E7E7E7E);
	AX5043PacketSetPaternLength0(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Raw(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch0Max(RADIO_UHF, 0x1F);

	AX5043PacketSetPaternMatch1(RADIO_UHF, 0x7E7E);
	AX5043PacketSetPaternLength1(RADIO_UHF, 0x0A);
	AX5043PacketSetPaternMatch1Raw(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch1Min(RADIO_UHF, 0x00);
	AX5043PacketSetPaternMatch1Max(RADIO_UHF, 0x0A);

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

//This Table is used to get the correct AGC Attack and Release speed based on the F3dB point for each possibility. Values calculated from datasheet formula
const uint32_t agcAttackRealeaseTable[16] = {79577, 59683, 34815, 18651, 9636, 4896, 2467, 1239, 620, 311, 155, 78, 39, 19, 10 ,5};
uint8_t RadioVHFModConfig(RadioConfigStruct configuration) {
	//Save configuration
	vhfRadioConfiguration = configuration;

	//Check if configurations are valid or not
	if(vhfRadioConfiguration.frequency > RADIO_VHF_FREQ_MAX || vhfRadioConfiguration.frequency < RADIO_VHF_FREQ_MIN) {
		return 1;
	}
	if(vhfRadioConfiguration.datarate > 250000 || vhfRadioConfiguration.datarate < 1000) {
		return 1;
	}
	if(vhfRadioConfiguration.modulation == FSK || vhfRadioConfiguration.modulation == MSK) {
		if(vhfRadioConfiguration.fskDeviation < (vhfRadioConfiguration.datarate >> 1)) {
			return 1;
		}
	}

	//Set Central Frequency
	uint32_t freq = (uint32_t)((vhfRadioConfiguration.frequency * (16777216.f / FXTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(RADIO_VHF, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_VHF);
	while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete

	//Set Modulation/Demodulation
	AX5043GeneralSetModulation(RADIO_VHF, vhfRadioConfiguration.modulation);

	//Set RX Bandwidth and IF Frequency
	uint32_t afcRXBW = vhfRadioConfiguration.afcRange * 4;
	uint32_t modulationRXBW = 0;
	if(vhfRadioConfiguration.modulation == FSK || vhfRadioConfiguration.modulation == MSK) {
		//FSK BW = (1 + h) * Bitrate; h -> Modulation index, for MSK is 0.5; FSK Deviation is h * Bitrate
		modulationRXBW = vhfRadioConfiguration.fskDeviation + vhfRadioConfiguration.datarate;
	}
	else if(vhfRadioConfiguration.modulation == AFSK) {
		//AFSK BW ~ (1 + 2*h) * Bitrate; But by testing needs BW ~ 5 * h * Bitrate aka 5 * FSK Deviation
		modulationRXBW = (5 * vhfRadioConfiguration.fskDeviation);
	}
	else if(vhfRadioConfiguration.modulation == PSK) {
		//PSK BW = Bitrate
		modulationRXBW = vhfRadioConfiguration.datarate;
	}
	else if(vhfRadioConfiguration.modulation == OQPSK) {
		//OQPSK BW = 2 * Bitrate
		modulationRXBW = 2 * vhfRadioConfiguration.datarate;
	}
	else if(vhfRadioConfiguration.modulation == ASK || vhfRadioConfiguration.modulation == ASK_Coherent) {
		//ASK BW = Bitrate
		modulationRXBW = vhfRadioConfiguration.datarate;
	}
	else if(vhfRadioConfiguration.modulation == FSK4) {
		//4-FSK BW = (1 + 3h) * Bitrate
		modulationRXBW = (3 * vhfRadioConfiguration.fskDeviation) + vhfRadioConfiguration.datarate;
	}

	//To set the RX BW (decimation) check what is the limiting factor, the modulation BW (modulationRXBW) or the AFC needed BW (needs min 4x the AFC Range)
	uint8_t decimation = 0;
	if(afcRXBW > modulationRXBW) {
		decimation = (uint8_t)(FXTAL / ((float)(afcRXBW << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_VHF, decimation);
		uint16_t ifF = (uint16_t)(((afcRXBW >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_VHF, ifF);
	}
	else {
		decimation = (uint8_t)(FXTAL / ((float)(modulationRXBW << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_VHF, decimation);
		uint16_t ifF = (uint16_t)(((modulationRXBW >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_VHF, ifF);
	}

	//Set RX AFC Range
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_VHF, 1);
	uint32_t afc = (uint32_t)((vhfRadioConfiguration.afcRange * (16777216.f / FXTAL)) + 0.5f);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_VHF, afc);

	//Set Datarates
	uint32_t rxDr = (FXTAL << 7) / (vhfRadioConfiguration.datarate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_VHF, rxDr);
	uint32_t txDr = (uint16_t)((vhfRadioConfiguration.datarate * (16777216.f / FXTAL)) + 0.5f);
	AX5043TXParamSetTXDatarate(RADIO_VHF, txDr);

	//Adjust RX Parameters that depend on datarate, AGC Attack and Settling as well as timing and datarate recovery
	uint8_t i = 0;
	for(i = 0; i < 15; i++) {
		//Attack f3dB should be ~Bitrate (Except for ASK)
		if(abs(agcAttackRealeaseTable[i] - configuration.datarate) < abs(agcAttackRealeaseTable[i+1] - configuration.datarate)) {
			AX5043RXParamSetAGCAttackSpeed0(RADIO_VHF, i);		//Original: 0x08; Calculated FSK-9600: 0x04
			AX5043RXParamSetAGCAttackSpeed1(RADIO_VHF, i);
			break;
		}
		else if(i == 15){
			AX5043RXParamSetAGCAttackSpeed0(RADIO_VHF, i+1);
			AX5043RXParamSetAGCAttackSpeed1(RADIO_VHF, i+1);
			break;
		}
	}

	for(i = 0; i < 15; i++) {
		//Release f3dB should be ~Bitrate/10 (Except for ASK)
		if(abs(agcAttackRealeaseTable[i] - (configuration.datarate / 10)) < abs(agcAttackRealeaseTable[i+1] - (configuration.datarate / 10))) {
			AX5043RXParamSetAGCReleaseSpeed0(RADIO_VHF, i);
			AX5043RXParamSetAGCReleaseSpeed1(RADIO_VHF, i);
			break;
		}
		else if(i == 15){
			AX5043RXParamSetAGCReleaseSpeed0(RADIO_VHF, i+1);
			AX5043RXParamSetAGCReleaseSpeed1(RADIO_VHF, i+1);
			break;
		}
	}

	uint8_t exp = floorf(log2f(((float)rxDr / 4.f) / 8.f));
	uint8_t man = roundf(((float)rxDr / 4.f) / (1 << exp));
	AX5043PacketSetGainTimingRecovery0(RADIO_VHF, man, exp);
	AX5043PacketSetGainTimingRecovery1(RADIO_VHF, man, exp);
	AX5043PacketSetGainTimingRecovery3(RADIO_VHF, man, exp);

	exp = floorf(log2f(((float)rxDr / 64.f) / 8.f));
	man = roundf(((float)rxDr / 64.f) / (1 << exp));
	AX5043PacketSetGainDatarateRecovery0(RADIO_VHF, man, exp);
	AX5043PacketSetGainDatarateRecovery1(RADIO_VHF, man, exp);
	AX5043PacketSetGainDatarateRecovery3(RADIO_VHF, man, exp);

	//Set frequency deviation
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

RadioConfigStruct RadioVHFGetModConfig() {
	return vhfRadioConfiguration;
}

uint8_t RadioUHFModConfig(RadioConfigStruct configuration) {
	//Save configuration
	uhfRadioConfiguration = configuration;

	//Check if configurations are valid or not
	if(uhfRadioConfiguration.frequency > RADIO_UHF_FREQ_MAX || uhfRadioConfiguration.frequency < RADIO_UHF_FREQ_MIN) {
		return 1;
	}
	if(uhfRadioConfiguration.datarate > 250000 || uhfRadioConfiguration.datarate < 1000) {
		return 1;
	}
	if(uhfRadioConfiguration.modulation == FSK || uhfRadioConfiguration.modulation == MSK) {
		if(uhfRadioConfiguration.fskDeviation < (uhfRadioConfiguration.datarate >> 1)) {
			return 1;
		}
	}

	//Set Central Frequency
	uint32_t freq = (uint32_t)((uhfRadioConfiguration.frequency * (16777216.f / FXTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(RADIO_UHF, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_UHF);
	while(AX5043SynthGetAutoRangingA(RADIO_UHF));	//Wait for Auto Ranging Complete

	//Set Modulation/Demodulation
	AX5043GeneralSetModulation(RADIO_UHF, uhfRadioConfiguration.modulation);

	//Set RX Bandwidth and IF Frequency
	uint32_t afcRXBW = uhfRadioConfiguration.afcRange * 4;
	uint32_t modulationRXBW = 0;
	if(uhfRadioConfiguration.modulation == FSK || uhfRadioConfiguration.modulation == MSK) {
		//FSK BW = (1 + h) * Bitrate; h -> Modulation index, for MSK is 0.5; FSK Deviation is h * Bitrate
		modulationRXBW = uhfRadioConfiguration.fskDeviation + uhfRadioConfiguration.datarate;
	}
	else if(uhfRadioConfiguration.modulation == AFSK) {
		//AFSK BW ~ (1 + 2*h) * Bitrate; But by testing needs BW ~ 5 * h * Bitrate aka 5 * FSK Deviation
		modulationRXBW = (5 * uhfRadioConfiguration.fskDeviation);
	}
	else if(uhfRadioConfiguration.modulation == PSK) {
		//PSK BW = Bitrate
		modulationRXBW = uhfRadioConfiguration.datarate;
	}
	else if(uhfRadioConfiguration.modulation == OQPSK) {
		//OQPSK BW = 2 * Bitrate
		modulationRXBW = 2 * uhfRadioConfiguration.datarate;
	}
	else if(uhfRadioConfiguration.modulation == ASK || uhfRadioConfiguration.modulation == ASK_Coherent) {
		//ASK BW = Bitrate
		modulationRXBW = uhfRadioConfiguration.datarate;
	}
	else if(uhfRadioConfiguration.modulation == FSK4) {
		//4-FSK BW = (1 + 3h) * Bitrate
		modulationRXBW = (3 * uhfRadioConfiguration.fskDeviation) + uhfRadioConfiguration.datarate;
	}

	//To set the RX BW (decimation) check what is the limiting factor, the modulation BW (modulationRXBW) or the AFC needed BW (needs min 4x the AFC Range)
	uint8_t decimation = 0;
	if(afcRXBW > modulationRXBW) {
		decimation = (uint8_t)(FXTAL / ((float)(afcRXBW << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_UHF, decimation);
		uint16_t ifF = (uint16_t)(((afcRXBW >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
	}
	else {
		decimation = (uint8_t)(FXTAL / ((float)(modulationRXBW << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
		AX5043RXParamSetDecimation(RADIO_UHF, decimation);
		uint16_t ifF = (uint16_t)(((modulationRXBW >> 1)) * (1048576.f / FXTAL) + 0.5f);
		AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
	}

	//Set RX AFC Range
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_UHF, 1);
	uint32_t afc = (uint32_t)((uhfRadioConfiguration.afcRange * (16777216.f / FXTAL)) + 0.5f);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_UHF, afc);

	//Set Datarates
	uint32_t rxDr = (FXTAL << 7) / (uhfRadioConfiguration.datarate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_UHF, rxDr);
	uint32_t txDr = (uint16_t)((uhfRadioConfiguration.datarate * (16777216.f / FXTAL)) + 0.5f);
	AX5043TXParamSetTXDatarate(RADIO_UHF, txDr);

	//Adjust RX Parameters that depend on datarate, AGC Attack and Settling as well as timing and datarate recovery
	uint8_t i = 0;
	for(i = 0; i < 15; i++) {
		//Attack f3dB should be ~Bitrate (Except for ASK)
		if(abs(agcAttackRealeaseTable[i] - uhfRadioConfiguration.datarate) < abs(agcAttackRealeaseTable[i+1] - uhfRadioConfiguration.datarate)) {
			AX5043RXParamSetAGCAttackSpeed0(RADIO_UHF, i);
			AX5043RXParamSetAGCAttackSpeed1(RADIO_UHF, i);
			break;
		}
		else if(i == 15){
			AX5043RXParamSetAGCAttackSpeed0(RADIO_UHF, i+1);
			AX5043RXParamSetAGCAttackSpeed1(RADIO_UHF, i+1);
			break;
		}
	}

	for(i = 0; i < 15; i++) {
		//Release f3dB should be ~Bitrate/10 (Except for ASK)
		if(abs(agcAttackRealeaseTable[i] - (uhfRadioConfiguration.datarate / 10)) < abs(agcAttackRealeaseTable[i+1] - (uhfRadioConfiguration.datarate / 10))) {
			AX5043RXParamSetAGCReleaseSpeed0(RADIO_UHF, i);
			AX5043RXParamSetAGCReleaseSpeed1(RADIO_UHF, i);
			break;
		}
		else if(i == 15){
			AX5043RXParamSetAGCReleaseSpeed0(RADIO_UHF, i+1);
			AX5043RXParamSetAGCReleaseSpeed1(RADIO_UHF, i+1);
			break;
		}
	}

	uint8_t exp = floorf(log2f(((float)rxDr / 4.f) / 8.f));
	uint8_t man = roundf(((float)rxDr / 4.f) / (1 << exp));
	AX5043PacketSetGainTimingRecovery0(RADIO_UHF, man, exp);
	AX5043PacketSetGainTimingRecovery1(RADIO_UHF, man, exp);
	AX5043PacketSetGainTimingRecovery3(RADIO_UHF, man, exp);

	exp = floorf(log2f(((float)rxDr / 64.f) / 8.f));
	man = roundf(((float)rxDr / 64.f) / (1 << exp));
	AX5043PacketSetGainDatarateRecovery0(RADIO_UHF, man, exp);
	AX5043PacketSetGainDatarateRecovery1(RADIO_UHF, man, exp);
	AX5043PacketSetGainDatarateRecovery3(RADIO_UHF, man, exp);

	//Set frequency deviation
	if(vhfRadioConfiguration.modulation != AFSK) {
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

RadioConfigStruct RadioUHFGetModConfig() {
	return uhfRadioConfiguration;
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
