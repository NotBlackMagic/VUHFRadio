#include "morse.h"

#define MORSE_THRESHOLD_VHF				-90
#define MORSE_CALL_MS					5

uint8_t morseSymbolIndex = 0;
uint32_t morseSymbol = 0;
uint8_t morseASCIIFrameIndex = 0;
uint8_t morseASCIIFrame[100];

uint8_t morseLastState = 0;		//Saves last state, if low or high aka ON or OFF
uint16_t morseDeltaTime = 0;
uint32_t morseLastStateTime = 0;
uint32_t morseStateMachineTime = 0;
void MorseStateMachine() {
	if(morseStateMachineTime + MORSE_CALL_MS <= GetSysTick()) {
		morseStateMachineTime = GetSysTick();

		int8_t vhfRSSI = AX5043GeneralGetRSSI(RADIO_VHF);

		if(vhfRSSI > MORSE_THRESHOLD_VHF) {
			GPIOWrite(GPIO_OUT_LED3, 1);

			if(morseLastState == 0) {
				morseDeltaTime = GetSysTick() - morseLastStateTime;

				//This marks a transition, end of LOW time, check if was a SYMBOL SAPCE, LETTER SPACE or WORD SPACE
				if(morseDeltaTime > 29 && morseDeltaTime < 91) {
					//Last was a SYMBOL SPACE, is 1 time unit aka one "0"
					morseSymbol = (morseSymbol << 1) + 0x00;
					morseSymbolIndex += 1;
					if(morseSymbolIndex > 20) {
						morseSymbolIndex = 0;
					}
				}
				else if(morseDeltaTime > 149 && morseDeltaTime < 211) {
					//Last was a LETTER SPACE, is 3 time unit aka three "0"
					morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);

					morseSymbol = 0;
					morseSymbolIndex = 0;
				}
				else if(morseDeltaTime > 209 && morseDeltaTime < 271) {
					//Last was a SYMBOL SPACE + LETTER SPACE, is 3 time unit aka three "0"
					morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);

					morseSymbol = 0;
					morseSymbolIndex = 0;
				}
				else if(morseDeltaTime > 389 && morseDeltaTime < 451) {
					//Last was a WORD SPACE, is 7 time unit aka seven "0"
					morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);
					morseASCIIFrame[morseASCIIFrameIndex++] = ' ';

					morseSymbol = 0;
					morseSymbolIndex = 0;
				}
				else if(morseDeltaTime > 569 && morseDeltaTime < 631) {
					//Last was a LETTER SPACE + WORD SPACE, is 7+3 time unit aka ten "0"
					morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);
					morseASCIIFrame[morseASCIIFrameIndex++] = ' ';

					morseSymbol = 0;
					morseSymbolIndex = 0;
				}
				else if(morseDeltaTime > 629 && morseDeltaTime < 691) {
					//Last was a SYMBOL SPACE + LETTER SPACE + WORD SPACE, is 7+3 time unit aka ten "0"
					morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);
					morseASCIIFrame[morseASCIIFrameIndex++] = ' ';

					morseSymbol = 0;
					morseSymbolIndex = 0;
				}
				else {
					//Invalid Time
					morseSymbol = 0;
					morseSymbolIndex = 0;
					morseASCIIFrameIndex = 0;
				}

				morseLastStateTime = GetSysTick();
			}

			morseLastState = 1;
		}
		else {
			GPIOWrite(GPIO_OUT_LED3, 0);

			if(morseLastState == 1) {
				morseDeltaTime = GetSysTick() - morseLastStateTime;

				//This marks a transition, end of HIGH time, check if was a DOT or DASH
				if(morseDeltaTime > 29 && morseDeltaTime < 91) {
					//Last was a DOT, is 1 time unit aka one "1"
					morseSymbol = (morseSymbol << 1) + 0x01;
					morseSymbolIndex += 1;
					if(morseSymbolIndex > 20) {
						morseSymbolIndex = 0;
					}
				}
				else if(morseDeltaTime > 149 && morseDeltaTime < 211) {
					//Last was a DASH, is 3 time units aka three "1"
					morseSymbol = (morseSymbol << 1) + 0x01;
					morseSymbolIndex += 1;
					if(morseSymbolIndex > 20) {
						morseSymbolIndex = 0;
					}

					morseSymbol = (morseSymbol << 1) + 0x01;
					morseSymbolIndex += 1;
					if(morseSymbolIndex > 20) {
						morseSymbolIndex = 0;
					}

					morseSymbol = (morseSymbol << 1) + 0x01;
					morseSymbolIndex += 1;
					if(morseSymbolIndex > 20) {
						morseSymbolIndex = 0;
					}
				}
				else {
					//Invalid time
					morseSymbol = 0;
					morseSymbolIndex = 0;
					morseASCIIFrameIndex = 0;
				}

				morseLastStateTime = GetSysTick();
			}
			else if((GetSysTick() - morseLastStateTime) > 700 && morseSymbolIndex > 0) {
				//Morse Timeout, use as end of frame
				morseASCIIFrame[morseASCIIFrameIndex++] = MorseSymbolToASCII(morseSymbol);
				morseASCIIFrame[morseASCIIFrameIndex++] = '\0';

				char str[200];
				uint8_t len = sprintf(str, "VHF+MORSE=%s\n", morseASCIIFrame);
				USBVCPWrite(str, len);

				morseSymbol = 0;
				morseSymbolIndex = 0;
				morseASCIIFrameIndex = 0;
			}

			morseLastState = 0;
		}
	}
}

