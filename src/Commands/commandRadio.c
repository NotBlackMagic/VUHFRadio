#include "commandRadio.h"

uint8_t CommandRadioUHFSend(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+SEND-U=<length>\n", 17);
			break;
		}
		case CommandType_Query: {
			return 1;
		}
		case CommandType_Set: {
			uint16_t length;
			uint8_t txBytes[500];
			uint8_t txBytesCount = 0;

			sscanf(args, "%d", &length);

			if(length > 500 || length == 0) {
				return 1;
			}

			//Power Down Radio, needed be done before entering TX mode
			AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);

			USBVCPWrite(">\n", 2);

			uint8_t rxBytesTmp[500];
			uint16_t rxBytesCountTmp = 0;
			while(txBytesCount < length) {
				if(USBVCPRead(rxBytesTmp, &rxBytesCountTmp) == 1) {
					uint16_t i;
					for(i = 0; i < rxBytesCountTmp; i++) {
						txBytes[txBytesCount++] = rxBytesTmp[i];

						if(txBytesCount >= length) {
							break;
						}
					}
				}
			}

			//Send Packet
			RadioUHFEnterTX();
			RadioUHFWritePreamble(0x55, 20);
			RadioUHFWriteFrame(txBytes, txBytesCount);
			AX5043FIFOSetFIFOStatCommand(RADIO_UHF, FIFOStat_Commit);

			//Wait for Transmission Complete
			RadioState radioState = AX5043GeneralRadioState(RADIO_UHF);
			do {
				radioState = AX5043GeneralRadioState(RADIO_UHF);

				if(radioState == RadioState_TX || radioState == RadioState_TXTail) {
					GPIOWrite(GPIO_OUT_LED0, 1);
				}
				else {
					GPIOWrite(GPIO_OUT_LED0, 0);
				}

				Delay(10);
			} while(radioState != RadioState_Idle);

			//Enter RX mode
			RadioUHFEnterRX();

			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioVHFSend(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+SEND-V=<length>\n", 17);
			break;
		}
		case CommandType_Query: {
			return 1;
		}
		case CommandType_Set: {
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioUHFModConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+MOD-U=<Frequency>,<Datarate>,<Modulation>,<Deviation>\n", 56);
			break;
		}
		case CommandType_Query: {
			RadioConfigStruct radioUHFConfig;

			radioUHFConfig = RadioUHFGetModConfig();

			char modulation[10];
			switch(radioUHFConfig.modulation) {
				case ASK:
					sprintf(modulation, "ASK");
					break;
				case ASK_Coherent:
					sprintf(modulation, "ASK_Coherent");
					break;
				case PSK:
					sprintf(modulation, "PSK");
					break;
				case OQPSK:
					sprintf(modulation, "OQPSK");
					break;
				case MSK:
					sprintf(modulation, "MSK");
					break;
				case FSK:
					sprintf(modulation, "FSK");
					break;
				case FSK4:
					sprintf(modulation, "FSK4");
					break;
				case AFSK:
					sprintf(modulation, "AFSK");
					break;
				case FM:
					sprintf(modulation, "FM");
					break;
			}

			char string[100];
			uint8_t len = sprintf(string, "+MOD-U=%d,%d,%s,%d\n", radioUHFConfig.frequency, radioUHFConfig.datarate, modulation, radioUHFConfig.fskDeviation);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			char modulation[10];
			RadioConfigStruct radioUHFConfig;

			if(sscanf(args, "%u,%u,%[^,],%u", &radioUHFConfig.frequency, &radioUHFConfig.datarate, modulation, &radioUHFConfig.fskDeviation) != 0x04) {
				return 1;
			}

			if(strcmp(modulation, "ASK") == 0x00) {
				radioUHFConfig.modulation = ASK;
			}
			else if(strcmp(modulation, "ASK_Coherent") == 0x00) {
				radioUHFConfig.modulation = ASK_Coherent;
			}
			else if(strcmp(modulation, "PSK") == 0x00) {
				radioUHFConfig.modulation = PSK;
			}
			else if(strcmp(modulation, "OQPSK") == 0x00) {
				radioUHFConfig.modulation = OQPSK;
			}
			else if(strcmp(modulation, "MSK") == 0x00) {
				radioUHFConfig.modulation = MSK;
			}
			else if(strcmp(modulation, "FSK") == 0x00) {
				radioUHFConfig.modulation = FSK;
			}
			else if(strcmp(modulation, "FSK4") == 0x00) {
				radioUHFConfig.modulation = FSK4;
			}
			else if(strcmp(modulation, "AFSK") == 0x00) {
				radioUHFConfig.modulation = AFSK;
			}
			else if(strcmp(modulation, "FM") == 0x00) {
				radioUHFConfig.modulation = FM;
			}

			return RadioUHFModConfig(radioUHFConfig);
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioVHFModConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+MOD-V=<Frequency>,<Datarate>,<Modulation>,<Deviation>\n", 56);
			break;
		}
		case CommandType_Query: {
			RadioConfigStruct radioVHFConfig;

			radioVHFConfig = RadioVHFGetModConfig();

			char modulation[10];
			switch(radioVHFConfig.modulation) {
				case ASK:
					sprintf(modulation, "ASK");
					break;
				case ASK_Coherent:
					sprintf(modulation, "ASK_Coherent");
					break;
				case PSK:
					sprintf(modulation, "PSK");
					break;
				case OQPSK:
					sprintf(modulation, "OQPSK");
					break;
				case MSK:
					sprintf(modulation, "MSK");
					break;
				case FSK:
					sprintf(modulation, "FSK");
					break;
				case FSK4:
					sprintf(modulation, "FSK4");
					break;
				case AFSK:
					sprintf(modulation, "AFSK");
					break;
				case FM:
					sprintf(modulation, "FM");
					break;
			}

			char string[100];
			uint8_t len = sprintf(string, "+MOD-V=%d,%d,%s,%d\n", radioVHFConfig.frequency, radioVHFConfig.datarate, modulation, radioVHFConfig.fskDeviation);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			char modulation[10];
			RadioConfigStruct radioVHFConfig;

			if(sscanf(args, "%u,%u,%[^,],%u", &radioVHFConfig.frequency, &radioVHFConfig.datarate, modulation, &radioVHFConfig.fskDeviation) != 0x04) {
				return 1;
			}

			if(strcmp(modulation, "ASK") == 0x00) {
				radioVHFConfig.modulation = ASK;
			}
			else if(strcmp(modulation, "ASK_Coherent") == 0x00) {
				radioVHFConfig.modulation = ASK_Coherent;
			}
			else if(strcmp(modulation, "PSK") == 0x00) {
				radioVHFConfig.modulation = PSK;
			}
			else if(strcmp(modulation, "OQPSK") == 0x00) {
				radioVHFConfig.modulation = OQPSK;
			}
			else if(strcmp(modulation, "MSK") == 0x00) {
				radioVHFConfig.modulation = MSK;
			}
			else if(strcmp(modulation, "FSK") == 0x00) {
				radioVHFConfig.modulation = FSK;
			}
			else if(strcmp(modulation, "FSK4") == 0x00) {
				radioVHFConfig.modulation = FSK4;
			}
			else if(strcmp(modulation, "AFSK") == 0x00) {
				radioVHFConfig.modulation = AFSK;
			}
			else if(strcmp(modulation, "FM") == 0x00) {
				radioVHFConfig.modulation = FM;
			}

			return RadioVHFModConfig(radioVHFConfig);
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioUHFEncConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+ENC-U=<MSB>,<Inversion>,<Differential>,<Scramble>\n", 51);
			break;
		}
		case CommandType_Query: {
			uint8_t enableMSB = AX5043PacketGetMSBFirst(RADIO_UHF);
			uint8_t enableInversion = AX5043PacketIsEncodeBitInversionEnabled(RADIO_UHF);
			uint8_t enableDifferential = AX5043PacketIsEncodeDifferentialEnabled(RADIO_UHF);
			uint8_t enableScramble = AX5043PacketIsEncodeScrambleEnabled(RADIO_UHF);

			char string[100];
			uint8_t len = sprintf(string, "+ENC-U=%d,%d,%d,%d\n", enableMSB, enableInversion, enableDifferential, enableScramble);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int enableMSB = 0;
			int enableInversion = 0;
			int enableDifferential = 0;
			int enableScramble = 0;

			if(sscanf(args, "%d,%d,%d,%d", &enableMSB, &enableInversion, &enableDifferential, &enableScramble) != 0x04) {
				return 1;
			}

			AX5043PacketSetMSBFirst(RADIO_UHF, (uint8_t)enableMSB);
			AX5043PacketEnableEncodeBitInversion(RADIO_UHF, (uint8_t)enableInversion);
			AX5043PacketEnableEncodeDifferential(RADIO_UHF, (uint8_t)enableDifferential);
			AX5043PacketEnableEncodeScramble(RADIO_UHF, (uint8_t)enableScramble);
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioVHFEncConfig(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+ENC-V=<MSB>,<Inversion>,<Differential>,<Scramble>\n", 51);
			break;
		}
		case CommandType_Query: {
			uint8_t enableMSB = AX5043PacketGetMSBFirst(RADIO_VHF);
			uint8_t enableInversion = AX5043PacketIsEncodeBitInversionEnabled(RADIO_VHF);
			uint8_t enableDifferential = AX5043PacketIsEncodeDifferentialEnabled(RADIO_VHF);
			uint8_t enableScramble = AX5043PacketIsEncodeScrambleEnabled(RADIO_VHF);

			char string[100];
			uint8_t len = sprintf(string, "+ENC-V=%d,%d,%d,%d\n", enableMSB, enableInversion, enableDifferential, enableScramble);
			USBVCPWrite(string, len);
			break;
		}
		case CommandType_Set: {
			int enableMSB = 0;
			int enableInversion = 0;
			int enableDifferential = 0;
			int enableScramble = 0;

			if(sscanf(args, "%d,%d,%d,%d", &enableMSB, &enableInversion, &enableDifferential, &enableScramble) != 0x04) {
				return 1;
			}

			AX5043PacketSetMSBFirst(RADIO_VHF, (uint8_t)enableMSB);
			AX5043PacketEnableEncodeBitInversion(RADIO_VHF, (uint8_t)enableInversion);
			AX5043PacketEnableEncodeDifferential(RADIO_VHF, (uint8_t)enableDifferential);
			AX5043PacketEnableEncodeScramble(RADIO_VHF, (uint8_t)enableScramble);
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}
