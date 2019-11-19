#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commands.h"

#include "commandsBasic.h"

//Number of Commands in command Array
#define COMMAND_LENGTH						8

typedef struct {
	uint16_t commandID;		//ID of the command
	char* commandString;	//Command string, compare to this to see if is this command
	char* commandInfo;		//Short string explaining the command
	uint8_t (*commandFunction)(CommandTypeEnum, uint8_t[], uint8_t);	//Command Function to be called; Return: Error; Args: Type, Data, Data Length
} CommandStruct;

uint8_t CommandHandler(uint8_t* command, uint8_t* args, CommandTypeEnum commandType);
uint8_t CommandTest(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);
uint8_t CommandList(CommandTypeEnum commandType, uint8_t* args, uint8_t argsLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDHANDLER_H_ */
