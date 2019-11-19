#include "atCmdInter.h"

//Variables used for AT Framing, for when command spans more then one ATCmdFraming function call
uint8_t framed[256];
uint8_t framedLength = 0;

/**
  * @brief	This function extracts a AT Command Frame, delimited by "AT" and '\r', can span over multiple calls to this function
  * @param	data: Current Input date string
  * @param	dataLength: Length of the data string
  * @param	dataOut: Pointer to be filled with the framed string pointer, if not found yet is set to NULL
  * @param	dataOutLength: Length of the framed string, if not found yet is set to 0
  * @return	Return 0 if a AT command frame was found, 1 if not or error occurred
  */
uint8_t ATCmdFraming(uint8_t data[], uint16_t dataLength, uint8_t** dataOut, uint8_t* dataOutLength) {
	*dataOut = NULL;
	*dataOutLength = 0;

	uint16_t i;
	for(i = 0; i < dataLength; i++) {
		//First search for "AT" token
		if(framedLength == 0 && i > 0) {
			//No "AT" token found yet
			if(data[i - 1] == 'A' && data[i] == 'T') {
				//"AT" Token found
				framed[framedLength++] = 'A';
				framed[framedLength++] = 'T';
			}
		}
		else if(framedLength != 0) {
			framed[framedLength++] = data[i];

			//Search for end of frame
			if(data[i] == '\r') {
				//End of frame found
				*dataOut = framed;
				*dataOutLength = framedLength;
				framedLength = 0;
				return 0;
			}
			else if(data[i] == '\n') {
				//Invalid character
				framedLength = 0;
				return 1;
			}
			else if(data[i] == '\0') {
				//Invalid character
				framedLength = 0;
				return 1;
			}
			else if(framedLength >= 250) {
				//Framed buffer overflow
				framedLength = 0;
				return 1;
			}
		}
	}

	return 1;
}

/**
  * @brief	This function extracts/parses the components/parameters of an AT Command from a framed string
  * @param	framed: A framed string, as created by ATCmdFraming
  * @param	dataLength: Length of the framed string
  * @param	ATCmdStruct: AT Command Struct to be filled with the parsed parameters
  * @return	Return 0 if a valid AT Command was found and successfully parsed, 1 if not or error occurred
  */
uint8_t ATCmdParse(uint8_t framed[], uint8_t framedLength, ATCmdStruct *atCmdStruct) {
	//First fill ATCmdStruct Header, is always the same "AT\0"
	atCmdStruct->header[0] = 'A';
	atCmdStruct->header[1] = 'T';
	atCmdStruct->header[2] = '\0';

	//int AT Command Struct
	atCmdStruct->args[0] = '\0';
	atCmdStruct->cmd[0] = '\0';

	//After Search for Header/Command separator '+'
	if(framed[2] != '+') {
		//No separator present, not a valid AT command
		return 1;
	}

	//Extract Command and Command Type
	uint8_t j = 0;
	uint8_t i;
	for(i = 3; i < framedLength; i++) {
		if(framed[i] == '=' && framed[i+1] == '?') {
			//This is a test command type
			if(framed[i+2] == '\r') {
				//Valid AT command
				atCmdStruct->type = ATCmdType_Test;
				atCmdStruct->cmd[j++] = '\0';
				return 0;
			}
			else {
				//Invalid AT command
				atCmdStruct->cmd[0] = '\0';
				return 1;
			}
		}
		else if(framed[i] == '=') {
			//This is a set command type
			if(framed[i+1] != '\r') {
				//Valid AT command
				atCmdStruct->type = ATCmdType_Set;
				atCmdStruct->cmd[j++] = '\0';
				i = i + 1;	//Skip '=' Character for arguments extraction
				break;
			}
			else {
				//Invalid AT command
				atCmdStruct->cmd[0] = '\0';
				return 1;
			}
		}
		else if(framed[i] == '?') {
			//This is a query command type
			if(framed[i+1] == '\r') {
				//Valid AT command
				atCmdStruct->type = ATCmdType_Query;
				atCmdStruct->cmd[j++] = '\0';
				return 0;
			}
			else {
				//Invalid AT command
				atCmdStruct->cmd[0] = '\0';
				return 1;
			}
		}
		else if(framed[i] == '\r') {
			//This is a execute command type
			atCmdStruct->type = ATCmdType_Execute;
			atCmdStruct->cmd[j++] = '\0';
			return 0;
		}
		else if(j >= 10) {
			//Command field to long, overflow
			atCmdStruct->cmd[0] = '\0';
			return 1;
		}
		else {
			atCmdStruct->cmd[j++] = framed[i];
		}
	}

	//Extract Arguments, only in case of Set command, all remaining bytes/chars are arguments
	j = 0;
	for(; i < framedLength; i++) {
		if(framed[i] == '\r') {
			atCmdStruct->args[j] = '\0';
		}
		else {
			atCmdStruct->args[j++] = framed[i];
		}
	}

	return 0;
}
