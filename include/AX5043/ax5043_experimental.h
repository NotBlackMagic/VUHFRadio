#ifndef AX5043_AX5043_DSPMODE_H_
#define AX5043_AX5043_DSPMODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of TMMUX Register
#define TMBOX_MASK							0x07	//TMBOX Bit Value Mask (for GPADCSourceSelection)
//TMMUX GPADC1 and GPADC2 Output Setting
typedef enum {
	GPADCSource_0 = 0,		//GPADC1: Default			GPADC2: Default
	GPADCSource_1 = 1,		//GPADC1: IREF10.NTST		GPADC2: VREF.800
	GPADCSource_2 = 2,		//GPADC1: ITEST.OSC			GPADC2: VDD.REF
	GPADCSource_3 = 3,		//GPADC1: AUXP.I			GPADC2: AUXN.I
	GPADCSource_4 = 4,		//GPADC1: AUXP.Q			GPADC2: AUXN.Q
	GPADCSource_5 = 5,		//GPADC1: AUXP.I			GPADC2: AUXP.Q
	GPADCSource_6 = 6,		//GPADC1: OUT.DET.I			GPADC2: OUT.DET.Q
	GPADCSource_7 = 7,		//GPADC1: VDD.REGS			GPADC2: VDD.MODEM
} GPADCSourceSelection;

//Register Configuration of BBDETECTOR Register
#define AUXEN_MASK							0x0F	//Baseband Enable Filter Output on Detector/Auxiliary Bus
#define DETCOMPEN_MASK						0x10	//Baseband Enable Detector
#define DETBUFEN_MASK						0x20	//Baseband Enable Detector Output Driver Amplifier
#define BBCOMPI_MASK						0x40	//Baseband Comparator I
#define BBCOMPQ_MASK						0x80	//Baseband Comparator Q

//Register Configuration of DSPMODESHREG Register
#define DSPMODESHREG_MASK					0xFF	//DSPMode SPI Mode Shift Register Mask

//Register Configuration of DSPMODECFG Register
#define SYNCSOURCE_MASK						0x03	//SYNCSOURCE Bit Value Mask (for SyncSourceSelection)
#define DSP_SPI_MASK						0x40	//If set to 1, the shift register (DSPMODESHREG) can be accessed over SPI
#define FSYNC_DLY_MASK						0x80	//If set to 0, FSYNC leads the first data bit by one bit. If set to 1, FSYNC coincides with the first data bit
//DSPMODECFG Sync Source Bits
typedef enum {
	SyncSource_Off = 0,
	SyncSource_Bit_Clock = 1,
	SyncSource_Sample_Clock = 2,
	SyncSource_Baseband_Clock = 3
} SyncSourceSelection;

//Register Configuration of DSPMODESKIP1 & DSPMODESKIP0 Register
#define DSPMODESKIP0_MASK					0xFF	//DSPMODESKIP0 Bit Values Mask (for DSPModeSkip)
#define DSPMODESKIP1_MASK					0xFF	//DSPMODESKIP1 Bit Values Mask (for DSPModeSkip)
//DSPMODESKIP0 & DSPMODESKIP1 Bits
typedef union {
	struct {
		uint8_t skipsoftsamp : 1;	//Skip Demodulator Soft Sample if set to 1
		uint8_t skipbasebandiq : 1;	//Skip Baseband IQ if set to 1
		uint8_t skipsampiq : 1;		//Skip Sample IQ if set to 1
		uint8_t skipsamprotiq : 1;	//Skip Rotated Sample IQ if set to 1
		uint8_t skipsampmag : 1;	//Skip Sample Magnitude if set to 1
		uint8_t skipsampphase : 1;	//Skip Sample Phase if set to 1
		uint8_t skipampl : 1;		//Skip Amplitude Tracking if set to 1
		uint8_t skiprffreq : 1;		//Skip RF Frequency Tracking if set to 1
		uint8_t skipfreq : 1;		//Skip Frequecy Tracking if set to 1
		uint8_t skipphase : 1;		//Skip Phase Tracking if set to 1
		uint8_t skipdatarate : 1;	//Skip Datarate Tracking if set to 1
		uint8_t skipfskdemod : 1;	//Skip FSK Demodulator Output if set to 1
		uint8_t skipafskdemod : 1;	//Skip AFSK Demodulator Output if set to 1
		uint8_t skiprssi : 1;		//Skip RSSI if set to 1
		uint8_t skipagc : 1;		//Skip AGC if set to 1
		uint8_t skipnone : 1;		////No valid/used bits
	};
	uint16_t raw;
} DSPModeSkip;

void AX5043ExperimentalSetGPADCMux(uint8_t interfaceID, GPADCSourceSelection gpadcMux);
GPADCSourceSelection AX5043ExperimentalGetGPADCMux(uint8_t interfaceID);
void AX5043ExperimentalEnableBasebandFilterOutput(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043ExperimentalIsEnabledBasebandFilterOutput(uint8_t interfaceID);
void AX5043ExperimentalEnableBasebandDetector(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043ExperimentalIsEnabledBasebandDetector(uint8_t interfaceID);
void AX5043ExperimentalEnableBasebandDetectorOutputDriver(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043ExperimentalIsEnabledBasebandDetectorOutputDriver(uint8_t interfaceID);
uint8_t AX5043ExperimentalGetBasebandIComparatorState(uint8_t interfaceID);
uint8_t AX5043ExperimentalGetBasebandQComparatorState(uint8_t interfaceID);
uint8_t AX5043ExperimentalGetDSPModeShiftRegisterValue(uint8_t interfaceID);
void AX5043ExperimentalSetSyncSource(uint8_t interfaceID, SyncSourceSelection source);
SyncSourceSelection AX5043ExperimentalGetSyncSource(uint8_t interfaceID);
void AX5043ExperimentalEnableDSPModeSPI(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043ExperimentalIsEnabledDSPModeSPI(uint8_t interfaceID);
void AX5043ExperimentalEnableFSYNCDelay(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043ExperimentalIsEnabledFSYNCDelay(uint8_t interfaceID);
void AX5043ExperimentalSetDSPModeSkipData(uint8_t interfaceID, DSPModeSkip skippedData);
DSPModeSkip AX5043ExperimentalGetDSPModeSkipData(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_DSPMODE_H_ */
