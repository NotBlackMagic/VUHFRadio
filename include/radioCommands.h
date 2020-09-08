#ifndef RADIOCOMMANDS_H_
#define RADIOCOMMANDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_baseband.h"
#include "ax5043_fifo.h"
#include "ax5043_general.h"
#include "ax5043_gpio.h"
#include "ax5043_interface.h"
#include "ax5043_irq.h"
#include "ax5043_lposc.h"
#include "ax5043_packet.h"
#include "ax5043_pllparam.h"
#include "ax5043_pwr.h"
#include "ax5043_rxparam.h"
#include "ax5043_rxtracking.h"
#include "ax5043_synth.h"
#include "ax5043_timer.h"
#include "ax5043_txparam.h"

#define RADIO_A								0
#define RADIO_B								1

#define RADIO_A_XTAL						16000000	//Xtal Frequency in Hz of Radio A
#define RADIO_B_XTAL						16000000	//Xtal Frequency in Hz of Radio A

#define RADIO_A_FREQ_MAX					437000000
#define RADIO_A_FREQ_MIN					435000000

#define RADIO_B_FREQ_MAX					147000000
#define RADIO_B_FREQ_MIN					145000000

uint8_t RadioSetCenterFrequency(uint8_t radio, uint32_t frequency);

#ifdef __cplusplus
}
#endif

#endif /* RADIOCOMMANDS_H_ */
