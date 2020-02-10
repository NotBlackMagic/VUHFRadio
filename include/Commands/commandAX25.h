#ifndef COMMANDS_COMMANDAX25_H_
#define COMMANDS_COMMANDAX25_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax25.h"
#include "commands.h"
#include "globalVariables.h"

uint8_t CommandAX25EnabledFilterUHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandAX25EnabledFilterVHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandAX25FilterValuesUHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandAX25FilterValuesVHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_COMMANDAX25_H_ */
