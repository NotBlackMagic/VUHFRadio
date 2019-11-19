#ifndef COMMANDS_H_
#define COMMANDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#include "usb_vcp.h"

typedef enum {
	CommandType_Test = 0,	//Command Format: AT+<x>=?		Queries the Set Command's internal parameters and their range of values
	CommandType_Query = 1,	//Command Format: AT+<x>?		Returns the current value of parameters
	CommandType_Set = 2,	//Command Format: AT+<x>=<...>	Sets the value of user-defined parameters in commands, and runs these commands
	CommandType_Execute = 3	//Command Format: AT+<x>		Runs commands with no user-defined parameters
} CommandTypeEnum;

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_H_ */
