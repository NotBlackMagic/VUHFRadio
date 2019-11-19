#include "ax5043_synth.h"

/**
  * @brief	This function enables/disables the External PLL Loop Filter
  * @param	interfaceID: Which interface (chip) used
  * @param	enableExtFilter: 1 -> Enable External Loop Filter, 0 -> Disable External Loop Filter
  * @return	None
  */
void AX5043SynthSetPLLLoopEnableExtFilter(uint8_t interfaceID, uint8_t enableExtFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	config = (config & ~PLLLOOP_FILTEN_MASK) | (enableExtFilter << 2);
	AX5043WriteShortAddress(interfaceID, PLLLOOP, &config, 1);
}

/**
  * @brief	This function gets if the External PLL Loop Filter is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> External Loop Filter Enabled, 0 -> External Loop Filter Disabled
  */
uint8_t AX5043SynthGetPLLLoopEnableExtFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	return ((config & PLLLOOP_FILTEN_MASK) >> 2);
}

/**
  * @brief	This function enables/disables the External PLL Loop Boost Filter
  * @param	interfaceID: Which interface (chip) used
  * @param	enableExtFilter: 1 -> Enable External Loop Filter, 0 -> Disable External Loop Filter
  * @return	None
  */
void AX5043SynthSetPLLLoopBoostEnableExtFilter(uint8_t interfaceID, uint8_t enableExtFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	config = (config & ~PLLLOOPBOOST_FILTEN_MASK) | (enableExtFilter << 2);
	AX5043WriteShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
}

/**
  * @brief	This function gets if the External PLL Loop Boost Filter is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> External Loop Filter Enabled, 0 -> External Loop Filter Disabled
  */
uint8_t AX5043SynthGetPLLLoopBoostEnableExtFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	return ((config & PLLLOOPBOOST_FILTEN_MASK) >> 2);
}

/**
  * @brief	This function enables/disables the Bypass External PLL Loop Filter
  * @param	interfaceID: Which interface (chip) used
  * @param	bypassExtFilter: 1 -> Bypass External Loop Filter, 0 -> Not Bypass External Loop Filter
  * @return	None
  */
void AX5043SynthSetPLLLoopBypassExtFilter(uint8_t interfaceID, uint8_t bypassExtFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	config = (config & ~PLLLOOP_DIRECT_MASK) | (bypassExtFilter << 3);
	AX5043WriteShortAddress(interfaceID, PLLLOOP, &config, 1);
}

/**
  * @brief	This function gets if the External PLL Loop Filter is Bypassed
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> External Loop Filter Bypassed, 0 -> External Loop Filter Not Bypassed
  */
uint8_t AX5043SynthGetPLLLoopBypassExtFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	return ((config & PLLLOOP_DIRECT_MASK) >> 3);
}

/**
  * @brief	This function enables/disables the Bypass External PLL Loop Boost Filter
  * @param	interfaceID: Which interface (chip) used
  * @param	bypassExtFilter: 1 -> Bypass External Loop Filter, 0 -> Not Bypass External Loop Filter
  * @return	None
  */
void AX5043SynthSetPLLLoopBoostBypassExtFilter(uint8_t interfaceID, uint8_t bypassExtFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	config = (config & ~PLLLOOPBOOST_DIRECT_MASK) | (bypassExtFilter << 3);
	AX5043WriteShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
}

/**
  * @brief	This function gets if the External PLL Loop Boost Filter is Bypassed
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> External Loop Filter Bypassed, 0 -> External Loop Filter Not Bypassed
  */
uint8_t AX5043SynthGetPLLLoopBoostBypassExtFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	return ((config & PLLLOOPBOOST_DIRECT_MASK) >> 3);
}

/**
  * @brief	This function selects which frequency registers to use (FREQA or FREQB) for the PLL
  * @param	interfaceID: Which interface (chip) used
  * @param	freqSelection: 1 -> Use FREQB Register, 0 -> Use FREQA Register
  * @return	None
  */
