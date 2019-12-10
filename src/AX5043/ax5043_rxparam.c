#include "ax5043_rxparam.h"

/**
  * @brief	This function sets the IF Frequency, IFFREQ = ((fif * fxtaldiv) / fxtal) * 2^20 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @param	ifFrequency: The IF Frequency
  * @return	None
  */
void AX5043RXParamSetIFFrequency(uint8_t interfaceID, uint16_t ifFrequency) {
	uint8_t config;
	config = (ifFrequency) & IFFREQ0_MASK;
	AX5043WriteLongAddress(interfaceID, IFFREQ0, &config, 1);
	config = (ifFrequency >> 8) & IFFREQ1_MASK;
	AX5043WriteLongAddress(interfaceID, IFFREQ1, &config, 1);
}

/**
  * @brief	This function gets the IF Frequency, IFFREQ = ((fif * fxtaldiv) / fxtal) * 2^20 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Frequency Shape
  */
uint16_t AX5043RXParamGetIFFrequency(uint8_t interfaceID) {
	uint16_t ifFrequency = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, IFFREQ0, &config, 1);
	ifFrequency = (config & IFFREQ0_MASK);
	AX5043ReadLongAddress(interfaceID, IFFREQ1, &config, 1);
	ifFrequency += (config & IFFREQ1_MASK) << 8;
	return ifFrequency;
}

/**
  * @brief	This function sets Decimation, fbaseband = fxtal / (2^4 * fxtaldiv * DECIMATION)
  * @param	interfaceID: Which interface (chip) used
  * @param	decimation: The Decimation Value
  * @return	None
  */
void AX5043RXParamSetDecimation(uint8_t interfaceID, uint8_t decimation) {
	uint8_t config = (decimation & DECIMATION_MASK);
	AX5043WriteLongAddress(interfaceID, DECIMATION, &config, 1);
}

/**
  * @brief	This function gets Decimation, fbaseband = fxtal / (2^4 * fxtaldiv * DECIMATION)
  * @param	interfaceID: Which interface (chip) used
  * @return	The Decimation Value
  */
uint8_t AX5043RXParamGetDecimation(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DECIMATION, &config, 1);
	return (config & DECIMATION_MASK);
}

/**
  * @brief	This function sets the RX Datarate, RXDATARATE = (2^7 * fxtal) / (fxtal * BITRATE * DECIMATION) + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @param	datarate: The RX Datarate
  * @return	None
  */
void AX5043RXParamSetRXDatarate(uint8_t interfaceID, uint32_t datarate) {
	uint8_t config;
	config = (datarate) & RXDATARATE0_MASK;
	AX5043WriteLongAddress(interfaceID, RXDATARATE0, &config, 1);
	config = (datarate >> 8) & RXDATARATE1_MASK;
	AX5043WriteLongAddress(interfaceID, RXDATARATE1, &config, 1);
	config = (datarate >> 16) & RXDATARATE2_MASK;
	AX5043WriteLongAddress(interfaceID, RXDATARATE2, &config, 1);
}

/**
  * @brief	This function gets the RX Datarate, RXDATARATE = (2^7 * fxtal) / (fxtal * BITRATE * DECIMATION) + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @return	The RX Datarate
  */
uint32_t AX5043RXParamGetRXDatarate(uint8_t interfaceID) {
	uint32_t datarate = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXDATARATE0, &config, 1);
	datarate = (config & RXDATARATE0_MASK);
	AX5043ReadLongAddress(interfaceID, RXDATARATE1, &config, 1);
	datarate += (config & RXDATARATE1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, RXDATARATE2, &config, 1);
	datarate += (config & RXDATARATE2_MASK) << 16;
	return datarate;
}

/**
  * @brief	This function sets the Maximum RX Datarate offset tolerated, MAXDROFFSET = (2^7 * fxtal * DBITRATE) / (fxtaldiv * BITRATE^2 * DECIMATION) + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @param	datarate: The Maximum RX Datarate offset tolerated
  * @return	None
  */
void AX5043RXParamSetRXMaximumDatarateOffset(uint8_t interfaceID, uint32_t datarate) {
	uint8_t config;
	config = (datarate) & MAXDROFFSET0_MASK;
	AX5043WriteLongAddress(interfaceID, MAXDROFFSET0, &config, 1);
	config = (datarate >> 8) & MAXDROFFSET1_MASK;
	AX5043WriteLongAddress(interfaceID, MAXDROFFSET1, &config, 1);
	config = (datarate >> 16) & MAXDROFFSET2_MASK;
	AX5043WriteLongAddress(interfaceID, MAXDROFFSET2, &config, 1);
}

/**
  * @brief	This function gets the Maximum RX Datarate offset tolerated, MAXDROFFSET = (2^7 * fxtal * DBITRATE) / (fxtaldiv * BITRATE^2 * DECIMATION) + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Maximum RX Datarate offset tolerated
  */
uint32_t AX5043RXParamGetRXMaximumDatarateOffset(uint8_t interfaceID) {
	uint32_t datarate = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MAXDROFFSET0, &config, 1);
	datarate = (config & MAXDROFFSET0_MASK);
	AX5043ReadLongAddress(interfaceID, MAXDROFFSET1, &config, 1);
	datarate += (config & MAXDROFFSET1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, MAXDROFFSET2, &config, 1);
	datarate += (config & MAXDROFFSET2_MASK) << 16;
	return datarate;
}

/**
  * @brief	This function sets the Maximum RX Frequency offset tolerated, MAXRFOFFSET =  (fcarrier / fxtal) * 2^24 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @param	datarate: The Maximum RX Frequency offset tolerated
  * @return	None
  */
void AX5043RXParamSetRXMaximumFrequencyOffset(uint8_t interfaceID, uint32_t frequency) {
	uint8_t config;
	config = (frequency) & MAXRFOFFSET0_MASK;
	AX5043WriteLongAddress(interfaceID, MAXRFOFFSET0, &config, 1);
	config = (frequency >> 8) & MAXRFOFFSET1_MASK;
	AX5043WriteLongAddress(interfaceID, MAXRFOFFSET1, &config, 1);
	config = (frequency >> 16) & MAXRFOFFSET2_MASK;
	AX5043WriteLongAddress(interfaceID, MAXRFOFFSET2, &config, 1);
}

/**
  * @brief	This function gets the Maximum RX Frequency offset tolerated, MAXRFOFFSET =  (fcarrier / fxtal) * 2^24 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Maximum RX Frequency offset tolerated
  */
uint32_t AX5043RXParamGetRXMaximumFrequencyOffset(uint8_t interfaceID) {
	uint32_t frequency = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MAXRFOFFSET0, &config, 1);
	frequency = (config & MAXRFOFFSET0_MASK);
	AX5043ReadLongAddress(interfaceID, MAXRFOFFSET1, &config, 1);
	frequency += (config & MAXRFOFFSET1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, MAXRFOFFSET2, &config, 1);
	frequency += (config & MAXRFOFFSET2_MASK) << 16;
	return frequency;
}

/**
  * @brief	This function sets where the frequency offset is corrected, at first LO or second
  * @param	interfaceID: Which interface (chip) used
  * @param	lo: 1 -> First LO, 0 -> Second LO
  * @return	None
  */
void AX5043RXParamSetCorrectFrequencyOffsetLO(uint8_t interfaceID, uint8_t lo) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MAXRFOFFSET2, &config, 1);
	config = (config & ~FREQOFFSCORR_MASK) | (lo << 7);
	AX5043WriteLongAddress(interfaceID, MAXRFOFFSET2, &config, 1);
}

/**
  * @brief	This function gets where the frequency offset is corrected, at first LO or second
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> First LO, 0 -> Second LO
  */
uint8_t AX5043RXParamGetCorrectFrequencyOffsetLO(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MAXRFOFFSET2, &config, 1);
	return ((config & FREQOFFSCORR_MASK) >> 7);
}

/**
  * @brief	This function sets the FSK Demodulator Max Deviation, In manual mode: FSKDMAX = 3 * 512 * fdeviation / BAUDRATE
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The FSK Demodulator Max Deviation
  * @return	None
  */
void AX5043RXParamSetRXFSKMaxDeviation(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation) & FSKDMAX0_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDMAX0, &config, 1);
	config = (deviation >> 8) & FSKDMAX1_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDMAX1, &config, 1);
}

/**
  * @brief	This function gets the FSK Demodulator Max Deviation, In manual mode: FSKDMAX = 3 * 512 * fdeviation / BAUDRATE
  * @param	interfaceID: Which interface (chip) used
  * @return	The FSK Demodulator Max Deviation
  */
