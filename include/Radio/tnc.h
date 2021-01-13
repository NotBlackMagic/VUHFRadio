#ifndef RADIO_KISS_H_
#define RADIO_KISS_H_

#ifdef __cplusplus
extern "C" {
#endif

//KISS Protocol
//Packet Format
//[ Begin ][  Command   ][ Data ][ End  ]
//[ FEND  ][ Port | Cmd ][  ... ][ FEND ]

//Special characters
#define FEND									0xC0
#define FESC									0xDB
#define TFEND									0xDC
#define TFESC									0xDD

//If FEND appears in the frame it is send as 2 bytes: FESC TFEND
//If FESC appears in the frame it is send as 2 bytes: FESC TFESC

//Command codes
#define KISS_PORT_MASK							0xF0
#define KISS_COMMAND_MASK						0x0F
typedef enum {
	DataFrame = 0,
	TXDelay = 1,
	P = 2,
	SlotTime = 3,
	TXTail = 4,
	FullDuplex = 5,
	SetHardware = 6,
	Return = 0xFF
} KissCmd;

#ifdef __cplusplus
}
#endif

#endif /* RADIO_KISS_H_ */
