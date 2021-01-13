
#ifndef AX5043_AX5043_TXPARAM_H_
#define AX5043_AX5043_TXPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of MODCFGF Register
#define FREQSHAPE_MASK						0x03	//FREQSHAPE Bit Value Mask (for FreqShape)
//FREQSHAPE  Bits
typedef enum {
	FreqShape_invalid = 0,
	FreqShape_extloopfilter = 1,
	FreqShape_gausBT03 = 2,
	FreqShape_gausBT05 = 3
} FreqShape;

//Register Configuration of FSKDEV Register for (G)FSK and AFSK
#define FSKDEV0_MASK						0xFF	//(G)FSK Frequency: FSKDEV = (fdeviation / fxtal) * 2^24 + 1/2; AFSK Frequency: FSKDEV = ((0.858785 * fdeviation) / fxtal) * 2^24 + 1/2
#define FSKDEV1_MASK						0xFF	//(G)FSK Frequency: FSKDEV = (fdeviation / fxtal) * 2^24 + 1/2; AFSK Frequency: FSKDEV = ((0.858785 * fdeviation) / fxtal) * 2^24 + 1/2
#define FSKDEV2_MASK						0xFF	//(G)FSK Frequency: FSKDEV = (fdeviation / fxtal) * 2^24 + 1/2; AFSK Frequency: FSKDEV = ((0.858785 * fdeviation) / fxtal) * 2^24 + 1/2
//Register Configuration of FSKDEV Register for FM Mode
#define FMSHIFT_MASK						0x07	//(FSKDEV0) These Bits Scale the ADC Value Mask (for FMShift)
#define FMINPUT_MASK						0x03	//(FSKDEV1) Input Selection Mask (for FMInput)
#define FMSEXT_MASK							0x40	//(FSKDEV1) ADC Sign Extension Mask
#define FMOFFS_MASK							0x80	//(FSKDEV1) ADC Offset Subtract Mask
//FMSHIFT Bits
typedef enum {
	FMShift_15 = 0,		//FM fdeviation = (ADCFS * fxtal) / 2^15
	FMShift_14 = 1,		//FM fdeviation = (ADCFS * fxtal) / 2^14
	FMShift_13 = 2,		//FM fdeviation = (ADCFS * fxtal) / 2^13
	FMShift_12 = 3,		//FM fdeviation = (ADCFS * fxtal) / 2^12
	FMShift_11 = 4,		//FM fdeviation = (ADCFS * fxtal) / 2^11
	FMShift_10 = 5,		//FM fdeviation = (ADCFS * fxtal) / 2^10
	FMShift_9 = 6,		//FM fdeviation = (ADCFS * fxtal) / 2^9
	FMShift_8 = 7		//FM fdeviation = (ADCFS * fxtal) / 2^8
} FMShift;
//FMINPUT Bits
typedef enum {
	FMInput_gpadc13 = 0,	//FM Input is GPADC13
	FMInput_gpadc1 = 0,		//FM Input is GPADC1
	FMInput_gpadc2 = 0,		//FM Input is GPADC2
	FMInput_gpadc3 = 0		//FM Input is GPADC3
} FMInput;

//Register Configuration of MODCFGA Register
#define TXDIFF_MASK							0x01	//Enable Differential Transmitter
#define TXSE_MASK							0x02	//Enable Single Ended Transmitter
#define AMPLSHAPE_MASK						0x04	//Amplitude shape: 0 -> Unshapped, 1 -> Raised Cosine Shaped
#define SLOWRAMP_MASK						0x30	//Slow ramp bit mask (for SlowRamp)
#define PTTLCKGATE_MASK						0x40	//If 1, disable transmitter if PLL looses lock
#define BROWNGATE_MASK						0x80	//If 1, disable transmitter if Brown Out is detected
//SLOWRAMP Bits
typedef enum {
	SlowRamp_normal,	//Normal Startup (1 Bit Time)
	SlowRamp_2bit,		//2 Bit Time Startup
	SlowRamp_4bit,		//4 Bit Time Startup
	SlowRamp_8bit		//8 Bit Time Startup
} SlowRamp;

//Register Configuration of TXRATE Register
#define TXRATE0_MASK						0xFF	//Transmit Bitrate Mask. TXRATE = (BITRATE / fxtal) * 2^24 + 1/2
#define TXRATE1_MASK						0xFF	//Transmit Bitrate Mask. TXRATE = (BITRATE / fxtal) * 2^24 + 1/2
#define TXRATE2_MASK						0xFF	//Transmit Bitrate Mask. TXRATE = (BITRATE / fxtal) * 2^24 + 1/2

//Register Configuration of TXPWRCOEFFA Register
#define TXPWRCOEFFA0_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFA = a0 * 2^12 + 1/2
#define TXPWRCOEFFA1_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFA = a0 * 2^12 + 1/2

//Register Configuration of TXPWRCOEFFB Register
#define TXPWRCOEFFB0_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFB = a1 * 2^12 + 1/2
#define TXPWRCOEFFB1_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFB = a1 * 2^12 + 1/2

//Register Configuration of TXPWRCOEFFC Register
#define TXPWRCOEFFC0_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFC = a2 * 2^12 + 1/2
#define TXPWRCOEFFC1_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFC = a2 * 2^12 + 1/2

//Register Configuration of TXPWRCOEFFD Register
#define TXPWRCOEFFD0_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFD = a3 * 2^12 + 1/2
#define TXPWRCOEFFD1_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFD = a3 * 2^12 + 1/2

