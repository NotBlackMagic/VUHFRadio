#include "commandsBasic.h"

uint8_t CommandBasicTemplate(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			break;
		}
		case CommandType_Query: {
			break;
		}
		case CommandType_Set: {
			break;
		}
		case CommandType_Execute: {
			break;
		}
	}

	return 0;
}

uint8_t CommandBasicPTTU(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		if(GPIORead(GPIO_IN_PTT_U)) {
			USBVCPWrite("PTT U SET \n", 11);
		}
		else {
			USBVCPWrite("PTT U NOT SET \n", 15);
		}
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}

uint8_t CommandBasicPTTV(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		if(GPIORead(GPIO_IN_PTT_V)) {
			USBVCPWrite("PTT V SET \n", 11);
		}
		else {
			USBVCPWrite("PTT V NOT SET \n", 15);
		}
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}

uint8_t CommandBasicCurrent(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		uint16_t currentU = ADC1Read(ADC_CH_I_VCC_U);
		currentU = (currentU * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		uint16_t currentV = ADC1Read(ADC_CH_I_VCC_V);
		currentV = (currentV * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		uint16_t currentM = ADC1Read(ADC_CH_I_VCC_M);
		currentM = (currentM * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		uint16_t current5V = ADC1Read(ADC_CH_I_5V);
		current5V = (current5V * 6875) / 53248;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)

		char string[100];
		sprintf(string, "Current: 5V: %umA; VCC-M: %umA; VCC-U: %umA; VCC-V: %umA \n", current5V, currentM, currentU, currentV);
		USBVCPWrite(string, strlen(string));
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}
