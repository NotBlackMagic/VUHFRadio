#ifndef USERCONFIGS_H_
#define USERCONFIGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "radioConfigs.h"

typedef enum {
	Memory_AFSK_1200,
	Memory_FSK_9600,
	Memory_FM_WB
} MemoryChannels;

extern volatile RadioConfigsStruct memoryChannelsFixed[3];

/*	AFSK-1200 Settings
	radioAConfig.baseConfigs.radio = RADIO_A;
	radioAConfig.baseConfigs.radioXTAL = RADIO_A_XTAL;
	radioAConfig.baseConfigs.radioCenterFrequencyMin = RADIO_A_FREQ_MIN;
	radioAConfig.baseConfigs.radioCenterFrequencyMax = RADIO_A_FREQ_MAX;
	radioAConfig.operationMode = RadioMode_RX;
	radioAConfig.centerFrequency = 436450000 + 4300;
	radioAConfig.modulation = RadioModulation_AFSK;
	radioAConfig.frequencyDeviation = 3000;
	radioAConfig.bandwidth = 15000;
	radioAConfig.ifFrequency = 7500;
	radioAConfig.rxDatarate = 1200;
	radioAConfig.txDatarate = 1200;
	radioAConfig.outputPower = 16;
	radioAConfig.afcRange = 3750;
	radioAConfig.agcSpeed = 7;

	radioAConfig.afskSpace = 2200;
	radioAConfig.afskMark = 1200;

	radioAConfig.tncMode = RadioTNCMode_KISS;
	radioAConfig.encoder = RadioEncoder_NRZI;
	radioAConfig.framing = RadioFraming_HDLC;
	radioAConfig.crc = RadioCRC_CCITT;
	radioAConfig.preambleSymbol = 0x55;
	radioAConfig.preambleLength = 20;
 */

/*	FSK-9600 (G3RUH) Settings
	radioAConfig.baseConfigs.radio = RADIO_A;
	radioAConfig.baseConfigs.radioXTAL = RADIO_A_XTAL;
	radioAConfig.baseConfigs.radioCenterFrequencyMin = RADIO_A_FREQ_MIN;
	radioAConfig.baseConfigs.radioCenterFrequencyMax = RADIO_A_FREQ_MAX;
	radioAConfig.operationMode = RadioMode_RX;
	radioAConfig.centerFrequency = 436450000 + 4300;
	radioAConfig.modulation = RadioModulation_FSK;
	radioAConfig.frequencyDeviation = 4800;
	radioAConfig.bandwidth = 14400;
	radioAConfig.ifFrequency = 7200;
	radioAConfig.rxDatarate = 9600;
	radioAConfig.txDatarate = 9600;
	radioAConfig.outputPower = 16;
	radioAConfig.afcRange = 3600;
	radioAConfig.agcSpeed = 7;

	radioAConfig.afskSpace = 2200;
	radioAConfig.afskMark = 1200;

	radioAConfig.tncMode = RadioTNCMode_KISS;
	radioAConfig.encoder = RadioEncoder_NRZI_S;
	radioAConfig.framing = RadioFraming_HDLC;
	radioAConfig.crc = RadioCRC_CCITT;
	radioAConfig.preambleSymbol = 0x55;
	radioAConfig.preambleLength = 20;
*/

#ifdef __cplusplus
}
#endif

#endif /* USERCONFIGS_H_ */