//Register Configuration of TXPWRCOEFFE Register
#define TXPWRCOEFFE0_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFE = a4 * 2^12 + 1/2
#define TXPWRCOEFFE1_MASK					0xFF	//Transmit Predistortion. TXPWRCOEFFE = a4 * 2^12 + 1/2

//Register Configuration of MODCFGP Register
#define PSKPULSELEN_MASK					0x07
#define PSKPULSECFG_MASK					0x18
#define PSKPULSEBOST_MASK					0xE0
//PSKPULSELEN Bits
typedef enum {
	PSKPulseLen_1 = 0,
	PSKPulseLen_2 = 1,
	PSKPulseLen_4 = 2,
	PSKPulseLen_8 = 3,
	PSKPulseLen_16 = 4,
	PSKPulseLen_32 = 5,
	PSKPulseLen_Off = 7
} PSKPulseLength;
//PSKPULSECFG Bits
typedef enum {
	PSKPulseCFG_Positive = 0,
	PSKPulseCFG_Negative = 1,
	PSKPulseCFG_Copysign = 2
} PSKPulsePolarity;
//PSKPULSEBOST Bits
typedef enum {
	PSKPulseBoost_1 = 0,
	PSKPulseBoost_2 = 1,
	PSKPulseBoost_4 = 2,
	PSKPulseBoost_8 = 3,
	PSKPulseBoost_16 = 4,
	PSKPulseBoost_32 = 5,
	PSKPulseBoost_64 = 6,
	PSKPulseBoost_Off = 7
} PSKPulseBoost;

void AX5043TXParamSetFrequencyShape(uint8_t interfaceID, FreqShape freqShape);
FreqShape AX5043TXParamGetFrequencyShape(uint8_t interfaceID);
void AX5043TXParamSetFSKFrequencyDeviation(uint8_t interfaceID, uint32_t freqDeviation);
uint32_t AX5043TXParamGetFSKFrequencyDeviation(uint8_t interfaceID);
void AX5043TXParamSetFMShift(uint8_t interfaceID, FMShift fmShift);
FMShift AX5043TXParamGetFMShift(uint8_t interfaceID);
void AX5043TXParamSetFMInput(uint8_t interfaceID, FMInput input);
FMShift AX5043TXParamGetFMInput(uint8_t interfaceID);
void AX5043TXParamSetADCSignExtension(uint8_t interfaceID, uint8_t signExt);
uint8_t AX5043TXParamGetADCSignExtension(uint8_t interfaceID);
void AX5043TXParamSetADCOffsetSubtraciont(uint8_t interfaceID, uint8_t adcSubtraction);
uint8_t AX5043TXParamGetADCOffsetSubtraciont(uint8_t interfaceID);
void AX5043TXParamEnableDiffTransmitter(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043TXParamIsDiffTransmitterEnabled(uint8_t interfaceID);
void AX5043TXParamEnableSingleEndedTransmitter(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043TXParamIsSingleEndedTransmitterEnabled(uint8_t interfaceID);
void AX5043TXParamSetAmplitudeShape(uint8_t interfaceID, uint8_t shape);
uint8_t AX5043TXParamGetAmplitudeShape(uint8_t interfaceID);
void AX5043TXParamSetSlowRamp(uint8_t interfaceID, SlowRamp slowRamp);
SlowRamp AX5043TXParamGetSlowRamp(uint8_t interfaceID);
void AX5043TXParamSetDisbleTransitterOnPLLLose(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043TXParamGetDisbleTransitterOnPLLLose(uint8_t interfaceID);
void AX5043TXParamSetDisbleTransitterOnBrownOut(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043TXParamGetDisbleTransitterOnBrownOut(uint8_t interfaceID);
void AX5043TXParamSetTXDatarate(uint8_t interfaceID, uint32_t datarate);
uint32_t AX5043TXParamGetTXDatarate(uint8_t interfaceID);
void AX5043TXParamSetTXPredistortionCoeffA(uint8_t interfaceID, uint16_t coeff);
uint16_t AX5043TXParamGetTXPredistortionCoeffA(uint8_t interfaceID);
void AX5043TXParamSetTXPredistortionCoeffB(uint8_t interfaceID, uint16_t coeff);
uint16_t AX5043TXParamGetTXPredistortionCoeffB(uint8_t interfaceID);
void AX5043TXParamSetTXPredistortionCoeffC(uint8_t interfaceID, uint16_t coeff);
uint16_t AX5043TXParamGetTXPredistortionCoeffC(uint8_t interfaceID);
void AX5043TXParamSetTXPredistortionCoeffD(uint8_t interfaceID, uint16_t coeff);
uint16_t AX5043TXParamGetTXPredistortionCoeffD(uint8_t interfaceID);
void AX5043TXParamSetTXPredistortionCoeffE(uint8_t interfaceID, uint16_t coeff);
uint16_t AX5043TXParamGetTXPredistortionCoeffE(uint8_t interfaceID);
void AX5043TXParamSetPSKPulseLength(uint8_t interfaceID, PSKPulseLength pulseLength);
PSKPulseLength AX5043TXParamGetPSKPulseLength(uint8_t interfaceID);
void AX5043TXParamSetPSKPulsePolarity(uint8_t interfaceID, PSKPulsePolarity pulsePolarity);
PSKPulsePolarity AX5043TXParamGetPSKPulsePolarity(uint8_t interfaceID);
void AX5043TXParamSetPSKPulseBoost(uint8_t interfaceID, PSKPulseBoost pulseBoost);
PSKPulseBoost AX5043TXParamGetPSKPulseBoost(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_TXPARAM_H_ */