uint16_t AX5043RXParamGetRXFSKMaxDeviation(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDMAX0, &config, 1);
	deviation = (config & FSKDMAX0_MASK);
	AX5043ReadLongAddress(interfaceID, FSKDMAX1, &config, 1);
	deviation += (config & FSKDMAX1_MASK) << 8;
	return deviation;
}

/**
  * @brief	This function sets the FSK Demodulator Min Deviation, In manual mode: FSKDEVMIN = -3 * 512 * fdeviation / BAUDRATE
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The FSK Demodulator Min Deviation
  * @return	None
  */
void AX5043RXParamSetRXFSKMinDeviation(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation) & FSKDMIN0_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDMIN0, &config, 1);
	config = (deviation >> 8) & FSKDMIN1_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDMIN1, &config, 1);
}

/**
  * @brief	This function gets the FSK Demodulator Min Deviation, In manual mode: FSKDEVMIN = -3 * 512 * fdeviation / BAUDRATE
  * @param	interfaceID: Which interface (chip) used
  * @return	The FSK Demodulator Min Deviation
  */
uint16_t AX5043RXParamGetRXFSKMinDeviation(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDMIN0, &config, 1);
	deviation = (config & FSKDMIN0_MASK);
	AX5043ReadLongAddress(interfaceID, FSKDMIN1, &config, 1);
	deviation += (config & FSKDMIN1_MASK) << 8;
	return deviation;
}

/**
  * @brief	This function sets the AFSK Space (0 Bit) Frequency, In RX: AFSKSPACE = (fafskspace * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskspace * 2^18) / fxtal + 0.5
  * @param	interfaceID: Which interface (chip) used
  * @param	spaceFreq: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetAFSKSpaceFrequency(uint8_t interfaceID, uint16_t spaceFreq) {
	uint8_t config;
	config = (spaceFreq) & AFSKSPACE0_MASK;
	AX5043WriteLongAddress(interfaceID, AFSKSPACE0, &config, 1);
	config = (spaceFreq >> 8) & AFSKSPACE1_MASK;
	AX5043WriteLongAddress(interfaceID, AFSKSPACE1, &config, 1);
}

/**
  * @brief	This function gets the AFSK Space (0 Bit) Frequency, In RX: AFSKSPACE = (fafskspace * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskspace * 2^18) / fxtal + 0.5
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetAFSKSpaceFrequency(uint8_t interfaceID) {
	uint16_t spaceFreq = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AFSKSPACE0, &config, 1);
	spaceFreq = (config & AFSKSPACE0_MASK);
	AX5043ReadLongAddress(interfaceID, AFSKSPACE1, &config, 1);
	spaceFreq += (config & AFSKSPACE1_MASK) << 8;
	return spaceFreq;
}

/**
  * @brief	This function sets the AFSK Mark (1 Bit) Frequency, In RX: AFSKMARK = (fafskmark * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskmark * 2^18) / fxtal + 0.5
  * @param	interfaceID: Which interface (chip) used
  * @param	spaceFreq: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetAFSKMarkFrequency(uint8_t interfaceID, uint16_t spaceFreq) {
	uint8_t config;
	config = (spaceFreq) & AFSKMARK0_MASK;
	AX5043WriteLongAddress(interfaceID, AFSKMARK0, &config, 1);
	config = (spaceFreq >> 8) & AFSKMARK1_MASK;
	AX5043WriteLongAddress(interfaceID, AFSKMARK1, &config, 1);
}

/**
  * @brief	This function gets the AFSK Mark (1 Bit) Frequency, In RX: AFSKMARK = (fafskmark * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskmark * 2^18) / fxtal + 0.5
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetAFSKMarkFrequency(uint8_t interfaceID) {
	uint16_t spaceFreq = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AFSKMARK0, &config, 1);
	spaceFreq = (config & AFSKMARK0_MASK);
	AX5043ReadLongAddress(interfaceID, AFSKMARK1, &config, 1);
	spaceFreq += (config & AFSKMARK1_MASK) << 8;
	return spaceFreq;
}

/**
  * @brief	This function sets the AFSK Detector Bandwidth = 2 * log2(fxtal / (2^5 * BITRATE * fxtaldiv * DECIMATION))
  * @param	interfaceID: Which interface (chip) used
  * @param	detBandwidth: The AFSK Detector Bandwidth
  * @return	None
  */
void AX5043RXParamSetAFSKDetBandwitdh(uint8_t interfaceID, uint8_t detBandwidth) {
	uint8_t config;
	config = (detBandwidth & AFSKSHIFT_MASK);
	AX5043WriteLongAddress(interfaceID, AFSKCTRL, &config, 1);
}

/**
  * @brief	This function gets the AFSK Detector Bandwidth = 2 * log2(fxtal / (2^5 * BITRATE * fxtaldiv * DECIMATION))
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Detector Bandwidth
  */
uint8_t AX5043RXParamGetAFSKDetBandwitdh(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AFSKCTRL, &config, 1);
	return (config & AFSKSHIFT_MASK);
}

/**
  * @brief	This function sets the Amplitude Lowpass Filter. fc = fxtal / (2^5 * pi * fxtaldiv * DECIMATION) * arccos((k^2 + 2k - 2) / (2 * (k - 1)))
  * @param	interfaceID: Which interface (chip) used
  * @param	filter: The Amplitude Lowpass Filter
  * @return	None
  */
void AX5043RXParamSetAmplitudeFilter(uint8_t interfaceID, uint8_t filter) {
	uint8_t config;
	config = (filter & AMPLFILTER_MASK);
	AX5043WriteLongAddress(interfaceID, AMPLFILTER, &config, 1);
}

/**
  * @brief	This function gets the Amplitude Lowpass Filter. fc = fxtal / (2^5 * pi * fxtaldiv * DECIMATION) * arccos((k^2 + 2k - 2) / (2 * (k - 1)))
  * @param	interfaceID: Which interface (chip) used
  * @return	The Amplitude Lowpass Filter
  */
uint8_t AX5043RXParamGetAmplitudeFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLFILTER, &config, 1);
	return (config & AMPLFILTER_MASK);
}

/**
  * @brief	This function sets the Leakiness of the Baseband Frequency Recovery Loop (0000 = off)
  * @param	interfaceID: Which interface (chip) used
  * @param	leakiness: The Leakiness of the Baseband Frequency Recovery Loop
  * @return	None
  */
void AX5043RXParamSetRXFrequncyLeak(uint8_t interfaceID, uint8_t leakiness) {
	uint8_t config;
	config = (leakiness & FREQUENCYLEAK_MASK);
	AX5043WriteLongAddress(interfaceID, FREQUENCYLEAK, &config, 1);
}

/**
  * @brief	This function gets Leakiness of the Baseband Frequency Recovery Loop (0000 = off)
  * @param	interfaceID: Which interface (chip) used
  * @return	The Leakiness of the Baseband Frequency Recovery Loop
  */
uint8_t AX5043RXParamGetRXFrequncyLeak(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQUENCYLEAK, &config, 1);
	return (config & FREQUENCYLEAK_MASK);
}

/**
  * @brief	This function sets the RX Parameter Set Number to be used for initial settling
  * @param	interfaceID: Which interface (chip) used
  * @param	number: RX Parameter Number
  * @return	None
  */
void AX5043RXParamSetRXParameterNumber0(uint8_t interfaceID, uint8_t number) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	config = (config & ~RXPS0_MASK) | (number);
	AX5043WriteLongAddress(interfaceID, RXPARAMSETS, &config, 1);
}

/**
  * @brief	This function gets the RX Parameter Set Number to be used for initial settling
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Number
  */
uint8_t AX5043RXParamGetRXParameterNumber0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	return (config & RXPS0_MASK);
}

/**
  * @brief	This function sets the RX Parameter Set Number to be used after Pattern 1 matched and before Pattern 0 match
  * @param	interfaceID: Which interface (chip) used
  * @param	number: RX Parameter Number
  * @return	None
  */
void AX5043RXParamSetRXParameterNumber1(uint8_t interfaceID, uint8_t number) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	config = (config & ~RXPS1_MASK) | (number << 2);
	AX5043WriteLongAddress(interfaceID, RXPARAMSETS, &config, 1);
}

/**
  * @brief	This function gets the RX Parameter Set Number to be used after Pattern 1 matched and before Pattern 0 match
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Number
  */
uint8_t AX5043RXParamGetRXParameterNumber1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	return ((config & RXPS1_MASK) >> 2);
}

/**
  * @brief	This function sets the RX Parameter Set Number to be used after Pattern 0 matched
  * @param	interfaceID: Which interface (chip) used
  * @param	number: RX Parameter Number
  * @return	None
  */
void AX5043RXParamSetRXParameterNumber2(uint8_t interfaceID, uint8_t number) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	config = (config & ~RXPS2_MASK) | (number << 4);
	AX5043WriteLongAddress(interfaceID, RXPARAMSETS, &config, 1);
}

