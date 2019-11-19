#include "commandHandler.h"

const CommandStruct commandArray[COMMAND_LENGTH] = {
		{0, "TEST", "This is a Test Function \n", CommandTest},
		{1, "LIST", "List all available commands \n", CommandList},
		{2, "PTT-U", "Get PTT UHF State \n", CommandBasicPTTU},
		{3, "PTT-V", "Get PTT VHF State \n", CommandBasicPTTV},
		{4, "CUR-U", "Get Current VCC U \n", CommandBasicCurrentVCCU},
		{5, "CUR-V", "Get Current VCC V \n", CommandBasicCurrentVCCV},
		{6, "CUR-M", "Get Current VCC MCU \n", CommandBasicCurrentVCCM},
		{7, "CUR-5V", "Get Current 5V/USB \n", CommandBasicCurrent5V}
};

uint8_t CommandHandler(uint8_t* command, uint8_t* args, CommandTypeEnum commandType) {
	uint8_t error;

	//Run through the command array and find matching command
	uint16_t i;
	for(i = 0; i < COMMAND_LENGTH; i++) {
		if(strcmp(command, commandArray[i].commandString) == 0) {
			error = commandArray[i].commandFunction(commandType, args, strlen(args));
			if(error == 0) {
				USBVCPWrite("OK\n", 3);
			}
			else {
				USBVCPWrite("ERROR\n", 6);
			}
		}
	}

	return 0;
}

char testStringParam[200];
uint8_t CommandTest(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	switch(commandType) {
		case CommandType_Test: {
			USBVCPWrite("+TEST:<string>\n", 15);
			break;
		}
		case CommandType_Query: {
			USBVCPWrite(testStringParam, strlen(testStringParam));
			break;
		}
		case CommandType_Set: {
			uint8_t i;
			for(i = 0; i < argsLength; i++) {
				testStringParam[i] = args[i];
			}
			testStringParam[i++] = '\n';
			testStringParam[i++] = '\0';
			break;
		}
		case CommandType_Execute: {
			USBVCPWrite("Test Execute \n", 14);
			break;
		}
	}

	return 0;
}

uint8_t CommandList(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength) {
	uint16_t i;
	for(i = 0; i < COMMAND_LENGTH; i++) {
		char string[200];
		sprintf(string, "AT+%-10s: %s", commandArray[i].commandString, commandArray[i].commandInfo);
		USBVCPWrite(string, strlen(string));
	}

	return 0;
}
