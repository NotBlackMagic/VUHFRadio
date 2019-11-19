#include "ax5043_baseband.h"

/**
  * @brief	This function sets the Baseband Tuning Value
  * @param	interfaceID: Which interface (chip) used
  * @param	value: Baseband Tune Value
  * @return	None
  */
void AX5043BasebandSetTuneValue(uint8_t interfaceID, uint8_t value) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBTUNE, &config, 1);
	config = (config & ~BBTUNE_MASK) | value;
	AX5043WriteLongAddress(interfaceID, BBTUNE, &config, 1);
}

/**
  * @brief	This function gets the Baseband Tuning Value
  * @param	interfaceID: Which interface (chip) used
  * @return	Baseband Tune Value
  */
uint8_t AX5043BasebandGetTuneValue(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBTUNE, &config, 1);
	return (config & BBTUNE_MASK);
}

/**
  * @brief	This function Starts or Stops Baseband Tuning
  * @param	interfaceID: Which interface (chip) used
  * @param	start: Start Baseband Tuning
  * @return	None
  */
void AX5043BasebandSetTuneRunning(uint8_t interfaceID, uint8_t start) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBTUNE, &config, 1);
	config = (config & ~BBTUNERUN_MASK) | (start << 4);
	AX5043WriteLongAddress(interfaceID, BBTUNE, &config, 1);
}

/**
  * @brief	This function gets if Baseband Tuning is Running
  * @param	interfaceID: Which interface (chip) used
  * @return	If Baseband Tuning is Running
  */
uint8_t AX5043BasebandGetTuneRunning(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBTUNE, &config, 1);
	return ((config & BBTUNERUN_MASK) >> 4);
}

/**
  * @brief	This function sets the Baseband Gain Block A Offset Compensation Capacitors
  * @param	interfaceID: Which interface (chip) used
  * @param	cap: Offset Compensation Capacitors Value
  * @return	None
  */
void AX5043BasebandSetGainOffsetCompCapA(uint8_t interfaceID, uint8_t cap) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSCAP, &config, 1);
	config = (config & ~CAPINTA_MASK) | cap;
	AX5043WriteLongAddress(interfaceID, BBOFFSCAP, &config, 1);
}

/**
  * @brief	This function gets the Baseband Gain Block A Offset Compensation Capacitors
  * @param	interfaceID: Which interface (chip) used
  * @return	Offset Compensation Capacitors Value
  */
uint8_t AX5043BasebandGetGainOffsetCompCapA(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSCAP, &config, 1);
	return (config & CAPINTA_MASK);
}

/**
  * @brief	This function sets the Baseband Gain Block B Offset Compensation Capacitors
  * @param	interfaceID: Which interface (chip) used
  * @param	cap: Offset Compensation Capacitors Value
  * @return	None
  */
void AX5043BasebandSetGainOffsetCompCapB(uint8_t interfaceID, uint8_t cap) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSCAP, &config, 1);
	config = (config & ~CAPINTB_MASK) | (cap << 4);
	AX5043WriteLongAddress(interfaceID, BBOFFSCAP, &config, 1);
}

/**
  * @brief	This function gets the Baseband Gain Block B Offset Compensation Capacitors
  * @param	interfaceID: Which interface (chip) used
  * @return	Offset Compensation Capacitors Value
  */
uint8_t AX5043BasebandGetGainOffsetCompCapB(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BBOFFSCAP, &config, 1);
	return ((config & CAPINTB_MASK) >> 4);
}