/**
  * @brief	This function gets the RX Parameter Set Number to be used after Pattern 0 matched
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Number
  */
uint8_t AX5043RXParamGetRXParameterNumber2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	return ((config & RXPS2_MASK) >> 4);
}

/**
  * @brief	This function sets the RX Parameter Set Number to be used after a packet start has been detected
  * @param	interfaceID: Which interface (chip) used
  * @param	number: RX Parameter Number
  * @return	None
  */
void AX5043RXParamSetRXParameterNumber3(uint8_t interfaceID, uint8_t number) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	config = (config & ~RXPS3_MASK) | (number << 6);
	AX5043WriteLongAddress(interfaceID, RXPARAMSETS, &config, 1);
}

/**
  * @brief	This function gets the RX Parameter Set Number to be used after a packet start has been detected
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Number
  */
uint8_t AX5043RXParamGetRXParameterNumber3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMSETS, &config, 1);
	return ((config & RXPS3_MASK) >> 6);
}

/**
  * @brief	This function gets the RX Parameter Set Index (determines which RXPS is used)
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Set Index
  */
uint8_t AX5043RXParamGetRXParameterCurrentIndex(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMCURSET, &config, 1);
	return (config & RXSI_MASK);
}

/**
  * @brief	This function gets the RX Parameter Set Number
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Set Index
  */
uint8_t AX5043RXParamGetRXParameterCurrentNumber(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMCURSET, &config, 1);
	return ((config & RXSN_MASK) >> 2);
}

/**
  * @brief	This function gets the RX Parameter Set Index (special function bit)
  * RXSI Bits:
  * 0xx -> Normal Function (indirection via RXPS)
  * 1x0 -> Coarse AGC
  * 1x1 -> Baseband Offset Acquisition
  * @param	interfaceID: Which interface (chip) used
  * @return	RX Parameter Set Index
  */
uint8_t AX5043RXParamGetRXParameterCurrentIndexSpecial(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RXPARAMCURSET, &config, 1);
	return ((config & RXSISF_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC gain reduction speed, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	attackSpeed: AGC gain reduction speed
  * @return	None
  */
void AX5043RXParamSetAGCAttackSpeed0(uint8_t interfaceID, uint8_t attackSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN0, &config, 1);
	config = (config & ~AGCATTACK0_MASK) | (attackSpeed);
	AX5043WriteLongAddress(interfaceID, AGCGAIN0, &config, 1);
}

/**
  * @brief	This function gets the AGC gain reduction speed, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain reduction speed
  */
uint8_t AX5043RXParamGetAGCAttackSpeed0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN0, &config, 1);
	return (config & AGCATTACK0_MASK);
}

/**
  * @brief	This function sets the AGC gain increase speed, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	releaseSpeed: AGC gain increase speed
  * @return	None
  */
void AX5043RXParamSetAGCReleaseSpeed0(uint8_t interfaceID, uint8_t releaseSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN0, &config, 1);
	config = (config & ~AGCATTACK0_MASK) | (releaseSpeed << 4);
	AX5043WriteLongAddress(interfaceID, AGCGAIN0, &config, 1);
}

/**
  * @brief	This function gets the AGC gain increase speed, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain increase speed
  */
uint8_t AX5043RXParamGetAGCReleaseSpeed0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN0, &config, 1);
	return ((config & AGCATTACK0_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC gain reduction speed, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	attackSpeed: AGC gain reduction speed
  * @return	None
  */
void AX5043RXParamSetAGCAttackSpeed1(uint8_t interfaceID, uint8_t attackSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN1, &config, 1);
	config = (config & ~AGCATTACK1_MASK) | (attackSpeed);
	AX5043WriteLongAddress(interfaceID, AGCGAIN1, &config, 1);
}

/**
  * @brief	This function gets the AGC gain reduction speed, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain reduction speed
  */
uint8_t AX5043RXParamGetAGCAttackSpeed1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN1, &config, 1);
	return (config & AGCATTACK1_MASK);
}

/**
  * @brief	This function sets the AGC gain increase speed, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	releaseSpeed: AGC gain increase speed
  * @return	None
  */
void AX5043RXParamSetAGCReleaseSpeed1(uint8_t interfaceID, uint8_t releaseSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN1, &config, 1);
	config = (config & ~AGCATTACK1_MASK) | (releaseSpeed << 4);
	AX5043WriteLongAddress(interfaceID, AGCGAIN1, &config, 1);
}

/**
  * @brief	This function gets the AGC gain increase speed, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain increase speed
  */
uint8_t AX5043RXParamGetAGCReleaseSpeed1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN1, &config, 1);
	return ((config & AGCATTACK1_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC gain reduction speed, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	attackSpeed: AGC gain reduction speed
  * @return	None
  */
void AX5043RXParamSetAGCAttackSpeed2(uint8_t interfaceID, uint8_t attackSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN2, &config, 1);
	config = (config & ~AGCATTACK2_MASK) | (attackSpeed);
	AX5043WriteLongAddress(interfaceID, AGCGAIN2, &config, 1);
}

/**
  * @brief	This function gets the AGC gain reduction speed, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain reduction speed
  */
uint8_t AX5043RXParamGetAGCAttackSpeed2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN2, &config, 1);
	return (config & AGCATTACK2_MASK);
}

/**
  * @brief	This function sets the AGC gain increase speed, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	releaseSpeed: AGC gain increase speed
  * @return	None
  */
void AX5043RXParamSetAGCReleaseSpeed2(uint8_t interfaceID, uint8_t releaseSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN2, &config, 1);
	config = (config & ~AGCATTACK2_MASK) | (releaseSpeed << 4);
	AX5043WriteLongAddress(interfaceID, AGCGAIN2, &config, 1);
}

/**
  * @brief	This function gets the AGC gain increase speed, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain increase speed
  */
uint8_t AX5043RXParamGetAGCReleaseSpeed2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN2, &config, 1);
	return ((config & AGCATTACK2_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC gain reduction speed, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	attackSpeed: AGC gain reduction speed
  * @return	None
  */
void AX5043RXParamSetAGCAttackSpeed3(uint8_t interfaceID, uint8_t attackSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN3, &config, 1);
	config = (config & ~AGCATTACK3_MASK) | (attackSpeed);
	AX5043WriteLongAddress(interfaceID, AGCGAIN3, &config, 1);
}

/**
  * @brief	This function gets the AGC gain reduction speed, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain reduction speed
  */
uint8_t AX5043RXParamGetAGCAttackSpeed3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN3, &config, 1);
	return (config & AGCATTACK3_MASK);
}

/**
  * @brief	This function sets the AGC gain increase speed, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	releaseSpeed: AGC gain increase speed
  * @return	None
  */
void AX5043RXParamSetAGCReleaseSpeed3(uint8_t interfaceID, uint8_t releaseSpeed) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN3, &config, 1);
	config = (config & ~AGCATTACK3_MASK) | (releaseSpeed << 4);
	AX5043WriteLongAddress(interfaceID, AGCGAIN3, &config, 1);
}

/**
  * @brief	This function gets the AGC gain increase speed, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC gain increase speed
  */
