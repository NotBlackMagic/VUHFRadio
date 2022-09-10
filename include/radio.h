#ifndef RADIO_H_
#define RADIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "math.h"
#include "stdlib.h"

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

#define FXTAL						16000000	//Xtal Frequency in Hz

#define RADIO_UHF_FREQ_MAX			437000000
#define RADIO_UHF_FREQ_MIN			435000000

typedef struct {
	//Radio Modulation Configuration
	uint32_t frequency;
	uint8_t modulation;
	uint32_t datarate;
	uint32_t fskDeviation;
	uint16_t afcRange;

	//This are variables filled out by Radio*HFConfig, don't need to be filled
	uint16_t afskSpaceRX;
	uint16_t afskMarkRX;
	uint16_t afskSpaceTX;
	uint16_t afskMarkTX;
} RadioConfigStruct;

//void RadioInterfacesInit();
//void RadioVHFInit();
void RadioUHFInit();
//uint8_t RadioVHFModConfig(RadioConfigStruct configuration);
uint8_t RadioUHFModConfig(RadioConfigStruct configuration);
//RadioConfigStruct RadioVHFGetModConfig();
RadioConfigStruct RadioUHFGetModConfig();

uint8_t RadioUHFSetRFFrequency(uint32_t frequency);
//uint8_t RadioVHFSetRFFrequency(uint32_t frequency);

void RadioUHFEnterAMMode(uint32_t frequency);
void RadioUHFEnterFMMode(uint32_t frequency);
//void RadioVHFEnterAMMode(uint32_t frequency);
//void RadioVHFEnterFMMode(uint32_t frequency);
//void RadioVHFEnterTX();
void RadioUHFEnterTX();
void RadioUHFEnterRX();
//void RadioVHFEnterRX();

//void RadioVHFWritePreamble(uint8_t symbol, uint8_t length);
void RadioUHFWritePreamble(uint8_t symbol, uint8_t length);
//void RadioVHFWriteFrame(uint8_t data[], uint8_t dataLength);
void RadioUHFWriteFrame(uint8_t data[], uint8_t dataLength);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_H_ */
