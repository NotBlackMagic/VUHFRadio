#include "ax5043_pwr.h"

/**
  * @brief	This function sets the Radio Power Mode
  * @param	interfaceID: Which interface (chip) used
  * @param	pwrMode: The power mode to set the radio to
  * @return	None
  */
void AX5043PwrSetPowerMode(uint8_t interfaceID, PwrModeSelection pwrMode) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	config = (config & ~PWRMODE_MASK) | (pwrMode & PWRMODE_MASK);
	AX5043WriteShortAddress(interfaceID, PWRMODE, &config, 1);
}

/**
  * @brief	This function gets the Radio Power Mode
  * @param	interfaceID: Which interface (chip) used
  * @return	PwrModeSelection, the current radio power mode
  */
PwrModeSelection AX5043PwrGetPowerMode(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	return (config & PWRMODE_MASK);
}

/**
  * @brief	This function enables/disables the Internal Reference Circuitry
  * @param	interfaceID: Which interface (chip) used
  * @param	enableRef: 1 -> Enable Internal Reference, 0 -> Disable Internal Reference
  * @return	None
  */
void AX5043PwrSetEnableReference(uint8_t interfaceID, uint8_t enableRef) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	config = (config & ~PWRMODE_REFEN_MASK) | (enableRef << 5);
	AX5043WriteShortAddress(interfaceID, PWRMODE, &config, 1);
}

/**
  * @brief	This function gets if the Internal Reference Circuitry is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable Internal Reference, 0 -> Disable Internal Reference
  */
uint8_t AX5043PwrGetEnableReference(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	return ((config & PWRMODE_REFEN_MASK) >> 5);
}

/**
  * @brief	This function enables/disables the Crystal Oscillator
  * @param	interfaceID: Which interface (chip) used
  * @param	enableXO: 1 -> Enable Crystal Oscillator, 0 -> Disable Crystal Oscillator
  * @return	None
  */
void AX5043PwrSetEnableXO(uint8_t interfaceID, uint8_t enableXO) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	config = (config & ~PWRMODE_XOEN_MASK) | (enableXO << 6);
	AX5043WriteShortAddress(interfaceID, PWRMODE, &config, 1);
}

/**
  * @brief	This function gets if the Crystal Oscillator is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable Crystal Oscillator, 0 -> Disable Crystal Oscillator
  */
uint8_t AX5043PwrGetEnableXO(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, PWRMODE, &config, 1);
	return ((config & PWRMODE_XOEN_MASK) >> 6);
}

/**
  * @brief	This function resets the chip
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043PwrReset(uint8_t interfaceID) {
	uint8_t reset = 0x80;	//Reset Command
	AX5043WriteShortAddress(interfaceID, PWRMODE, &reset, 1);
	for(uint16_t i = 0; i < 0x1000; i++);
	reset = 0x60;			//Enable Internal Reference and Crystal Oscillator (Reset value of this register)
	AX5043WriteShortAddress(interfaceID, PWRMODE, &reset, 1);
}

/**
  * @brief	This function gets Power Status
  * @param	interfaceID: Which interface (chip) used
  * @return	PwrStatus: Power status bits
  */
PwrStatus AX5043PwrStats(uint8_t interfaceID) {
	PwrStatus status;
	AX5043ReadShortAddress(interfaceID, POWSTAT, &status.raw, 1);
	return status;
}

/**
  * @brief	This function gets Power Sticky Status
  * @param	interfaceID: Which interface (chip) used
  * @return	PwrStatus: Power status sticky bits
  */
PwrStatus AX5043PwrStickyStats(uint8_t interfaceID) {
	PwrStatus status;
	AX5043ReadShortAddress(interfaceID, POWSTICKYSTAT, &status.raw, 1);
	return status;
}

/**
  * @brief	This function sets the Power IRQ Masks
  * @param	interfaceID: Which interface (chip) used
  * @param	irqMask: The IRQ Mask to be used
  * @return	None
  */
void AX5043PwrSetIRQMask(uint8_t interfaceID, PwrIRQMask irqMask) {
	AX5043WriteShortAddress(interfaceID, POWIRQMASK, &irqMask.raw, 1);
}

/**
  * @brief	This function gets the Power IRQ Masks
  * @param	interfaceID: Which interface (chip) used
  * @return	PwrIRQMask: The IRQ Mask used
  */
PwrIRQMask AX5043PwrGetIRQMask(uint8_t interfaceID) {
	PwrIRQMask irqMask;
	AX5043ReadShortAddress(interfaceID, POWIRQMASK, &irqMask.raw, 1);
	return irqMask;
}