void AX5043SynthSetPLLLoopSelectFrequency(uint8_t interfaceID, uint8_t freqSelection) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	config = (config & ~PLLLOOP_FRQSEL_MASK) | (freqSelection << 7);
	AX5043WriteShortAddress(interfaceID, PLLLOOP, &config, 1);
}

/**
  * @brief	This function gets which frequency registers is set (FREQA or FREQB) for the PLL
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> FREQB Register used, 0 -> FREQA Register used
  */
uint8_t AX5043SynthGetPLLLoopSelectFrequency(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	return ((config & PLLLOOP_FRQSEL_MASK) >> 7);
}

/**
  * @brief	This function selects which frequency registers to use (FREQA or FREQB) for the PLL Boost
  * @param	interfaceID: Which interface (chip) used
  * @param	freqSelection: 1 -> Use FREQB Register, 0 -> Use FREQA Register
  * @return	None
  */
void AX5043SynthSetPLLLoopBoostSelectFrequency(uint8_t interfaceID, uint8_t freqSelection) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	config = (config & ~PLLLOOPBOOST_FRQSEL_MASK) | (freqSelection << 7);
	AX5043WriteShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
}

/**
  * @brief	This function gets which frequency registers is set (FREQA or FREQB) for the PLL Boost
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> FREQB Register used, 0 -> FREQA Register used
  */
uint8_t AX5043SynthGetPLLLoopBoostSelectFrequency(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	return ((config & PLLLOOPBOOST_FRQSEL_MASK) >> 7);
}

/**
  * @brief	This function selects which PLL Loop filter to use
  * @param	interfaceID: Which interface (chip) used
  * @param	pllLoopFilter: Which PLL Loop Filter to use
  * @return	None
  */
void AX5043SynthSetPLLLoopFilter(uint8_t interfaceID, PLLLoopFilter pllLoopFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	config = (config & ~PLLLOOP_FLT_MASK) | (pllLoopFilter);
	AX5043WriteShortAddress(interfaceID, PLLLOOP, &config, 1);
}

/**
  * @brief	This function gets which PLL Loop filter is in use
  * @param	interfaceID: Which interface (chip) used
  * @return	PLLLoopFilter: Which PLL Loop Filter is in use
  */
PLLLoopFilter AX5043SynthGetPLLLoopFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOP, &config, 1);
	return (config & PLLLOOP_FLT_MASK);
}

/**
  * @brief	This function selects which PLL Loop Boost filter to use
  * @param	interfaceID: Which interface (chip) used
  * @param	pllLoopFilter: Which PLL Loop Boost Filter to use
  * @return	None
  */
void AX5043SynthSetPLLLoopBoostFilter(uint8_t interfaceID, PLLLoopBoostFilter pllLoopFilter) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	config = (config & ~PLLLOOPBOOST_FLT_MASK) | (pllLoopFilter);
	AX5043WriteShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
}

/**
  * @brief	This function gets which PLL Loop Boost filter is in use
  * @param	interfaceID: Which interface (chip) used
  * @return	PLLLoopBoostFilter: Which PLL Loop Boost Filter is in use
  */
PLLLoopBoostFilter AX5043SynthGetPLLLoopBoostFilter(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLLOOPBOOST, &config, 1);
	return (config & PLLLOOPBOOST_FLT_MASK);
}

/**
  * @brief	This function sets the PLL Charge Pump Current, in multiples of 8.5uA
  * @param	interfaceID: Which interface (chip) used
  * @param	current: The current multiple
  * @return	None
  */
void AX5043SynthSetPLLChargePumpCurrent(uint8_t interfaceID, uint8_t current) {
	AX5043WriteShortAddress(interfaceID, PLLCPI_MASK, &current, 1);
}

/**
  * @brief	This function gets the PLL Charge Pump Current, in multiples of 8.5uA
  * @param	interfaceID: Which interface (chip) used
  * @return	The current multiple
  */
uint8_t AX5043SynthGetPLLChargePumpCurrent(uint8_t interfaceID) {
	uint8_t current;
	AX5043ReadShortAddress(interfaceID, PLLCPI_MASK, &current, 1);
	return current;
}