uint8_t AX5043RXParamGetAGCReleaseSpeed3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCGAIN3, &config, 1);
	return ((config & AGCATTACK3_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	target: AGC Target Average Magnitude
  * @return	None
  */
void AX5043RXParamSetAGCTargetAvgMagnitude0(uint8_t interfaceID, uint8_t target) {
	uint8_t config = (target & AGCTARGET0_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET0, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Average Magnitude
  */
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET0, &config, 1);
	return (config & AGCTARGET0_MASK);
}

/**
  * @brief	This function sets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	target: AGC Target Average Magnitude
  * @return	None
  */
void AX5043RXParamSetAGCTargetAvgMagnitude1(uint8_t interfaceID, uint8_t target) {
	uint8_t config = (target & AGCTARGET1_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET1, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Average Magnitude
  */
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET1, &config, 1);
	return (config & AGCTARGET1_MASK);
}

/**
  * @brief	This function sets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	target: AGC Target Average Magnitude
  * @return	None
  */
void AX5043RXParamSetAGCTargetAvgMagnitude2(uint8_t interfaceID, uint8_t target) {
	uint8_t config = (target & AGCTARGET2_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET2, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Average Magnitude
  */
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET2, &config, 1);
	return (config & AGCTARGET2_MASK);
}

/**
  * @brief	This function sets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	target: AGC Target Average Magnitude
  * @return	None
  */
void AX5043RXParamSetAGCTargetAvgMagnitude3(uint8_t interfaceID, uint8_t target) {
	uint8_t config = (target & AGCTARGET3_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET3, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Average Magnitude = 2 * (AGCTARGETx / 16), RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Average Magnitude
  */
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET3, &config, 1);
	return (config & AGCTARGET3_MASK);
}

/**
  * @brief	This function sets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	hysteresis: AGC Target Hysteresis
  * @return	None
  */
void AX5043RXParamSetAGCTargetHysteresis0(uint8_t interfaceID, uint8_t hysteresis) {
	uint8_t config = (hysteresis & AGCAHYST0_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET0, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Hysteresis
  */
uint8_t AX5043RXParamGetAGCTargetHysteresis0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET0, &config, 1);
	return (config & AGCAHYST0_MASK);
}

/**
  * @brief	This function sets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	hysteresis: AGC Target Hysteresis
  * @return	None
  */
void AX5043RXParamSetAGCTargetHysteresis1(uint8_t interfaceID, uint8_t hysteresis) {
	uint8_t config = (hysteresis & AGCAHYST1_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET1, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Hysteresis
  */
uint8_t AX5043RXParamGetAGCTargetHysteresis1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET1, &config, 1);
	return (config & AGCAHYST1_MASK);
}

/**
  * @brief	This function sets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	hysteresis: AGC Target Hysteresis
  * @return	None
  */
void AX5043RXParamSetAGCTargetHysteresis2(uint8_t interfaceID, uint8_t hysteresis) {
	uint8_t config = (hysteresis & AGCAHYST2_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET2, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Hysteresis
  */
uint8_t AX5043RXParamGetAGCTargetHysteresis2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET2, &config, 1);
	return (config & AGCAHYST2_MASK);
}

/**
  * @brief	This function sets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	hysteresis: AGC Target Hysteresis
  * @return	None
  */
void AX5043RXParamSetAGCTargetHysteresis3(uint8_t interfaceID, uint8_t hysteresis) {
	uint8_t config = (hysteresis & AGCAHYST3_MASK);
	AX5043WriteLongAddress(interfaceID, AGCTARGET3, &config, 1);
}

/**
  * @brief	This function gets the AGC Target Hysteresis = (AGCAHYSTx + 1) * 3dB, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Target Hysteresis
  */
uint8_t AX5043RXParamGetAGCTargetHysteresis3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCTARGET3, &config, 1);
	return (config & AGCAHYST3_MASK);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds minimum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMinimumReset0(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX0, &config, 1);
	config = (config & ~AGCMINDA0_MASK) | (threshold);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX0, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds minimum threshold
  */
uint8_t AX5043RXParamGetAGCMinimumReset0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX0, &config, 1);
	return (config & AGCMINDA0_MASK);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds maximum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMaximumReset0(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX0, &config, 1);
	config = (config & ~AGCMAXDA0_MASK) | (threshold << 4);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX0, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds maximum threshold
  */
uint8_t AX5043RXParamGetAGCMaximumReset0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX0, &config, 1);
	return ((config & AGCMAXDA0_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds minimum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMinimumReset1(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX1, &config, 1);
	config = (config & ~AGCMINDA1_MASK) | (threshold);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX1, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds minimum threshold
  */
uint8_t AX5043RXParamGetAGCMinimumReset1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX1, &config, 1);
	return (config & AGCMINDA1_MASK);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds maximum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMaximumReset1(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX1, &config, 1);
	config = (config & ~AGCMAXDA1_MASK) | (threshold << 4);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX1, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds maximum threshold
  */
uint8_t AX5043RXParamGetAGCMaximumReset1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX1, &config, 1);
	return ((config & AGCMAXDA1_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds minimum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMinimumReset2(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX2, &config, 1);
	config = (config & ~AGCMINDA2_MASK) | (threshold);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX2, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds minimum threshold
  */
uint8_t AX5043RXParamGetAGCMinimumReset2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX2, &config, 1);
	return (config & AGCMINDA2_MASK);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds maximum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMaximumReset2(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX2, &config, 1);
	config = (config & ~AGCMAXDA2_MASK) | (threshold << 4);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX2, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds maximum threshold
  */
uint8_t AX5043RXParamGetAGCMaximumReset2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX2, &config, 1);
	return ((config & AGCMAXDA2_MASK) >> 4);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds minimum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMinimumReset3(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX3, &config, 1);
	config = (config & ~AGCMINDA3_MASK) | (threshold);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX3, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds minimum threshold, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds minimum threshold
  */
uint8_t AX5043RXParamGetAGCMinimumReset3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX3, &config, 1);
	return (config & AGCMINDA3_MASK);
}

/**
  * @brief	This function sets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: AGC Reset Value if exceeds maximum threshold
  * @return	None
  */
void AX5043RXParamSetAGCMaximumReset3(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX3, &config, 1);
	config = (config & ~AGCMAXDA3_MASK) | (threshold << 4);
	AX5043WriteLongAddress(interfaceID, AGCMINMAX3, &config, 1);
}

/**
  * @brief	This function gets the AGC Reset Value if exceeds maximum threshold, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Reset Value if exceeds maximum threshold
  */
uint8_t AX5043RXParamGetAGCMaximumReset3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AGCMINMAX3, &config, 1);
	return ((config & AGCMAXDA3_MASK) >> 4);
}

/**
  * @brief	This function sets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa
  * @param	exponent: Gain of the timing recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainTimingRecovery0(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & TIMEGAIN0E_MASK) + ((mantissa << 4) & TIMEGAIN0M_MASK);
	AX5043WriteLongAddress(interfaceID, TIMEGAIN0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa return value
  * @param	exponent: Gain of the timing recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainTimingRecovery0(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TIMEGAIN0, &config, 1);
	*mantissa = (config & TIMEGAIN0E_MASK) >> 4;
	*exponent = (config & TIMEGAIN0M_MASK);
}

/**
  * @brief	This function sets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa
  * @param	exponent: Gain of the timing recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainTimingRecovery1(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & TIMEGAIN1E_MASK) + ((mantissa << 4) & TIMEGAIN1M_MASK);
	AX5043WriteLongAddress(interfaceID, TIMEGAIN1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa return value
  * @param	exponent: Gain of the timing recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainTimingRecovery1(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TIMEGAIN1, &config, 1);
	*mantissa = (config & TIMEGAIN1E_MASK) >> 4;
	*exponent = (config & TIMEGAIN1M_MASK);
}

/**
  * @brief	This function sets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa
  * @param	exponent: Gain of the timing recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainTimingRecovery2(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & TIMEGAIN2E_MASK) + ((mantissa << 4) & TIMEGAIN2M_MASK);
	AX5043WriteLongAddress(interfaceID, TIMEGAIN2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa return value
  * @param	exponent: Gain of the timing recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainTimingRecovery2(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TIMEGAIN2, &config, 1);
	*mantissa = (config & TIMEGAIN2E_MASK) >> 4;
	*exponent = (config & TIMEGAIN2M_MASK);
}

/**
  * @brief	This function sets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa
  * @param	exponent: Gain of the timing recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainTimingRecovery3(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & TIMEGAIN3E_MASK) + ((mantissa << 4) & TIMEGAIN3M_MASK);
	AX5043WriteLongAddress(interfaceID, TIMEGAIN3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the timing recovery loop, TIMEGAINx = arg min| RXDATARATE / TMGCORRFRACx - TIMEGAINxM * 2^TIMEGAINxE|, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the timing recovery loop Mantissa return value
  * @param	exponent: Gain of the timing recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainTimingRecovery3(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TIMEGAIN3, &config, 1);
	*mantissa = (config & TIMEGAIN3E_MASK) >> 4;
	*exponent = (config & TIMEGAIN3M_MASK);
}

/**
  * @brief	This function sets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa
  * @param	exponent: Gain of the datarate recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainDatarateRecovery0(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & DRGAIN0E_MASK) + ((mantissa << 4) & DRGAIN0M_MASK);
	AX5043WriteLongAddress(interfaceID, DRGAIN0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa return value
  * @param	exponent: Gain of the datarate recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainDatarateRecovery0(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DRGAIN0, &config, 1);
	*mantissa = (config & DRGAIN0E_MASK) >> 4;
	*exponent = (config & DRGAIN0M_MASK);
}

/**
  * @brief	This function sets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa
  * @param	exponent: Gain of the datarate recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainDatarateRecovery1(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & DRGAIN1E_MASK) + ((mantissa << 4) & DRGAIN1M_MASK);
	AX5043WriteLongAddress(interfaceID, DRGAIN1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa return value
  * @param	exponent: Gain of the datarate recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainDatarateRecovery1(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DRGAIN1, &config, 1);
	*mantissa = (config & DRGAIN1E_MASK) >> 4;
	*exponent = (config & DRGAIN1M_MASK);
}

/**
  * @brief	This function sets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa
  * @param	exponent: Gain of the datarate recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainDatarateRecovery2(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & DRGAIN2E_MASK) + ((mantissa << 4) & DRGAIN2M_MASK);
	AX5043WriteLongAddress(interfaceID, DRGAIN2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa return value
  * @param	exponent: Gain of the datarate recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainDatarateRecovery2(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DRGAIN2, &config, 1);
	*mantissa = (config & DRGAIN2E_MASK) >> 4;
	*exponent = (config & DRGAIN2M_MASK);
}

/**
  * @brief	This function sets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa
  * @param	exponent: Gain of the datarate recovery loop Exponent
  * @return	None
  */
