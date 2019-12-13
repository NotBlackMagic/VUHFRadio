#include "ax5043_rxtracking.h"

/**
  * @brief	This function gets the Current datarate tracking value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current datarate tracking value
  */
uint32_t AX5043RXTrackingDatarate(uint8_t interfaceID) {
	uint32_t datarate = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKDATARATE0, &config, 1);
	datarate = (config & TRKDATARATE0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKDATARATE1, &config, 1);
	datarate += (config & TRKDATARATE1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, TRKDATARATE2, &config, 1);
	datarate += (config & TRKDATARATE2_MASK) << 16;
	return datarate;
}

/**
  * @brief	This function gets the Current amplitude tracking value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current amplitude tracking value
  */
uint16_t AX5043RXTrackingAmplitude(uint8_t interfaceID) {
	uint16_t amplitude = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKAMPL0, &config, 1);
	amplitude = (config & TRKAMPL0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKAMPL1, &config, 1);
	amplitude += (config & TRKAMPL1_MASK) << 8;
	return amplitude;
}

/**
  * @brief	This function gets the Current phase  tracking value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current phase  tracking value
  */
uint16_t AX5043RXTrackingPhase(uint8_t interfaceID) {
	uint16_t phase = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKPHASE0, &config, 1);
	phase = (config & TRKPHASE0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKPHASE1, &config, 1);
	phase += (config & TRKPHASE1_MASK) << 8;
	return phase;
}

/**
  * @brief	This function sets the Current RF frequency tracking value
  * @param	interfaceID: Which interface (chip) used
  * @param	trackRFFreq: RF frequency tracking value
  * @return	None
  */
void AX5043RXTrackingSetRFFrequency(uint8_t interfaceID, uint32_t trackRFFreq) {
	uint8_t config;
	config = (trackRFFreq & TRKRFFREQ0_MASK);
	AX5043WriteShortAddress(interfaceID, TRKRFFREQ0, &config, 1);
	config = (trackRFFreq >> 8) & TRKRFFREQ1_MASK;
	AX5043WriteShortAddress(interfaceID, TRKRFFREQ1, &config, 1);
	config = (trackRFFreq >> 16) & TRKRFFREQ2_MASK;
	AX5043WriteShortAddress(interfaceID, TRKRFFREQ2, &config, 1);
}

/**
  * @brief	This function gets the Current RF frequency tracking value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current RF frequency tracking value
  */
uint32_t AX5043RXTrackingGetRFFrequency(uint8_t interfaceID) {
	uint32_t frequency = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKRFFREQ0, &config, 1);
	frequency = (config & TRKRFFREQ0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKRFFREQ1, &config, 1);
	frequency += (config & TRKRFFREQ1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, TRKRFFREQ2, &config, 1);
	frequency += (config & TRKRFFREQ2_MASK) << 16;
	return frequency;
}

/**
  * @brief	This function sets the Current frequency tracking value
  * @param	interfaceID: Which interface (chip) used
  * @param	trackFreq: Frequency tracking value
  * @return	None
  */
void AX5043RXTrackingSetFrequency(uint8_t interfaceID, uint32_t trackFreq) {
	uint8_t config;
	config = (trackFreq & TRKFREQ0_MASK);
	AX5043WriteShortAddress(interfaceID, TRKFREQ0, &config, 1);
	config = (trackFreq >> 8) & TRKFREQ1_MASK;
	AX5043WriteShortAddress(interfaceID, TRKFREQ1, &config, 1);
}

/**
  * @brief	This function gets the Current frequency tracking value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current frequency tracking value
  */
uint16_t AX5043RXTrackingGetFrequency(uint8_t interfaceID) {
	uint16_t frequency = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKFREQ0, &config, 1);
	frequency = (config & TRKFREQ0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKFREQ1, &config, 1);
	frequency += (config & TRKFREQ1_MASK) << 8;
	return frequency;
}

/**
  * @brief	This function gets the Current FSK demodulator value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current FSK demodulator value
  */
uint16_t AX5043RXTrackingFSKDemodulation(uint8_t interfaceID) {
	uint16_t fskDem = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKFSKDEMOD0, &config, 1);
	fskDem = (config & TRKFSKDEMOD0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKFSKDEMOD1, &config, 1);
	fskDem += (config & TRKFSKDEMOD1_MASK) << 8;
	return fskDem;
}

/**
  * @brief	This function gets the Current AFSK demodulator value
  * @param	interfaceID: Which interface (chip) used
  * @return	Current AFSK demodulator value
  */
uint16_t AX5043RXTrackingAFSKDemodulation(uint8_t interfaceID) {
	uint16_t afskDem = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TRKAFSKDEMOD0, &config, 1);
	afskDem = (config & TRKAFSKDEMOD0_MASK);
	AX5043ReadShortAddress(interfaceID, TRKAFSKDEMOD1, &config, 1);
	afskDem += (config & TRKAFSKDEMOD1_MASK) << 8;
	return afskDem;
}

/**
  * @brief	This function resets/clears the Datarate Tracking Register
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043RXTrackingResetDatarate(uint8_t interfaceID) {
	uint8_t config = DTRKRESET_BIT;
	AX5043WriteShortAddress(interfaceID, TRKAMPL0, &config, 1);
}

/**
  * @brief	This function resets/clears the Amplitude Tracking Register
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043RXTrackingResetAmplitude(uint8_t interfaceID) {
	uint8_t config = ATRKRESET_BIT;
	AX5043WriteShortAddress(interfaceID, TRKAMPL0, &config, 1);
}

/**
  * @brief	This function resets/clears the Phase Tracking Register
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043RXTrackingResetPhase(uint8_t interfaceID) {
	uint8_t config = PTRKRESET_BIT;
	AX5043WriteShortAddress(interfaceID, TRKAMPL0, &config, 1);
}

/**
  * @brief	This function resets/clears the RF Frequency Tracking Register
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043RXTrackingResetRFFrequency(uint8_t interfaceID) {
	uint8_t config = RTRKRESET_BIT;
	AX5043WriteShortAddress(interfaceID, TRKAMPL0, &config, 1);
}

/**
  * @brief	This function resets/clears the Frequency Tracking Register
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043RXTrackingResetFrequency(uint8_t interfaceID) {
	uint8_t config = FTRKRESET_BIT;
	AX5043WriteShortAddress(interfaceID, TRKAMPL0, &config, 1);
}
