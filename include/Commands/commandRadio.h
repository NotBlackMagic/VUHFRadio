#ifndef COMMANDS_COMMANDRADIO_H_
#define COMMANDS_COMMANDRADIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commands.h"
#include "radio.h"

uint8_t CommandRadioUHFSend(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandRadioVHFSend(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandRadioUHFModConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandRadioVHFModConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandRadioUHFEncConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandRadioVHFEncConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_COMMANDRADIO_H_ */