void AX5043PacketSetGainDatarateRecovery3(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (exponent & DRGAIN3E_MASK) + ((mantissa << 4) & DRGAIN3M_MASK);
	AX5043WriteLongAddress(interfaceID, DRGAIN3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the datarate recovery loop, TIMEGAINx = arg min| RXDATARATE / DRGCORRFRACx - DRGAINxM * 2^DRGAINxE|, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Gain of the datarate recovery loop Mantissa return value
  * @param	exponent: Gain of the datarate recovery loop Exponent return value
  * @return	None
  */
void AX5043PacketGetGainDatarateRecovery3(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DRGAIN3, &config, 1);
	*mantissa = (config & DRGAIN3E_MASK) >> 4;
	*exponent = (config & DRGAIN3M_MASK);
}

/**
  * @brief	This function sets the Gain of the phase recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	phaseGain: The Gain of the phase recovery loop
  * @return	None
  */
void AX5043RXParamSetRXPhaseGain0(uint8_t interfaceID, uint8_t phaseGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN0, &config, 1);
	config = (config & ~PHASEGAIN0_MASK) | (phaseGain);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the phase recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the phase recovery loop
  */
uint8_t AX5043RXParamGetRXPhaseGain0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN0, &config, 1);
	return (config & PHASEGAIN0_MASK);
}

/**
  * @brief	This function sets the Decimation Filter Fractional Bandwidth, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	filter: The Decimation Filter Fractional Bandwidth
  * @return	None
  */
void AX5043RXParamSetRXDecimationFilter0(uint8_t interfaceID, uint8_t filter) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN0, &config, 1);
	config = (config & ~FILTERIDX0_MASK) | (filter << 6);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN0, &config, 1);
}

/**
  * @brief	This function gets the Decimation Filter Fractional Bandwidth, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Decimation Filter Fractional Bandwidth
  */
uint8_t AX5043RXParamGetRXDecimationFilter0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN0, &config, 1);
	return ((config & FILTERIDX0_MASK) >> 6);
}

/**
  * @brief	This function sets the Gain of the phase recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	phaseGain: The Gain of the phase recovery loop
  * @return	None
  */
void AX5043RXParamSetRXPhaseGain1(uint8_t interfaceID, uint8_t phaseGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN1, &config, 1);
	config = (config & ~PHASEGAIN1_MASK) | (phaseGain);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the phase recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the phase recovery loop
  */
uint8_t AX5043RXParamGetRXPhaseGain1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN1, &config, 1);
	return (config & PHASEGAIN1_MASK);
}

/**
  * @brief	This function sets the Decimation Filter Fractional Bandwidth, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	filter: The Decimation Filter Fractional Bandwidth
  * @return	None
  */
void AX5043RXParamSetRXDecimationFilter1(uint8_t interfaceID, uint8_t filter) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN1, &config, 1);
	config = (config & ~FILTERIDX1_MASK) | (filter << 6);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN1, &config, 1);
}

/**
  * @brief	This function gets the Decimation Filter Fractional Bandwidth, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Decimation Filter Fractional Bandwidth
  */
uint8_t AX5043RXParamGetRXDecimationFilter1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN1, &config, 1);
	return ((config & FILTERIDX1_MASK) >> 6);
}

/**
  * @brief	This function sets the Gain of the phase recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	phaseGain: The Gain of the phase recovery loop
  * @return	None
  */
void AX5043RXParamSetRXPhaseGain2(uint8_t interfaceID, uint8_t phaseGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN2, &config, 1);
	config = (config & ~PHASEGAIN2_MASK) | (phaseGain);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the phase recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the phase recovery loop
  */
uint8_t AX5043RXParamGetRXPhaseGain2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN2, &config, 1);
	return (config & PHASEGAIN2_MASK);
}

/**
  * @brief	This function sets the Decimation Filter Fractional Bandwidth, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	filter: The Decimation Filter Fractional Bandwidth
  * @return	None
  */
void AX5043RXParamSetRXDecimationFilter2(uint8_t interfaceID, uint8_t filter) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN2, &config, 1);
	config = (config & ~FILTERIDX2_MASK) | (filter << 6);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN2, &config, 1);
}

/**
  * @brief	This function gets the Decimation Filter Fractional Bandwidth, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Decimation Filter Fractional Bandwidth
  */
uint8_t AX5043RXParamGetRXDecimationFilter2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN2, &config, 1);
	return ((config & FILTERIDX2_MASK) >> 6);
}

/**
  * @brief	This function sets the Gain of the phase recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	phaseGain: The Gain of the phase recovery loop
  * @return	None
  */
void AX5043RXParamSetRXPhaseGain3(uint8_t interfaceID, uint8_t phaseGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN3, &config, 1);
	config = (config & ~PHASEGAIN3_MASK) | (phaseGain);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the phase recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the phase recovery loop
  */
uint8_t AX5043RXParamGetRXPhaseGain3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN3, &config, 1);
	return (config & PHASEGAIN3_MASK);
}

/*
  * @brief	This function sets the Decimation Filter Fractional Bandwidth, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	filter: The Decimation Filter Fractional Bandwidth
  * @return	None
  */
void AX5043RXParamSetRXDecimationFilter3(uint8_t interfaceID, uint8_t filter) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN3, &config, 1);
	config = (config & ~FILTERIDX3_MASK) | (filter << 6);
	AX5043WriteLongAddress(interfaceID, PHASEGAIN3, &config, 1);
}

/**
  * @brief	This function gets the Decimation Filter Fractional Bandwidth, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Decimation Filter Fractional Bandwidth
  */
