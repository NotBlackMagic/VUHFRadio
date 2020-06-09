#ifndef RADIOSTATEMACHINE_H_
#define RADIOSTATEMACHINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"

#include "usb_vcp.h"

#include "ax25.h"
#include "radio.h"

#include "globalVariables.h"

extern uint32_t errorBits;
extern uint32_t totalBits;

void RadioStateMachine();

void RadioDCLKVHFHandler();
void RadioDCLKUHFHandler();

#ifdef __cplusplus
}
#endif

#endif /* RADIOSTATEMACHINE_H_ */
