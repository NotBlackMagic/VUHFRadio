#ifndef COMMANDS_CATEXTENDEDMENU_H_
#define COMMANDS_CATEXTENDEDMENU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#include "radioConfigs.h"
#include "radioCommands.h"

#include "memoryChannelConfigs.h"

#include "config.h"

#include "CATHelper.h"

uint8_t CATCommandExtendedMenu(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_CATEXTENDEDMENU_H_ */