uint8_t AX5043RXParamGetRXDecimationFilter3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PHASEGAIN3, &config, 1);
	return ((config & FILTERIDX3_MASK) >> 6);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainA0(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	config = (config & ~FREQGAINA0_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINA0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainA0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	return (config & FREQGAINA0_MASK);
}

/*
  * @brief	This function sets that only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetUpdate0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	config = (config & ~FREQAMPLGATE0_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FREQGAINA0, &config, 1);
}

/**
  * @brief	This function gets if only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	return ((config & FREQAMPLGATE0_MASK) >> 4);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x1fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapHalf0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	config = (config & ~FREQHALFMOD0_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, FREQGAINA0, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x1fff to 0x2000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	return ((config & FREQHALFMOD0_MASK) >> 5);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x3fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapFull0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	config = (config & ~FREQMODULO0_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINA0, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x3fff to 0x4000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	return ((config & FREQMODULO0_MASK) >> 6);
}

/*
  * @brief	This function sets limit Frequency Offset to 0x4000...0x3fff, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set limit Frequency Offset to 0x4000...0x3fff
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetLimit0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	config = (config & ~FREQLIM0_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINA0, &config, 1);
}

/**
  * @brief	This function gets if the limit Frequency Offset is 0x4000...0x3fff, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If limit Frequency Offset is 0x4000...0x3fff
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA0, &config, 1);
	return ((config & FREQLIM0_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainA1(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	config = (config & ~FREQGAINA1_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINA1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainA1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	return (config & FREQGAINA1_MASK);
}

/*
  * @brief	This function sets that only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetUpdate1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	config = (config & ~FREQAMPLGATE1_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FREQGAINA1, &config, 1);
}

/**
  * @brief	This function gets if only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	return ((config & FREQAMPLGATE1_MASK) >> 4);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x1fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapHalf1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	config = (config & ~FREQHALFMOD1_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, FREQGAINA1, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x1fff to 0x2000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	return ((config & FREQHALFMOD1_MASK) >> 5);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x3fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapFull1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	config = (config & ~FREQMODULO1_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINA1, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x3fff to 0x4000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	return ((config & FREQMODULO1_MASK) >> 6);
}

/*
  * @brief	This function sets limit Frequency Offset to 0x4000...0x3fff, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set limit Frequency Offset to 0x4000...0x3fff
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetLimit1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	config = (config & ~FREQLIM1_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINA1, &config, 1);
}

/**
  * @brief	This function gets if the limit Frequency Offset is 0x4000...0x3fff, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If limit Frequency Offset is 0x4000...0x3fff
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA1, &config, 1);
	return ((config & FREQLIM1_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainA2(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	config = (config & ~FREQGAINA2_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINA2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainA2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	return (config & FREQGAINA2_MASK);
}

/*
  * @brief	This function sets that only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetUpdate2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	config = (config & ~FREQAMPLGATE2_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FREQGAINA2, &config, 1);
}

/**
  * @brief	This function gets if only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	return ((config & FREQAMPLGATE2_MASK) >> 4);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x1fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapHalf2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	config = (config & ~FREQHALFMOD2_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, FREQGAINA2, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x1fff to 0x2000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	return ((config & FREQHALFMOD2_MASK) >> 5);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x3fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapFull2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	config = (config & ~FREQMODULO2_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINA2, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x3fff to 0x4000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	return ((config & FREQMODULO2_MASK) >> 6);
}

/*
  * @brief	This function sets limit Frequency Offset to 0x4000...0x3fff, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set limit Frequency Offset to 0x4000...0x3fff
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetLimit2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	config = (config & ~FREQLIM2_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINA2, &config, 1);
}

/**
  * @brief	This function gets if the limit Frequency Offset is 0x4000...0x3fff, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If limit Frequency Offset is 0x4000...0x3fff
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA2, &config, 1);
	return ((config & FREQLIM2_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainA3(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	config = (config & ~FREQGAINA3_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINA3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainA3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	return (config & FREQGAINA3_MASK);
}

/*
  * @brief	This function sets that only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetUpdate3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	config = (config & ~FREQAMPLGATE3_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FREQGAINA3, &config, 1);
}

/**
  * @brief	This function gets if only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	Only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	return ((config & FREQAMPLGATE3_MASK) >> 4);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x1fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapHalf3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	config = (config & ~FREQHALFMOD3_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, FREQGAINA3, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x1fff to 0x2000, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x1fff to 0x2000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	return ((config & FREQHALFMOD3_MASK) >> 5);
}

/*
  * @brief	This function sets the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set Frequency offset wraps around from 0x3fff to 0x2000
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetWrapFull3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	config = (config & ~FREQMODULO3_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINA3, &config, 1);
}

/**
  * @brief	This function gets if the Frequency offset wraps around from 0x3fff to 0x4000, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If Frequency offset wraps around from 0x3fff to 0x4000
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	return ((config & FREQMODULO3_MASK) >> 6);
}

/*
  * @brief	This function sets limit Frequency Offset to 0x4000...0x3fff, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Set limit Frequency Offset to 0x4000...0x3fff
  * @return	None
  */
void AX5043RXParamSetRXFrequencyOffsetLimit3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	config = (config & ~FREQLIM3_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINA3, &config, 1);
}

/**
  * @brief	This function gets if the limit Frequency Offset is 0x4000...0x3fff, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If limit Frequency Offset is 0x4000...0x3fff
  */
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINA3, &config, 1);
	return ((config & FREQLIM3_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainB0(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	config = (config & ~FREQGAINB0_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINB0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainB0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	return (config & FREQGAINB0_MASK);
}

/*
  * @brief	This function sets use Average the frequency offset of two consecutive bits, RX Parameter Number 0
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Use Average the frequency offset of two consecutive bits
  * @return	None
  */
void AX5043RXParamSetRXFrequencyAverage2Bits0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	config = (config & ~FREQAVG0_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINB0, &config, 1);
}

/**
  * @brief	This function gets if Average the frequency offset of two consecutive bits is used, RX Parameter Number 0
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @return	If Average the frequency offset of two consecutive bits is used
  */
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	return ((config & FREQAVG0_MASK) >> 6);
}

/*
  * @brief	This function sets if Freeze the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the baseband frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXFrequencyFreeze0(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	config = (config & ~FREQFREEZE0_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINB0, &config, 1);
}

/**
  * @brief	This function gets if Freeze the baseband frequency recovery loop if set, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the baseband frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXFrequencyFreeze0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB0, &config, 1);
	return ((config & FREQFREEZE0_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainB1(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	config = (config & ~FREQGAINB1_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINB1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainB1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	return (config & FREQGAINB1_MASK);
}

/*
  * @brief	This function sets use Average the frequency offset of two consecutive bits, RX Parameter Number 1
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Use Average the frequency offset of two consecutive bits
  * @return	None
  */
void AX5043RXParamSetRXFrequencyAverage2Bits1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	config = (config & ~FREQAVG1_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINB1, &config, 1);
}

/**
  * @brief	This function gets if Average the frequency offset of two consecutive bits is used, RX Parameter Number 1
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @return	If Average the frequency offset of two consecutive bits is used
  */
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	return ((config & FREQAVG1_MASK) >> 6);
}

/*
  * @brief	This function sets if Freeze the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the baseband frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXFrequencyFreeze1(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	config = (config & ~FREQFREEZE1_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINB1, &config, 1);
}

/**
  * @brief	This function gets if Freeze the baseband frequency recovery loop if set, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the baseband frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXFrequencyFreeze1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB1, &config, 1);
	return ((config & FREQFREEZE1_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainB2(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	config = (config & ~FREQGAINB2_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINB2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainB2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	return (config & FREQGAINB2_MASK);
}

/*
  * @brief	This function sets use Average the frequency offset of two consecutive bits, RX Parameter Number 2
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Use Average the frequency offset of two consecutive bits
  * @return	None
  */
void AX5043RXParamSetRXFrequencyAverage2Bits2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	config = (config & ~FREQAVG2_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINB2, &config, 1);
}

/**
  * @brief	This function gets if Average the frequency offset of two consecutive bits is used, RX Parameter Number 2
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @return	If Average the frequency offset of two consecutive bits is used
  */
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	return ((config & FREQAVG2_MASK) >> 6);
}

/*
  * @brief	This function sets if Freeze the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the baseband frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXFrequencyFreeze2(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	config = (config & ~FREQFREEZE2_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINB2, &config, 1);
}

/**
  * @brief	This function gets if Freeze the baseband frequency recovery loop if set, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the baseband frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXFrequencyFreeze2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB2, &config, 1);
	return ((config & FREQFREEZE2_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainB3(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	config = (config & ~FREQGAINB3_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINB3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainB3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	return (config & FREQGAINB3_MASK);
}

/*
  * @brief	This function sets use Average the frequency offset of two consecutive bits, RX Parameter Number 3
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Use Average the frequency offset of two consecutive bits
  * @return	None
  */
void AX5043RXParamSetRXFrequencyAverage2Bits3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	config = (config & ~FREQAVG3_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, FREQGAINB3, &config, 1);
}

/**
  * @brief	This function gets if Average the frequency offset of two consecutive bits is used, RX Parameter Number 3
  * This is useful for 0101 preambles in FSK mode
  * @param	interfaceID: Which interface (chip) used
  * @return	If Average the frequency offset of two consecutive bits is used
  */
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	return ((config & FREQAVG3_MASK) >> 6);
}

/*
  * @brief	This function sets if Freeze the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the baseband frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXFrequencyFreeze3(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	config = (config & ~FREQFREEZE3_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAINB3, &config, 1);
}

/**
  * @brief	This function gets if Freeze the baseband frequency recovery loop if set, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the baseband frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXFrequencyFreeze3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINB3, &config, 1);
	return ((config & FREQFREEZE3_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainC0(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC0, &config, 1);
	config = (config & ~FREQGAINC0_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainC0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC0, &config, 1);
	return (config & FREQGAINC0_MASK);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainC1(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC1, &config, 1);
	config = (config & ~FREQGAINC1_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainC1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC1, &config, 1);
	return (config & FREQGAINC1_MASK);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainC2(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC2, &config, 1);
	config = (config & ~FREQGAINC2_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainC2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC2, &config, 1);
	return (config & FREQGAINC2_MASK);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainC3(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC3, &config, 1);
	config = (config & ~FREQGAINC3_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainC3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAINC3, &config, 1);
	return (config & FREQGAINC3_MASK);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainD0(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND0, &config, 1);
	config = (config & ~FREQGAIND0_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC0, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainD0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND0, &config, 1);
	return (config & FREQGAIND0_MASK);
}

/*
  * @brief	This function sets if Freeze the RF frequency recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the RF frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXRFFrequencyFreeze0(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND0, &config, 1);
	config = (config & ~RFFREQFREEZE0_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAIND0, &config, 1);
}

/**
  * @brief	This function gets if Freeze the RF frequency recovery loop if set, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the RF frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXRFFrequencyFreeze0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND0, &config, 1);
	return ((config & RFFREQFREEZE0_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainD1(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND1, &config, 1);
	config = (config & ~FREQGAIND1_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC1, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainD1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND1, &config, 1);
	return (config & FREQGAIND1_MASK);
}

/*
  * @brief	This function sets if Freeze the RF frequency recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the RF frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXRFFrequencyFreeze1(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND1, &config, 1);
	config = (config & ~RFFREQFREEZE1_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAIND1, &config, 1);
}

/**
  * @brief	This function gets if Freeze the RF frequency recovery loop if set, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the RF frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXRFFrequencyFreeze1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND1, &config, 1);
	return ((config & RFFREQFREEZE1_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainD2(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND2, &config, 1);
	config = (config & ~FREQGAIND2_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC2, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainD2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND2, &config, 1);
	return (config & FREQGAIND2_MASK);
}

/**
  * @brief	This function sets if Freeze the RF frequency recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the RF frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXRFFrequencyFreeze2(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND2, &config, 1);
	config = (config & ~RFFREQFREEZE2_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAIND2, &config, 1);
}

/**
  * @brief	This function gets if Freeze the RF frequency recovery loop if set, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the RF frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXRFFrequencyFreeze2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND2, &config, 1);
	return ((config & RFFREQFREEZE2_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freqGain: The Gain of the baseband frequency recovery loop
  * @return	None
  */
