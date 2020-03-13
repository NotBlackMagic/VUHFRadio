#include "commandAX25.h"

uint8_t CommandAX25EnabledFilterUHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+AX-ENFLT-U=<Source>,<Destination>,<Control>,<PID>\n", 51);
			break;
		}
		case CommandType_Query: {
			char string[100];
			uint8_t len = sprintf(string, "+AX-ENFLT-U=%d,%d,%d,%d\n", uhfAX25FltStruct.onSourceAddress, uhfAX25FltStruct.onDestinationAddress, uhfAX25FltStruct.onControlField, uhfAX25FltStruct.onPIDField);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int flt1, flt2, flt3, flt4;
			if(sscanf(args, "%d,%d,%d,%d", &flt1, &flt2, &flt3, &flt4) != 0x04) {
				return 1;
			}

			if(flt1 > 0x01 || flt2 > 0x01 || flt3 > 0x01 || flt4 > 0x01) {
				return 1;
			}

			uhfAX25FltStruct.onSourceAddress = (uint8_t)flt1;
			uhfAX25FltStruct.onDestinationAddress = (uint8_t)flt2;
			uhfAX25FltStruct.onControlField = (uint8_t)flt3;
			uhfAX25FltStruct.onPIDField = (uint8_t)flt4;

			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandAX25EnabledFilterVHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+AX-ENFLT-V=<Source>,<Destination>,<Control>,<PID>\n", 51);
			break;
		}
		case CommandType_Query: {
			char string[100];
			uint8_t len = sprintf(string, "+AX-ENFLT-V=%d,%d,%d,%d\n", vhfAX25FltStruct.onSourceAddress, vhfAX25FltStruct.onDestinationAddress, vhfAX25FltStruct.onControlField, vhfAX25FltStruct.onPIDField);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int flt1, flt2, flt3, flt4;
			if(sscanf(args, "%d,%d,%d,%d", &flt1, &flt2, &flt3, &flt4) != 0x04) {
				return 1;
			}

			if(flt1 > 0x01 || flt2 > 0x01 || flt3 > 0x01 || flt4 > 0x01) {
				return 1;
			}

			vhfAX25FltStruct.onSourceAddress = (uint8_t)flt1;
			vhfAX25FltStruct.onDestinationAddress = (uint8_t)flt2;
			vhfAX25FltStruct.onControlField = (uint8_t)flt3;
			vhfAX25FltStruct.onPIDField = (uint8_t)flt4;

			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandAX25FilterValuesUHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+AX-FLT-U=<Source>,<Destination>,<Control>,<PID>\n", 49);
			break;
		}
		case CommandType_Query: {
			char string[100];
			uint8_t len = sprintf(string, "+AX-FLT-U=%s,%s,%d,%d\n", uhfAX25FltStruct.sourceAddress, uhfAX25FltStruct.destinationAddress, uhfAX25FltStruct.control, uhfAX25FltStruct.pid);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int ctrl, pid;
			if(sscanf(args, "%7[^,],%7[^,],%d,%d", uhfAX25FltStruct.sourceAddress, uhfAX25FltStruct.destinationAddress, &ctrl, &pid) != 0x04) {
				return 1;
			}

			uhfAX25FltStruct.control = ctrl;
			uhfAX25FltStruct.pid = pid;
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandAX25FilterValuesVHF(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+AX-FLT-V=<Source>,<Destination>,<Control>,<PID>\n", 49);
			break;
		}
		case CommandType_Query: {
			char string[100];
			uint8_t len = sprintf(string, "+AX-FLT-V=%s,%s,%d,%d\n", vhfAX25FltStruct.sourceAddress, vhfAX25FltStruct.destinationAddress, vhfAX25FltStruct.control, vhfAX25FltStruct.pid);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int ctrl, pid;
			if(sscanf(args, "%7[^,],%7[^,],%d,%d", vhfAX25FltStruct.sourceAddress, vhfAX25FltStruct.destinationAddress, &ctrl, &pid) != 0x04) {
				return 1;
			}

			vhfAX25FltStruct.control = ctrl;
			vhfAX25FltStruct.pid = pid;
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}
