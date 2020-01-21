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

uint8_t CommandRadioUHFRFFrequency(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+RFFREQ-U:<frequency>\n", 22);
			break;
		}
		case CommandType_Query: {
			uint32_t freq = AX5043SynthGetFrequencyA(RADIO_UHF);
			freq = (uint32_t)(((float)freq - 0.5f) * (FXTAL / 16777216.f));

			char str[200];
			uint8_t len = sprintf(str, "%d", freq);
			USBVCPWrite(str, len);
			break;
		}
		case CommandType_Set: {
			uint32_t freq = 0;

			sscanf(args, "%d", &freq);

			//Set Central Frequency
			if(freq > RADIO_UHF_FREQ_MAX || freq < RADIO_UHF_FREQ_MIN) {
				return 1;
			}
			freq = (uint32_t)((freq * (16777216.f / FXTAL)) + 0.5f);
			AX5043SynthSetFrequencyA(RADIO_UHF, freq);

			//Perform auto ranging
			AX5043SynthStartAutoRangingA(RADIO_VHF);
			while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete
			break;
		}
		case CommandType_Execute: {
			return 1;
		}
	}

	return 0;
}

uint8_t CommandRadioUHFSend(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+SEND-U:<length>\n", 17);
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
