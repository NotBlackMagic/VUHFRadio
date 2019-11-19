#include "ax5043_pllparam.h"

/**
  * @brief	This function sets the Bias Current for both VCOs, increments of 50uA for VCO1 and 10uA for VCO2
  * @param	interfaceID: Which interface (chip) used
  * @param	biasCurrent: Bias Current for VCOs
  * @return	None
  */
void AX5043PLLParamSetVCOBias(uint8_t interfaceID, uint8_t biasCurrent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLVCOI, &config, 1);
	config = (config & ~VCOI_MASK) | (biasCurrent);
	AX5043WriteLongAddress(interfaceID, PLLVCOI, &config, 1);
}

/**
  * @brief	This function gets the Bias Current for both VCOs
  * @param	interfaceID: Which interface (chip) used
  * @return	Bias Current for VCOs
  */
uint8_t AX5043PLLParamGetVCOBias(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLVCOI, &config, 1);
	return (config & VCOI_MASK);
}

/**
  * @brief	This function enables Manual Bias Current for both VCOs
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable Manual VCOI
  * @return	None
  */
void AX5043PLLParamEnableManualVCOI(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLVCOI, &config, 1);
	config = (config & ~VCOIE_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, PLLVCOI, &config, 1);
}

/**
  * @brief	This function gets if Manual Bias Current is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> If enabled, 0 -> if disabled
  */
uint8_t AX5043PLLParamIsManualVCOIEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLVCOI, &config, 1);
	return ((config & VCOIE_MASK) >> 7);
}

/**
  * @brief	This function gets the Actual Bias Current for both VCOs, same as VCOI if Manual
  * @param	interfaceID: Which interface (chip) used
  * @return	Bias Current for VCOs
  */
uint8_t AX5043PLLParamGetActualVCOBias(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLVCOIR, &config, 1);
	return (config & VCOIR_MASK);
}

/**
  * @brief	This function sets the PLL Lock Detector Delay
  * @param	interfaceID: Which interface (chip) used
  * @param	delay: Lock Delay value
  * @return	None
  */
void AX5043PLLParamSetLockDetectDelay(uint8_t interfaceID, LockDetectorDelay delay) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLLOCKDET, &config, 1);
	config = (config & ~LOCKDETDLY_MASK) | (delay);
	AX5043WriteLongAddress(interfaceID, PLLLOCKDET, &config, 1);
}

/**
  * @brief	This function gets the PLL Lock Detector Delay
  * @param	interfaceID: Which interface (chip) used
  * @return	Lock Delay value
  */
LockDetectorDelay AX5043PLLParamGetLockDetectDelay(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLLOCKDET, &config, 1);
	return (LockDetectorDelay)(config & LOCKDETDLY_MASK);
}

/**
  * @brief	This function enables Manual Lock Delay
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable Manual Lock Delay
  * @return	None
  */
void AX5043PLLParamEnableManualLockDelay(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLLOCKDET, &config, 1);
	config = (config & ~LOCKDETDLYM_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, PLLLOCKDET, &config, 1);
}

/**
  * @brief	This function gets if Manual Lock Delay is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> If enabled, 0 -> if disabled
  */
uint8_t AX5043PLLParamIsManualLockDelayEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLLOCKDET, &config, 1);
	return ((config & LOCKDETDLYM_MASK) >> 2);
}

/**
  * @brief	This function gets the Actual PLL Lock Detector Delay
  * @param	interfaceID: Which interface (chip) used
  * @return	Lock Delay value
  */
LockDetectorDelay AX5043PLLParamGetActualLockDetectDelay(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLLOCKDET, &config, 1);
	return (LockDetectorDelay)((config & LOCKDETDLYR_MASK) >> 6);
}

/**
  * @brief	This function sets the PLL Ranging Clock
  * @param	interfaceID: Which interface (chip) used
  * @param	clock: PLL Ranging Clock
  * @return	None
  */
void AX5043PLLParamSetPLLRangingClock(uint8_t interfaceID, PLLRangingClock clock) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLRNGCLK, &config, 1);
	config = (config & ~PLLRNGCLK_MASK) | (clock);
	AX5043WriteLongAddress(interfaceID, PLLRNGCLK, &config, 1);
}

/**
  * @brief	This function gets the PLL Ranging Clock
  * @param	interfaceID: Which interface (chip) used
  * @return	PLL Ranging Clock
  */
PLLRangingClock AX5043PLLParamGetPLLRangingClock(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PLLRNGCLK, &config, 1);
	return (config & PLLRNGCLK_MASK);
}
