#include "CATInterface.h"

uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value);
uint32_t UIntPow(uint8_t base, uint8_t exp);

/**
  * @brief	This function
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> Valid Command, 1->Invalid Command (Error)
  *
  * CAT Command Example: Set: FA145895000; Read: FA; Return: FA145895000;
  */
uint8_t CATInterfaceHandler(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	if(data[0] == 'A' && data[1] == 'F') {
		uint8_t radio = 0;
		if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
			*rDataLength = sprintf(rData, "?;\n", afcRangeA);
			return 1;
		}

		//Check if is a Set or Read command
		if(data[3] == ';') {
			//Read Command
			if(radio == RADIO_A) {
				*rDataLength = sprintf(rData, "AF0%06d;\n", afcRangeA);
				return 0;
			}
		}
		else if(data[9] == ';') {
			uint32_t value = 0;
			if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
				*rDataLength = sprintf(rData, "?;\n", afcRangeA);
				return 1;
			}

			if(radio == RADIO_A) {
				//Save and program new AFC value
				afcRangeA = value;
			}
		}
		else {
			*rDataLength = sprintf(rData, "?;\n", afcRangeA);
			return 1;
		}
	}

	*rDataLength = sprintf(rData, "OK;\n", afcRangeA);
	return 0;
}

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
