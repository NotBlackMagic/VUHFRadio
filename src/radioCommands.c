#include "radioCommands.h"

/**
  * @brief	This function Inits the Radio with the base configurations, fixed ones not changed by other commands including RadioSetFullConfiguration
  * @param	radio: Selects the Radio
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioInitBaseConfiguration(uint8_t radio) {
	//Reset Radio
	AX5043PwrReset(radio);

	//Power Down
	AX5043PwrSetPowerMode(radio, PwrMode_Powerdown);

	//Set GPIOs
	AX5043GPIOCnfgSysClk(radio, SysClk_Low, 0);
	AX5043GPIOCnfgDCLK(radio, DCLK_Low, 0, 0);
	AX5043GPIOCnfgDATA(radio, DATA_Low, 0, 0);			//DATA_Modem_Data_Output
	AX5043GPIOCnfgIRQ(radio, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(radio, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(radio, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(radio, DACInput_RSSI);
	AX5043GPIOSetDACInputShift(radio, 0x0C);
	AX5043GPIOSetDACOutputMode(radio, 0x00);
	AX5043GPIOSetDACClockDoubling(radio, 0x01);

	//Set ADC, set-up used for Analog-FM TX
	AX5043GPIOSetADCSamplingPeriod(radio, 0x14);				//Set Sampling rate to 25kHz
	AX5043GPIOSetEnableSamplingADCGPADC13(radio, 0x01);			//Enable GPADC1-3
	AX5043GPIOSetEnableADCContinuousSampling(radio, 0x01);		//Continuous  sampling

	//Set IRQ
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifonotempty = 1;
	AX5043IrqEnableIRQs(radio, irqMask);

	//Set Events
	RadioEventMask radioEvenMask;
	radioEvenMask.raw = 0x00;
//	radioEvenMask.revmdone = 1;
	AX5043IrqEnableRadioEvents(radio, radioEvenMask);

	//Calibrate RSSI: Compensate for Board effects
	AX5043PacketSetRSSIOffset(radio, 0xF5);					//Offset: -11dBm

	//Set Performance Tuning Registers
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(radio, PERFTUNE0, &data, 1);		//F00
	data = 0x04;
	AX5043WriteLongAddress(radio, PERFTUNE8, &data, 1);		//F08: Power Control 1??
	data = 0x03;
	AX5043WriteLongAddress(radio, PERFTUNE13, &data, 1);	//F0D: Ref ??
	data = 0x04;
	AX5043WriteLongAddress(radio, PERFTUNE16, &data, 1);	//F10: XTALOSC ??
	data = 0x00;
	AX5043WriteLongAddress(radio, PERFTUNE17, &data, 1);	//F11: XTALAMPL ??
	data = 0x06;	//For TX
//	data = 0x02;	//For RX
	AX5043WriteLongAddress(radio, PERFTUNE24, &data, 1);	//F18
	data = 0x07;
	AX5043WriteLongAddress(radio, PERFTUNE28, &data, 1);	//F1C
	data = 0x68;
	AX5043WriteLongAddress(radio, PERFTUNE33, &data, 1);	//F21
	data = 0xFF;
	AX5043WriteLongAddress(radio, PERFTUNE34, &data, 1);	//F22
	data = 0x84;
	AX5043WriteLongAddress(radio, PERFTUNE35, &data, 1);	//F23
	data = 0x98;
	AX5043WriteLongAddress(radio, PERFTUNE38, &data, 1);	//F26
	data = 0x3F;
	AX5043WriteLongAddress(radio, PERFTUNE48, &data, 1);	//F30
	data = 0xF0;
	AX5043WriteLongAddress(radio, PERFTUNE49, &data, 1);	//F31
	data = 0x3F;
	AX5043WriteLongAddress(radio, PERFTUNE50, &data, 1);	//F32
	data = 0xF0;
	AX5043WriteLongAddress(radio, PERFTUNE51, &data, 1);	//F33
	data = 0x28;	//Set to 0x28 if RFDIV is set, 0x08 otherwise
	AX5043WriteLongAddress(radio, PERFTUNE52, &data, 1);	//F34
	data = 0x10;
	AX5043WriteLongAddress(radio, PERFTUNE53, &data, 1);	//F35
	data = 0x25;
	AX5043WriteLongAddress(radio, PERFTUNE68, &data, 1);	//F44
	data = 0xE7;
	AX5043WriteLongAddress(radio, PERFTUNE95, &data, 1);	//F5F: MODCFGP (PSK: 0xE1)
	data = 0x00;	//Set to 0x06 if "Raw, Soft Bits"
	AX5043WriteLongAddress(radio, PERFTUNE114, &data, 1);	//F72

	//Set Synth
	if(radio == RADIO_A) {
		AX5043SynthSetPLLLoopFilter(RADIO_A, PLLLoop_Filter500kHz);
//		AX5043SynthSetPLLChargePumpCurrent(RADIO_A, 0x10);
		AX5043SynthSetPLLVCOSelection(RADIO_A, 0);			//Use VCO 1
//		AX5043SynthSetPLLVCO2Internal(RADIO_A, 1);			//Use VCO 2 with external inductor
		AX5043SynthSetPLLVCOEnableRefDivider(RADIO_A, 1);
		AX5043SynthSetFrequencyA(RADIO_A, 0x1B473334);		//For 436.45MHz is 0x1B473334 calculated but calibrated value is 0x1B474335
//		AX5043SynthSetFrequencyB(RADIO_A, 0x1B474335);
	}
	else if(radio == RADIO_B) {
//		AX5043SynthSetPLLLoopFilter(RADIO_B, PLLLoop_Filter100kHz);
//		AX5043SynthSetPLLChargePumpCurrent(RADIO_B, 0x10);
		AX5043SynthSetPLLVCOSelection(RADIO_B, 1);			//Use VCO 2 with external inductor
		AX5043SynthSetPLLVCO2Internal(RADIO_B, 1);			//Use VCO 2 with external inductor
		AX5043SynthSetPLLVCOEnableRefDivider(RADIO_B, 1);
		AX5043SynthSetFrequencyA(RADIO_B, 0x06166667);		//For 145.895MHz is 0x091E51EC calculated value
//		AX5043SynthSetFrequencyB(RADIO_B, 0x08B22E58);
	}

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(radio);
	while(AX5043SynthGetAutoRangingA(radio));	//Wait for Auto Ranging Complete
//	AX5043SynthStartAutoRangingB(radio);
//	while(AX5043SynthGetAutoRangingB(radio));	//Wait for Auto Ranging Complete

	//Set PLL/VCO Parameters
	//AX5043PLLParamSetVCOBias(radio, 0x07);
	//AX5043PLLParamIsManualVCOIEnabled(radio);
	//AX5043PLLParamSetLockDetectDelay(radio, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(radio, PLLRangingClock_11);	//Default

	//RX Parameters
//	AX5043RXParamSetIFFrequency(RADIO_VHF, 0x0276);			//AFSK: 0x099A -> ~37498Hz; FSK-9600: 0x0276 -> ~9600Hz
//	AX5043RXParamSetDecimation(RADIO_VHF, 0x04);			//AFSK: 0x04 -> ~250kHz; FSK-9600: 0x05; Needs to be > 2 * Signal Bandwidth
//	AX5043RXParamSetRXDatarate(RADIO_VHF, 0x099A);			//AFSK: 0x0682AB -> ~1200 bits/s; FSK-9600: 0xA6AA
	AX5043RXParamSetRXMaximumDatarateOffset(radio, 0x00);
//	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_VHF, 0xCCCC);	//0x28F6: Set to 10kHz; FSK-9600: 0x0831
	AX5043RXParamSetCorrectFrequencyOffsetLO(radio, 1);
//	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x25);	//Set RX AFSK Space freq. of 2200 Hz
//	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x14);		//Set RX AFSK Mark freq. of 1200 Hz
//	AX5043RXParamSetAFSKDetBandwitdh(RADIO_VHF, 0x0E);
	AX5043RXParamSetRXFSKMaxDeviation(radio, 0x43C0);		//AFSK: 0x43C0; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXFSKMinDeviation(radio, 0xDC40);		//AFSK: 0xDC40; Only used if in manual mode, currently all auto
	AX5043RXParamSetRXParameterNumber0(radio, 0);
	AX5043RXParamSetRXParameterNumber1(radio, 0);			//1
	AX5043RXParamSetRXParameterNumber2(radio, 0);			//3
	AX5043RXParamSetRXParameterNumber3(radio, 0);			//3
	//RX Parameter 0
//	AX5043RXParamSetAGCReleaseSpeed0(RADIO_VHF, 0x0E);				//Original: 0x0E; Calculated FSK-9600: 0x07
//	AX5043RXParamSetAGCAttackSpeed0(RADIO_VHF, 0x08);				//Original: 0x08; Calculated FSK-9600: 0x04
//	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
	AX5043RXParamSetAGCTargetHysteresis0(radio, 0x00);
	AX5043RXParamSetAGCMaximumReset0(radio, 0x00);
	AX5043RXParamSetAGCMinimumReset0(radio, 0x00);
//	AX5043PacketSetGainTimingRecovery0(RADIO_VHF, 0x0D, 0x0E);		//AFSK: 0x0D, 0x0E; FSK-9600: 0x0A, 0x0A
//	AX5043PacketSetGainDatarateRecovery0(RADIO_VHF, 0x0D, 0x08);	//AFSK: 0x0D, 0x08; FSK-9600: 0x0A, 0x04
	AX5043RXParamSetRXPhaseGain0(radio, 0x03);
	AX5043RXParamSetRXDecimationFilter0(radio, 0x03);
//	AX5043RXParamSetRXFrequencyGainA0(RADIO_VHF, 0x0F);
//	AX5043RXParamSetRXFrequencyGainB0(RADIO_VHF, 0x1F);
//	AX5043RXParamSetRXFrequencyGainC0(RADIO_VHF, 0x0A);
//	AX5043RXParamSetRXFrequencyGainD0(RADIO_VHF, 0x0A);
//	AX5043RXParamSetRXAmplitudeGain0(RADIO_VHF, 0x06);
	AX5043RXParamSetRXAmplitudeAGCJump0(radio, 0x00);
	AX5043RXParamSetRXAmplitudeRecoveryByAverage0(radio, 0x00);
	AX5043RXParamSetRXFrequencyDeviation0(radio, 0x00);
	AX5043RXParamSetDeviationDecay0(radio, 0x06);
	AX5043RXParamEnableDeviationUpdate0(radio, 0x01);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(radio, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(radio, 0x00);
	//RX Parameter 1
//	AX5043RXParamSetAGCReleaseSpeed1(RADIO_VHF, 0x07);				//Original: 0x0E; Calculated FSK-9600: 0x07
//	AX5043RXParamSetAGCAttackSpeed1(RADIO_VHF, 0x04);				//Original: 0x08; Calculated FSK-9600: 0x04
//	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
//	AX5043RXParamSetAGCTargetHysteresis1(RADIO_VHF, 0x00);
//	AX5043RXParamSetAGCMaximumReset1(RADIO_VHF, 0x00);
//	AX5043RXParamSetAGCMinimumReset1(RADIO_VHF, 0x00);
//	AX5043PacketSetGainTimingRecovery1(RADIO_VHF, 0x0A, 0x0A);		//AFSK: 0x0D, 0x0C; FSK-9600: 0x0A, 0x08
//	AX5043PacketSetGainDatarateRecovery1(RADIO_VHF, 0x0A, 0x06);	//AFSK: 0x0D, 0x07; FSK-9600: 0x0A, 0x03
//	AX5043RXParamSetRXPhaseGain1(RADIO_VHF, 0x03);
//	AX5043RXParamSetRXDecimationFilter1(RADIO_VHF, 0x03);
//	AX5043RXParamSetRXFrequencyGainA1(RADIO_VHF, 0x0F);
//	AX5043RXParamSetRXFrequencyGainB1(RADIO_VHF, 0x1F);
//	AX5043RXParamSetRXFrequencyGainC1(RADIO_VHF, 0x0A);
//	AX5043RXParamSetRXFrequencyGainD1(RADIO_VHF, 0x0A);
//	AX5043RXParamSetRXAmplitudeGain1(RADIO_VHF, 0x06);
//	AX5043RXParamSetRXAmplitudeAGCJump1(RADIO_VHF, 0x00);
//	AX5043RXParamSetRXFrequencyDeviation1(RADIO_VHF, 0x00);			//AFSK: 0x01C0; FSK-9600: 0x002D; Not needed, maybe improves performance?
//	AX5043RXParamSetDeviationDecay1(RADIO_VHF, 0x06);
//	AX5043RXParamEnableDeviationUpdate1(RADIO_VHF, 0x01);
//	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_VHF, 0x00);
//	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_VHF, 0x00);
	//RX Parameter 3
//	AX5043RXParamSetAGCReleaseSpeed3(RADIO_VHF, 0x0F);
//	AX5043RXParamSetAGCAttackSpeed3(RADIO_VHF, 0x0F);
//	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_VHF, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
//	AX5043RXParamSetAGCTargetHysteresis3(RADIO_VHF, 0x00);
//	AX5043RXParamSetAGCMaximumReset3(RADIO_VHF, 0x00);
//	AX5043RXParamSetAGCMinimumReset3(RADIO_VHF, 0x00);
//	AX5043PacketSetGainTimingRecovery3(RADIO_VHF, 0x0A, 0x0A);		//AFSK: 0x0D, 0x0B; FSK-9600: 0x0A, 0x07
//	AX5043PacketSetGainDatarateRecovery3(RADIO_VHF, 0x0A, 0x06);	//AFSK: 0x0D, 0x06; FSK-9600: 0x0A, 0x02
//	AX5043RXParamSetRXPhaseGain3(RADIO_VHF, 0x03);
//	AX5043RXParamSetRXDecimationFilter3(RADIO_VHF, 0x03);
//	AX5043RXParamSetRXFrequencyGainA3(RADIO_VHF, 0x0F);
//	AX5043RXParamSetRXFrequencyGainB3(RADIO_VHF, 0x1F);
//	AX5043RXParamSetRXFrequencyGainC3(RADIO_VHF, 0x0D);
//	AX5043RXParamSetRXFrequencyGainD3(RADIO_VHF, 0x0D);
//	AX5043RXParamSetRXAmplitudeGain3(RADIO_VHF, 0x06);
//	AX5043RXParamSetRXFrequencyDeviation3(RADIO_VHF, 0x00);			//AFSK: 0x01C0; FSK-9600: 0x002D; Not needed, maybe improves performance?
//	AX5043RXParamSetDeviationDecay3(RADIO_VHF, 0x06);
//	AX5043RXParamEnableDeviationUpdate3(RADIO_VHF, 0x01);
//	AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(RADIO_VHF, 0x00);
//	AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(RADIO_VHF, 0x00);

	//Set Packet, encoding and framing
//	AX5043PacketSetMSBFirst(radio, 0);
//	AX5043PacketEnableEncodeBitInversion(radio, 1);
//	AX5043PacketEnableEncodeDifferential(radio, 1);
//	AX5043PacketEnableEncodeScramble(radio, 1);
//	AX5043PacketSetFrameMode(radio, FrmMode_HDLC);
//	AX5043PacketSetCRCMode(radio, CRCMode_CCITT);
	AX5043PacketSetPacketChunkSize(radio, PacketChunkSize_240byte);
	AX5043PacketSetLengthByteSignificantBits(radio, 0x0F);	//Enable arbitrary packet length
	AX5043PacketSetMaxLength(radio, 0xFF);
	AX5043PacketSetAcceptPacketsMultiChuck(radio, 0);
	AX5043PacketSetAcceptPacketsCRCFailed(radio, 1);

	//Append RX tracking data in FIFO
//	AX5043PacketEnableStoreRFFrequencyValue(radio, 0x01);	//Append/save RF frequency offset
//	AX5043PacketEnableStoreDatarateValue(radio, 0x01);		//Append/save RX datarate
//	AX5043PacketEnableStoreRSSI(radio, 0x01);				//Append/save RSSI value

	//Set Pattern Matching
	AX5043PacketSetPaternMatch0(radio, 0x7E7E7E7E);
	AX5043PacketSetPaternLength0(radio, 0x00);
	AX5043PacketSetPaternMatch0Raw(radio, 0);
	AX5043PacketSetPaternMatch0Min(radio, 0x00);
	AX5043PacketSetPaternMatch0Max(radio, 0x1F);

	AX5043PacketSetPaternMatch1(radio, 0x7E7E);
	AX5043PacketSetPaternLength1(radio, 0x0A);
	AX5043PacketSetPaternMatch1Raw(radio, 0x00);
	AX5043PacketSetPaternMatch1Min(radio, 0x00);
	AX5043PacketSetPaternMatch1Max(radio, 0x0A);

	//Set packet control
	AX5043PacketSetTXPLLBoostTime(radio, 0x02, 0x03);
	AX5043PacketSetTXPLLSettlingTime(radio, 0x14, 0x00);
	AX5043PacketSetRXPLLBoostTime(radio, 0x02, 0x03);
	AX5043PacketSetRXPLLSettlingTime(radio, 0x14, 0x00);
	AX5043PacketSetRXDCOffsetAcquisitionTime(radio, 0x00, 0x00);
	AX5043PacketSetRXCoarseAGCTime(radio, 0x13, 0x03);				//19*2^3 us = 152 us
	AX5043PacketSetRXAGCSettlingTime(radio, 0x00, 0x00);
	AX5043PacketSetRXRSSISettlingTime(radio, 0x03, 0x00);
	AX5043PacketSetRXPreamble1Timeout(radio, 0x00, 0x00);
	AX5043PacketSetRXPreamble2Timeout(radio, 0x17, 0x00);
	AX5043PacketSetRXPreamble3Timeout(radio, 0x00, 0x00);

	return 0x00;
}

/**
  * @brief	This function sets the Radio with the complete configuration passed
  * @param	radio: Selects the Radio
  * @param	configuration: RadioConfigsStruct holding all configurations to be set/programmed
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetFullConfiguration(uint8_t radio, RadioConfigsStruct configuration) {
	if(RadioSetCenterFrequency(radio, configuration.centerFrequency) != 0x00) return 0x01;
	if(RadioSetModulation(radio, configuration.modulation) != 0x00) return 0x01;
	if(RadioSetTXDeviation(radio, configuration.frequencyDeviation) != 0x00) return 0x01;
	if(RadioSetBandwidth(radio, configuration.bandwidth) != 0x00) return 0x01;
	if(RadioSetIF(radio, configuration.ifFrequency) != 0x00) return 0x01;
	if(RadioSetRXDatarate(radio, configuration.rxDatarate) != 0x00) return 0x01;
	if(RadioSetTXDatarate(radio, configuration.txDatarate) != 0x00) return 0x01;
	if(RadioSetTXPower(radio, configuration.outputPower) != 0x00) return 0x01;
	if(RadioSetAFCRange(radio, configuration.afcRange) != 0x00) return 0x01;
	if(RadioSetAGCSpeed(radio, configuration.agcSpeed) != 0x00) return 0x01;
	if(RadioSetOperationMode(radio, configuration.operationMode) != 0x00) return 0x01;

	//Have to be done AFTER operation mode is set, depends on operationMode
	if(RadioSetAFSKSpaceFreq(radio, configuration.afskSpace) != 0x00) return 0x01;
	if(RadioSetAFSKMarkFreq(radio, configuration.afskMark) != 0x00) return 0x01;

	if(RadioSetEncodingMode(radio, configuration.encoder) != 0x00) return 0x01;
	if(RadioSetFramingMode(radio, configuration.framing) != 0x00) return 0x01;
	if(RadioSetCRCMode(radio, configuration.crc) != 0x00) return 0x01;

	return 0x00;
}

/**
  * @brief	This function sets the Radio Center Frequency
  * @param	radio: Selects the Radio
  * @param	frequency: The center frequency in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetCenterFrequency(uint8_t radio, uint32_t frequency) {
	//Check limits
	if(radio == RADIO_A) {
//		if(frequency < RADIO_A_FREQ_MIN || frequency > RADIO_A_FREQ_MAX) {
//			return 1;
//		}
	}
	else if(radio == RADIO_B) {
//		if(frequency < RADIO_B_FREQ_MIN || frequency > RADIO_B_FREQ_MAX) {
//			return 1;
//		}
	}
	else {
		//Invalid Radio ID/Index
		return 1;
	}

	//Set Central Frequency
	uint32_t freq = (uint32_t)((frequency * (16777216.f / RADIO_A_XTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(radio, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(radio);
	while(AX5043SynthGetAutoRangingA(radio));	//Wait for Auto Ranging Complete

	//Check if ranging was successful
	return AX5043SynthGetAutoRangingErrorA(radio);
}

/**
  * @brief	This function sets the AFC Range
  * @param	radio: Selects the Radio
  * @param	range: The AFC Range in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetAFCRange(uint8_t radio, uint32_t range) {
	//Check limits, AFC Range hsa to be < 1/4 RX BW
//	if(radio == RADIO_A) {
//		if(range > (bandwidthA >> 2)) {
//			return 1;
//		}
//	}
//	else if(radio == RADIO_B) {
//		if(range > (bandwidthB >> 2)) {
//			return 1;
//		}
//	}
//	else {
//		return 1;
//	}

	//Set AFC Range
	uint32_t afc = (uint32_t)((range * (16777216.f / RADIO_A_XTAL)) + 0.5f);
	AX5043RXParamSetRXMaximumFrequencyOffset(radio, afc);

	return 0;
}

/**
  * @brief	This function sets the AGC Speed
  * @param	radio: Selects the Radio
  * @param	speed: The AGC Speed
  * AGC Speeds:
  * 0: 79577Hz;
  * 1: 59683Hz;
  * 2: 34815Hz;
  * 3: 18651Hz;
  * 4: 9636Hz;
  * 5: 4896Hz;
  * 6: 2467Hz;
  * 7: 1239Hz;
  * 8: 620Hz;
  * 9: 311Hz;
  * 10: 155Hz;
  * 11: 78Hz;
  * 12: 39Hz;
  * 13: 19Hz;
  * 14: 10Hz;
  * 15: OFF
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetAGCSpeed(uint8_t radio, uint8_t speed) {
	//Check limits
	if(speed > 15) {
		return 1;
	}

	//Set AGC Attack Speed Range
	AX5043RXParamSetAGCAttackSpeed0(radio, speed);
	AX5043RXParamSetAGCAttackSpeed1(radio, speed);

	//Set AGC Release Speed, should be 1/10 of Attack speed
	uint8_t releaseSpeedIndex[16] = {4, 5, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 14, 14, 14, 15};
	AX5043RXParamSetAGCReleaseSpeed0(radio, releaseSpeedIndex[speed]);
	AX5043RXParamSetAGCReleaseSpeed1(radio, releaseSpeedIndex[speed]);

	return 0;
}

/**
  * @brief	This function sets the CRC Check Mode
  * @param	radio: Selects the Radio
  * @param	crcMode: Selects the CRC Mode
  * CRC Modes:
  * 0: OFF
  * 1: CCITT
  * 2: CRC16
  * 3: DNP
  * 4: CRC32
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetCRCMode(uint8_t radio, RadioCRC crcMode) {
	//Check limits
	if(crcMode > 5) {
		return 1;
	}

	//Set CRC Mode
	if(crcMode == RadioCRC_CRC32) {
		//This has a different index then passed through crcMode, is 0x06
		AX5043PacketSetCRCMode(radio, CRCMode_CRC32);
	}
	else {
		AX5043PacketSetCRCMode(radio, crcMode);
	}

	return 0;
}

/**
  * @brief	This function sets the Encoding Mode
  * @param	radio: Selects the Radio
  * @param	encMode: Selects the Encoding Mode
  * Encoding Modes:
  * 0: NRZ
  * 1: NRZ-S
  * 2: NRZI
  * 3: NRZI-S
  * 4: FM1
  * 5: FM0
  * 6: MANCHESTER
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetEncodingMode(uint8_t radio, RadioEncoder encMode) {
	//Check limits
	if(encMode > 6) {
		return 1;
	}

	//Set Encoding Mode
	AX5043PacketSetMSBFirst(radio, 0);
	switch(encMode) {
		case RadioEncoder_NRZ:
			//NRZ Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 0);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case RadioEncoder_NRZ_S:
			//NRZ + Scramble Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 0);
			AX5043PacketEnableEncodeScramble(radio, 1);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case RadioEncoder_NRZI:
			//NRZI Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case RadioEncoder_NRZI_S:
			//NRZI + Scramble Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 1);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case RadioEncoder_FM1:
			//FM1 Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 1);
			break;
		case RadioEncoder_FM0:
			//FM0 Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 1);
			break;
		case RadioEncoder_Manchester:
			//Manchester Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 0);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 1);
			break;
		default:
			return 1;
	}

	return 0;
}

/**
  * @brief	This function sets the Framing Mode
  * @param	radio: Selects the Radio
  * @param	frmMode: Selects the Framing Mode
  * Framing Modes:
  * 0: RAW
  * 1: HDLC
  * 2: Wireless M-Bus
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetFramingMode(uint8_t radio, RadioFraming frmMode) {
	//Check limits
	if(frmMode > 2) {
		return 1;
	}

	//Set Framing Mode
	switch(frmMode) {
		case RadioFraming_RAW:
			//Raw Mode
			AX5043PacketSetFrameMode(radio, FrmMode_Raw);
			break;
		case RadioFraming_HDLC:
			//HDLC Mode
			AX5043PacketSetFrameMode(radio, FrmMode_HDLC);
			break;
		case RadioFraming_WMBus:
			//Wireless M-Bus Mode
			AX5043PacketSetFrameMode(radio, FrmMode_WMBUS);
			break;
		default:
			return 1;
	}

	return 0;
}

/**
  * @brief	This function sets the Modulation and all necessary parameters
  * @param	radio: Selects the Radio
  * @param	modulation: Selects the Modulation
  * Modulations:
  * 0: NA
  * 1: AM
  * 2: FM
  * 3: AFSK
  * 4: ASK
  * 5: FSK
  * 6: GMSK
  * 7: 4-FSK
  * 8: BPSK
  * 9: QPSK
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetModulation(uint8_t radio, RadioModulation modulation) {
	//Check limits
	if(modulation < 1 || modulation > 9) {
		return 1;
	}

	//Set Framing Mode
	switch(modulation) {
		case RadioModulation_AM:
			//AM Modulation
			//Set DAC
			AX5043GPIOSetDACInput(radio, DACInput_TRKAmplitude);
			AX5043GPIOSetDACInputShift(radio, 0x0B);
			AX5043GPIOSetDACOutputMode(radio, 0x00);
			AX5043GPIOSetDACClockDoubling(radio, 0x01);

			//Set Modulation
			AX5043GeneralSetModulation(radio, FM);

		    //RX Parameter 0
		    AX5043RXParamSetAGCTargetAvgMagnitude0(radio, 0x79);	//Target: 192
		    AX5043RXParamSetRXAmplitudeGain0(radio, 0x04);
			AX5043PacketSetGainTimingRecovery0(radio, 0x00, 0x00);
			AX5043PacketSetGainDatarateRecovery0(radio, 0x00, 0x00);
			break;
		case RadioModulation_FM:
			//FM Modulation
			//Set DAC
			AX5043GPIOSetDACInput(radio, DACInput_TRKFrequency);
			AX5043GPIOSetDACInputShift(radio, 0x0C);
			AX5043GPIOSetDACOutputMode(radio, 0x00);
			AX5043GPIOSetDACClockDoubling(radio, 0x01);

			//Set Modulation
			AX5043GeneralSetModulation(radio, FM);

			//RX Parameter 0
			AX5043RXParamSetAGCTargetAvgMagnitude0(radio, 0x80);
			AX5043RXParamSetRXFrequencyGainA0(radio, 0x0F);			//OFF
			AX5043RXParamSetRXFrequencyGainB0(radio, 0x04);			//Bandwidth of “inner” AFC loop used for FM demodulation. f_3dB = 0.115*BR
			AX5043RXParamSetRXFrequencyGainC0(radio, 0x1F);			//OFF
			AX5043RXParamSetRXFrequencyGainD0(radio, 0x08);			//bandwidth of “outer” AFC loop (tracking frequency mismatch), 78 Hz @ BR = 100 kbps, f_xtal = 16 MHz
			AX5043PacketSetGainTimingRecovery0(radio, 0x00, 0x00);
			AX5043PacketSetGainDatarateRecovery0(radio, 0x00, 0x00);
			break;
		case RadioModulation_AFSK:
			//AFSK Modulation
			AX5043GeneralSetModulation(radio, AFSK);
			break;
		case RadioModulation_ASK:
			//ASK Modulation
			AX5043GeneralSetModulation(radio, ASK);
			break;
		case RadioModulation_FSK:
			//FSK Modulation
			AX5043GeneralSetModulation(radio, FSK);
			break;
		case RadioModulation_GMSK:
			//GMSK Modulation
			AX5043GeneralSetModulation(radio, FSK);
			break;
		case RadioModulation_4FSK:
			//4-FSK Modulation
			AX5043GeneralSetModulation(radio, FSK4);
			break;
		case RadioModulation_BPSK:
			//BPSK Modulation
			AX5043GeneralSetModulation(radio, PSK);
			break;
		case RadioModulation_QPSK:
			//QPSK Modulation
			AX5043GeneralSetModulation(radio, OQPSK);
			break;
		default:
			return 1;
	}

	if(modulation != RadioModulation_AM && modulation != RadioModulation_FM) {
		//RX Parameter 0, set to default in case was changed in FM or AM modulations
		AX5043RXParamSetAGCTargetAvgMagnitude0(radio, 0x89);		//3/4 of maximum, which is 2^9 - 1 = 511
		AX5043RXParamSetRXFrequencyGainA0(radio, 0x0F);
		AX5043RXParamSetRXFrequencyGainB0(radio, 0x1F);
		AX5043RXParamSetRXFrequencyGainC0(radio, 0x0A);
		AX5043RXParamSetRXFrequencyGainD0(radio, 0x0A);

		uint8_t dec = AX5043RXParamGetDecimation(radio);
		uint32_t rxRate = AX5043RXParamGetRXDatarate(radio);
		rxRate = (uint32_t)((FXTAL << 7) / (((float)rxRate - 0.5f) * dec));

		uint8_t exp = floorf(log2f(((float)rxRate / 4.f) / 8.f));
		uint8_t man = roundf(((float)rxRate / 4.f) / (1 << exp));
		AX5043PacketSetGainTimingRecovery0(radio, man, exp);
		AX5043PacketSetGainTimingRecovery1(radio, man, exp);
		AX5043PacketSetGainTimingRecovery2(radio, man, exp);
		AX5043PacketSetGainTimingRecovery3(radio, man, exp);

		exp = floorf(log2f(((float)rxRate / 64.f) / 8.f));
		man = roundf(((float)rxRate / 64.f) / (1 << exp));
		AX5043PacketSetGainDatarateRecovery0(radio, man, exp);
		AX5043PacketSetGainDatarateRecovery1(radio, man, exp);
		AX5043PacketSetGainDatarateRecovery2(radio, man, exp);
		AX5043PacketSetGainDatarateRecovery3(radio, man, exp);

		uint16_t afskBW = (uint16_t)(2.f * log2f((float)FXTAL / (32 * rxRate * dec)) + 1.5f);
		AX5043RXParamSetAFSKDetBandwitdh(radio, afskBW);
	}

	if(modulation == RadioModulation_BPSK) {
		//MODCFGP: PSK settings, enable PSK
//		AX5043TXParamSetPSKPulseLength(radio, PSKPulseLen_2);	//F5F: MODCFGP (PSK: 0xE1)
	}
	else {
		//MODCFGP: PSK settings, disable PSK
//		AX5043TXParamSetPSKPulseLength(radio, PSKPulseLen_Off);	//F5F: MODCFGP (PSK: 0xE7)
	}

	return 0;
}

/**
  * @brief	This function sets the Radio Operation Mode
  * @param	radio: Selects the Radio
  * @param	opMode: Selects the Framing Mode
  * Operation Modes:
  * 0: OFF/Standby
  * 1: RX
  * 2: TX
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetOperationMode(uint8_t radio, RadioMode opMode) {
	//Check limits
	if(opMode > 2) {
		return 1;
	}

	//Set Operation Mode
	switch(opMode) {
		case RadioMode_OFF:
			//OFF/Standby Mode
//			PwrStatus status = AX5043PwrStats(radio);
			AX5043PwrSetPowerMode(radio, PwrMode_Powerdown);
//			status = AX5043PwrStats(radio);
//			while(status.svmodem != 0x01) {
//				status = AX5043PwrStats(radio);
//			}
			break;
		case RadioMode_RX: {
			//RX Mode
//			PwrStatus status = AX5043PwrStats(radio);
			//Issue/Silicon Errata "Radio Controller may not Properly Release FIFO Read orWrite Port" workaround
			//Can't switch directly from TXEN to RXEN and vice-versa
			PwrStatus status = AX5043PwrStats(radio);
			do {
				AX5043PwrSetPowerMode(radio, PwrMode_Standby);
				status = AX5043PwrStats(radio);
			} while(status.svmodem != 0x00);
			AX5043PwrSetPowerMode(radio, PwrMode_FIFOEN);
			AX5043PwrSetPowerMode(radio, PwrMode_RXEN);
			status = AX5043PwrStats(radio);
			while(status.svmodem != 0x01) {
				status = AX5043PwrStats(radio);
			}
			break;
		}
		case RadioMode_TX: {
			//TX Mode
//			PwrStatus status = AX5043PwrStats(radio);
			//Issue/Silicon Errata "Radio Controller may not Properly Release FIFO Read orWrite Port" workaround
			//Can't switch directly from TXEN to RXEN and vice-versa
			PwrStatus status = AX5043PwrStats(radio);
			do {
				AX5043PwrSetPowerMode(radio, PwrMode_Standby);
				status = AX5043PwrStats(radio);
			} while(status.svmodem != 0x00);
			AX5043PwrSetPowerMode(radio, PwrMode_FIFOEN);
			AX5043PwrSetPowerMode(radio, PwrMode_TXEN);
			status = AX5043PwrStats(radio);
			while(status.svmodem != 0x01) {
				status = AX5043PwrStats(radio);
			}
			break;
		}
		default:
			return 1;
	}

	return 0;
}

/**
  * @brief	This function sets the TX Output Power
  * @param	radio: Selects the Radio
  * @param	power: Output Power, -10 to 16 dBm
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetTXPower(uint8_t radio, int8_t power) {
	//Check limits
	if(power < -10 || power > 16) {
		return 1;
	}

	//Set TX Power, Pout = TXPWRCOEFFB / (2^12 - 1) * Pmax; Pmax = 16 dBm
	uint16_t powerCoef = ((uint32_t)power * 4095) >> 4;
	AX5043TXParamSetTXPredistortionCoeffB(radio, powerCoef);

	return 0;
}

/**
  * @brief	This function sets the RX Bandwidth
  * @param	radio: Selects the Radio
  * @param	bandwidth: RX Bandwidth
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetBandwidth(uint8_t radio, uint32_t bandwidth) {
	//Check Limits
	if(bandwidth > 500000) {
		return 1;
	}

	//Set RX Bandwidth, aka Decimation
	uint8_t decimation = (uint8_t)((FXTAL * 0.210858f) / (float)(bandwidth << 4));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
	AX5043RXParamSetDecimation(radio, decimation);

	return 0;
}

/**
  * @brief	This function sets the RX IF
  * @param	radio: Selects the Radio
  * @param	frequency: IF in H
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetIF(uint8_t radio, uint32_t frequency) {
	//Check Limits
	if(frequency > 500000) {
		return 1;
	}

	//Set RX IF Frequency
	uint16_t ifF = (uint16_t)(frequency * (1048576.f / RADIO_A_XTAL) + 0.5f);
	AX5043RXParamSetIFFrequency(radio, ifF);

	return 0;
}

/**
  * @brief	This function sets the RX Datarate
  * @param	radio: Selects the Radio
  * @param	bitrate: Datarate in bits/s
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetRXDatarate(uint8_t radio, uint32_t bitrate) {
	//Check Limits
	if(bitrate > 250000) {
		return 1;
	}

	//Set RX Datarate
	uint8_t decimation = AX5043RXParamGetDecimation(radio);
	uint32_t rxDr = (RADIO_A_XTAL << 7) / (bitrate * decimation);
	AX5043RXParamSetRXDatarate(radio, rxDr);

	Modulations modulation = (Modulations)AX5043GeneralGetModulation(radio);
	if(modulation != FM) {
		//Set RX Datarate dependent parameters
		uint8_t exp = floorf(log2f(((float)bitrate / 4.f) / 8.f));
		uint8_t man = roundf(((float)bitrate / 4.f) / (1 << exp));
		AX5043PacketSetGainTimingRecovery0(radio, man, exp);
		AX5043PacketSetGainTimingRecovery1(radio, man, exp);
		AX5043PacketSetGainTimingRecovery3(radio, man, exp);

		exp = floorf(log2f(((float)bitrate / 64.f) / 8.f));
		man = roundf(((float)bitrate / 64.f) / (1 << exp));
		AX5043PacketSetGainDatarateRecovery0(radio, man, exp);
		AX5043PacketSetGainDatarateRecovery1(radio, man, exp);
		AX5043PacketSetGainDatarateRecovery3(radio, man, exp);

		uint16_t afskBW = (uint16_t)(2.f * log2f((float)FXTAL / (32 * bitrate * decimation)) + 1.5f);
		AX5043RXParamSetAFSKDetBandwitdh(radio, afskBW);
	}

	return 0;
}

/**
  * @brief	This function sets the TX Datarate
  * @param	radio: Selects the Radio
  * @param	bitrate: Datarate in bits/s
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetTXDatarate(uint8_t radio, uint32_t bitrate) {
	//Check Limits
	if(bitrate > 250000) {
		return 1;
	}

	//Set TX Datarate
	uint32_t txDr = (uint16_t)((bitrate * (16777216.f / FXTAL)) + 0.5f);
	AX5043TXParamSetTXDatarate(radio, txDr);

	return 0;
}

/**
  * @brief	This function sets the Frequency Deviation, for FSK, AFSK and FM
  * @param	radio: Selects the Radio
  * @param	deviation: Frequency Deviation in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetTXDeviation(uint8_t radio, uint32_t deviation) {
	//Check Limits
	if(deviation > 100000) {
		return 1;
	}

	Modulations modulation = (Modulations)AX5043GeneralGetModulation(radio);

	uint32_t fDev = 0;
	switch(modulation) {
		case FM: {
			fDev = (uint8_t)(roundf(15.0f - log2f((float)FXTAL / deviation)));
			if(fDev > 0x07) {
				fDev = 0x07;
			}
			fDev += 0xC000;	//Add sign extension and mid-code subtraction from ADC
			break;
		}
		case AFSK: {
			//Calculate deviation for AFSK
			fDev = (uint16_t)(((deviation * 0.858785f) * (16777216.f / FXTAL)) + 0.5f);
			break;
		}
		default: {
			//Calculate deviation for FSK
			fDev = (uint32_t)(((deviation >> 1) * (16777216.f / FXTAL)) + 0.5f);
			break;
		}
	}

	AX5043TXParamSetFSKFrequencyDeviation(radio, fDev);

	return 0;
}

/**
  * @brief	This function sets the AFSK Space Frequency
  * @param	radio: Selects the Radio
  * @param	spaceFreq: AFSK Space Frequency in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetAFSKSpaceFreq(uint8_t radio, uint16_t spaceFreq) {
	uint16_t afskSpace = 0;

	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(radio);
	if(pwrMode == PwrMode_RXEN) {
		//Configuration for AFSK RX
		uint8_t decimation = AX5043RXParamGetDecimation(radio);
		afskSpace = (uint16_t)((spaceFreq * decimation << 16) / (float)FXTAL + 0.5f);
	}
	else {
		//Configuration for AFSK TX
		afskSpace = (uint16_t)(spaceFreq * (262144.f / FXTAL) + 0.5f);
	}

	AX5043RXParamSetAFSKSpaceFrequency(radio, afskSpace);		//Set RX AFSK Space Frequency

	return 0;
}

/**
  * @brief	This function sets the AFSK Mark Frequency
  * @param	radio: Selects the Radio
  * @param	spaceFreq: AFSK Mark Frequency in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetAFSKMarkFreq(uint8_t radio, uint16_t markFreq) {
	uint16_t afskMark = 0;

	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(radio);
	if(pwrMode == PwrMode_RXEN) {
		//Configuration for AFSK RX
		uint8_t decimation = AX5043RXParamGetDecimation(radio);
		afskMark = (uint16_t)((markFreq * decimation << 16) / (float)FXTAL + 0.5f);
	}
	else {
		//Configuration for AFSK TX
		afskMark = (uint16_t)(markFreq * (262144.f / FXTAL) + 0.5f);
	}

	AX5043RXParamSetAFSKMarkFrequency(radio, afskMark);		//Set RX AFSK Space Frequency

	return 0;
}

/**
  * @brief	This function writes a REPEATDATA packet to the Radio FIFO, a preamble
  * @param	radio: Selects the Radio
  * @param	dataByte: The DATA byte to be sent "count" times
  * @param	count: Number of times to send the "dataByte"
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioWriteFIFORepeatData(uint8_t radio, uint8_t dataByte, uint8_t count) {
	uint8_t fifoData[4];

	uint16_t fifoFree = AX5043FIFOGetFIFOFree(radio);
	if(fifoFree < 4) {
		return 1;
	}

	fifoData[0] = FIFO_REPEATDATA;	//FIFO Repeat Data command
	fifoData[1] = REPEATDATA_RAW | REPEATDATA_NOCRC;	//Send as RAW and supress CRC generation
	fifoData[2] = count;
	fifoData[3] = dataByte;

	AX5043FIFOSetFIFO(radio, fifoData, 4);

	return 0;
}

/**
  * @brief	This function writes a DATA packet to the Radio FIFO
  * @param	radio: Selects the Radio
  * @param	data: The DATA Frame bytes
  * @param	dataLength: Length of the DATA Frame
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioWriteFIFOData(uint8_t radio, uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	//Check for Space in FIFO
	uint16_t fifoFree = AX5043FIFOGetFIFOFree(radio);
	if(fifoFree < (dataLength + 3)) {
		return 1;
	}

	fifoData[i++] = FIFO_DATA;			//FIFO Data command
	fifoData[i++] = dataLength + 1; 	//FIFO Data Length + 1 (info/flag byte, the next byte)
	fifoData[i++] = DATA_PKTSTART | DATA_PKTEND;		//Set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(radio, fifoData, i);

	return 0;
}
