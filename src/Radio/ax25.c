#include "ax25.h"

void AX25Decode(uint8_t data[], uint16_t length, AX25Struct* ax25Struct) {
	uint16_t index = 0;

	//Get Destination Address
	ax25Struct->destinationAddress[0] = data[index++] >> 1;
	ax25Struct->destinationAddress[1] = data[index++] >> 1;
	ax25Struct->destinationAddress[2] = data[index++] >> 1;
	ax25Struct->destinationAddress[3] = data[index++] >> 1;
	ax25Struct->destinationAddress[4] = data[index++] >> 1;
	ax25Struct->destinationAddress[5] = data[index++] >> 1;
	ax25Struct->destinationAddress[6] = data[index++] >> 1;
	ax25Struct->destinationAddress[7] = '\0';

	//Get Source Address
	ax25Struct->sourceAddress[0] = data[index++] >> 1;
	ax25Struct->sourceAddress[1] = data[index++] >> 1;
	ax25Struct->sourceAddress[2] = data[index++] >> 1;
	ax25Struct->sourceAddress[3] = data[index++] >> 1;
	ax25Struct->sourceAddress[4] = data[index++] >> 1;
	ax25Struct->sourceAddress[5] = data[index++] >> 1;
	ax25Struct->sourceAddress[6] = data[index++] >> 1;
	ax25Struct->sourceAddress[7] = '\0';

	//Get Control Field
	ax25Struct->control = data[index++];

	//Get PID Field
	ax25Struct->pid = data[index++];

	//Calculate Payload Length
	ax25Struct->payloadLength = length - index - 2;

	//Get Payload
	uint16_t i;
	for(i = 0; i < ax25Struct->payloadLength; i++) {
		ax25Struct->payload[i] = data[index++];
	}
	ax25Struct->payload[i] = '\0';
}

void AX25Encode(uint8_t data[], uint16_t* length, AX25Struct ax25Struct) {
	uint16_t index = 0;

	//Set Source Address
	data[index++] = ax25Struct.sourceAddress[0] << 1;
	data[index++] = ax25Struct.sourceAddress[1] << 1;
	data[index++] = ax25Struct.sourceAddress[2] << 1;
	data[index++] = ax25Struct.sourceAddress[3] << 1;
	data[index++] = ax25Struct.sourceAddress[4] << 1;
	data[index++] = ax25Struct.sourceAddress[5] << 1;
	data[index++] = ax25Struct.sourceAddress[6] << 1;

	//Set Destination Address
	data[index++] = ax25Struct.destinationAddress[0] << 1;
	data[index++] = ax25Struct.destinationAddress[1] << 1;
	data[index++] = ax25Struct.destinationAddress[2] << 1;
	data[index++] = ax25Struct.destinationAddress[3] << 1;
	data[index++] = ax25Struct.destinationAddress[4] << 1;
	data[index++] = ax25Struct.destinationAddress[5] << 1;
	data[index++] = (ax25Struct.destinationAddress[6] << 1) | 0x01;	//Set last bit to indicate end of address fields

	//Set Control Field
	data[index++] = ax25Struct.control;

	//Set PID Field
	data[index++] = ax25Struct.pid;

	//Set Payload
	uint16_t i;
	for(i = 0; i < ax25Struct.payloadLength; i++) {
		data[index++] = ax25Struct.payload[i];
	}

	*length = index;
}

uint8_t AX25Filter(AX25Struct ax25Struct, AX25FilterStruct ax25FilterStruct) {
	if(ax25FilterStruct.onSourceAddress == 0x01) {
		//Filter on Source Address
		if(strcmp(ax25Struct.sourceAddress, ax25FilterStruct.sourceAddress) != 0x00) {
			//Source Address mismatch
			return 1;
		}
	}
	if(ax25FilterStruct.onDestinationAddress == 0x01) {
		//Filter on Destination Address
		if(strcmp(ax25Struct.destinationAddress, ax25FilterStruct.destinationAddress) != 0x00) {
			//Destination Address mismatch
			return 1;
		}
	}
	if(ax25FilterStruct.onControlField == 0x01) {
		//Filter on Control Field
		if(ax25Struct.control != ax25FilterStruct.control) {
			//Control Field mismatch
			return 1;
		}
	}
	if(ax25FilterStruct.onPIDField == 0x01) {
		//Filter on Control Field
		if(ax25Struct.pid != ax25FilterStruct.pid) {
			//Control Field mismatch
			return 1;
		}
	}

	return 0;
}
