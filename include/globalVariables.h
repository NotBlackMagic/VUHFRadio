#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax25.h"

typedef enum {
	AX_25_Mode,
	Raw_Bit_Mode,
	BER_Mode
} ModuleDataMode;

extern ModuleDataMode moduleDataMode;		//Working Mode configuration for the Module

extern AX25Struct uhfTXAX25Struct;			//Used to safe AX25 parameters to send
extern AX25FilterStruct uhfAX25FltStruct;	//USed to safe AX25 parameters to filter received messages

extern AX25Struct vhfTXAX25Struct;			//Used to safe AX25 parameters to send
extern AX25FilterStruct vhfAX25FltStruct;	//USed to safe AX25 parameters to filter received messages

void GlobalVariablesInit();

#ifdef __cplusplus
}
#endif

#endif /* GLOBALVARIABLES_H_ */
