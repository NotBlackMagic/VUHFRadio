#ifndef CONFIGS_H_
#define CONFIGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//Radio A (UHF) Configurations
//Basic, shared for all modulations
volatile uint8_t operationModeA;		//0-> Off, 1-> RX, 2-> TX
volatile uint32_t centerFrequencyA;		//Hz
volatile uint8_t modulationA;			//1: AM; 2: FM; 3: AFSK; 4: ASK; 5: FSK; 6: GMSK; 8: BPSK; 9: QPSK;
volatile uint32_t ifFrequncyA;			//Hz
volatile uint32_t bandwidthA;			//Hz
volatile uint32_t txDatarateA;			//bit/s
volatile uint32_t rxDatarateA;			//bit/s
volatile uint32_t afcRangeA;			//Hz
volatile uint8_t outputPowerA;			//1dBm step, 0: -10dBm -> 26: 16 dBm
volatile uint8_t agcSpeedA;				//0: 79577Hz; 1: 59683Hz; 2: 34815Hz; 3: 18651Hz; 4: 9636Hz; 5: 4896Hz; 6: 2467Hz; 7: 1239Hz; 8: 620Hz; 9: 311Hz; 10: 155Hz; 11: 78Hz; 12: 39Hz; 13: 19Hz; 14: 10Hz; 15: 5Hz

//Special for FSK
volatile uint32_t frequencyDeviationA;	//Hz

//Special for AFSK
volatile uint16_t afskSpaceA;			//Hz
volatile uint16_t afskMarkA;			//Hz
volatile uint16_t afskDetectorBWA;		//Hz

//Special for Morse
volatile uint8_t morseSpeedA;			//WPM (0-> Off)

//Digital Packet Settings
volatile uint8_t encoderA;				//0: NRZ; 1: NRZI; 2: FM1; 3: FM0; 4: Manchester
volatile uint8_t framingA;				//0: Raw; 1: HDLC; 3: WM-Bus
volatile uint8_t crcA;					//0: Off; 1: CCITT; 2: CRC16; 3: DNP; 4: CRC32

#ifdef __cplusplus
}
#endif

#endif /* CONFIGS_H_ */
