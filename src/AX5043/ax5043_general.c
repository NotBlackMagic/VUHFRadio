#include "ax5043_general.h"

/**
  * @brief	This function reads the value of the revision register
  * @param	interfaceID: Which interface (chip) used
  * @return	Silicon Revision value
  */
uint8_t AX5043GeneralRevision(uint8_t interfaceID) {
	uint8_t revision;
	AX5043ReadShortAddress(interfaceID, REVISION, &revision, 1);
	return revision;
}

/**
  * @brief	This function reads the value of the scratch register, used to test SPI Interface
  * @param	interfaceID: Which interface (chip) used
  * @return	Scratch Register value (0xC5: 0b11000101)
  */
uint8_t AX5043GeneralScratch(uint8_t interfaceID) {
	uint8_t scratch;
	AX5043ReadShortAddress(interfaceID, SCRATCH, &scratch, 1);
	return scratch;
}

/**
  * @brief	This function gets the Radio State
  * @param	interfaceID: Which interface (chip) used
  * @return	RadioState: The Current Radio State
  */
RadioState AX5043GeneralRadioState(uint8_t interfaceID) {
	uint8_t radioState;
	AX5043ReadShortAddress(interfaceID, RADIOSTATE, &radioState, 1);
	radioState = radioState & RADIOSTATE_MASK;
	return radioState;
}

/**
  * @brief	This function gets the XTAL State
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Crystal oscillator running and stable
  */
uint8_t AX5043GeneralXTALStatus(uint8_t interfaceID) {
	uint8_t xtalState;
	AX5043ReadShortAddress(interfaceID, XTALSTATUS, &xtalState, 1);
	xtalState = xtalState & XTALSTATUS_MASK;
	return xtalState;
}

/**
  * @brief	This function gets the RSSI
  * @param	interfaceID: Which interface (chip) used
  * @return	RSSI Value in dB
  */
int8_t AX5043GeneralGetRSSI(uint8_t interfaceID) {
	int8_t rssi;
	AX5043ReadShortAddress(interfaceID, RSSI, &rssi, 1);
	return (rssi & RSSI_MASK);
}

/**
  * @brief	This function sets the Background Noise
  * @param	interfaceID: Which interface (chip) used
  * @param	noise: Background noise value
  * @return	None
  */
void AX5043GeneralSetBackgroundNoise(uint8_t interfaceID, uint8_t noise) {
	AX5043WriteShortAddress(interfaceID, BGNDRSSI, &noise, 1);
}

/**
  * @brief	This function gets the Background Noise
  * @param	interfaceID: Which interface (chip) used
  * @return	Background noise value
  */
uint8_t AX5043GeneralGetBackgroundNoise(uint8_t interfaceID) {
	uint8_t noise;
	AX5043ReadShortAddress(interfaceID, BGNDRSSI, &noise, 1);
	return (noise & BGNDRSSI_MASK);
}

/**
  * @brief	This function gets the current AGC gain
  * @param	interfaceID: Which interface (chip) used
  * @return	AGC Gain in 0.75 dB steps
  */
uint8_t AX5043GeneralGetAGCCurrentGain(uint8_t interfaceID) {
	uint8_t agcCnt;
	AX5043ReadShortAddress(interfaceID, AGCCOUNTER, &agcCnt, 1);
	return (agcCnt & AGCCOUNTER_MASK);
}

/**
  * @brief	This function Enables/Disables the Antenna Diversity
  * @param	interfaceID: Which interface (chip) used
  * @param	antennaDiversity: 1 -> Enable Antenna Diversity, 0 -> Disable Antenna Diversity
  * @return	None
  */
void AX5043GeneralSetEnableAntennaDiversity(uint8_t interfaceID, uint8_t antennaDiversity) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, DIVERSITY, &config, 1);
	config = (config & ~DIVERSITY_DIVENA_MASK) | (antennaDiversity);
	AX5043WriteShortAddress(interfaceID, DIVERSITY, &config, 1);
}

/**
  * @brief	This function gets if the Antenna Diversity is Enabled/Disabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Antenna Diversity Enabled, 0 -> Antenna Diversity Disabled
  */
uint8_t AX5043GeneralGetAntennaDiversity(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, DIVERSITY, &config, 1);
	return (config & DIVERSITY_DIVENA_MASK);
}

/**
  * @brief	This function selects the Antenna
  * @param	interfaceID: Which interface (chip) used
  * @param	antennaSelect: Selects the Antenna
  * @return	None
  */
void AX5043GeneralSetAntennaSelection(uint8_t interfaceID, uint8_t antennaSelect) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, DIVERSITY, &config, 1);
	config = (config & ~DIVERSITY_ANTSEL_MASK) | (antennaSelect << 1);
	AX5043WriteShortAddress(interfaceID, DIVERSITY, &config, 1);
}

/**
  * @brief	This function gets which antenna is used
  * @param	interfaceID: Which interface (chip) used
  * @return	The Selected Antenna
  */
uint8_t AX5043GeneralGetAntennaSelection(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, DIVERSITY, &config, 1);
	return ((config & DIVERSITY_ANTSEL_MASK) >> 1);
}

/**
  * @brief	This function sets the XTAL Load Capacitance
  * @param	interfaceID: Which interface (chip) used
  * @param	cap: Load Capacitance Configuration: CL = 8pF + 0.5pF*cap
  * @return	None
  */
void AX5043GeneralSetXTALLoadCap(uint8_t interfaceID, uint8_t cap) {
	uint8_t config = (cap & XTALCAP_MASK);
	AX5043WriteShortAddress(interfaceID, XTALCAP, &config, 1);
}

/**
  * @brief	This function gets the XTAL Load Capacitance
  * @param	interfaceID: Which interface (chip) used
  * @return	Load Capacitance Configuration: CL = 8pF + 0.5pF*cap
  */
uint8_t AX5043GeneralGetXTALLoadCap(uint8_t interfaceID) {
	uint8_t cap;
	AX5043WriteShortAddress(interfaceID, XTALCAP, &cap, 1);
	return (cap & XTALCAP_MASK);
}

/**
  * @brief	This function sets the modulation mode
  * @param	interfaceID: Which interface (chip) used
  * @param	Modulations: Selects the modulation/demodulation mode
  * @return	None
  */
void AX5043GeneralSetModulation(uint8_t interfaceID, Modulations modulation) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, MODULATION, &config, 1);
	config = (config & ~MODULATION_MASK) | (modulation);
	AX5043WriteShortAddress(interfaceID, MODULATION, &config, 1);
}

/**
  * @brief	This function gets the modulation mode
  * @param	interfaceID: Which interface (chip) used
  * @return	The Modulations mode
  */
Modulations AX5043GeneralGetModulation(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, MODULATION, &config, 1);
	return (Modulations)(config & MODULATION_MASK);
}

/**
  * @brief	This function sets RX half speed
  * @param	interfaceID: Which interface (chip) used
  * @param	halfSpeed: If set, halves the received bitrate
  * @return	None
  */
void AX5043GeneralSetRXHalfSpeed(uint8_t interfaceID, uint8_t halfSpeed) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, MODULATION, &config, 1);
	config = (config & ~RXHALFSPEED_MASK) | (halfSpeed << 4);
	AX5043WriteShortAddress(interfaceID, MODULATION, &config, 1);
}

/**
  * @brief	This function gets if RX half speed is used
  * @param	interfaceID: Which interface (chip) used
  * @return	If received bitrate is halved
  */
uint8_t AX5043GeneralGetRXHalfSpeed(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, MODULATION, &config, 1);
	return ((config & RXHALFSPEED_MASK) >> 4);
}
