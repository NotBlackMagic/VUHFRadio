#include "ax5043_lposc.h"

/**
  * @brief	This function Enables the Low Power Oscillator
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable Low Power Oscillator
  * @return	None
  */
void AX5043LPOSCEnable(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_ENA_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the Low Power Oscillator is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the Low Power Oscillator is Enabled
  */
uint8_t AX5043LPOSCIsEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return (config & LPOSC_ENA_MASK);
}

/**
  * @brief	This function Selects the LPOSC Frequency
  * @param	interfaceID: Which interface (chip) used
  * @param	fast: If 1 is in fast mode, 10.24 kHz, if 0 in normal mode, 640 Hz
  * @return	None
  */
void AX5043LPOSCSetFrequncy(uint8_t interfaceID, uint8_t fast) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_FAST_MASK) | (fast << 1);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets the LPOSC Frequency
  * @param	interfaceID: Which interface (chip) used
  * @return	1 is in fast mode, 10.24 kHz, if 0 in normal mode, 640 Hz
  */
uint8_t AX5043LPOSCGetFrequncy(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_FAST_MASK) >> 1);
}

/**
  * @brief	This function Enable LPOSC interrupt on Rising Edge
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable LPOSC interrupt on Rising Edge
  * @return	None
  */
void AX5043LPOSCEnableInterrruptRising(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_IRQR_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the LPOSC interrupt on Rising Edge is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the LPOSC interrupt on Rising Edge is Enabled
  */
uint8_t AX5043LPOSCIsEnabledInterruptRising(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_IRQR_MASK) >> 2);
}

/**
  * @brief	This function Enable LPOSC interrupt on Falling Edge
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable LPOSC interrupt on Falling Edge
  * @return	None
  */
void AX5043LPOSCEnableInterrruptFalling(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_IRQF_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the LPOSC interrupt on Falling Edge is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the LPOSC interrupt on Falling Edge is Enabled
  */
uint8_t AX5043LPOSCIsEnabledInterruptFalling(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_IRQF_MASK) >> 3);
}

/**
  * @brief	This function Enable LPOSC Calibration on Falling Edge
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable LPOSC Calibration on Falling Edge
  * @return	None
  */
void AX5043LPOSCEnableCalibrationFalling(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_CALIBF_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the LPOSC Calibration on Falling Edge is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the LPOSC Calibration on Falling Edge is Enabled
  */
uint8_t AX5043LPOSCIsEnabledCalibrationFalling(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_CALIBF_MASK) >> 4);
}

/**
  * @brief	This function Enable LPOSC Calibration on Rising Edge
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable LPOSC Calibration on Rising Edge
  * @return	None
  */
void AX5043LPOSCEnableCalibrationRising(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_CALIBR_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the LPOSC Calibration on Rising Edge is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If the LPOSC Calibration on Rising Edge is Enabled
  */
uint8_t AX5043LPOSCIsEnabledCalibrationRising(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_CALIBR_MASK) >> 5);
}

/**
  * @brief	This function Enables the LPOSC Frequency doubling
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable LPOSC Oscillator Frequency doubling
  * @return	None
  */
void AX5043LPOSCEnableFrequencyDoubling(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_OSC_DOUBLE_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if the LPOSC Calibration Frequency Doubling
  * @param	interfaceID: Which interface (chip) used
  * @return	If the LPOSC Frequency Doubling is Enabled
  */
uint8_t AX5043LPOSCIsEnabledFrequencyDoubling(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_OSC_DOUBLE_MASK) >> 6);
}

/**
  * @brief	This function Inverts the LPOSC Clock Signal
  * @param	interfaceID: Which interface (chip) used
  * @param	invert: Inverts the LPOSC Clock Signal
  * @return	None
  */
void AX5043LPOSCInvertClock(uint8_t interfaceID, uint8_t invert) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	config = (config & ~LPOSC_OSC_INV_MASK) | (invert << 7);
	AX5043WriteLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
}

/**
  * @brief	This function gets if LPOSC Clock is inverted
  * @param	interfaceID: Which interface (chip) used
  * @return	If LPOSC Clock is inverted
  */
uint8_t AX5043LPOSCIsInvertClock(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &config, 1);
	return ((config & LPOSC_OSC_INV_MASK) >> 7);
}

/**
  * @brief	This function gets the LPOSC Status
  * @param	interfaceID: Which interface (chip) used
  * @return	The LPOSC Status Bits
  */
