#ifndef COMMANDS_CATHELPER_H_
#define COMMANDS_CATHELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

uint32_t UIntPow(uint8_t base, uint8_t exp);
uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_CATHELPER_H_ */
