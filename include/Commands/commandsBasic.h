#ifndef COMMANDS_COMMANDSBASIC_H_
#define COMMANDS_COMMANDSBASIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "adc.h"
#include "gpio.h"

#include "commands.h"

uint8_t CommandBasicTemplate(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandBasicPTTU(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandBasicPTTV(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandBasicCurrent(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_COMMANDSBASIC_H_ */
