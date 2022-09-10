#include "CATInterface.h"

typedef uint8_t (*CATCommandHandler)(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

typedef struct {
	char code[3];
	CATCommandHandler handler;
} CATCommandStruct;

//CAT Command Handlers
uint8_t CATCommandAFCControl(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCRC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandEncoding(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDatarateRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDatarateTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCenterFequencyA(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCenterFequencyB(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFraming(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFunctionRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFunctionTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFirmware(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandAGCSpeed(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandIdentification(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandIFFrequency(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandRecallMemory(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandReadMemory(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandModulation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandTXPower(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandRXGain(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandBandwidth(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandReadMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandRSSI(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandTNC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandPacketMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

//CAT Commands Handler List
#define CAT_COMMAND_LIST_LENGTH						31
CATCommandStruct catCommands[CAT_COMMAND_LIST_LENGTH] = {
		{.code = "AF\0", .handler = CATCommandAFCControl},
		{.code = "CT\0", .handler = CATCommandCRC},
		{.code = "DA\0", .handler = NULL},
		{.code = "EM\0", .handler = CATCommandEncoding},
		{.code = "EX\0", .handler = CATCommandExtendedMenu},
		{.code = "DR\0", .handler = CATCommandDatarateRX},
		{.code = "DT\0", .handler = CATCommandDatarateTX},
		{.code = "FA\0", .handler = CATCommandCenterFequencyA},
		{.code = "FB\0", .handler = CATCommandCenterFequencyB},
		{.code = "FM\0", .handler = CATCommandFraming},
		{.code = "FR\0", .handler = CATCommandFunctionRX},
		{.code = "FT\0", .handler = CATCommandFunctionTX},
		{.code = "FW\0", .handler = CATCommandFirmware},
		{.code = "GT\0", .handler = CATCommandAGCSpeed},
		{.code = "ID\0", .handler = CATCommandIdentification},
		{.code = "IS\0", .handler = CATCommandIFFrequency},
		{.code = "KS\0", .handler = NULL},
		{.code = "MC\0", .handler = CATCommandRecallMemory},
		{.code = "MD\0", .handler = CATCommandModulation},
		{.code = "MR\0", .handler = CATCommandReadMemory},
		{.code = "MW\0", .handler = NULL},
		{.code = "PC\0", .handler = CATCommandTXPower},
		{.code = "PM\0", .handler = CATCommandPacketMeter},
		{.code = "QI\0", .handler = NULL},						//Store settings in quick memory (temporary/RAM)
		{.code = "QR\0", .handler = NULL},						//Recall settings in quick memory (temporary/RAM)
		{.code = "RG\0", .handler = CATCommandRXGain},
		{.code = "RM\0", .handler = CATCommandReadMeter},
		{.code = "SH\0", .handler = CATCommandBandwidth},
		{.code = "SM\0", .handler = CATCommandRSSI},
		{.code = "SQ\0", .handler = NULL},						//Sets and reads the squelch level
		{.code = "TC\0", .handler = CATCommandTNC}
};

/**
  * @brief	This function handles all incoming data/commands
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * CAT Command Example: Set: FA145895000; Read: FA; Return: FA145895000;
  */
uint8_t CATInterfaceHandler(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint8_t status = 0x01;

	//Check for command handler in list
	uint8_t i;
	for(i = 0; i < CAT_COMMAND_LIST_LENGTH; i++) {
//		if(strcmp(catCommands[i].code, data) == 0) {
		if(catCommands[i].code[0] == data[0] && catCommands[i].code[1] == data[1]) {
			if(catCommands[i].handler == NULL) {
				//Is CAT command but handler was not defined
				status = 0x00;
				break;
			}

			//Call CAT command handler function
			catCommands[i].handler(data, dataLength, rData, rDataLength);

			status = 0x00;
			break;
		}
		else {
			status = 0x01;
		}
	}

	//Not a CAT Command
	if(status != 0x00) {
		if(data[0] == '?' && data[1] == ';') {
			//Command return ERROR
			return 1;
		}
		else if(data[0] == 'O' && data[1] == 'K' && data[2] == ';') {
			//Command return OK
			return 0;
		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}

	return status;
}

/**
  * @brief	This function handles the AFC Range CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: AFC1125000; Read: AFC1; Return: AFC1125000;
  */
uint8_t CATCommandAFCControl(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "AF0%06d;", radioAConfig.afcRange);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "AF1%06d;", radioBConfig.afcRange);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[9] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetAFCRange(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.afcRange = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.afcRange = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the CRC Mode Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: CT10; Read: CT1; Return: CT10;
  */
uint8_t CATCommandCRC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "CT0%01d;", radioAConfig.crc);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "CT1%01d;", radioBConfig.crc);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetCRCMode(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.crc = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.crc = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Encoding Mode CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: EM14; Read: EM1; Return: EM14;
  */
uint8_t CATCommandEncoding(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "EM0%01d;", radioAConfig.encoder);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "EM1%01d;", radioBConfig.encoder);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetEncodingMode(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.encoder = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.encoder = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Datarate RX CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: DR1001200; Read: DR1; Return: DR1001200;
  */
uint8_t CATCommandDatarateRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "DR0%06d;", radioAConfig.rxDatarate);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "DR1%06d;", radioBConfig.rxDatarate);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[9] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		//Set RX Datarate
		if(RadioSetRXDatarate(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.rxDatarate = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.rxDatarate = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Datarate TX CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: DT0250000; Read: DT0; Return: DT0250000;
  */
uint8_t CATCommandDatarateTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "DT0%06d;", radioAConfig.txDatarate);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "DT1%06d;", radioBConfig.txDatarate);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[9] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		//Set TX Datarate
		if(RadioSetTXDatarate(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.txDatarate = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.txDatarate = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Center Frequency A CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FA145895000; Read: FA; Return: FA145895000;
  */
uint8_t CATCommandCenterFequencyA(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	//Check if is a Set or Read command
	if(data[2] == ';') {
		//Read Command
		*rDataLength = sprintf(rData, "FA%09d;", radioAConfig.centerFrequency);
		return 0;
	}
	else if(data[11] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetCenterFrequency(RADIO_AX, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
		radioAConfig.centerFrequency = value;
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Center Frequency B CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FB145895000; Read: FB; Return: FB145895000;
  */
uint8_t CATCommandCenterFequencyB(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
//	//Check if is a Set or Read command
//	if(data[2] == ';') {
//		//Read Command
//		*rDataLength = sprintf(rData, "FB%09d;", radioBConfig.centerFrequency);
//		return 0;
//	}
//	else if(data[11] == ';') {
//		//Write/Set Command
//		uint32_t value = 0;
//		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
//			*rDataLength = sprintf(rData, "?;");
//			return 1;
//		}
//
//		if(RadioSetCenterFrequency(RADIO_B, value) != 0x00) {
//			*rDataLength = sprintf(rData, "?;");
//			return 1;
//		}
//		radioBConfig.centerFrequency = value;
//	}
//	else {
//		//Syntax Error
//		*rDataLength = sprintf(rData, "?;");
//		return 1;
//	}
//
//	*rDataLength = sprintf(rData, "OK;");
//	return 0;
}

/**
  * @brief	This function handles the Framing Mode CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FM02; Read: FM0; Return: FM02;
  */
uint8_t CATCommandFraming(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "FM0%01d;", radioAConfig.framing);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "FM1%01d;", radioBConfig.framing);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetFramingMode(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.framing = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.framing = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Function RX (RX On/Off) CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FR00; Read: FR0; Return: FR00;
  */
uint8_t CATCommandFunctionRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			if(radioAConfig.operationMode == 0x01) {
				//In RX Mode
				*rDataLength = sprintf(rData, "FR01;");
			}
			else {
				//Not in RX Mode
				*rDataLength = sprintf(rData, "FR00;");
			}
			return 0;
		}
//		else if(radio == RADIO_B) {
//			if(radioBConfig.operationMode == 0x01) {
//				//In RX Mode
//				*rDataLength = sprintf(rData, "FR11;");
//			}
//			else {
//				//Not in RX Mode
//				*rDataLength = sprintf(rData, "FR10;");
//			}
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetOperationMode(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			if(value == 0x01) {
				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioAConfig.modulation == 0x03) {
					RadioSetAFSKSpaceFreq(radio, radioAConfig.afskSpace);
					RadioSetAFSKMarkFreq(radio, radioAConfig.afskMark);
				}
			}
			radioAConfig.operationMode = value;
		}
//		else if(radio == RADIO_B) {
//			if(value == 0x01) {
//				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
//				if(radioBConfig.modulation == 0x03) {
//					RadioSetAFSKSpaceFreq(radio, radioBConfig.afskSpace);
//					RadioSetAFSKMarkFreq(radio, radioBConfig.afskMark);
//				}
//			}
//			radioBConfig.operationMode = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Function TX (TX On/Off) CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FT01; Read: FT0; Return: FT01;
  */
uint8_t CATCommandFunctionTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			if(radioAConfig.operationMode == 0x02) {
				//In TX Mode
				*rDataLength = sprintf(rData, "FT01;");
			}
			else {
				//Not in TX Mode
				*rDataLength = sprintf(rData, "FT00;");
			}
			return 0;
		}
//		else if(radio == RADIO_B) {
//			if(radioBConfig.operationMode == 0x02) {
//				//In TX Mode
//				*rDataLength = sprintf(rData, "FT11;");
//			}
//			else {
//				//Not in TX Mode
//				*rDataLength = sprintf(rData, "FT10;");
//			}
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetOperationMode(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			if(value == 0x00) {
				radioAConfig.operationMode = 0x00;
			}
			else if(value == 0x01) {
				radioAConfig.operationMode = 0x02;

				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioAConfig.modulation == 0x03) {
					RadioSetAFSKSpaceFreq(radio, radioAConfig.afskSpace);
					RadioSetAFSKMarkFreq(radio, radioAConfig.afskMark);
				}
			}
			else {
				return 1;
			}
		}
//		else if(radio == RADIO_B) {
//			if(value == 0x00) {
//				radioBConfig.operationMode = 0x00;
//			}
//			else if(value == 0x01) {
//				radioBConfig.operationMode = 0x02;
//
//				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
//				if(radioBConfig.modulation == 0x04) {
//					RadioSetAFSKSpaceFreq(radio, radioBConfig.afskSpace);
//					RadioSetAFSKMarkFreq(radio, radioBConfig.afskMark);
//				}
//			}
//			else {
//				return 1;
//			}
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Identification Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: FW; Return: FW010323232323230002323232323;
  */
uint8_t CATCommandFirmware(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	if(data[2] == ';') {
		//Read Command
		*rDataLength = sprintf(rData, "FW%02d%02d%010d%02d%02d%010d;", SOFTWARE_VERSION_MAJOR, SOFTWARE_VERSION_MINOR, SOFTWARE_HASH, CAT_VERSION_MAJOR, CAT_VERSION_MINOR, CAT_VERSION_HASH);
		return 0;
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

/**
  * @brief	This function handles the AGC Speed Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: GT001; Read: GT0; Return: GT001;
  */
uint8_t CATCommandAGCSpeed(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "GT0%02d;", (15-radioAConfig.agcSpeed));
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "GT1%02d;", (15-radioBConfig.agcSpeed));
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[5] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetAGCSpeed(radio, (15 - value)) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.agcSpeed = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.agcSpeed = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Identification Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: ID; Return: ID0103;
  */
uint8_t CATCommandIdentification(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	if(data[2] == ';') {
		//Read Command
		*rDataLength = sprintf(rData, "ID%02d%02d;", HARDWARE_VERSION_MAJOR, HARDWARE_VERSION_MINOR);
		return 0;
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

/**
  * @brief	This function handles the IF Frequency Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: IS1010000; Read: IS1; Return: IS1010000;
  */
uint8_t CATCommandIFFrequency(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "IS0%06d;", radioAConfig.ifFrequency);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "IS1%06d;", radioBConfig.ifFrequency);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[9] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		//Set IF Frequency
		if(RadioSetIF(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.ifFrequency = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.ifFrequency = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Recall Memory Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: MC1105; Read: MC1; Return: MC1105;
  */
uint8_t CATCommandRecallMemory(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "MC0%01d%02d;", radioAMemoryBank, radioAMemoryChannel);
			return 0;
		}
//		else if(radio == RADIO_B) {
////			*rDataLength = sprintf(rData, "MC1%02d;", NULL);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[6] == ';') {
		//Write/Set Command
		uint32_t memoryBank = 0;
		if(CATASCIIToNumber(&data[3], 1, &memoryBank) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		uint32_t memoryChannel;
		if(CATASCIIToNumber(&data[4], 2, &memoryChannel) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetFullConfiguration(radio, memoryChannelsFixed[memoryChannel]) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAMemoryBank = memoryBank;
			radioAMemoryChannel = memoryChannel;
			radioAConfig = memoryChannelsFixed[memoryChannel];
		}
//		else if(radio == RADIO_B) {
//			radioBConfig = memoryChannelsFixed[value];
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Read Memory Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: MC11109; Return: MC11109xxxxxxx;
  */
uint8_t CATCommandReadMemory(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[7] == ';') {
		//Read Command
		uint32_t nRXSettings;
		if(CATASCIIToNumber(&data[3], 1, &nRXSettings) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		uint32_t memoryBank;
		if(CATASCIIToNumber(&data[4], 1, &memoryBank) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		uint32_t memoryChannel;
		if(CATASCIIToNumber(&data[5], 2, &memoryChannel) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Modulation Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: MD01; Read: MD0; Return: MD01;
  */
uint8_t CATCommandModulation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is a Set or Read command
	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "MD0%01d;", radioAConfig.modulation);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "MD1%01d;", radioBConfig.modulation);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetModulation(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.modulation = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.modulation = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the TX Power Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: PC110; Read: PC1; Return: PC110;
  */
uint8_t CATCommandTXPower(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "PC0%02d;", (radioAConfig.outputPower + 10));
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "PC1%02d;", (radioBConfig.outputPower + 10));
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[5] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetTXPower(radio, (value - 10)) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			radioAConfig.outputPower = value - 10;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.outputPower = value - 10;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the RX Gain Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: PG1010; Read: PG1; Return: PG1010;
  */
uint8_t CATCommandRXGain(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "RG0%03d;", radioATracking.agcGainTracking);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "RG1%03d;", radioBTracking.agcGainTracking);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[5] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 3, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the RX Bandwidth Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: SH0250000; Read: SH0; Return: SH0250000;
  */
uint8_t CATCommandBandwidth(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "SH0%06d;", radioAConfig.bandwidth);
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "SH1%06d;", radioBConfig.bandwidth);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[9] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		//Set RX Bandwidth
		if(RadioSetBandwidth(radio, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		//Should also reconfigure RX Datarate, depends on Decimation value
		if(radio == RADIO_AX) {
			if(RadioSetRXDatarate(radio, radioAConfig.rxDatarate) != 0x00) {
				*rDataLength = sprintf(rData, "?;");
				return 1;
			}
		}
//		else if(radio == RADIO_B) {
//			if(RadioSetRXDatarate(radio, radioBConfig.rxDatarate) != 0x00) {
//				*rDataLength = sprintf(rData, "?;");
//				return 1;
//			}
//		}

		if(radio == RADIO_AX) {
			radioAConfig.bandwidth = value;
		}
//		else if(radio == RADIO_B) {
//			radioBConfig.bandwidth = value;
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Read Meter Value
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: RM10; Return: RM10100;
  */
uint8_t CATCommandReadMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	uint32_t meter = 0;
	if(CATASCIIToNumber(&data[3], 1, &meter) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[4] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			switch(meter) {
				case 0x00:
					//Read RSSI Value
					*rDataLength = sprintf(rData, "RM00%03d;", (-radioATracking.rssiTracking));
					break;
				case 0x01:
					//Read RF Frequency Value
					if(radioATracking.rfFrequencyTracking >= 0) {
						*rDataLength = sprintf(rData, "RM01+%06d;", radioATracking.rfFrequencyTracking);
					}
					else {
						*rDataLength = sprintf(rData, "RM01-%06d;", (-radioATracking.rfFrequencyTracking));
					}
					break;
				case 0x02:
					//Read AGC Gain Value
					*rDataLength = sprintf(rData, "RM02%03d;", radioATracking.agcGainTracking);
					break;
				default:
					*rDataLength = sprintf(rData, "?;");
					return 1;
			}

			return 0;
		}
//		else if(radio == RADIO_B) {
//			switch(meter) {
//				case 0x00:
//					//Read RSSI Value
//					*rDataLength = sprintf(rData, "RM10%03d;", (-radioBTracking.rssiTracking));
//					break;
//				case 0x01:
//					//Read RF Frequency Value
//					if(radioBTracking.rfFrequencyTracking >= 0) {
//						*rDataLength = sprintf(rData, "RM11+%06d;", radioBTracking.rfFrequencyTracking);
//					}
//					else {
//						*rDataLength = sprintf(rData, "RM11-%06d;", (-radioBTracking.rfFrequencyTracking));
//					}
//					break;
//				case 0x02:
//					//Read AGC Gain Value
//					*rDataLength = sprintf(rData, "RM12%03d;", radioATracking.agcGainTracking);
//					break;
//				default:
//					*rDataLength = sprintf(rData, "?;");
//					return 1;
//			}
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

/**
  * @brief	This function handles the RSSI CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: SM1; Return: SM1100;
  */
uint8_t CATCommandRSSI(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			*rDataLength = sprintf(rData, "SM0%03d;", (-radioATracking.rssiTracking));
			return 0;
		}
//		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "SM1%03d;", (-radioBTracking.rssiTracking));
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

/**
  * @brief	This function handles the Function TNC (TNC On/Off) CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: TC01; Read: TC0; Return: TC01;
  */
uint8_t CATCommandTNC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			if(radioAConfig.tncMode == RadioTNCMode_OFF) {
				//TNC Mode Off
				*rDataLength = sprintf(rData, "TC00;");
			}
			else {
				//TNC Mode On
				*rDataLength = sprintf(rData, "TC01;");
			}
			return 0;
		}
//		else if(radio == RADIO_B) {
//			if(radioBConfig.tncMode == RadioTNCMode_OFF) {
//				//TNC Mode Off
//				*rDataLength = sprintf(rData, "TC10;");
//			}
//			else {
//				//TNC Mode On
//				*rDataLength = sprintf(rData, "TC11;");
//			}
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[4] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_AX) {
			if(value == 0x00) {
				radioAConfig.tncMode = RadioTNCMode_OFF;
			}
			else if(value == 0x01) {
				radioAConfig.tncMode = RadioTNCMode_KISS;
			}
			else if(value == 0x02) {
				radioAConfig.tncMode = RadioTNCMode_SMACK;
			}
			else {
				*rDataLength = sprintf(rData, "?;");
				return 1;
			}
		}
//		else if(radio == RADIO_B) {
//			if(value == 0x00) {
//				radioBConfig.tncMode = RadioTNCMode_OFF;
//			}
//			else if(value == 0x01) {
//				radioBConfig.tncMode = RadioTNCMode_KISS;
//			}
//			else if(value == 0x02) {
//				radioBConfig.tncMode = RadioTNCMode_SMACK;
//			}
//			else {
//				*rDataLength = sprintf(rData, "?;");
//				return 1;
//			}
//		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[4] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
//			*rDataLength = sprintf(rData, "SM0%03d;", frequencyDeviationA);
			return 0;
		}
//		else if(radio == RADIO_B) {
////			*rDataLength = sprintf(rData, "SM1%03d;", frequencyDeviationB);
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else if(data[5] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

uint8_t CATCommandPacketMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	uint32_t meter = 0;
	if(CATASCIIToNumber(&data[3], 1, &meter) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[4] == ';') {
		//Read Command
		if(radio == RADIO_AX) {
			switch(meter) {
				case 0x00:
					//Read RSSI Value
					*rDataLength = sprintf(rData, "PM00%03d;", (-radioAPacketTracking.rssiTracking));
					break;
				case 0x01:
					//Read RF Frequency Value
					if(radioATracking.rfFrequencyTracking >= 0) {
						*rDataLength = sprintf(rData, "PM01+%06d;", radioAPacketTracking.rfFrequencyTracking);
					}
					else {
						*rDataLength = sprintf(rData, "PM01-%06d;", (-radioAPacketTracking.rfFrequencyTracking));
					}
					break;
				default:
					*rDataLength = sprintf(rData, "?;");
					return 1;
			}

			return 0;
		}
//		else if(radio == RADIO_B) {
//			switch(meter) {
//				case 0x00:
//					//Read RSSI Value
//					*rDataLength = sprintf(rData, "PM10%03d;", (-radioBPacketTracking.rssiTracking));
//					break;
//				case 0x01:
//					//Read RF Frequency Value
//					if(radioBTracking.rfFrequencyTracking >= 0) {
//						*rDataLength = sprintf(rData, "PM11+%06d;", radioBPacketTracking.rfFrequencyTracking);
//					}
//					else {
//						*rDataLength = sprintf(rData, "PM11-%06d;", (-radioBPacketTracking.rfFrequencyTracking));
//					}
//					break;
//				default:
//					*rDataLength = sprintf(rData, "?;");
//					return 1;
//			}
//			return 0;
//		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}
