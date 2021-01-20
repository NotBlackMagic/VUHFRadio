#ifndef RADIOSTATEMACHINE_H_
#define RADIOSTATEMACHINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"

#include "radioCommands.h"
#include "radioConfigs.h"

//Platform Specific Peripherals Includes
#include "gpio.h"

extern volatile uint32_t errorBits;
extern volatile uint32_t totalBits;

extern volatile uint8_t newFIFODataPacketA;
extern volatile uint8_t fifoDataPacketLengthA;
extern volatile uint8_t fifoDataPacketA[255];
extern volatile uint8_t newFIFODataPacketB;
extern volatile uint8_t fifoDataPacketLengthB;
extern volatile uint8_t fifoDataPacketB[255];

void RadioAIRQHandler();
void RadioBIRQHandler();
void RadioTrackingUpdateHandler();
void RadioADCLKHandler();
void RadioBDCLKHandler();

#ifdef __cplusplus
}
#endif

#endif /* RADIOSTATEMACHINE_H_ */
