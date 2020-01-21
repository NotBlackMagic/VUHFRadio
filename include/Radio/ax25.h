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
	uint16_t crc;
} AX25Struct;

void AX25Decode(uint8_t data[], uint16_t length, AX25Struct* ax25Struct);
void AX25Encode(uint8_t data[], uint16_t* length, AX25Struct ax25Struct);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_AX25_H_ */
