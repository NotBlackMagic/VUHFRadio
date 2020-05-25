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

void RadioStateMachine(uint8_t radio);

#ifdef __cplusplus
}
#endif

#endif /* RADIOSTATEMACHINE_H_ */
