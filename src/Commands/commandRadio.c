#include "commandRadio.h"

uint8_t CommandRadioUHFModulation(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+MOD-U:<modulation>\n", 18);
			break;
		}
		case CommandType_Query: {
			Modulations modulation = AX5043GeneralGetModulation(RADIO_UHF);
			switch(modulation) {
				case ASK:
					USBVCPWrite("ASK\n", 4);
					break;
				case ASK_Coherent:
					USBVCPWrite("ASK Coherent\n", 13);
					break;
				case PSK:
					USBVCPWrite("PSK\n", 4);
					break;
				case OQSK:
					USBVCPWrite("OQSK\n", 5);
					break;
				case MSK:
					USBVCPWrite("MSK\n", 4);
					break;
				case FSK:
					USBVCPWrite("FSK\n", 4);
					break;
				case FSK4:
					USBVCPWrite("FSK4\n", 5);
					break;
				case AFSK:
					USBVCPWrite("AFSK\n", 5);
					break;
				case FM:
					USBVCPWrite("FM\n", 3);
					break;
			}
			break;
		}
		case CommandType_Set: {
			if(strcmp(args, "ASK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, ASK);
			}
			else if(strcmp(args, "ASK Coherent") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, ASK_Coherent);
			}
			else if(strcmp(args, "PSK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, PSK);
			}
			else if(strcmp(args, "OQSK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, OQSK);
			}
			else if(strcmp(args, "MSK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, MSK);
			}
			else if(strcmp(args, "FSK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, FSK);
			}
			else if(strcmp(args, "FSK4") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, FSK4);
			}
			else if(strcmp(args, "AFSK") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, AFSK);
			}
			else if(strcmp(args, "FM") == 0) {
				AX5043GeneralSetModulation(RADIO_UHF, FM);
			}
			else {
				return 1;
			}
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}
