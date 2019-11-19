#include "ax5043_timer.h"

/**
  * @brief	This function gets the Timer value (Ftim = fXtal / 16)
  * @param	interfaceID: Which interface (chip) used
  * @return	Current Timer value
  */
uint32_t AX5043TimerGetTimerValue(uint8_t interfaceID) {
	uint32_t timer = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, TIMER0, &config, 1);
	timer = (config & TIMER0_MASK);
	AX5043ReadShortAddress(interfaceID, TIMER1, &config, 1);
	timer += (config & TIMER1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, TIMER2, &config, 1);
	timer += (config & TIMER2_MASK) << 16;
	return timer;
}

/**
  * @brief	This function gets the Wakeup Timer value (Fwtim = 640Hz or 10.24kHz)
  * @param	interfaceID: Which interface (chip) used
  * @return	Wakeup Current Timer value
  */
uint16_t AX5043TimerGetWakeupTimerValue(uint8_t interfaceID) {
	uint16_t timer = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, WAKEUPTIMER0, &config, 1);
	timer = (config & WAKEUPTIMER0_MASK);
	AX5043ReadShortAddress(interfaceID, WAKEUPTIMER1, &config, 1);
	timer += (config & WAKEUPTIMER1_MASK) << 8;
	return timer;
}

/**
  * @brief	This function sets the Wakeup Time value
  * @param	interfaceID: Which interface (chip) used
  * @param	wakeupTime: Wakeup Time Value to be programmed
  * @return	None
  */
void AX5043TimerSetWakeupTimeValue(uint8_t interfaceID, uint16_t wakeupTime) {
	uint8_t config;
	config = (wakeupTime) & WAKEUP0_MASK;
	AX5043WriteShortAddress(interfaceID, WAKEUP0, &config, 1);
	config = (wakeupTime >> 8) & WAKEUP1_MASK;
	AX5043WriteShortAddress(interfaceID, WAKEUP1, &config, 1);
}

/**
  * @brief	This function gets the Wakeup Time value
  * @param	interfaceID: Which interface (chip) used
  * @return	Wakeup Time Value programmed
  */
uint16_t AX5043TimerGetWakeupTimeValue(uint8_t interfaceID) {
	uint16_t wakeupTime = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, WAKEUP0, &config, 1);
	wakeupTime = (config & WAKEUP0_MASK);
	AX5043ReadShortAddress(interfaceID, WAKEUP1, &config, 1);
	wakeupTime += (config & WAKEUP1_MASK) << 8;
	return wakeupTime;
}

/**
  * @brief	This function sets the Wakeup Auto Reload value, value that is loaded into the Wakeup Time register after wakeup timer triggers
  * @param	interfaceID: Which interface (chip) used
  * @param	wakeupTime: Wakeup Time Auto Reload Value to be programmed
  * @return	None
  */
void AX5043TimerSetWakeupAutoReloadValue(uint8_t interfaceID, uint16_t wakeupTime) {
	uint8_t config;
	config = (wakeupTime) & WAKEUPFREQ0_MASK;
	AX5043WriteShortAddress(interfaceID, WAKEUPFREQ0, &config, 1);
	config = (wakeupTime >> 8) & WAKEUPFREQ1_MASK;
	AX5043WriteShortAddress(interfaceID, WAKEUPFREQ1, &config, 1);
}

/**
  * @brief	This function gets the Wakeup Auto Reload value, value that is loaded into the Wakeup Time register after wakeup timer triggers
  * @param	interfaceID: Which interface (chip) used
  * @return	Wakeup Time Auto Reload Value programmed
  */
uint16_t AX5043TimerGetWakeupAutoReloadValue(uint8_t interfaceID) {
	uint16_t wakeupTime = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, WAKEUPFREQ0, &config, 1);
	wakeupTime = (config & WAKEUPFREQ0_MASK);
	AX5043ReadShortAddress(interfaceID, WAKEUPFREQ1, &config, 1);
	wakeupTime += (config & WAKEUPFREQ1_MASK) << 8;
	return wakeupTime;
}

/**
  * @brief	This function sets the Number of LPOSC clock cycles by which the Crystal is woken up before the main receiver
  * @param	interfaceID: Which interface (chip) used
  * @param	value: Number of LPOSC clock cycles
  * @return	None
  */
void AX5043TimerSetXOEarly(uint8_t interfaceID, uint8_t value) {
	AX5043WriteShortAddress(interfaceID, WAKEUPXOEARLY, &value, 1);
}

/**
  * @brief	This function gets the Number of LPOSC clock cycles by which the Crystal is woken up before the main receiver
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of LPOSC clock cycles
  */
uint8_t AX5043TimerGetXOEarly(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, WAKEUPXOEARLY, &config, 1);
	return config;
}
