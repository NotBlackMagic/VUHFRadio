#ifndef RADIO_H_
#define RADIO_H_

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

#define RADIO_UHF					0
#define RADIO_VHF					1

void RadioInterfacesInit();
void RadioVHFInit();
void RadioUHFInit();
void RadioVHFEnterTX();
void RadioUHFEnterTX();
void RadioVHFWriteFrame(uint8_t data[], uint8_t dataLength);
void RadioUHFWriteFrame(uint8_t data[], uint8_t dataLength);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_H_ */
