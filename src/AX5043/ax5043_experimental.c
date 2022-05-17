#include "ax5043_experimental.h"

/**
  * @brief	This function sets the GPADC Pin Multiplexer
  * @param	interfaceID: Which interface (chip) used
  * @param	gpadcMux: What function is connected to the GPADC pins
  * @return	None
  */
void AX5043ExperimentalSetGPADCMux(uint8_t interfaceID, GPADCSourceSelection gpadcMux) {
	uint8_t config = (config & ~TMBOX_MASK) | gpadcMux;
	AX5043WriteLongAddress(interfaceID, TMMUX, &config, 1);
}

/**
  * @brief	This function gets the GPADC Pin Multiplexer configuration
  * @param	interfaceID: Which interface (chip) used
  * @return	GPADCSourceSelection: What function is connected to the GPADC pins
  */
GPADCSourceSelection AX5043ExperimentalGetGPADCMux(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMMUX, &config, 1);
	return (GPADCSourceSelection)(config & TMBOX_MASK);
}

/**
  * @brief	This function enables the baseband filter output on detector/auxiliary bus
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable baseband filter output
  * @return	None
  */
void AX5043ExperimentalEnableBasebandFilterOutput(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	config = (config & ~AUXEN_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, BBDETECTOR0, &config, 1);
}

/**
  * @brief	This function gets if the baseband filter output on detector/auxiliary bus is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the baseband filter output is enabled
  */
uint8_t AX5043ExperimentalIsEnabledBasebandFilterOutput(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	return ((config & AUXEN_MASK) >> 3);
}

/**
  * @brief	This function enables the baseband detector
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable baseband detector
  * @return	None
  */
void AX5043ExperimentalEnableBasebandDetector(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	config = (config & ~DETCOMPEN_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, BBDETECTOR0, &config, 1);
}

/**
  * @brief	This function gets if the baseband detector is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the baseband detector is enabled
  */
uint8_t AX5043ExperimentalIsEnabledBasebandDetector(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	return ((config & DETCOMPEN_MASK) >> 4);
}

/**
  * @brief	This function enables the baseband detector output driver amplifier
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable baseband detector output driver amplifier
  * @return	None
  */
void AX5043ExperimentalEnableBasebandDetectorOutputDriver(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	config = (config & ~DETBUFEN_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, BBDETECTOR0, &config, 1);
}

/**
  * @brief	This function gets if the baseband detector output driver amplifier is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the baseband detector output driver amplifier is enabled
  */
uint8_t AX5043ExperimentalIsEnabledBasebandDetectorOutputDriver(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	return ((config & DETBUFEN_MASK) >> 5);
}

/**
  * @brief	This function gets the baseband I comparator state
  * @param	interfaceID: Which interface (chip) used
  * @return	If the baseband I comparator is set or not
  */
uint8_t AX5043ExperimentalGetBasebandIComparatorState(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	return ((config & BBCOMPI_MASK) >> 6);
}

/**
  * @brief	This function gets the baseband Q comparator state
  * @param	interfaceID: Which interface (chip) used
  * @return	If the baseband Q comparator is set or not
  */
uint8_t AX5043ExperimentalGetBasebandQComparatorState(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBDETECTOR0, &config, 1);
	return ((config & BBCOMPQ_MASK) >> 7);
}

/**
  * @brief	This function gets the DSPMode shift register value (when DSPMode is in SPI mode)
  * @param	interfaceID: Which interface (chip) used
  * @return	DSPMode shift register value
  */
uint8_t AX5043ExperimentalGetDSPModeShiftRegisterValue(uint8_t interfaceID) {
	uint8_t value = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, DSPMODESHREG, &config, 1);
	value = (config & DSPMODESHREG_MASK);
	return value;
}

/**
  * @brief	This function sets the Sync Source
  * @param	interfaceID: Which interface (chip) used
  * @param	source: What sync source should be used
  * @return	None
  */
void AX5043ExperimentalSetSyncSource(uint8_t interfaceID, SyncSourceSelection source) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	config = (config & ~SYNCSOURCE_MASK) | (source);
	AX5043WriteLongAddress(interfaceID, DSPMODECFG, &config, 1);
}

/**
  * @brief	This function gets the Sync Source
  * @param	interfaceID: Which interface (chip) used
  * @return	SyncSourceSelection: Which sync source is being used
  */
SyncSourceSelection AX5043ExperimentalGetSyncSource(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	return (SyncSourceSelection)(config & SYNCSOURCE_MASK);
}

/**
  * @brief	This function enables the DSPMode over SPI, enables access to the shift register (DSPMODESHREG) over SPI
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable DSPMode over SPI
  * @return	None
  */
void AX5043ExperimentalEnableDSPModeSPI(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	config = (config & ~DSP_SPI_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, DSPMODECFG, &config, 1);
}

/**
  * @brief	This function gets if the DSPMode over SPI is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the DSPMode over SPI is enabled
  */
uint8_t AX5043ExperimentalIsEnabledDSPModeSPI(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	return ((config & DSP_SPI_MASK) >> 6);
}

/**
  * @brief	This function enables the FSYNC delay: If set to 0, FSYNC leads the first data bit by one bit. If set to 1, FSYNC coincides with the first data bit
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable FSYNC delay
  * @return	None
  */
void AX5043ExperimentalEnableFSYNCDelay(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	config = (config & ~FSYNC_DLY_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, DSPMODECFG, &config, 1);
}

/**
  * @brief	This function gets if the FSYNC delay is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the FSYNC delay is enabled
  */
uint8_t AX5043ExperimentalIsEnabledFSYNCDelay(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODECFG, &config, 1);
	return ((config & FSYNC_DLY_MASK) >> 7);
}

/**
  * @brief	This function sets what data should be output over the DSPmode interface in receive mode, which data should be skipped
  * @param	interfaceID: Which interface (chip) used
  * @param	skippedData: What data should be skipped
  * @return	None
  */
void AX5043ExperimentalSetDSPModeSkipData(uint8_t interfaceID, DSPModeSkip skippedData) {
	uint8_t config = skippedData.raw & DSPMODESKIP0_MASK;
	AX5043WriteLongAddress(interfaceID, DSPMODESKIP0, &config, 1);
	config = (skippedData.raw >> 8) & DSPMODESKIP1_MASK;
	AX5043WriteLongAddress(interfaceID, DSPMODESKIP1, &config, 1);
}

/**
  * @brief	This function gets what data should be output over the DSPmode interface in receive mode, which data should be skipped
  * @param	interfaceID: Which interface (chip) used
  * @return	DSPModeSkip: What data are skipped
  */
DSPModeSkip AX5043ExperimentalGetDSPModeSkipData(uint8_t interfaceID) {
	DSPModeSkip skippedData;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DSPMODESKIP0, &config, 1);
	skippedData.raw = config & DSPMODESKIP0_MASK;
	AX5043ReadLongAddress(interfaceID, DSPMODESKIP1, &config, 1);
	skippedData.raw += (config & DSPMODESKIP1_MASK) << 8;
	return skippedData;
}
