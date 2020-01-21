#ifndef COMMANDS_ATCMDINTER_H_
#define COMMANDS_ATCMDINTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef enum {
	ATCmdType_Test = 0,		//Command Format: AT+<x>=?		Queries the Set Command's internal parameters and their range of values
	ATCmdType_Query = 1,	//Command Format: AT+<x>?		Returns the current value of parameters
	ATCmdType_Set = 2,		//Command Format: AT+<x>=<...>	Sets the value of user-defined parameters in commands, and runs these commands
	ATCmdType_Execute = 3	//Command Format: AT+<x>		Runs commands with no user-defined parameters
} ATCmdTypeEnum;

typedef struct {
	uint8_t header[3];
	uint8_t cmd[11];
	ATCmdTypeEnum type;
	uint8_t args[512];
} ATCmdStruct;

uint8_t ATCmdFraming(uint8_t data[], uint16_t dataLength, uint8_t** dataOut, uint16_t* dataOutLength);
uint8_t ATCmdParse(uint8_t framed[], uint16_t framedLength, ATCmdStruct *atCmdStruct);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_ATCMDINTER_H_ */
