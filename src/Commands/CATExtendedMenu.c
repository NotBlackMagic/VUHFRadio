#include "CATExtendedMenu.h"

//CAT Extended Menu Command Handlers

uint8_t CATCommandExtendedMenu(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	uint32_t menuSel = 0;
	if(CATASCIIToNumber(&data[3], 3, &menuSel) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	uint8_t status = 0x00;
	switch(menuSel) {
		case 0: {
			status = RadioSetExperimentalMode(radio, RadioExperimental_DSPMode);
			break;
		}
	}

	return status;
}