void AX5043RXParamSetRXFrequencyGainD3(uint8_t interfaceID, uint8_t freqGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND3, &config, 1);
	config = (config & ~FREQGAIND3_MASK) | (freqGain);
	AX5043WriteLongAddress(interfaceID, FREQGAINC3, &config, 1);
}

/**
  * @brief	This function gets the Gain of the baseband frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the baseband frequency recovery loop
  */
uint8_t AX5043RXParamGetRXFrequencyGainD3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND3, &config, 1);
	return (config & FREQGAIND0_MASK);
}

/*
  * @brief	This function sets if Freeze the RF frequency recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	freeze: Freeze the RF frequency recovery loop if set
  * @return	None
  */
void AX5043RXParamSetRXRFFrequencyFreeze3(uint8_t interfaceID, uint8_t freeze) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND3, &config, 1);
	config = (config & ~RFFREQFREEZE3_MASK) | (freeze << 7);
	AX5043WriteLongAddress(interfaceID, FREQGAIND3, &config, 1);
}

/**
  * @brief	This function gets if Freeze the RF frequency recovery loop if set, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If Freeze the RF frequency recovery loop if set is used
  */
uint8_t AX5043RXParamGetRXRFFrequencyFreeze3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQGAIND3, &config, 1);
	return ((config & RFFREQFREEZE3_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the amplitude recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	ampGain: The Gain of the amplitude recovery loop
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeGain0(uint8_t interfaceID, uint8_t ampGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	config = (config & ~AMPLGAIN0_MASK) | (ampGain);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN0, &config, 1);
}

/**
  * @brief	This function gets Gain of the amplitude recovery loop, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the amplitude recovery loop
  */
uint8_t AX5043RXParamGetRXAmplitudeGain0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	return (config & AMPLGAIN0_MASK);
}

/*
  * @brief	This function sets if try to correct the amplitude register when AGC jumps, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Try to correct the amplitude register when AGC jumps
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeAGCJump0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	config = (config & ~AMPLAGC0_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN0, &config, 1);
}

/**
  * @brief	This function gets if try to correct the amplitude register when AGC jumps is enabled, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	If try to correct the amplitude register when AGC jumps
  */
uint8_t AX5043RXParamGetRXAmplitudeAGCJump0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	return ((config & AMPLAGC0_MASK) >> 6);
}

/*
  * @brief	This function sets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	byAverage: 0 -> Amplitude recovery by peak detector, 1 -> By average
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeRecoveryByAverage0(uint8_t interfaceID, uint8_t byAverage) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	config = (config & ~AMPLAGC0_MASK) | (byAverage << 7);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN0, &config, 1);
}

/**
  * @brief	This function gets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Amplitude recovery by peak detector, 1 -> By average
  */
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN0, &config, 1);
	return ((config & AMPLAGC0_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the amplitude recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	ampGain: The Gain of the amplitude recovery loop
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeGain1(uint8_t interfaceID, uint8_t ampGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	config = (config & ~AMPLGAIN1_MASK) | (ampGain);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN1, &config, 1);
}

/**
  * @brief	This function gets Gain of the amplitude recovery loop, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the amplitude recovery loop
  */
uint8_t AX5043RXParamGetRXAmplitudeGain1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	return (config & AMPLGAIN1_MASK);
}

/*
  * @brief	This function sets if try to correct the amplitude register when AGC jumps, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Try to correct the amplitude register when AGC jumps
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeAGCJump1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	config = (config & ~AMPLAGC1_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN1, &config, 1);
}

/**
  * @brief	This function gets if try to correct the amplitude register when AGC jumps is enabled, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	If try to correct the amplitude register when AGC jumps
  */
uint8_t AX5043RXParamGetRXAmplitudeAGCJump1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	return ((config & AMPLAGC1_MASK) >> 6);
}

/*
  * @brief	This function sets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	byAverage: 0 -> Amplitude recovery by peak detector, 1 -> By average
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeRecoveryByAverage1(uint8_t interfaceID, uint8_t byAverage) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	config = (config & ~AMPLAGC1_MASK) | (byAverage << 7);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN1, &config, 1);
}

/**
  * @brief	This function gets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Amplitude recovery by peak detector, 1 -> By average
  */
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN1, &config, 1);
	return ((config & AMPLAGC1_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the amplitude recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	ampGain: The Gain of the amplitude recovery loop
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeGain2(uint8_t interfaceID, uint8_t ampGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	config = (config & ~AMPLGAIN2_MASK) | (ampGain);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN2, &config, 1);
}

/**
  * @brief	This function gets Gain of the amplitude recovery loop, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the amplitude recovery loop
  */
uint8_t AX5043RXParamGetRXAmplitudeGain2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	return (config & AMPLGAIN2_MASK);
}

/*
  * @brief	This function sets if try to correct the amplitude register when AGC jumps, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Try to correct the amplitude register when AGC jumps
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeAGCJump2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	config = (config & ~AMPLAGC2_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN2, &config, 1);
}

/**
  * @brief	This function gets if try to correct the amplitude register when AGC jumps is enabled, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	If try to correct the amplitude register when AGC jumps
  */
uint8_t AX5043RXParamGetRXAmplitudeAGCJump2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	return ((config & AMPLAGC2_MASK) >> 6);
}

/*
  * @brief	This function sets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	byAverage: 0 -> Amplitude recovery by peak detector, 1 -> By average
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeRecoveryByAverage2(uint8_t interfaceID, uint8_t byAverage) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	config = (config & ~AMPLAGC2_MASK) | (byAverage << 7);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN2, &config, 1);
}

/**
  * @brief	This function gets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Amplitude recovery by peak detector, 1 -> By average
  */
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN2, &config, 1);
	return ((config & AMPLAGC2_MASK) >> 7);
}

/*
  * @brief	This function sets the Gain of the amplitude recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	ampGain: The Gain of the amplitude recovery loop
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeGain3(uint8_t interfaceID, uint8_t ampGain) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	config = (config & ~AMPLGAIN3_MASK) | (ampGain);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN3, &config, 1);
}

/**
  * @brief	This function gets Gain of the amplitude recovery loop, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Gain of the amplitude recovery loop
  */
uint8_t AX5043RXParamGetRXAmplitudeGain3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	return (config & AMPLGAIN3_MASK);
}

/*
  * @brief	This function sets if try to correct the amplitude register when AGC jumps, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Try to correct the amplitude register when AGC jumps
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeAGCJump3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	config = (config & ~AMPLAGC3_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN3, &config, 1);
}

/**
  * @brief	This function gets if try to correct the amplitude register when AGC jumps is enabled, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	If try to correct the amplitude register when AGC jumps
  */
uint8_t AX5043RXParamGetRXAmplitudeAGCJump3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	return ((config & AMPLAGC3_MASK) >> 6);
}

/*
  * @brief	This function sets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	byAverage: 0 -> Amplitude recovery by peak detector, 1 -> By average
  * @return	None
  */
void AX5043RXParamSetRXAmplitudeRecoveryByAverage3(uint8_t interfaceID, uint8_t byAverage) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	config = (config & ~AMPLAGC3_MASK) | (byAverage << 7);
	AX5043WriteLongAddress(interfaceID, AMPLGAIN3, &config, 1);
}