/**
  * @brief	This function sets the PLL Boost Charge Pump Current, in multiples of 8.5uA
  * @param	interfaceID: Which interface (chip) used
  * @param	current: The current multiple
  * @return	None
  */
void AX5043SynthSetPLLBoostChargePumpCurrent(uint8_t interfaceID, uint8_t current) {
	AX5043WriteShortAddress(interfaceID, PLLCPIBOOST_MASK, &current, 1);
}

/**
  * @brief	This function gets the PLL Boost Charge Pump Current, in multiples of 8.5uA
  * @param	interfaceID: Which interface (chip) used
  * @return	The current multiple
  */
uint8_t AX5043SynthGetPLLBoostChargePumpCurrent(uint8_t interfaceID) {
	uint8_t current;
	AX5043ReadShortAddress(interfaceID, PLLCPIBOOST_MASK, &current, 1);
	return current;
}

/**
  * @brief	This function enables/disables the PLL VCO Reference Divider
  * @param	interfaceID: Which interface (chip) used
  * @param	enableRefDivider: 1 -> Enable PLL VCO Reference Divider, 0 -> Disable PLL VCO Reference Divider
  * @return	None
  */
void AX5043SynthSetPLLVCOEnableRefDivider(uint8_t interfaceID, uint8_t enableRefDivider) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	config = (config & ~PLLVCODIV_RFDIV_MASK) | (enableRefDivider << 2);
	AX5043WriteShortAddress(interfaceID, PLLVCODIV, &config, 1);
}

/**
  * @brief	This function gets if the PLL VCO Reference Divider is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PLL VCO Reference Divider is Enabled, 0 -> PLL VCO Reference Divider is Disabled
  */
uint8_t AX5043SynthGetPLLVCOEnableRefDivider(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	return ((config & PLLVCODIV_RFDIV_MASK) >> 2);
}

/**
  * @brief	This function selects which VCO to use
  * @param	interfaceID: Which interface (chip) used
  * @param	selectVCO: 0 -> VCO1, 1 -> VCO2 with external inductor or external VCO
  * @return	None
  */
void AX5043SynthSetPLLVCOSelection(uint8_t interfaceID, uint8_t selectVCO) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	config = (config & ~PLLVCODIV_VCOSEL) | (selectVCO << 4);
	AX5043WriteShortAddress(interfaceID, PLLVCODIV, &config, 1);
}

/**
  * @brief	This function gets which VCO is used
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> VCO1, 1 -> VCO2 with external inductor or external VCO
  */
uint8_t AX5043SynthGetPLLVCOSelection(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	return ((config & PLLVCODIV_RFDIV_MASK) >> 4);
}

/**
  * @brief	This function selects which VCO2 to use
  * @param	interfaceID: Which interface (chip) used
  * @param	internalVCO2: 1 -> VCO2 with external inductor 0 -> External VCO
  * @return	None
  */
void AX5043SynthSetPLLVCO2Internal(uint8_t interfaceID, uint8_t internalVCO2) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	config = (config & ~PLLVCODIV_VCO2INT) | (internalVCO2 << 5);
	AX5043WriteShortAddress(interfaceID, PLLVCODIV, &config, 1);
}

/**
  * @brief	This function gets which VCO2 is used
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> VCO2 with external inductor 0 -> External VCO
  */
uint8_t AX5043SynthGetPLLVCO2Internal(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	return ((config & PLLVCODIV_VCO2INT) >> 5);
}

/**
  * @brief	This function selects the PLL Reference Divider
  * @param	interfaceID: Which interface (chip) used
  * @param	pllRefDivider: Which PLL Reference Divider to use to use
  * @return	None
  */
void AX5043SynthSetPLLRefDivider(uint8_t interfaceID, PLLCodivRefrenceDivider pllRefDivider) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	config = (config & ~PLLVCODIV_REFDIV_MASK) | (pllRefDivider);
	AX5043WriteShortAddress(interfaceID, PLLVCODIV, &config, 1);
}

/**
  * @brief	This function gets which PLL Loop filter is in use
  * @param	interfaceID: Which interface (chip) used
  * @return	PLLCodivRefrenceDivider: Which PLL Reference Divider to use is in use
  */
