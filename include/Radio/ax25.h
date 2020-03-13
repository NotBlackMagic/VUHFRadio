#ifndef RADIO_AX25_H_
#define RADIO_AX25_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint8_t sourceAddress[8];
	uint8_t destinationAddress[8];
	uint8_t control;
	uint8_t pid;
	uint8_t* payload;
	uint8_t payloadLength;
} AX25Struct;

typedef struct {
	uint8_t sourceAddress[8];
	uint8_t destinationAddress[8];
	uint8_t control;
	uint8_t pid;

	uint8_t onSourceAddress;
	uint8_t onDestinationAddress;
	uint8_t onControlField;
	uint8_t onPIDField;
} AX25FilterStruct;

void AX25Decode(uint8_t data[], uint16_t length, AX25Struct* ax25Struct);
void AX25Encode(uint8_t data[], uint16_t* length, AX25Struct ax25Struct);
uint8_t AX25Filter(AX25Struct ax25Struct, AX25FilterStruct ax25FilterStruct);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_AX25_H_ */
