#ifndef CONFIGS_H_
#define CONFIGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RADIO_RSSI_THRESHOLD						-90		//Radio RSSI activity threshold, above this level channel activity is assumed (for Morse and LED indication)

#define RADIO_A								0
#define RADIO_B								1

#define RADIO_A_XTAL						16000000	//Xtal Frequency in Hz of Radio A
#define RADIO_B_XTAL						16000000	//Xtal Frequency in Hz of Radio A

#define RADIO_A_FREQ_MAX					437000000
#define RADIO_A_FREQ_MIN					435000000

#define RADIO_B_FREQ_MAX					147000000
#define RADIO_B_FREQ_MIN					145000000

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
	RadioTNCMode_OFF = 0,
	RadioTNCMode_KISS = 1,
	RadioTNCMode_SMACK = 2
} RadioTNCMode;

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

typedef struct {
	uint8_t radio;						//RADIO_A: 0; RADIO_B: 1;
	uint32_t radioXTAL;					//Xtal Frequency in Hz
	uint32_t radioCenterFrequencyMin;	//Min RF Center Frequency
	uint32_t radioCenterFrequencyMax;	//Max RF Center Frequency
	int8_t radioRSSIOffset;				//Calibrate RSSI: Compensate for Board effects
} RadioBaseConfigs;

typedef struct {
	//Basic, shared for all modulations
	RadioMode operationMode;		//0-> Off, 1-> RX, 2-> TX
	uint32_t centerFrequency;		//Hz
	RadioModulation modulation;		//1: AM; 2: FM; 3: AFSK; 4: ASK; 5: FSK; 6: GMSK; 7: 4-FSK; 8: BPSK; 9: QPSK;
	uint32_t ifFrequency;			//Hz
	uint32_t bandwidth;				//Hz
	uint32_t txDatarate;			//bit/s
	uint32_t rxDatarate;			//bit/s
	uint32_t afcRange;				//Hz
	int8_t outputPower;				//In dBm from -10dBm to 16 dBm
	uint8_t agcSpeed;				//0: 79577Hz; 1: 59683Hz; 2: 34815Hz; 3: 18651Hz; 4: 9636Hz; 5: 4896Hz; 6: 2467Hz; 7: 1239Hz; 8: 620Hz; 9: 311Hz; 10: 155Hz; 11: 78Hz; 12: 39Hz; 13: 19Hz; 14: 10Hz; 15: OFF
	//Special for FSK
	uint32_t frequencyDeviation;	//Hz
	//Special for AFSK
	uint16_t afskSpace;				//Hz
	uint16_t afskMark;				//Hz
	uint16_t afskDetectorBW;		//Hz
	//Special for Morse
	uint8_t morseSpeed;				//WPM (0-> Off)
	//Digital Packet Settings
	RadioTNCMode tncMode;			//0: TNC Mode Off; 1: TNC Mode On
	RadioEncoder encoder;			//0: NRZ; 1: NRZ-S; 2: NRZI; 3: NRZI-S; 4: FM1; 5: FM0; 6: Manchester
	RadioFraming framing;			//0: RAW; 1: HDLC; 2: Wireless M-Bus
	RadioCRC crc;					//0: OFF; 1: CCITT; 2: CRC16; 3: DNP; 4: CRC32
	uint8_t preambleSymbol;			//Byte
	uint8_t preambleLength;			//Length
} RadioConfigsStruct;

typedef struct {
	int8_t rssiTracking;			//RSSI in signed format
	int32_t rfFrequencyTracking;	//Tracking in signed format and counts not Hz
} RadioTrackingStruct;

//Radio A (UHF) Configurations
extern volatile RadioBaseConfigs radioABaseConfigs;			//Base Radio Configs Module
extern volatile RadioConfigsStruct radioAConfig;

//Tracking Variables
extern volatile RadioTrackingStruct radioATracking;

//Radio B (UHF) Configurations
extern volatile RadioBaseConfigs radioBBaseConfigs;			//Base Radio Configs Module
extern volatile RadioConfigsStruct radioBConfig;

//Tracking Variables
extern volatile RadioTrackingStruct radioBTracking;

#ifdef __cplusplus
}
#endif

#endif /* CONFIGS_H_ */