PLLCodivRefrenceDivider AX5043SynthGetPLLRefDivider(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLVCODIV, &config, 1);
	return (config & PLLVCODIV_REFDIV_MASK);
}

/**
  * @brief	This function selects the VCO Range A
  * @param	interfaceID: Which interface (chip) used
  * @param	vcoRange: The VCO Range
  * @return	None
  */
void AX5043SynthSetVCORangeA(uint8_t interfaceID, uint8_t vcoRange) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	config = (config & ~PLLRANGINGA_VCORA_MASK) | (vcoRange);
	AX5043WriteShortAddress(interfaceID, PLLRANGINGA, &config, 1);
}

/**
  * @brief	This function gets the VCO Range A
  * @param	interfaceID: Which interface (chip) used
  * @return	The VCO Range
  */
uint8_t AX5043SynthGetVCORangeA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	return (config & PLLRANGINGA_VCORA_MASK);
}

/**
  * @brief	This function selects the VCO Range B
  * @param	interfaceID: Which interface (chip) used
  * @param	vcoRange: The VCO Range
  * @return	None
  */
void AX5043SynthSetVCORangeB(uint8_t interfaceID, uint8_t vcoRange) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	config = (config & ~PLLRANGINGB_VCORB_MASK) | (vcoRange);
	AX5043WriteShortAddress(interfaceID, PLLRANGINGB, &config, 1);
}

/**
  * @brief	This function gets the VCO Range B
  * @param	interfaceID: Which interface (chip) used
  * @return	The VCO Range
  */
uint8_t AX5043SynthGetVCORangeB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	return (config & PLLRANGINGB_VCORB_MASK);
}

/**
  * @brief	This function starts the autoranging on VCO A
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043SynthStartAutoRangingA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	config = (config & ~PLLRANGINGA_RNGSTART_MASK) | (PLLRANGINGA_RNGSTART_MASK);
	AX5043WriteShortAddress(interfaceID, PLLRANGINGA, &config, 1);
}

/**
  * @brief	This function gets the autoranging status of VCO A
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Autorangeing Done, 1 -> Autorannging in Progress
  */
uint8_t AX5043SynthGetAutoRangingA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	return ((config & PLLRANGINGA_RNGSTART_MASK) >> 4);
}

/**
  * @brief	This function starts the autoranging on VCO B
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043SynthStartAutoRangingB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	config = (config & ~PLLRANGINGB_RNGSTART_MASK) | (PLLRANGINGA_RNGSTART_MASK);
	AX5043WriteShortAddress(interfaceID, PLLRANGINGB, &config, 1);
}

/**
  * @brief	This function gets the autoranging status of VCO B
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Autorangeing Done, 1 -> Autorannging in Progress
  */
uint8_t AX5043SynthGetAutoRangingB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	return ((config & PLLRANGINGB_RNGSTART_MASK) >> 4);
}

/**
  * @brief	This function gets the autoranging error status of VCO A
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Error after autoragning start, programmed frequency not achieved, 0 -> No Error
  */
uint8_t AX5043SynthGetAutoRangingErrorA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	return ((config & PLLRANGINGA_RNGERR_MASK) >> 5);
}

/**
  * @brief	This function gets the autoranging error status of VCO B
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Error after autoragning start, programmed frequency not achieved, 0 -> No Error
  */
uint8_t AX5043SynthGetAutoRangingErrorB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	return ((config & PLLRANGINGB_RNGERR_MASK) >> 5);
}

/**
  * @brief	This function gets the PLL Lock status of VCO A
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PLL Locked, 0 -> PLL not Locked
  */
uint8_t AX5043SynthGetPLLLockA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	return ((config & PLLRANGINGA_PLLLOCK_MASK) >> 6);
}

/**
  * @brief	This function gets the PLL Lock status of VCO B
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PLL Locked, 0 -> PLL not Locked
  */
uint8_t AX5043SynthGetPLLLockB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	return ((config & PLLRANGINGB_PLLLOCK_MASK) >> 6);
}

