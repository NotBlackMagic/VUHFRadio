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

#include "radioConfigs.h"

void RadioInterfacesInit();
uint8_t RadioInitBaseConfiguration(uint8_t radio);
uint8_t RadioSetFullConfiguration(uint8_t radio, RadioConfigsStruct configuration);

uint8_t RadioSetCenterFrequency(uint8_t radio, uint32_t frequency);
uint8_t RadioSetAFCRange(uint8_t radio, uint32_t range);
uint8_t RadioSetAGCSpeed(uint8_t radio, uint8_t speed);
uint8_t RadioSetFMDetectorBandwidth(uint8_t radio, uint32_t bandwidth);
uint8_t RadioSetCRCMode(uint8_t radio, RadioCRC crcMode);
uint8_t RadioSetEncodingMode(uint8_t radio, RadioEncoder encMode);
uint8_t RadioSetFramingMode(uint8_t radio, RadioFraming frmMode);
uint8_t RadioSetModulation(uint8_t radio, RadioModulation modulation);
uint8_t RadioSetOperationMode(uint8_t radio, RadioMode opMode);
uint8_t RadioSetTXPower(uint8_t radio, int8_t power);
uint8_t RadioSetBandwidth(uint8_t radio, uint32_t bandwidth);
uint8_t RadioSetIF(uint8_t radio, uint32_t frequency);
uint8_t RadioSetRXDatarate(uint8_t radio, uint32_t bitrate);
uint8_t RadioSetRXDeviationSensitivity(uint8_t radio, uint32_t sensitivity);
uint8_t RadioSetTXDatarate(uint8_t radio, uint32_t bitrate);
uint8_t RadioSetTXDeviation(uint8_t radio, uint32_t deviation);
uint8_t RadioSetAFSKSpaceFreq(uint8_t radio, uint16_t spaceFreq);
uint8_t RadioSetAFSKMarkFreq(uint8_t radio, uint16_t markFreq);
uint8_t RadioWriteFIFORepeatData(uint8_t radio, uint8_t dataByte, uint8_t count);
uint8_t RadioWriteFIFOData(uint8_t radio, uint8_t data[], uint8_t dataLength);

#ifdef __cplusplus
}
#endif

#endif /* RADIOCOMMANDS_H_ */
