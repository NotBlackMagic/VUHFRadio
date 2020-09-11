#include "radioCommands.h"

/**
  * @brief	This function sets the Radio Center Frequency
  * @param	radio: Selects the Radio
  * @param	frequency: The center frequency in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetCenterFrequency(uint8_t radio, uint32_t frequency) {
	//Check limits
	if(radio == RADIO_A) {
		if(frequency < RADIO_A_FREQ_MIN || frequency > RADIO_A_FREQ_MAX) {
			return 1;
		}
	}
	else if(radio == RADIO_B) {
		if(frequency < RADIO_B_FREQ_MIN || frequency > RADIO_B_FREQ_MAX) {
			return 1;
		}
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

	return 0;
}

/**
  * @brief	This function sets the AFC Range
  * @param	radio: Selects the Radio
  * @param	range: The AFC Range in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetAFCRange(uint8_t radio, uint32_t range) {
	//Check limits, AFC Range hsa to be < 1/4 RX BW
	if(radio == RADIO_A) {
		if(range > (bandwidthA >> 2)) {
			return 1;
		}
	}
	else if(radio == RADIO_B) {
		if(range > (bandwidthB >> 2)) {
			return 1;
		}
	}
	else {
		return 1;
	}

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
uint8_t RadioSetCRCMode(uint8_t radio, uint8_t crcMode) {
	//Check limits
	if(crcMode > 5) {
		return 1;
	}

	//Set CRC Mode
	if(crcMode == 0x04) {
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
uint8_t RadioSetEncodingMode(uint8_t radio, uint8_t encMode) {
	//Check limits
	if(encMode > 6) {
		return 1;
	}

	//Set Encoding Mode
	switch(encMode) {
		case 0x00:
			//NRZ Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 0);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case 0x01:
			//NRZ + Scramble Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 0);
			AX5043PacketEnableEncodeScramble(radio, 1);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case 0x02:
			//NRZI Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case 0x03:
			//NRZI + Scramble Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 1);
			AX5043PacketEnableEncodeManchester(radio, 0);
			break;
		case 0x04:
			//FM1 Mode
			AX5043PacketEnableEncodeBitInversion(radio, 1);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 1);
			break;
		case 0x05:
			//FM0 Mode
			AX5043PacketEnableEncodeBitInversion(radio, 0);
			AX5043PacketEnableEncodeDifferential(radio, 1);
			AX5043PacketEnableEncodeScramble(radio, 0);
			AX5043PacketEnableEncodeManchester(radio, 1);
			break;
		case 0x06:
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
uint8_t RadioSetFramingMode(uint8_t radio, uint8_t frmMode) {
	//Check limits
	if(frmMode > 2) {
		return 1;
	}

	//Set Framing Mode
	switch(frmMode) {
		case 0x00:
			//Raw Mode
			AX5043PacketSetFrameMode(radio, FrmMode_Raw);
			break;
		case 0x01:
			//HDLC Mode
			AX5043PacketSetFrameMode(radio, FrmMode_HDLC);
			break;
		case 0x02:
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
uint8_t RadioSetModulation(uint8_t radio, uint8_t modulation) {
	//Check limits
	if(modulation < 1 || modulation > 9) {
		return 1;
	}

	//Set Framing Mode
	switch(modulation) {
		case 0x01:
			//AM Modulation
			//Set DAC
			AX5043GPIOSetDACInput(radio, DACInput_TRKAmplitude);
			AX5043GPIOSetDACInputShift(radio, 0x0B);
			AX5043GPIOSetDACOutputMode(radio, 0x00);
			AX5043GPIOSetDACClockDoubling(radio, 0x01);

			//Set Modulation
			AX5043GeneralSetModulation(radio, FM);

			//Set Demodulation for RX Mode
			AX5043RXParamSetIFFrequency(radio, 0x0290);		//~10 kHz
			AX5043RXParamSetDecimation(radio, 0x02);		//~500 kHz
			AX5043RXParamSetRXDatarate(radio, 0x1400);		//~200 kbits/s
			AX5043RXParamSetRXMaximumFrequencyOffset(radio, 0x00);	//Set to 0x00, no AFC
			AX5043RXParamSetCorrectFrequencyOffsetLO(radio, 0x01);

		    //RX Parameter 0
		    AX5043RXParamSetAGCReleaseSpeed0(radio, 0x0E);
			AX5043RXParamSetAGCAttackSpeed0(radio, 0x0E);
		    AX5043RXParamSetAGCTargetAvgMagnitude0(radio, 0x79);	//Target: 192
		    AX5043RXParamSetRXAmplitudeGain0(radio, 0x04);
			AX5043RXParamSetRXAmplitudeAGCJump0(radio, 0x00);
			AX5043RXParamSetRXAmplitudeRecoveryByAverage0(radio, 0x00);
		//	AX5043RXParamSetRXFrequencyGainA0(radio, 0x02);
		//	AX5043RXParamSetRXFrequencyGainB0(radio, 0x1E);
		//	AX5043RXParamSetRXFrequencyGainC0(radio, 0x1F);
		//	AX5043RXParamSetRXFrequencyGainD0(radio, 0x1F);
		//	AX5043RXParamSetRXFrequncyLeak(radio, 0x00);
			AX5043PacketSetGainTimingRecovery0(radio, 0x00, 0x00);
			AX5043PacketSetGainDatarateRecovery0(radio, 0x00, 0x00);
			break;
		case 0x02:
			//FM Modulation
			//Set DAC
			AX5043GPIOSetDACInput(radio, DACInput_TRKFrequency);
			AX5043GPIOSetDACInputShift(radio, 0x0D);
			AX5043GPIOSetDACOutputMode(radio, 0x00);
			AX5043GPIOSetDACClockDoubling(radio, 0x01);

			//Set Modulation
			AX5043GeneralSetModulation(radio, FM);

			//Set Demodulation for RX Mode
			AX5043RXParamSetIFFrequency(radio, 0x0290);		//~10 kHz
			AX5043RXParamSetDecimation(radio, 0x02);		//~500 kHz
			AX5043RXParamSetRXDatarate(radio, 0x1400);		//~200 kbits/s
			AX5043RXParamSetRXMaximumFrequencyOffset(radio, 0xCCCC);	//Set to 50kHz
			AX5043RXParamSetCorrectFrequencyOffsetLO(radio, 0x01);

			//RX Parameter 0
			AX5043RXParamSetAGCReleaseSpeed0(radio, 0x0E);
			AX5043RXParamSetAGCAttackSpeed0(radio, 0x0A);
			AX5043RXParamSetAGCTargetAvgMagnitude0(radio, 0x80);
			AX5043RXParamSetRXFrequencyGainA0(radio, 0x0F);
			AX5043RXParamSetRXFrequencyGainB0(radio, 0x04);
			AX5043RXParamSetRXFrequencyGainC0(radio, 0x1F);
			AX5043RXParamSetRXFrequencyGainD0(radio, 0x08);
			AX5043RXParamSetRXFrequncyLeak(radio, 0x00);
			AX5043PacketSetGainTimingRecovery0(radio, 0x00, 0x00);
			AX5043PacketSetGainDatarateRecovery0(radio, 0x00, 0x00);
			break;
		case 0x03:
			//AFSK Modulation
			AX5043GeneralSetModulation(radio, AFSK);
			break;
		case 0x04:
			//ASK Modulation
			AX5043GeneralSetModulation(radio, ASK);
			break;
		case 0x05:
			//FSK Modulation
			AX5043GeneralSetModulation(radio, FSK);
			break;
		case 0x06:
			//GMSK Modulation
			AX5043GeneralSetModulation(radio, FSK);
			break;
		case 0x07:
			//4-FSK Modulation
			AX5043GeneralSetModulation(radio, FSK4);
			break;
		case 0x08:
			//BPSK Modulation
			AX5043GeneralSetModulation(radio, PSK);
			break;
		case 0x09:
			//QPSK Modulation
			AX5043GeneralSetModulation(radio, OQPSK);
			break;
		default:
			return 1;
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
uint8_t RadioSetOperationMode(uint8_t radio, uint8_t opMode) {
	//Check limits
	if(opMode > 2) {
		return 1;
	}

	//Set Framing Mode
	switch(opMode) {
		case 0x00:
			//OFF/Standby Mode
//			PwrStatus status = AX5043PwrStats(radio);
			AX5043PwrSetPowerMode(radio, PwrMode_Standby);
//			status = AX5043PwrStats(radio);
//			while(status.svmodem != 0x01) {
//				status = AX5043PwrStats(radio);
//			}
			break;
		case 0x01: {
			//RX Mode
//			PwrStatus status = AX5043PwrStats(radio);
			AX5043PwrSetPowerMode(radio, PwrMode_RXEN);
			PwrStatus status = AX5043PwrStats(radio);
			while(status.svmodem != 0x01) {
				status = AX5043PwrStats(radio);
			}
			break;
		}
		case 0x02: {
			//TX Mode
//			PwrStatus status = AX5043PwrStats(radio);
			AX5043PwrSetPowerMode(radio, PwrMode_TXEN);
			PwrStatus status = AX5043PwrStats(radio);
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
	uint8_t decimation = (uint8_t)(FXTAL / ((float)(bandwidth << 4) / 0.221497f));	//For fractional bandwidth of 0.25 nominal, 0.221497 -3dB
	AX5043RXParamSetDecimation(radio, decimation);
	//Set RX IF Frequency to center of RX Bandwidth
	uint16_t ifF = (uint16_t)((bandwidth >> 1) * (1048576.f / RADIO_A_XTAL) + 0.5f);
	AX5043RXParamSetIFFrequency(radio, ifF);

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
