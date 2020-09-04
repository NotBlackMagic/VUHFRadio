#ifndef COMMANDS_CATCOMMANDINTERFACE_H_
#define COMMANDS_CATCOMMANDINTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

uint8_t CATInterfaceHandler(uint8_t* data, uint16_t dataLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_CATCOMMANDINTERFACE_H_ */