/**
  * @brief	This function gets the PLL Lock Sticky status of VCO A
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PLL Locked, 0 -> PLL lost lock after last read of PLLRANGINGA
  */
uint8_t AX5043SynthGetPLLLockStickyA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGA, &config, 1);
	return ((config & PLLRANGINGA_STICKYLOCK) >> 7);
}

/**
  * @brief	This function gets the PLL Lock Sticky status of VCO B
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PLL Locked, 0 -> PLL lost lock after last read of PLLRANGINGB
  */
uint8_t AX5043SynthGetPLLLockStickyB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PLLRANGINGB, &config, 1);
	return ((config & PLLRANGINGB_STICKYLOCK) >> 7);
}

/**
  * @brief	This function sets the Frequency A
  * @param	interfaceID: Which interface (chip) used
  * @param	frequency: Frequency A = fCarrier/FXtal * 2^24 + 1/2
  * @return	None
  */
void AX5043SynthSetFrequencyA(uint8_t interfaceID, uint32_t frequency) {
	uint8_t config;
	config = frequency & FREQA0_MASK;
	AX5043WriteShortAddress(interfaceID, FREQA0, &config, 1);
	config = (frequency >> 8) & FREQA1_MASK;
	AX5043WriteShortAddress(interfaceID, FREQA1, &config, 1);
	config = (frequency >> 16) & FREQA2_MASK;
	AX5043WriteShortAddress(interfaceID, FREQA2, &config, 1);
	config = (frequency >> 24) & FREQA3_MASK;
	AX5043WriteShortAddress(interfaceID, FREQA3, &config, 1);
}

/**
  * @brief	This function gets the Frequency A
  * @param	interfaceID: Which interface (chip) used
  * @return	Frequency A = fCarrier/FXtal * 2^24 + 1/2
  */
uint32_t AX5043SynthGetFrequencyA(uint8_t interfaceID) {
	uint8_t config;
	uint32_t frequency = 0;
	AX5043ReadShortAddress(interfaceID, FREQA0, &config, 1);
	frequency = config;
	AX5043ReadShortAddress(interfaceID, FREQA1, &config, 1);
	frequency += (config << 8);
	AX5043ReadShortAddress(interfaceID, FREQA2, &config, 1);
	frequency += (config << 16);
	AX5043ReadShortAddress(interfaceID, FREQA3, &config, 1);
	frequency += (config << 24);
	return frequency;
}

/**
  * @brief	This function sets the Frequency B
  * @param	interfaceID: Which interface (chip) used
  * @param	frequency: Frequency B = fCarrier/FXtal * 2^24 + 1/2
  * @return	None
  */
void AX5043SynthSetFrequencyB(uint8_t interfaceID, uint32_t frequency) {
	uint8_t config;
	config = frequency & FREQB0_MASK;
	AX5043WriteShortAddress(interfaceID, FREQB0, &config, 1);
	config = (frequency >> 8) & FREQB1_MASK;
	AX5043WriteShortAddress(interfaceID, FREQB1, &config, 1);
	config = (frequency >> 16) & FREQB2_MASK;
	AX5043WriteShortAddress(interfaceID, FREQB2, &config, 1);
	config = (frequency >> 24) & FREQB3_MASK;
	AX5043WriteShortAddress(interfaceID, FREQB3, &config, 1);
}

/**
  * @brief	This function gets the Frequency B
  * @param	interfaceID: Which interface (chip) used
  * @return	Frequency B = fCarrier/FXtal * 2^24 + 1/2
  */
uint32_t AX5043SynthGetFrequencyB(uint8_t interfaceID) {
	uint8_t config;
	uint32_t frequency = 0;
	AX5043ReadShortAddress(interfaceID, FREQB0, &config, 1);
	frequency = config;
	AX5043ReadShortAddress(interfaceID, FREQB1, &config, 1);
	frequency += (config << 8);
	AX5043ReadShortAddress(interfaceID, FREQB2, &config, 1);
	frequency += (config << 16);
	AX5043ReadShortAddress(interfaceID, FREQB3, &config, 1);
	frequency += (config << 24);
	return frequency;
}
