#include "CATInterface.h"

uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value);

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
uint8_t CATCommandAGCSpeed(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandIFFrequency(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandModulation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandTXPower(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandBandwidth(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandReadMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandRSSI(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

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
	if(data[0] == 'A' && data[1] == 'F') {
		//AFC Control
		return CATCommandAFCControl(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'C' && data[1] == 'T') {
		//CRC/CCITT Control
		return CATCommandCRC(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'D' && data[1] == 'A') {
		//Screen Brightness setting
	}
	else if(data[0] == 'E' && data[1] == 'M') {
		//Bit Encoding Mode
		return CATCommandEncoding(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'E' && data[1] == 'X') {
		//Extended Menu
	}
	else if(data[0] == 'D' && data[1] == 'R') {
		//Datarate RX
		return CATCommandDatarateRX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'D' && data[1] == 'T') {
		//Datarate TX
		return CATCommandDatarateTX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'A') {
		//Center Frequency of Radio A
		return CATCommandCenterFequencyA(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'B') {
		//Center Frequency of Radio B
		return CATCommandCenterFequencyB(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'M') {
		//Framing Mode
		return CATCommandFraming(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'R') {
		//Function RX (ON or OFF)
		return CATCommandFunctionRX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'T') {
		//Function TX (ON or OFF)
		return CATCommandFunctionTX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'G' && data[1] == 'T') {
		//AGC Speed setting
		return CATCommandAGCSpeed(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'I' && data[1] == 'S') {
		//IF Frequency setting
		return CATCommandIFFrequency(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'K' && data[1] == 'S') {
		//CW/Morse Key Speed
	}
	else if(data[0] == 'M' && data[1] == 'D') {
		//Operating Mode/Modulation
		return CATCommandModulation(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'P' && data[1] == 'C') {
		//TX Output Power
		return CATCommandTXPower(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'R' && data[1] == 'G') {
		//RF Gain, LNA/AGC Gain
	}
	else if(data[0] == 'R' && data[1] == 'M') {
		//Read Meter/Tracking Value
		return CATCommandReadMeter(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'S' && data[1] == 'H') {
		//RX Bandwidth
		return CATCommandBandwidth(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'S' && data[1] == 'M') {
		//RSSI Reading
		return CATCommandRSSI(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'T' && data[1] == 'C') {
		//TNC Mode
	}
	else {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	return 0;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "AF0%06d;", afcRangeA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "AF1%06d;", afcRangeB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			afcRangeA = value;
		}
		else if(radio == RADIO_B) {
			afcRangeB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "CT0%01d;", crcA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "CT1%01d;", crcB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			crcA = value;
		}
		else if(radio == RADIO_B) {
			crcB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "EM0%01d;", encoderA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "EM1%01d;", encoderB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			encoderA = value;
		}
		else if(radio == RADIO_B) {
			encoderB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "DR0%06d;", rxDatarateA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "DR1%06d;", rxDatarateB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			rxDatarateA = value;
		}
		else if(radio == RADIO_B) {
			rxDatarateB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "DT0%06d;", txDatarateA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "DT1%06d;", txDatarateB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			txDatarateA = value;
		}
		else if(radio == RADIO_B) {
			txDatarateB = value;
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
		*rDataLength = sprintf(rData, "FA%09d;", centerFrequencyA);
		return 0;
	}
	else if(data[11] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetCenterFrequency(RADIO_A, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
		centerFrequencyA = value;
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
	//Check if is a Set or Read command
	if(data[2] == ';') {
		//Read Command
		*rDataLength = sprintf(rData, "FB%09d;", centerFrequencyB);
		return 0;
	}
	else if(data[11] == ';') {
		//Write/Set Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(RadioSetCenterFrequency(RADIO_B, value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
		centerFrequencyB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "FM0%01d;", framingA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "FM1%01d;", framingB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			framingA = value;
		}
		else if(radio == RADIO_B) {
			framingB = value;
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
		if(radio == RADIO_A) {
			if(operationModeB == 0x01) {
				//In RX Mode
				*rDataLength = sprintf(rData, "FR01;");
			}
			else {
				//Not in RX Mode
				*rDataLength = sprintf(rData, "FR00;");
			}
			return 0;
		}
		else if(radio == RADIO_B) {
			if(operationModeB == 0x01) {
				//In RX Mode
				*rDataLength = sprintf(rData, "FR11;");
			}
			else {
				//Not in RX Mode
				*rDataLength = sprintf(rData, "FR10;");
			}
			return 0;
		}
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

		if(radio == RADIO_A) {
			if(value == 0x01) {
				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(modulationA == 0x03) {
					RadioSetAFSKSpaceFreq(radio, afskSpaceA);
					RadioSetAFSKMarkFreq(radio, afskMarkA);
				}
			}
			operationModeA = value;
		}
		else if(radio == RADIO_B) {
			if(value == 0x01) {
				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(modulationB == 0x03) {
					RadioSetAFSKSpaceFreq(radio, afskSpaceB);
					RadioSetAFSKMarkFreq(radio, afskMarkB);
				}
			}
			operationModeB = value;
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
		if(radio == RADIO_A) {
			if(operationModeB == 0x02) {
				//In TX Mode
				*rDataLength = sprintf(rData, "FT01;");
			}
			else {
				//Not in TX Mode
				*rDataLength = sprintf(rData, "FT00;");
			}
			return 0;
		}
		else if(radio == RADIO_B) {
			if(operationModeB == 0x02) {
				//In TX Mode
				*rDataLength = sprintf(rData, "FT11;");
			}
			else {
				//Not in TX Mode
				*rDataLength = sprintf(rData, "FT10;");
			}
			return 0;
		}
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

		if(radio == RADIO_A) {
			if(value == 0x00) {
				operationModeA = 0x00;
			}
			else if(value == 0x01) {
				operationModeA = 0x02;

				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(modulationA == 0x03) {
					RadioSetAFSKSpaceFreq(radio, afskSpaceA);
					RadioSetAFSKMarkFreq(radio, afskMarkA);
				}
			}
			else {
				return 1;
			}
		}
		else if(radio == RADIO_B) {
			if(value == 0x00) {
				operationModeB = 0x00;
			}
			else if(value == 0x01) {
				operationModeB = 0x02;

				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(modulationB == 0x04) {
					RadioSetAFSKSpaceFreq(radio, afskSpaceB);
					RadioSetAFSKMarkFreq(radio, afskMarkB);
				}
			}
			else {
				return 1;
			}
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "GT0%02d;", (15-agcSpeedA));
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "GT1%02d;", (15-agcSpeedB));
			return 0;
		}
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

		if(radio == RADIO_A) {
			agcSpeedA = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
		}
		else if(radio == RADIO_B) {
			agcSpeedB = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "IS0%06d;", ifFrequencyA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "IS1%06d;", ifFrequencyB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			ifFrequencyA = value;
		}
		else if(radio == RADIO_B) {
			ifFrequencyB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "MD0%01d;", modulationA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "MD1%01d;", modulationB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			modulationA = value;
		}
		else if(radio == RADIO_B) {
			modulationB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "PC0%02d;", outputPowerA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "PC1%02d;", outputPowerB);
			return 0;
		}
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

		if(radio == RADIO_A) {
			outputPowerA = value;
		}
		else if(radio == RADIO_B) {
			outputPowerB = value;
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "SH0%06d;", bandwidthA);
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "SH1%06d;", bandwidthB);
			return 0;
		}
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
		if(radio == RADIO_A) {
			if(RadioSetRXDatarate(radio, rxDatarateA) != 0x00) {
				*rDataLength = sprintf(rData, "?;");
				return 1;
			}
		}
		else if(radio == RADIO_B) {
			if(RadioSetRXDatarate(radio, rxDatarateB) != 0x00) {
				*rDataLength = sprintf(rData, "?;");
				return 1;
			}
		}

		if(radio == RADIO_A) {
			bandwidthA = value;
		}
		else if(radio == RADIO_B) {
			bandwidthB = value;
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
		if(radio == RADIO_A) {
			switch(meter) {
				case 0x00:
					//Read RSSI Value
					*rDataLength = sprintf(rData, "RM00%03d;", (-rssiTrackingA));
					break;
				case 0x01:
					//Read RF Frequency Value
					if(rfFrequencyTrackingA >= 0) {
						*rDataLength = sprintf(rData, "RM01+%06d;", rfFrequencyTrackingA);
					}
					else {
						*rDataLength = sprintf(rData, "RM01-%06d;", (-rfFrequencyTrackingA));
					}
					break;
				default:
					*rDataLength = sprintf(rData, "?;");
					return 1;
			}

			return 0;
		}
		else if(radio == RADIO_B) {
			switch(meter) {
				case 0x00:
					//Read RSSI Value
					*rDataLength = sprintf(rData, "RM10%03d;", (-rssiTrackingB));
					break;
				case 0x01:
					//Read RF Frequency Value
					if(rfFrequencyTrackingB >= 0) {
						*rDataLength = sprintf(rData, "RM11+%06d;", rfFrequencyTrackingB);
					}
					else {
						*rDataLength = sprintf(rData, "RM11-%06d;", (-rfFrequencyTrackingB));
					}
					break;
				default:
					*rDataLength = sprintf(rData, "?;");
					return 1;
			}
			return 0;
		}
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
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "SM0%03d;", (-rssiTrackingA));
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "SM1%03d;", (-rssiTrackingB));
			return 0;
		}
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

uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[4] == ';') {
		//Read Command
		if(radio == RADIO_A) {
//			*rDataLength = sprintf(rData, "SM0%03d;", frequencyDeviationA);
			return 0;
		}
		else if(radio == RADIO_B) {
//			*rDataLength = sprintf(rData, "SM1%03d;", frequencyDeviationB);
			return 0;
		}
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
}

/**
  * @brief	This function calculates the Power of base^exp, both uint8_t
  * @param	base: Base value of the Power
  * @param	exp: Exponent value of the Power
  * @return	The Power of base^exp
  */
uint32_t UIntPow(uint8_t base, uint8_t exp) {
	if(exp == 0) {
		return 1;
	}

	uint32_t value = base;
	uint8_t i;
	for(i = 1; i < exp; i++) {
		value *= base;
	}

	return value;
}

/**
  * @brief	This function converts the CAT value fields to int
  * @param	ascii: The CAT value field in ASCII
  * @param	asciiLength: Length of the ASCII field aka N digits
  * @param	value: Pointer to return value
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value) {
	*value = 0;

	uint8_t i;
	for(i = 0; i < asciiLength; i++) {
		if(ascii[i] < '0' || ascii[i] > '9') {
			return 1;
		}
		uint32_t mult = UIntPow(10, (asciiLength - i - 1));
		*value += (ascii[i] - '0') * mult;
	}

	return 0;
}
