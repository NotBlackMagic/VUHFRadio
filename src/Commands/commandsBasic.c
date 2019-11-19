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

uint8_t CommandBasicCurrentVCCU(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		uint16_t current = ADC1Read(ADC_CH_I_VCC_U);
		current = (current * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		char string[100];
		sprintf(string, "VCC U Current: %umA \n", current);
		USBVCPWrite(string, strlen(string));
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}

uint8_t CommandBasicCurrentVCCV(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		uint16_t current = ADC1Read(ADC_CH_I_VCC_V);
		current = (current * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		char string[100];
		sprintf(string, "VCC V Current: %umA \n", current);
		USBVCPWrite(string, strlen(string));
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}

uint8_t CommandBasicCurrentVCCM(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		uint16_t current = ADC1Read(ADC_CH_I_VCC_M);
		current = (current * 625) / 12288;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		char string[100];
		sprintf(string, "VCC MCU Current: %umA \n", current);
		USBVCPWrite(string, strlen(string));
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}

uint8_t CommandBasicCurrent5V(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	if(commandType == CommandType_Query) {
		uint16_t current = ADC1Read(ADC_CH_I_5V);
		current = (current * 6875) / 53248;	//Converts from ADC code (12 bits) to current in mA (Vo=IsRsRl/5K)
		char string[100];
		sprintf(string, "USB/5V Current: %umA \n", current);
		USBVCPWrite(string, strlen(string));
	}
	else {
		//Not Valid Command Type
		return 1;
	}

	return 0;
}