LPOscStatus AX5043LPOSCStatus(uint8_t interfaceID) {
	LPOscStatus status;
	AX5043ReadLongAddress(interfaceID, LPOSCCONFIG, &status.raw, 1);
	return status;
}

/**
  * @brief	This function sets the LPOSC Filter
  * @param	interfaceID: Which interface (chip) used
  * @param	kFilter: Filter Value kFilter = (21333 * 2^20) / fxtal
  * @return	None
  */
void AX5043LPOSCSetFilter(uint8_t interfaceID, uint16_t kFilter) {
	uint8_t config;
	config = (kFilter) & LPOSCKFILT0_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCKFILT0, &config, 1);
	config = (kFilter >> 8) & LPOSCKFILT1_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCKFILT1, &config, 1);
}

/**
  * @brief	This function gets the LPOSC Filter
  * @param	interfaceID: Which interface (chip) used
  * @return	Filter Value kFilter in (21333 * 2^20) / fxtal
  */
uint16_t AX5043LPOSCGetFilter(uint8_t interfaceID) {
	uint16_t freqDivider = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCKFILT0, &config, 1);
	freqDivider = (config & LPOSCKFILT0_MASK);
	AX5043ReadLongAddress(interfaceID, LPOSCKFILT1, &config, 1);
	freqDivider += (config & LPOSCKFILT1_MASK) << 8;
	return freqDivider;
}

/**
  * @brief	This function sets the LPOSC Reference Frequency Divider
  * @param	interfaceID: Which interface (chip) used
  * @param	freqDivider: Frequency Divider, set so that LPOSC Frequency is = fxtal / 640
  * @return	None
  */
void AX5043LPOSCSetFrequencyDivider(uint8_t interfaceID, uint16_t freqDivider) {
	uint8_t config;
	config = (freqDivider) & LPOSCREF0_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCREF0, &config, 1);
	config = (freqDivider >> 8) & LPOSCREF1_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCREF1, &config, 1);
}

/**
  * @brief	This function gets the LPOSC Reference Frequency Divider
  * @param	interfaceID: Which interface (chip) used
  * @return	Frequency Divider Value
  */
uint16_t AX5043LPOSCGetFrequencyDivider(uint8_t interfaceID) {
	uint16_t freqDivider = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCREF0, &config, 1);
	freqDivider = (config & LPOSCREF0_MASK);
	AX5043ReadLongAddress(interfaceID, LPOSCREF1, &config, 1);
	freqDivider += (config & LPOSCREF1_MASK) << 8;
	return freqDivider;
}

/**
  * @brief	This function sets the LPOSC Frequency Tune Value
  * @param	interfaceID: Which interface (chip) used
  * @param	tune: Frequency Tune Value in 1/32 %
  * @return	None
  */
void AX5043LPOSCSetFrequencyTune(uint8_t interfaceID, uint16_t tune) {
	uint8_t config;
	config = (tune << 6) & LPOSCFREQ0_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCFREQ0, &config, 1);
	config = (tune >> 2) & LPOSCFREQ1_MASK;
	AX5043WriteLongAddress(interfaceID, LPOSCFREQ1, &config, 1);
}

/**
  * @brief	This function gets the LPOSC Frequency Tune Value
  * @param	interfaceID: Which interface (chip) used
  * @return	Frequency Tune Value in 1/32 %
  */
uint16_t AX5043LPOSCGetFrequencyTune(uint8_t interfaceID) {
	uint16_t tune = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCFREQ0, &config, 1);
	tune = (config & LPOSCFREQ0_MASK) >> 6;
	AX5043ReadLongAddress(interfaceID, LPOSCFREQ1, &config, 1);
	tune += (config & LPOSCFREQ1_MASK) << 2;
	return tune;
}

/**
  * @brief	This function gets the LPOSC Period
  * @param	interfaceID: Which interface (chip) used
  * @return	Last measured LPOSC Period
  */
uint16_t AX5043LPOSCGetPeriod(uint8_t interfaceID) {
	uint16_t period = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, LPOSCPER0, &config, 1);
	period = (config & LPOSCPER0_MASK);
	AX5043ReadLongAddress(interfaceID, LPOSCPER1, &config, 1);
	period += (config & LPOSCPER0_MASK) << 8;
	return period;
}
