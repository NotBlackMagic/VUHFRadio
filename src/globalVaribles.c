#include "globalVariables.h"

ModuleDataMode moduleDataMode;		//Working Mode configuration for the Module

AX25Struct uhfTXAX25Struct;			//Used to safe AX25 parameters to send
AX25FilterStruct uhfAX25FltStruct;	//Used to safe AX25 parameters to filter received messages

AX25Struct vhfTXAX25Struct;			//Used to safe AX25 parameters to send
AX25FilterStruct vhfAX25FltStruct;	//Used to safe AX25 parameters to filter received messages

void GlobalVariablesInit() {
	//Init Module Data Mode
	moduleDataMode = BER_Mode;

	//Init UHF TX AX25 Struct
	uhfTXAX25Struct.sourceAddress[0] = 'A';
	uhfTXAX25Struct.sourceAddress[1] = 'A';
	uhfTXAX25Struct.sourceAddress[2] = 'A';
	uhfTXAX25Struct.sourceAddress[3] = 'A';
	uhfTXAX25Struct.sourceAddress[4] = 'A';
	uhfTXAX25Struct.sourceAddress[5] = 'A';
	uhfTXAX25Struct.sourceAddress[6] = 'A';
	uhfTXAX25Struct.sourceAddress[7] = '\0';

	uhfTXAX25Struct.destinationAddress[0] = 'A';
	uhfTXAX25Struct.destinationAddress[1] = 'A';
	uhfTXAX25Struct.destinationAddress[2] = 'A';
	uhfTXAX25Struct.destinationAddress[3] = 'A';
	uhfTXAX25Struct.destinationAddress[4] = 'A';
	uhfTXAX25Struct.destinationAddress[5] = 'A';
	uhfTXAX25Struct.destinationAddress[6] = 'A';
	uhfTXAX25Struct.destinationAddress[7] = '\0';

	uhfTXAX25Struct.control = 0;
	uhfTXAX25Struct.pid = 0;

	//Init UHF RX Filter AX25 Struct
	uhfAX25FltStruct.sourceAddress[0] = 'A';
	uhfAX25FltStruct.sourceAddress[1] = 'A';
	uhfAX25FltStruct.sourceAddress[2] = 'A';
	uhfAX25FltStruct.sourceAddress[3] = 'A';
	uhfAX25FltStruct.sourceAddress[4] = 'A';
	uhfAX25FltStruct.sourceAddress[5] = 'A';
	uhfAX25FltStruct.sourceAddress[6] = 'A';
	uhfAX25FltStruct.sourceAddress[7] = '\0';

	uhfAX25FltStruct.destinationAddress[0] = 'A';
	uhfAX25FltStruct.destinationAddress[1] = 'A';
	uhfAX25FltStruct.destinationAddress[2] = 'A';
	uhfAX25FltStruct.destinationAddress[3] = 'A';
	uhfAX25FltStruct.destinationAddress[4] = 'A';
	uhfAX25FltStruct.destinationAddress[5] = 'A';
	uhfAX25FltStruct.destinationAddress[6] = 'A';
	uhfAX25FltStruct.destinationAddress[7] = '\0';

	uhfAX25FltStruct.control = 0;
	uhfAX25FltStruct.pid = 0;

	uhfAX25FltStruct.onSourceAddress = 0;
	uhfAX25FltStruct.onDestinationAddress = 0;
	uhfAX25FltStruct.onControlField = 0;
	uhfAX25FltStruct.onPIDField = 0;

	//Init VHF TX AX25 Struct
	vhfTXAX25Struct.sourceAddress[0] = 'A';
	vhfTXAX25Struct.sourceAddress[1] = 'A';
	vhfTXAX25Struct.sourceAddress[2] = 'A';
	vhfTXAX25Struct.sourceAddress[3] = 'A';
	vhfTXAX25Struct.sourceAddress[4] = 'A';
	vhfTXAX25Struct.sourceAddress[5] = 'A';
	vhfTXAX25Struct.sourceAddress[6] = 'A';
	vhfTXAX25Struct.sourceAddress[7] = '\0';

	vhfTXAX25Struct.destinationAddress[0] = 'A';
	vhfTXAX25Struct.destinationAddress[1] = 'A';
	vhfTXAX25Struct.destinationAddress[2] = 'A';
	vhfTXAX25Struct.destinationAddress[3] = 'A';
	vhfTXAX25Struct.destinationAddress[4] = 'A';
	vhfTXAX25Struct.destinationAddress[5] = 'A';
	vhfTXAX25Struct.destinationAddress[6] = 'A';
	vhfTXAX25Struct.destinationAddress[7] = '\0';

	vhfTXAX25Struct.control = 0;
	vhfTXAX25Struct.pid = 0;

	//Init VHF RX Filter AX25 Struct
	vhfAX25FltStruct.sourceAddress[0] = 'A';
	vhfAX25FltStruct.sourceAddress[1] = 'A';
	vhfAX25FltStruct.sourceAddress[2] = 'A';
	vhfAX25FltStruct.sourceAddress[3] = 'A';
	vhfAX25FltStruct.sourceAddress[4] = 'A';
	vhfAX25FltStruct.sourceAddress[5] = 'A';
	vhfAX25FltStruct.sourceAddress[6] = 'A';
	vhfAX25FltStruct.sourceAddress[7] = '\0';

	vhfAX25FltStruct.destinationAddress[0] = 'A';
	vhfAX25FltStruct.destinationAddress[1] = 'A';
	vhfAX25FltStruct.destinationAddress[2] = 'A';
	vhfAX25FltStruct.destinationAddress[3] = 'A';
	vhfAX25FltStruct.destinationAddress[4] = 'A';
	vhfAX25FltStruct.destinationAddress[5] = 'A';
	vhfAX25FltStruct.destinationAddress[6] = 'A';
	vhfAX25FltStruct.destinationAddress[7] = '\0';

	vhfAX25FltStruct.control = 0;
	vhfAX25FltStruct.pid = 0;

	vhfAX25FltStruct.onSourceAddress = 0;
	vhfAX25FltStruct.onDestinationAddress = 0;
	vhfAX25FltStruct.onControlField = 0;
	vhfAX25FltStruct.onPIDField = 0;
}