uint8_t MorseSymbolToASCII(uint32_t morseSymbol) {
	uint8_t ascii = 0;
	switch(morseSymbol) {
		case 0x17:
			ascii = 'A';
			break;
		case 0x01D5:
			ascii = 'B';
			break;
		case 0x075D:
			ascii = 'C';
			break;
		case 0x75:
			ascii = 'D';
			break;
		case 0x01:
			ascii = 'E';
			break;
		case 0x015D:
			ascii = 'F';
			break;
		case 0x01DD:
			ascii = 'G';
			break;
		case 0x55:
			ascii = 'H';
			break;
		case 0x05:
			ascii = 'I';
			break;
		case 0x1777:
			ascii = 'J';
			break;
		case 0x01D7:
			ascii = 'K';
			break;
		case 0x0175:
			ascii = 'L';
			break;
		case 0x77:
			ascii = 'M';
			break;
		case 0x1D:
			ascii = 'N';
			break;
		case 0x0777:
			ascii = 'O';
			break;
		case 0x05DD:
			ascii = 'P';
			break;
		case 0x1DD7:
			ascii = 'Q';
			break;
		case 0x5D:
			ascii = 'R';
			break;
		case 0x15:
			ascii = 'S';
			break;
		case 0x07:
			ascii = 'T';
			break;
		case 0x57:
			ascii = 'U';
			break;
		case 0x0157:
			ascii = 'V';
			break;
		case 0x0177:
			ascii = 'W';
			break;
		case 0x0757:
			ascii = 'X';
			break;
		case 0x1D77:
			ascii = 'Y';
			break;
		case 0x0775:
			ascii = 'Z';
			break;
		case 0x017777:
			ascii = '1';
			break;
		case 0x5777:
			ascii = '2';
			break;
		case 0x1577:
			ascii = '3';
			break;
		case 0x0557:
			ascii = '4';
			break;
		case 0x0155:
			ascii = '5';
			break;
		case 0x0755:
			ascii = '6';
			break;
		case 0x1DD5:
			ascii = '7';
			break;
		case 0x7775:
			ascii = '8';
			break;
		case 0x01DDDD:
			ascii = '9';
			break;
		case 0x077777:
			ascii = '0';
			break;
	}

	return ascii;
}
