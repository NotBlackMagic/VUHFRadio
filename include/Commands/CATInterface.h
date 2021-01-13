#ifndef COMMANDS_CATCOMMANDINTERFACE_H_
#define COMMANDS_CATCOMMANDINTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#include "radioConfigs.h"
#include "radioCommands.h"

#include "memoryChannelConfigs.h"

uint8_t CATInterfaceHandler(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_CATCOMMANDINTERFACE_H_ */
