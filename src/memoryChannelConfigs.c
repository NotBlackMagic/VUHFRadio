#include "memoryChannelConfigs.h"

volatile RadioConfigsStruct memoryChannelsFixed[MEMORY_CHANNELS_FIXED] = {
{		//AFSK-1200 Settings
		.operationMode = RadioMode_RX,
		.centerFrequency = 0,
		.modulation = RadioModulation_AFSK,
		.frequencyDeviation = 3000,
		.bandwidth = 15000,
		.ifFrequency = 7500,
		.rxDatarate = 1200,
		.txDatarate = 1200,
		.outputPower = 16,
		.afcRange = 3750,
		.agcSpeed = 7,

		.afskSpace = 2200,
		.afskMark = 1200,

		.tncMode = RadioTNCMode_KISS,
		.encoder = RadioEncoder_NRZI,
		.framing = RadioFraming_HDLC,
		.crc = RadioCRC_CCITT,
		.preambleSymbol = 0x55,
		.preambleLength = 20
},
{		//FSK-9600 (G3RUH) Settings
		.operationMode = RadioMode_RX,
		.centerFrequency = 0,
		.modulation = RadioModulation_FSK,
		.frequencyDeviation = 4800,
		.bandwidth = 14400,
		.ifFrequency = 7200,
		.rxDatarate = 9600,
		.txDatarate = 9600,
		.outputPower = 16,
		.afcRange = 3600,
		.agcSpeed = 4,

		.afskSpace = 2200,
		.afskMark = 1200,

		.tncMode = RadioTNCMode_KISS,
		.encoder = RadioEncoder_NRZI_S,
		.framing = RadioFraming_HDLC,
		.crc = RadioCRC_CCITT,
		.preambleSymbol = 0x55,
		.preambleLength = 20
},
{		//BPSK-9600 Settings
		.operationMode = RadioMode_RX,
		.centerFrequency = 0,
		.modulation = RadioModulation_BPSK,
		.frequencyDeviation = 4800,
		.bandwidth = 19200,
		.ifFrequency = 9600,
		.rxDatarate = 9600,
		.txDatarate = 9600,
		.outputPower = 16,
		.afcRange = 4800,
		.agcSpeed = 4,

		.afskSpace = 2200,
		.afskMark = 1200,

		.tncMode = RadioTNCMode_KISS,
		.encoder = RadioEncoder_NRZI_S,
		.framing = RadioFraming_HDLC,
		.crc = RadioCRC_CCITT,
		.preambleSymbol = 0x55,
		.preambleLength = 20
},
{		//FM Wideband
		.operationMode = RadioMode_RX,
		.centerFrequency = 93200000 + 50000,			//Comercial: 97400000, RFM: 93200000, Mega Hits: 92400000
		.modulation = RadioModulation_FM,
		.frequencyDeviation = 65000,
		.bandwidth = 100000,
		.ifFrequency = 10000,
		.rxDatarate = 200000,
		.txDatarate = 200000,
		.outputPower = 16,
		.afcRange = 25000,
		.agcSpeed = 9,

		.afskSpace = 2200,
		.afskMark = 1200,

		.tncMode = RadioTNCMode_OFF,
		.encoder = RadioEncoder_NRZI,
		.framing = RadioFraming_HDLC,
		.crc = RadioCRC_CCITT,
		.preambleSymbol = 0x55,
		.preambleLength = 20
}
};
