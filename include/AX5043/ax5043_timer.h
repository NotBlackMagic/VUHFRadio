#ifndef AX5043_AX5043_TIMER_H_
#define AX5043_AX5043_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of TIMER Register
#define TIMER0_MASK							0xFF
#define TIMER1_MASK							0xFF
#define TIMER2_MASK							0xFF

//Register Configuration of WAKEUPTIMER Register
#define WAKEUPTIMER0_MASK					0xFF
#define WAKEUPTIMER1_MASK					0xFF

//Register Configuration of WAKEUP Register
#define WAKEUP0_MASK						0xFF
#define WAKEUP1_MASK						0xFF

//Register Configuration of WAKEUPFREQ Register
#define WAKEUPFREQ0_MASK					0xFF
#define WAKEUPFREQ1_MASK					0xFF

//Register Configuration of WAKEUPXOEARLY Register
#define WAKEUPXOEARLY_MASK					0xFF

uint32_t AX5043TimerGetTimerValue(uint8_t interfaceID);
uint16_t AX5043TimerGetWakeupTimerValue(uint8_t interfaceID);
void AX5043TimerSetWakeupTimeValue(uint8_t interfaceID, uint16_t wakeupTime);
uint16_t AX5043TimerGetWakeupTimeValue(uint8_t interfaceID);
void AX5043TimerSetWakeupAutoReloadValue(uint8_t interfaceID, uint16_t wakeupTime);
uint16_t AX5043TimerGetWakeupAutoReloadValue(uint8_t interfaceID);
void AX5043TimerSetXOEarly(uint8_t interfaceID, uint8_t value);
uint8_t AX5043TimerGetXOEarly(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_TIMER_H_ */
