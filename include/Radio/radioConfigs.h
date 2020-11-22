#ifndef CONFIGS_H_
#define CONFIGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RADIO_RSSI_THRESHOLD						-90		//Radio RSSI activity threshold, above this level channel activity is assumed (for Morse and LED indication)

typedef enum {
	RadioMode_OFF = 0,
	RadioMode_RX = 1,
	RadioMode_TX = 2
} RadioMode;

typedef enum {
	RadioModulation_AM = 1,
	RadioModulation_FM = 2,
	RadioModulation_AFSK = 3,
	RadioModulation_ASK = 4,
	RadioModulation_FSK = 5,
	RadioModulation_GMSK = 6,
	RadioModulation_4FSK = 7,
	RadioModulation_BPSK = 8,
	RadioModulation_QPSK = 9
} RadioModulation;

typedef enum {
	RadioEncoder_NRZ = 0,
	RadioEncoder_NRZ_S = 1,
	RadioEncoder_NRZI = 2,
	RadioEncoder_NRZI_S = 3,
	RadioEncoder_FM1 = 4,
	RadioEncoder_FM0 = 5,
	RadioEncoder_Manchester = 6,
} RadioEncoder;

typedef enum {
	RadioFraming_RAW = 0,
	RadioFraming_HDLC = 1,
	RadioFraming_WMBus = 2,
} RadioFraming;

typedef enum {
	RadioCRC_OFF = 0,
	RadioCRC_CCITT = 1,
	RadioCRC_CRC16 = 2,
	RadioCRC_DNP = 3,
	RadioCRC_CRC32 = 4
} RadioCRC;

//Radio A (UHF) Configurations
//Basic, shared for all modulations
volatile RadioMode operationModeA;		//0-> Off, 1-> RX, 2-> TX
volatile uint32_t centerFrequencyA;		//Hz
volatile RadioModulation modulationA;	//1: AM; 2: FM; 3: AFSK; 4: ASK; 5: FSK; 6: GMSK; 7: 4-FSK; 8: BPSK; 9: QPSK;
volatile uint32_t ifFrequncyA;			//Hz
volatile uint32_t bandwidthA;			//Hz
volatile uint32_t txDatarateA;			//bit/s
volatile uint32_t rxDatarateA;			//bit/s
volatile uint32_t afcRangeA;			//Hz
volatile uint8_t outputPowerA;			//1dBm step, 0: -10dBm -> 26: 16 dBm
volatile uint8_t agcSpeedA;				//0: 79577Hz; 1: 59683Hz; 2: 34815Hz; 3: 18651Hz; 4: 9636Hz; 5: 4896Hz; 6: 2467Hz; 7: 1239Hz; 8: 620Hz; 9: 311Hz; 10: 155Hz; 11: 78Hz; 12: 39Hz; 13: 19Hz; 14: 10Hz; 15: OFF

//Special for FSK
volatile uint32_t frequencyDeviationA;	//Hz

//Special for AFSK
volatile uint16_t afskSpaceA;			//Hz
volatile uint16_t afskMarkA;			//Hz
volatile uint16_t afskDetectorBWA;		//Hz

//Special for Morse
volatile uint8_t morseSpeedA;			//WPM (0-> Off)

//Digital Packet Settings
volatile RadioEncoder encoderA;			//0: NRZ; 1: NRZ-S; 2: NRZI; 3: NRZI-S; 4: FM1; 5: FM0; 6: Manchester
volatile RadioFraming framingA;			//0: RAW; 1: HDLC; 2: Wireless M-Bus
volatile RadioCRC crcA;					//0: OFF; 1: CCITT; 2: CRC16; 3: DNP; 4: CRC32

//Tracking Variables
volatile int8_t rssiTrackingA;			//RSSI in signed format
volatile int32_t rfFrequencyTrackingA;	//Tracking in signed format and counts not Hz

//Radio B (UHF) Configurations
//Basic, shared for all modulations
volatile RadioMode operationModeB;		//0-> Off, 1-> RX, 2-> TX
volatile uint32_t centerFrequencyB;		//Hz
volatile RadioModulation modulationB;	//1: AM; 2: FM; 3: AFSK; 4: ASK; 5: FSK; 6: GMSK; 8: BPSK; 9: QPSK;
volatile uint32_t ifFrequncyB;			//Hz
volatile uint32_t bandwidthB;			//Hz
volatile uint32_t txDatarateB;			//bit/s
volatile uint32_t rxDatarateB;			//bit/s
volatile uint32_t afcRangeB;			//Hz
volatile uint8_t outputPowerB;			//1dBm step, 0: -10dBm -> 26: 16 dBm
volatile uint8_t agcSpeedB;				//0: 79577Hz; 1: 59683Hz; 2: 34815Hz; 3: 18651Hz; 4: 9636Hz; 5: 4896Hz; 6: 2467Hz; 7: 1239Hz; 8: 620Hz; 9: 311Hz; 10: 155Hz; 11: 78Hz; 12: 39Hz; 13: 19Hz; 14: 10Hz; 15: 5Hz

//Special for FSK
volatile uint32_t frequencyDeviationB;	//Hz

//Special for AFSK
volatile uint16_t afskSpaceB;			//Hz
volatile uint16_t afskMarkB;			//Hz
volatile uint16_t afskDetectorBWB;		//Hz

//Special for Morse
volatile uint8_t morseSpeedB;			//WPM (0-> Off)

//Digital Packet Settings
volatile RadioEncoder encoderB;			//0: NRZ; 1: NRZI; 2: FM1; 3: FM0; 4: Manchester
volatile RadioFraming framingB;			//0: Raw; 1: HDLC; 3: WM-Bus
volatile RadioCRC crcB;					//0: Off; 1: CCITT; 2: CRC16; 3: DNP; 4: CRC32

//Tracking Variables
volatile int8_t rssiTrackingB;			//RSSI in signed format
volatile int32_t rfFrequencyTrackingB;	//Tracking in signed format and counts not Hz

#ifdef __cplusplus
}
#endif

#endif /* CONFIGS_H_ */
