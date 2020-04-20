#ifndef RADIO_MORSE_H_
#define RADIO_MORSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "gpio.h"
#include "rcc.h"
#include "usb_vcp.h"

#include "radio.h"

void MorseStateMachine();
uint8_t MorseSymbolToASCII(uint32_t morseSymbol);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_MORSE_H_ */
