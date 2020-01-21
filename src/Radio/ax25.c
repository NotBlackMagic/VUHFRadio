#include "ax25.h"

void AX25Decode(uint8_t data[], uint16_t length, AX25Struct* ax25Struct) {
	uint16_t index = 0;

	//Get Source Address
	ax25Struct->sourceAddress[0] = data[index++] >> 1;
	ax25Struct->sourceAddress[1] = data[index++] >> 1;
	ax25Struct->sourceAddress[2] = data[index++] >> 1;
	ax25Struct->sourceAddress[3] = data[index++] >> 1;
	ax25Struct->sourceAddress[4] = data[index++] >> 1;
	ax25Struct->sourceAddress[5] = data[index++] >> 1;
	ax25Struct->sourceAddress[6] = data[index++] >> 1;
	ax25Struct->sourceAddress[7] = '\0';

	//Get Destination Address
	ax25Struct->destinationAddress[0] = data[index++] >> 1;
	ax25Struct->destinationAddress[1] = data[index++] >> 1;
	ax25Struct->destinationAddress[2] = data[index++] >> 1;
	ax25Struct->destinationAddress[3] = data[index++] >> 1;
	ax25Struct->destinationAddress[4] = data[index++] >> 1;
	ax25Struct->destinationAddress[5] = data[index++] >> 1;
	ax25Struct->destinationAddress[6] = data[index++] >> 1;
	ax25Struct->destinationAddress[7] = '\0';

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

	//Get CRC Field
	ax25Struct->crc = (data[index++] << 8) + data[index++];
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