/**
  * @brief	This function gets if Amplitude is recovered by peak detector (0) or average (1), RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Amplitude recovery by peak detector, 1 -> By average
  */
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, AMPLGAIN3, &config, 1);
	return ((config & AMPLAGC3_MASK) >> 7);
}

/**
  * @brief	This function sets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetRXFrequencyDeviation0(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation) & FREQDEV00_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV00, &config, 1);
	config = (deviation >> 8) & FREQDEV01_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV10, &config, 1);
}

/**
  * @brief	This function gets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetRXFrequencyDeviation0(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQDEV00, &config, 1);
	deviation = (config & FREQDEV00_MASK);
	AX5043ReadLongAddress(interfaceID, FREQDEV10, &config, 1);
	deviation += (config & FREQDEV01_MASK) << 8;
	return deviation;
}

/**
  * @brief	This function sets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetRXFrequencyDeviation1(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation) & FREQDEV01_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV01, &config, 1);
	config = (deviation >> 8) & FREQDEV11_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV11, &config, 1);
}

/**
  * @brief	This function gets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetRXFrequencyDeviation1(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQDEV01, &config, 1);
	deviation = (config & FREQDEV01_MASK);
	AX5043ReadLongAddress(interfaceID, FREQDEV11, &config, 1);
	deviation += (config & FREQDEV11_MASK) << 8;
	return deviation;
}

/**
  * @brief	This function sets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetRXFrequencyDeviation2(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation & FREQDEV02_MASK);
	AX5043WriteLongAddress(interfaceID, FREQDEV02, &config, 1);
	config = (deviation >> 8) & FREQDEV12_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV12, &config, 1);
}

/**
  * @brief	This function gets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetRXFrequencyDeviation2(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQDEV02, &config, 1);
	deviation = (config & FREQDEV02_MASK);
	AX5043ReadLongAddress(interfaceID, FREQDEV12, &config, 1);
	deviation += (config & FREQDEV12_MASK) << 8;
	return deviation;
}

/**
  * @brief	This function sets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	deviation: The AFSK Space (0 Bit) Frequency
  * @return	None
  */
void AX5043RXParamSetRXFrequencyDeviation3(uint8_t interfaceID, uint16_t deviation) {
	uint8_t config;
	config = (deviation & FREQDEV03_MASK);
	AX5043WriteLongAddress(interfaceID, FREQDEV03, &config, 1);
	config = (deviation >> 8) & FREQDEV13_MASK;
	AX5043WriteLongAddress(interfaceID, FREQDEV13, &config, 1);
}

/**
  * @brief	This function gets the Receiver Frequency Deviation, FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The AFSK Space (0 Bit) Frequency
  */
uint16_t AX5043RXParamGetRXFrequencyDeviation3(uint8_t interfaceID) {
	uint16_t deviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FREQDEV03, &config, 1);
	deviation = (config & FREQDEV03_MASK);
	AX5043ReadLongAddress(interfaceID, FREQDEV13, &config, 1);
	deviation += (config & FREQDEV13_MASK) << 8;
	return deviation;
}

/*
  * @brief	This function sets the Deviation Decay, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	decay: The Deviation Decay
  * @return	None
  */
void AX5043RXParamSetDeviationDecay0(uint8_t interfaceID, uint8_t decay) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK0, &config, 1);
	config = (config & ~DEVDECAY0_MASK) | (decay);
	AX5043WriteLongAddress(interfaceID, FOURFSK0, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetDeviationDecay0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK0, &config, 1);
	return (config & DEVDECAY0_MASK);
}

/*
  * @brief	This function enables the Deviation Update, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: The Deviation Decay
  * @return	None
  */
void AX5043RXParamEnableDeviationUpdate0(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK0, &config, 1);
	config = (config & ~DEVDECAY0_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FOURFSK0, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK0, &config, 1);
	return ((config & DEVDECAY0_MASK) >> 4);
}

/*
  * @brief	This function sets the Deviation Decay, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	decay: The Deviation Decay
  * @return	None
  */
void AX5043RXParamSetDeviationDecay1(uint8_t interfaceID, uint8_t decay) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK1, &config, 1);
	config = (config & ~DEVDECAY1_MASK) | (decay);
	AX5043WriteLongAddress(interfaceID, FOURFSK1, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetDeviationDecay1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK1, &config, 1);
	return (config & DEVDECAY1_MASK);
}

/*
  * @brief	This function enables the Deviation Update, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: The Deviation Decay
  * @return	None
  */
void AX5043RXParamEnableDeviationUpdate1(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK1, &config, 1);
	config = (config & ~DEVDECAY1_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FOURFSK1, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK1, &config, 1);
	return ((config & DEVDECAY1_MASK) >> 4);
}

/*
  * @brief	This function sets the Deviation Decay, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	decay: The Deviation Decay
  * @return	None
  */
void AX5043RXParamSetDeviationDecay2(uint8_t interfaceID, uint8_t decay) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK2, &config, 1);
	config = (config & ~DEVDECAY2_MASK) | (decay);
	AX5043WriteLongAddress(interfaceID, FOURFSK2, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetDeviationDecay2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK2, &config, 1);
	return (config & DEVDECAY2_MASK);
}

/*
  * @brief	This function enables the Deviation Update, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: The Deviation Decay
  * @return	None
  */
void AX5043RXParamEnableDeviationUpdate2(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK2, &config, 1);
	config = (config & ~DEVDECAY2_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FOURFSK2, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK2, &config, 1);
	return ((config & DEVDECAY2_MASK) >> 4);
}

/*
  * @brief	This function sets the Deviation Decay, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	decay: The Deviation Decay
  * @return	None
  */
void AX5043RXParamSetDeviationDecay3(uint8_t interfaceID, uint8_t decay) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK3, &config, 1);
	config = (config & ~DEVDECAY3_MASK) | (decay);
	AX5043WriteLongAddress(interfaceID, FOURFSK3, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetDeviationDecay3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK3, &config, 1);
	return (config & DEVDECAY3_MASK);
}

/*
  * @brief	This function enables the Deviation Update, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: The Deviation Decay
  * @return	None
  */
void AX5043RXParamEnableDeviationUpdate3(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK3, &config, 1);
	config = (config & ~DEVDECAY3_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FOURFSK3, &config, 1);
}

/**
  * @brief	This function gets the Deviation Decay, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Deviation Decay
  */
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FOURFSK3, &config, 1);
	return ((config & DEVDECAY3_MASK) >> 4);
}

/*
  * @brief	This function set Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES0, &config, 1);
	config = (config & ~RESINTA0_MASK) | (resistor);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES0, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES0, &config, 1);
	return (config & RESINTA0_MASK);
}

/*
  * @brief	This function set Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES0, &config, 1);
	config = (config & ~RESINTB0_MASK) | (resistor << 4);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES0, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES0, &config, 1);
	return ((config & RESINTB0_MASK) >> 4);
}

/*
  * @brief	This function set Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES1, &config, 1);
	config = (config & ~RESINTA1_MASK) | (resistor);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES1, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES1, &config, 1);
	return (config & RESINTA1_MASK);
}

/*
  * @brief	This function set Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES1, &config, 1);
	config = (config & ~RESINTB1_MASK) | (resistor << 4);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES1, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 1
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES1, &config, 1);
	return ((config & RESINTB1_MASK) >> 4);
}

/*
  * @brief	This function set Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes2(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES2, &config, 1);
	config = (config & ~RESINTA2_MASK) | (resistor);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES2, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES2, &config, 1);
	return (config & RESINTA2_MASK);
}

/*
  * @brief	This function set Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes2(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES2, &config, 1);
	config = (config & ~RESINTB2_MASK) | (resistor << 4);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES2, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes2(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES2, &config, 1);
	return ((config & RESINTB2_MASK) >> 4);
}

/*
  * @brief	This function set Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES3, &config, 1);
	config = (config & ~RESINTA3_MASK) | (resistor);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES3, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block A Offset Compensation Resistors, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES3, &config, 1);
	return (config & RESINTA3_MASK);
}

/*
  * @brief	This function set Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @param	resistor: The Baseband Gain Block A Offset Compensation Resistors
  * @return	None
  */
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(uint8_t interfaceID, uint8_t resistor) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES3, &config, 1);
	config = (config & ~RESINTB3_MASK) | (resistor << 4);
	AX5043WriteLongAddress(interfaceID, BBOFFSRES3, &config, 1);
}

/**
  * @brief	This function gets Baseband Gain Block B Offset Compensation Resistors, RX Parameter Number 3
  * @param	interfaceID: Which interface (chip) used
  * @return	The Baseband Gain Block A Offset Compensation Resistors
  */
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes3(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSRES3, &config, 1);
	return ((config & RESINTB3_MASK) >> 4);
}
