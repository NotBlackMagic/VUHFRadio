#ifndef AX5043_AX5043_RXPARAM_H_
#define AX5043_AX5043_RXPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of IFFREQ Register
#define IFFREQ0_MASK						0xFF	//IF Frequency. IFFREQ = ((fif * fxtaldiv) / fxtal) * 2^20 + 1/2
#define IFFREQ1_MASK						0xFF	//IF Frequency. IFFREQ = ((fif * fxtaldiv) / fxtal) * 2^20 + 1/2

//Register Configuration of DECIMATION Register
#define DECIMATION_MASK						0x7F	//Filter Decimation factor; Filter Output runs at: fbaseband = fxtal / (2^4 * fxtaldiv * DECIMATION)

//Register Configuration of RXDATARATE Register
#define RXDATARATE0_MASK					0xFF	//RX Datarate. RXDATARATE = (2^7 * fxtal) / (fxtal * BITRATE * DECIMATION) + 1/2
#define RXDATARATE1_MASK					0xFF	//RX Datarate. RXDATARATE = (2^7 * fxtal) / (fxtal * BITRATE * DECIMATION) + 1/2
#define RXDATARATE2_MASK					0xFF	//RX Datarate. RXDATARATE = (2^7 * fxtal) / (fxtal * BITRATE * DECIMATION) + 1/2

//Register Configuration of MAXDROFFSET Register
#define MAXDROFFSET0_MASK					0xFF	//The maximum bitrate offset the receiver is able to tolerate. MAXDROFFSET = (2^7 * fxtal * DBITRATE) / (fxtaldiv * BITRATE^2 * DECIMATION) + 1/2
#define MAXDROFFSET1_MASK					0xFF	//The maximum bitrate offset the receiver is able to tolerate. MAXDROFFSET = (2^7 * fxtal * DBITRATE) / (fxtaldiv * BITRATE^2 * DECIMATION) + 1/2
#define MAXDROFFSET2_MASK					0xFF	//The maximum bitrate offset the receiver is able to tolerate. MAXDROFFSET = (2^7 * fxtal * DBITRATE) / (fxtaldiv * BITRATE^2 * DECIMATION) + 1/2

//Register Configuration of MAXRFOFFSET Register
#define MAXRFOFFSET0_MASK					0xFF	//The maximum frequency offset the AFC should handle. MAXRFOFFSET =  (fcarrier / fxtal) * 2^24 + 1/2
#define MAXRFOFFSET1_MASK					0xFF	//The maximum frequency offset the AFC should handle. MAXRFOFFSET =  (fcarrier / fxtal) * 2^24 + 1/2
#define MAXRFOFFSET2_MASK					0x0F	//The maximum frequency offset the AFC should handle. MAXRFOFFSET =  (fcarrier / fxtal) * 2^24 + 1/2
#define FREQOFFSCORR_MASK					0x80	//Correct frequency offset at the first LO if this bit is one; at the second LO if this bit is zero

//Register Configuration of FSKDMAX Register
#define FSKDMAX0_MASK						0xFF	//Current FSK Demodulator Max Deviation. In manual mode FSKDMAX = 3 * 512 * fdeviation / BAUDRATE
#define FSKDMAX1_MASK						0xFF	//Current FSK Demodulator Max Deviation. In manual mode FSKDMAX = 3 * 512 * fdeviation / BAUDRATE

//Register Configuration of FSKDMIN Register
#define FSKDMIN0_MASK						0xFF	//Current FSK Demodulator Min Deviation. In manual mode FSKDEVMIN = -3 * 512 * fdeviation / BAUDRATE
#define FSKDMIN1_MASK						0xFF	//Current FSK Demodulator Min Deviation. In manual mode FSKDEVMIN = -3 * 512 * fdeviation / BAUDRATE

//Register Configuration of AFSKSPACE Register
#define AFSKSPACE0_MASK						0xFF	//AFSK Space (0-Bit encoding) Frequency. In RX: AFSKSPACE = (fafskspace * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskspace * 2^18) / fxtal + 0.5
#define AFSKSPACE1_MASK						0xFF	//AFSK Space (0-Bit encoding) Frequency. In RX: AFSKSPACE = (fafskspace * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskspace * 2^18) / fxtal + 0.5

//Register Configuration of AFSKMARK Register
#define AFSKMARK0_MASK						0xFF	//AFSK Mark (1-Bit encoding) Frequency. In RX: AFSKMARK = (fafskmark * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskmark * 2^18) / fxtal + 0.5
#define AFSKMARK1_MASK						0xFF	//AFSK Mark (1-Bit encoding) Frequency. In RX: AFSKMARK = (fafskmark * DECIMATION * fxtaldiv * 2^16) / fxtal + 1/2, In TX: AFSKSPACE = (fafskmark * 2^18) / fxtal + 0.5

//Register Configuration of AFSKCTRL Register
#define AFSKSHIFT_MASK						0x1F	//AFSK Detector Bandwidth = 2 * log2(fxtal / (2^5 * BITRATE * fxtaldiv * DECIMATION))

//Register Configuration of AMPLFILTER Register
#define AMPLFILTER_MASK						0x0F	//Amplitude Lowpass Filter. fc = fxtal / (2^5 * pi * fxtaldiv * DECIMATION) * arccos((k^2 + 2k - 2) / (2 * (k - 1)))

//Register Configuration of FREQUENCYLEAK Register
#define FREQUENCYLEAK_MASK					0x0F	//Leakiness of the Baseband Frequency Recovery Loop (0000 = off)

//Register Configuration of RXPARAMSETS Register
#define RXPS0_MASK							0x03	//RX Parameter Set Number to be used for initial settling
#define RXPS1_MASK							0x0C	//RX Parameter Set Number to be used after Pattern 1 matched and before Pattern 0 match
#define RXPS2_MASK							0x30	//RX Parameter Set Number to be used after Pattern 0 matched
#define RXPS3_MASK							0xC0	//RX Parameter Set Number to be used after a packet start has been detected

//Register Configuration of RXPARAMCURSET Register
#define RXSI_MASK							0x03	//RX Parameter Set Index (determines which RXPS is used)
#define RXSN_MASK							0x0C	//RX Parameter Set Number
#define RXSISF_MASK							0x10	//Rx Parameter Set Index (special function bit)
//RXSI Bits:
//0xx -> Normal Function (indirection via RXPS)
//1x0 -> Coarse AGC
//1x1 -> Baseband Offset Acquisition

//Register Configuration of AGCGAIN0 Register
#define AGCATTACK0_MASK						0x0F	//AGC gain reduction speed
#define AGCDECAY0_MASK						0xF0	//AGC gain increase speed

//Register Configuration of AGCGAIN1 Register
#define AGCATTACK1_MASK						0x0F	//AGC gain reduction speed
#define AGCDECAY1_MASK						0xF0	//AGC gain increase speed

//Register Configuration of AGCGAIN2 Register
#define AGCATTACK2_MASK						0x0F	//AGC gain reduction speed
#define AGCDECAY2_MASK						0xF0	//AGC gain increase speed

//Register Configuration of AGCGAIN3 Register
#define AGCATTACK3_MASK						0x0F	//AGC gain reduction speed
#define AGCDECAY3_MASK						0xF0	//AGC gain increase speed

//Register Configuration of AGCTARGET0 Register
#define AGCTARGET0_MASK						0xFF	//The target ADC output average magnitude = 2 * (AGCTARGETx / 16)

//Register Configuration of AGCTARGET1 Register
#define AGCTARGET1_MASK						0xFF	//The target ADC output average magnitude = 2 * (AGCTARGETx / 16)

//Register Configuration of AGCTARGET2 Register
#define AGCTARGET2_MASK						0xFF	//The target ADC output average magnitude = 2 * (AGCTARGETx / 16)

//Register Configuration of AGCTARGET3 Register
#define AGCTARGET3_MASK						0xFF	//The target ADC output average magnitude = 2 * (AGCTARGETx / 16)

//Register Configuration of AGCAHYST0 Register
#define AGCAHYST0_MASK						0x07	//his field specifies Digital Threshold Range = (AGCAHYSTx + 1) * 3dB

//Register Configuration of AGCAHYST1 Register
#define AGCAHYST1_MASK						0x07	//his field specifies Digital Threshold Range = (AGCAHYSTx + 1) * 3dB

//Register Configuration of AGCAHYST2 Register
#define AGCAHYST2_MASK						0x07	//his field specifies Digital Threshold Range = (AGCAHYSTx + 1) * 3dB

//Register Configuration of AGCAHYST3 Register
#define AGCAHYST3_MASK						0x07	//his field specifies Digital Threshold Range = (AGCAHYSTx + 1) * 3dB

//Register Configuration of AGCMINMAX0 Register
#define AGCMINDA0_MASK						0x07	//AGC Reset Value if exceeds minimum threshold
#define AGCMAXDA0_MASK						0x70	//AGC Reset Value if exceeds maximum threshold

//Register Configuration of AGCMINMAX1 Register
#define AGCMINDA1_MASK						0x07	//AGC Reset Value if exceeds minimum threshold
#define AGCMAXDA1_MASK						0x70	//AGC Reset Value if exceeds maximum threshold

//Register Configuration of AGCMINMAX2 Register
#define AGCMINDA2_MASK						0x07	//AGC Reset Value if exceeds minimum threshold
#define AGCMAXDA2_MASK						0x70	//AGC Reset Value if exceeds maximum threshold

//Register Configuration of AGCMINMAX3 Register
#define AGCMINDA3_MASK						0x07	//AGC Reset Value if exceeds minimum threshold
#define AGCMAXDA3_MASK						0x70	//AGC Reset Value if exceeds maximum threshold

//Register Configuration of TIMEGAIN0 Register
#define TIMEGAIN0E_MASK						0x0F	//Gain of the timing recovery loop; this is the exponent
#define TIMEGAIN0M_MASK						0xF0	//Gain of the timing recovery loop; this is the mantissa

//Register Configuration of TIMEGAIN1 Register
#define TIMEGAIN1E_MASK						0x0F	//Gain of the timing recovery loop; this is the exponent
#define TIMEGAIN1M_MASK						0xF0	//Gain of the timing recovery loop; this is the mantissa

//Register Configuration of TIMEGAIN2 Register
#define TIMEGAIN2E_MASK						0x0F	//Gain of the timing recovery loop; this is the exponent
#define TIMEGAIN2M_MASK						0xF0	//Gain of the timing recovery loop; this is the mantissa

//Register Configuration of TIMEGAIN3 Register
#define TIMEGAIN3E_MASK						0x0F	//Gain of the timing recovery loop; this is the exponent
#define TIMEGAIN3M_MASK						0xF0	//Gain of the timing recovery loop; this is the mantissa

//Register Configuration of DRGAIN0 Register
#define DRGAIN0E_MASK						0x0F	//Gain of the datarate recovery loop; this is the exponent
#define DRGAIN0M_MASK						0xF0	//Gain of the datarate recovery loop; this is the mantissa

//Register Configuration of DRGAIN1 Register
#define DRGAIN1E_MASK						0x0F	//Gain of the datarate recovery loop; this is the exponent
#define DRGAIN1M_MASK						0xF0	//Gain of the datarate recovery loop; this is the mantissa

//Register Configuration of DRGAIN2 Register
#define DRGAIN2E_MASK						0x0F	//Gain of the datarate recovery loop; this is the exponent
#define DRGAIN2M_MASK						0xF0	//Gain of the datarate recovery loop; this is the mantissa

//Register Configuration of DRGAIN3 Register
#define DRGAIN3E_MASK						0x0F	//Gain of the datarate recovery loop; this is the exponent
#define DRGAIN3M_MASK						0xF0	//Gain of the datarate recovery loop; this is the mantissa

//Register Configuration of PHASEGAIN0 Register
#define PHASEGAIN0_MASK						0x0F	//Gain of the phase recovery loop
#define FILTERIDX0_MASK						0xC0	//Decimation Filter Fractional Bandwidth

//Register Configuration of PHASEGAIN1 Register
#define PHASEGAIN1_MASK						0x0F	//Gain of the phase recovery loop
#define FILTERIDX1_MASK						0xC0	//Decimation Filter Fractional Bandwidth

//Register Configuration of PHASEGAIN2 Register
#define PHASEGAIN2_MASK						0x0F	//Gain of the phase recovery loop
#define FILTERIDX2_MASK						0xC0	//Decimation Filter Fractional Bandwidth

//Register Configuration of PHASEGAIN3 Register
#define PHASEGAIN3_MASK						0x0F	//Gain of the phase recovery loop
#define FILTERIDX3_MASK						0xC0	//Decimation Filter Fractional Bandwidth

//Register Configuration of FREQGAINA0 Register
#define FREQGAINA0_MASK						0x0F	//Gain of the baseband frequency recovery loop
#define FREQAMPLGATE0_MASK					0x10	//If set to 1, only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum (or larger than the average amplitude)
#define FREQHALFMOD0_MASK					0x20	//If 1, the Frequency offset wraps around from 0x1fff to 0x2000, and vice versa
#define FREQMODULO0_MASK					0x40	//If 1, the Frequency offset wraps around from 0x3fff to 0x4000, and vice versa
#define FREQLIM0_MASK						0x80	//If 1, limit Frequency Offset to 0x4000...0x3fff

//Register Configuration of FREQGAINA1 Register
#define FREQGAINA1_MASK						0x0F	//Gain of the baseband frequency recovery loop
#define FREQAMPLGATE1_MASK					0x10	//If set to 1, only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum (or larger than the average amplitude)
#define FREQHALFMOD1_MASK					0x20	//If 1, the Frequency offset wraps around from 0x1fff to 0x2000, and vice versa
#define FREQMODULO1_MASK					0x40	//If 1, the Frequency offset wraps around from 0x3fff to 0x4000, and vice versa
#define FREQLIM1_MASK						0x80	//If 1, limit Frequency Offset to 0x4000...0x3fff

//Register Configuration of FREQGAINA2 Register
#define FREQGAINA2_MASK						0x0F	//Gain of the baseband frequency recovery loop
#define FREQAMPLGATE2_MASK					0x10	//If set to 1, only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum (or larger than the average amplitude)
#define FREQHALFMOD2_MASK					0x20	//If 1, the Frequency offset wraps around from 0x1fff to 0x2000, and vice versa
#define FREQMODULO2_MASK					0x40	//If 1, the Frequency offset wraps around from 0x3fff to 0x4000, and vice versa
#define FREQLIM2_MASK						0x80	//If 1, limit Frequency Offset to 0x4000...0x3fff

//Register Configuration of FREQGAINA3 Register
#define FREQGAINA3_MASK						0x0F	//Gain of the baseband frequency recovery loop
#define FREQAMPLGATE3_MASK					0x10	//If set to 1, only update the frequency offset recovery loops if the amplitude of the signal is larger than half the maximum (or larger than the average amplitude)
#define FREQHALFMOD3_MASK					0x20	//If 1, the Frequency offset wraps around from 0x1fff to 0x2000, and vice versa
#define FREQMODULO3_MASK					0x40	//If 1, the Frequency offset wraps around from 0x3fff to 0x4000, and vice versa
#define FREQLIM3_MASK						0x80	//If 1, limit Frequency Offset to 0x4000...0x3fff

//Register Configuration of FREQGAINB0 Register
#define FREQGAINB0_MASK						0x1F	//Gain of the baseband frequency recovery loop; the frequency error is measured with the frequency detector
#define FREQAVG0_MASK						0x40	//Average the frequency offset of two consecutive bits; this is useful for 0101 preambles in FSK mode
#define FREQFREEZE0_MASK					0x80	//Freeze the baseband frequency recovery loop if set

//Register Configuration of FREQGAINB1 Register
#define FREQGAINB1_MASK						0x1F	//Gain of the baseband frequency recovery loop; the frequency error is measured with the frequency detector
#define FREQAVG1_MASK						0x40	//Average the frequency offset of two consecutive bits; this is useful for 0101 preambles in FSK mode
#define FREQFREEZE1_MASK					0x80	//Freeze the baseband frequency recovery loop if set

//Register Configuration of FREQGAINB2 Register
#define FREQGAINB2_MASK						0x1F	//Gain of the baseband frequency recovery loop; the frequency error is measured with the frequency detector
#define FREQAVG2_MASK						0x40	//Average the frequency offset of two consecutive bits; this is useful for 0101 preambles in FSK mode
#define FREQFREEZE2_MASK					0x80	//Freeze the baseband frequency recovery loop if set

//Register Configuration of FREQGAINB3 Register
#define FREQGAINB3_MASK						0x1F	//Gain of the baseband frequency recovery loop; the frequency error is measured with the frequency detector
#define FREQAVG3_MASK						0x40	//Average the frequency offset of two consecutive bits; this is useful for 0101 preambles in FSK mode
#define FREQFREEZE3_MASK					0x80	//Freeze the baseband frequency recovery loop if set

//Register Configuration of FREQGAINC0 Register
#define FREQGAINC0_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the phase detector

//Register Configuration of FREQGAINC1 Register
#define FREQGAINC1_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the phase detector

//Register Configuration of FREQGAINC2 Register
#define FREQGAINC2_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the phase detector

//Register Configuration of FREQGAINC3 Register
#define FREQGAINC3_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the phase detector

//Register Configuration of FREQGAIND0 Register
#define FREQGAIND0_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the frequency detector
#define RFFREQFREEZE0_MASK					0x80	//Freeze the RF frequency recovery loop if set

//Register Configuration of FREQGAIND1 Register
#define FREQGAIND1_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the frequency detector
#define RFFREQFREEZE1_MASK					0x80	//Freeze the RF frequency recovery loop if set

//Register Configuration of FREQGAIND2 Register
#define FREQGAIND2_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the frequency detector
#define RFFREQFREEZE2_MASK					0x80	//Freeze the RF frequency recovery loop if set

//Register Configuration of FREQGAIND3 Register
#define FREQGAIND3_MASK						0x1F	//Gain of the RF frequency recovery loop; the frequency error is measured with the frequency detector
#define RFFREQFREEZE3_MASK					0x80	//Freeze the RF frequency recovery loop if set

//Register Configuration of AMPLGAIN0 Register
#define AMPLGAIN0_MASK						0x0F	//Gain of the amplitude recovery loop
#define AMPLAGC0_MASK						0x40	//If 1, try to correct the amplitude register when AGC jumps. This is not perfect, though
#define AMPLAVG0_MASK						0x80	//If 0, the amplitude is recovered by a peak detector with decay; if 1, the amplitude is recovered by averaging

//Register Configuration of AMPLGAIN1 Register
#define AMPLGAIN1_MASK						0x0F	//Gain of the amplitude recovery loop
#define AMPLAGC1_MASK						0x40	//If 1, try to correct the amplitude register when AGC jumps. This is not perfect, though
#define AMPLAVG1_MASK						0x80	//If 0, the amplitude is recovered by a peak detector with decay; if 1, the amplitude is recovered by averaging

//Register Configuration of AMPLGAIN2 Register
#define AMPLGAIN2_MASK						0x0F	//Gain of the amplitude recovery loop
#define AMPLAGC2_MASK						0x40	//If 1, try to correct the amplitude register when AGC jumps. This is not perfect, though
#define AMPLAVG2_MASK						0x80	//If 0, the amplitude is recovered by a peak detector with decay; if 1, the amplitude is recovered by averaging

//Register Configuration of AMPLGAIN3 Register
#define AMPLGAIN3_MASK						0x0F	//Gain of the amplitude recovery loop
#define AMPLAGC3_MASK						0x40	//If 1, try to correct the amplitude register when AGC jumps. This is not perfect, though
#define AMPLAVG3_MASK						0x80	//If 0, the amplitude is recovered by a peak detector with decay; if 1, the amplitude is recovered by averaging

//Register Configuration of FREQDEV0 Register
#define FREQDEV00_MASK						0xFF	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2
#define FREQDEV10_MASK						0x0F	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2

//Register Configuration of FREQDEV1 Register
#define FREQDEV01_MASK						0xFF	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2
#define FREQDEV11_MASK						0x0F	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2

//Register Configuration of FREQDEV2 Register
#define FREQDEV02_MASK						0xFF	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2
#define FREQDEV12_MASK						0x0F	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2

//Register Configuration of FREQDEV3 Register
#define FREQDEV03_MASK						0xFF	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2
#define FREQDEV13_MASK						0x0F	//Receiver Frequency Deviation. FRQDEVx = (fdeviation * 2^8 * ksf) / BITRATE + 1/2

//Register Configuration of FOURFSK0 Register
#define DEVDECAY0_MASK						0x0F	//Deviation Decay
#define DEVUPDATE0_MASK						0x10	//Enable Deviation Update

//Register Configuration of FOURFSK1 Register
#define DEVDECAY1_MASK						0x0F	//Deviation Decay
#define DEVUPDATE1_MASK						0x10	//Enable Deviation Update

//Register Configuration of FOURFSK2 Register
#define DEVDECAY2_MASK						0x0F	//Deviation Decay
#define DEVUPDATE2_MASK						0x10	//Enable Deviation Update

//Register Configuration of FOURFSK3 Register
#define DEVDECAY3_MASK						0x0F	//Deviation Decay
#define DEVUPDATE3_MASK						0x10	//Enable Deviation Update

//Register Configuration of BBOFFSRES0 Register
#define RESINTA0_MASK						0x0F	//Baseband Gain Block A Offset Compensation Resistors
#define RESINTB0_MASK						0xF0	//Baseband Gain Block B Offset Compensation Resistors

//Register Configuration of BBOFFSRES1 Register
#define RESINTA1_MASK						0x0F	//Baseband Gain Block A Offset Compensation Resistors
#define RESINTB1_MASK						0xF0	//Baseband Gain Block B Offset Compensation Resistors

//Register Configuration of BBOFFSRES2 Register
#define RESINTA2_MASK						0x0F	//Baseband Gain Block A Offset Compensation Resistors
#define RESINTB2_MASK						0xF0	//Baseband Gain Block B Offset Compensation Resistors

//Register Configuration of BBOFFSRES3 Register
#define RESINTA3_MASK						0x0F	//Baseband Gain Block A Offset Compensation Resistors
#define RESINTB3_MASK						0xF0	//Baseband Gain Block B Offset Compensation Resistors

void AX5043RXParamSetIFFrequency(uint8_t interfaceID, uint16_t ifFrequency);
uint16_t AX5043RXParamGetIFFrequency(uint8_t interfaceID);
void AX5043RXParamSetDecimation(uint8_t interfaceID, uint8_t decimation);
uint8_t AX5043RXParamGetDecimation(uint8_t interfaceID);
void AX5043RXParamSetRXDatarate(uint8_t interfaceID, uint32_t datarate);
uint32_t AX5043RXParamGetRXDatarate(uint8_t interfaceID);
void AX5043RXParamSetRXMaximumDatarateOffset(uint8_t interfaceID, uint32_t datarate);
uint32_t AX5043RXParamGetRXMaximumDatarateOffset(uint8_t interfaceID);
void AX5043RXParamSetRXMaximumFrequencyOffset(uint8_t interfaceID, uint32_t frequency);
uint32_t AX5043RXParamGetRXMaximumFrequencyOffset(uint8_t interfaceID);
void AX5043RXParamSetCorrectFrequencyOffsetLO(uint8_t interfaceID, uint8_t lo);
uint8_t AX5043RXParamGetCorrectFrequencyOffsetLO(uint8_t interfaceID);
void AX5043RXParamSetRXFSKMaxDeviation(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFSKMaxDeviation(uint8_t interfaceID);
void AX5043RXParamSetRXFSKMinDeviation(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFSKMinDeviation(uint8_t interfaceID);
void AX5043RXParamSetAFSKSpaceFrequency(uint8_t interfaceID, uint16_t spaceFreq);
uint16_t AX5043RXParamGetAFSKSpaceFrequency(uint8_t interfaceID);
void AX5043RXParamSetAFSKMarkFrequency(uint8_t interfaceID, uint16_t spaceFreq);
uint16_t AX5043RXParamGetAFSKMarkFrequency(uint8_t interfaceID);
void AX5043RXParamSetAFSKDetBandwitdh(uint8_t interfaceID, uint8_t detBandwidth);
uint8_t AX5043RXParamGetAFSKDetBandwitdh(uint8_t interfaceID);
void AX5043RXParamSetAmplitudeFilter(uint8_t interfaceID, uint8_t filter);
uint8_t AX5043RXParamGetAmplitudeFilter(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyLeak(uint8_t interfaceID, uint8_t leakiness);
uint8_t AX5043RXParamGetRXFrequencyLeak(uint8_t interfaceID);
void AX5043RXParamSetRXParameterNumber0(uint8_t interfaceID, uint8_t number);
uint8_t AX5043RXParamGetRXParameterNumber0(uint8_t interfaceID);
void AX5043RXParamSetRXParameterNumber1(uint8_t interfaceID, uint8_t number);
uint8_t AX5043RXParamGetRXParameterNumber1(uint8_t interfaceID);
void AX5043RXParamSetRXParameterNumber2(uint8_t interfaceID, uint8_t number);
uint8_t AX5043RXParamGetRXParameterNumber2(uint8_t interfaceID);
void AX5043RXParamSetRXParameterNumber3(uint8_t interfaceID, uint8_t number);
uint8_t AX5043RXParamGetRXParameterNumber3(uint8_t interfaceID);
uint8_t AX5043RXParamGetRXParameterCurrentIndex(uint8_t interfaceID);
uint8_t AX5043RXParamGetRXParameterCurrentNumber(uint8_t interfaceID);
uint8_t AX5043RXParamGetRXParameterCurrentIndexSpecial(uint8_t interfaceID);
void AX5043RXParamSetAGCAttackSpeed0(uint8_t interfaceID, uint8_t attackSpeed);
uint8_t AX5043RXParamGetAGCAttackSpeed0(uint8_t interfaceID);
void AX5043RXParamSetAGCReleaseSpeed0(uint8_t interfaceID, uint8_t releaseSpeed);
uint8_t AX5043RXParamGetAGCReleaseSpeed0(uint8_t interfaceID);
void AX5043RXParamSetAGCAttackSpeed1(uint8_t interfaceID, uint8_t attackSpeed);
uint8_t AX5043RXParamGetAGCAttackSpeed1(uint8_t interfaceID);
void AX5043RXParamSetAGCReleaseSpeed1(uint8_t interfaceID, uint8_t releaseSpeed);
uint8_t AX5043RXParamGetAGCReleaseSpeed1(uint8_t interfaceID);
void AX5043RXParamSetAGCAttackSpeed2(uint8_t interfaceID, uint8_t attackSpeed);
uint8_t AX5043RXParamGetAGCAttackSpeed2(uint8_t interfaceID);
void AX5043RXParamSetAGCReleaseSpeed2(uint8_t interfaceID, uint8_t releaseSpeed);
uint8_t AX5043RXParamGetAGCReleaseSpeed2(uint8_t interfaceID);
void AX5043RXParamSetAGCAttackSpeed3(uint8_t interfaceID, uint8_t attackSpeed);
uint8_t AX5043RXParamGetAGCAttackSpeed3(uint8_t interfaceID);
void AX5043RXParamSetAGCReleaseSpeed3(uint8_t interfaceID, uint8_t releaseSpeed);
uint8_t AX5043RXParamGetAGCReleaseSpeed3(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetAvgMagnitude0(uint8_t interfaceID, uint8_t target);
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude0(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetAvgMagnitude1(uint8_t interfaceID, uint8_t target);
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude1(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetAvgMagnitude2(uint8_t interfaceID, uint8_t target);
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude2(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetAvgMagnitude3(uint8_t interfaceID, uint8_t target);
uint8_t AX5043RXParamGetAGCTargetAvgMagnitude3(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetHysteresis0(uint8_t interfaceID, uint8_t hysteresis);
uint8_t AX5043RXParamGetAGCTargetHysteresis0(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetHysteresis1(uint8_t interfaceID, uint8_t hysteresis);
uint8_t AX5043RXParamGetAGCTargetHysteresis1(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetHysteresis2(uint8_t interfaceID, uint8_t hysteresis);
uint8_t AX5043RXParamGetAGCTargetHysteresis2(uint8_t interfaceID);
void AX5043RXParamSetAGCTargetHysteresis3(uint8_t interfaceID, uint8_t hysteresis);
uint8_t AX5043RXParamGetAGCTargetHysteresis3(uint8_t interfaceID);
void AX5043RXParamSetAGCMinimumReset0(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMinimumReset0(uint8_t interfaceID);
void AX5043RXParamSetAGCMaximumReset0(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMaximumReset0(uint8_t interfaceID);
void AX5043RXParamSetAGCMinimumReset1(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMinimumReset1(uint8_t interfaceID);
void AX5043RXParamSetAGCMaximumReset1(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMaximumReset1(uint8_t interfaceID);
void AX5043RXParamSetAGCMinimumReset2(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMinimumReset2(uint8_t interfaceID);
void AX5043RXParamSetAGCMaximumReset2(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMaximumReset2(uint8_t interfaceID);
void AX5043RXParamSetAGCMinimumReset3(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMinimumReset3(uint8_t interfaceID);
void AX5043RXParamSetAGCMaximumReset3(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043RXParamGetAGCMaximumReset3(uint8_t interfaceID);
void AX5043PacketSetGainTimingRecovery0(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainTimingRecovery0(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainTimingRecovery1(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainTimingRecovery1(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainTimingRecovery2(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainTimingRecovery2(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainTimingRecovery3(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainTimingRecovery3(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainDatarateRecovery0(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainDatarateRecovery0(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainDatarateRecovery1(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainDatarateRecovery1(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainDatarateRecovery2(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainDatarateRecovery2(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetGainDatarateRecovery3(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetGainDatarateRecovery3(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043RXParamSetRXPhaseGain0(uint8_t interfaceID, uint8_t phaseGain);
uint8_t AX5043RXParamGetRXPhaseGain0(uint8_t interfaceID);
void AX5043RXParamSetRXDecimationFilter0(uint8_t interfaceID, uint8_t filter);
uint8_t AX5043RXParamGetRXDecimationFilter0(uint8_t interfaceID);
void AX5043RXParamSetRXPhaseGain1(uint8_t interfaceID, uint8_t phaseGain);
uint8_t AX5043RXParamGetRXPhaseGain1(uint8_t interfaceID);
void AX5043RXParamSetRXDecimationFilter1(uint8_t interfaceID, uint8_t filter);
uint8_t AX5043RXParamGetRXDecimationFilter1(uint8_t interfaceID);
void AX5043RXParamSetRXPhaseGain2(uint8_t interfaceID, uint8_t phaseGain);
uint8_t AX5043RXParamGetRXPhaseGain2(uint8_t interfaceID);
void AX5043RXParamSetRXDecimationFilter2(uint8_t interfaceID, uint8_t filter);
uint8_t AX5043RXParamGetRXDecimationFilter2(uint8_t interfaceID);
void AX5043RXParamSetRXPhaseGain3(uint8_t interfaceID, uint8_t phaseGain);
uint8_t AX5043RXParamGetRXPhaseGain3(uint8_t interfaceID);
void AX5043RXParamSetRXDecimationFilter3(uint8_t interfaceID, uint8_t filter);
uint8_t AX5043RXParamGetRXDecimationFilter3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainA0(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainA0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetUpdate0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapHalf0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapFull0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetLimit0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainA1(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainA1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetUpdate1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapHalf1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapFull1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetLimit1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainA2(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainA2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetUpdate2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapHalf2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapFull2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetLimit2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainA3(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainA3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetUpdate3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetUpdate3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapHalf3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapHalf3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetWrapFull3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetWrapFull3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyOffsetLimit3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyOffsetLimit3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainB0(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainB0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyAverage2Bits0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyFreeze0(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXFrequencyFreeze0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainB1(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainB1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyAverage2Bits1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyFreeze1(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXFrequencyFreeze1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainB2(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainB2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyAverage2Bits2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyFreeze2(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXFrequencyFreeze2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainB3(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainB3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyAverage2Bits3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXFrequencyAverage2Bits3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyFreeze3(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXFrequencyFreeze3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainC0(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainC0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainC1(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainC1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainC2(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainC2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainC3(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainC3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainD0(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainD0(uint8_t interfaceID);
void AX5043RXParamSetRXRFFrequencyFreeze0(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXRFFrequencyFreeze0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainD1(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainD1(uint8_t interfaceID);
void AX5043RXParamSetRXRFFrequencyFreeze1(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXRFFrequencyFreeze1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainD2(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainD2(uint8_t interfaceID);
void AX5043RXParamSetRXRFFrequencyFreeze2(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXRFFrequencyFreeze2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyGainD3(uint8_t interfaceID, uint8_t freqGain);
uint8_t AX5043RXParamGetRXFrequencyGainD3(uint8_t interfaceID);
void AX5043RXParamSetRXRFFrequencyFreeze3(uint8_t interfaceID, uint8_t freeze);
uint8_t AX5043RXParamGetRXRFFrequencyFreeze3(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeGain0(uint8_t interfaceID, uint8_t ampGain);
uint8_t AX5043RXParamGetRXAmplitudeGain0(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeAGCJump0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXAmplitudeAGCJump0(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeRecoveryByAverage0(uint8_t interfaceID, uint8_t byAverage);
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage0(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeGain1(uint8_t interfaceID, uint8_t ampGain);
uint8_t AX5043RXParamGetRXAmplitudeGain1(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeAGCJump1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXAmplitudeAGCJump1(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeRecoveryByAverage1(uint8_t interfaceID, uint8_t byAverage);
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage1(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeGain2(uint8_t interfaceID, uint8_t ampGain);
uint8_t AX5043RXParamGetRXAmplitudeGain2(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeAGCJump2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXAmplitudeAGCJump2(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeRecoveryByAverage2(uint8_t interfaceID, uint8_t byAverage);
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage2(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeGain3(uint8_t interfaceID, uint8_t ampGain);
uint8_t AX5043RXParamGetRXAmplitudeGain3(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeAGCJump3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetRXAmplitudeAGCJump3(uint8_t interfaceID);
void AX5043RXParamSetRXAmplitudeRecoveryByAverage3(uint8_t interfaceID, uint8_t byAverage);
uint8_t AX5043RXParamGetRXAmplitudeRecoveryByAverage3(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyDeviation0(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFrequencyDeviation0(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyDeviation1(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFrequencyDeviation1(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyDeviation2(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFrequencyDeviation2(uint8_t interfaceID);
void AX5043RXParamSetRXFrequencyDeviation3(uint8_t interfaceID, uint16_t deviation);
uint16_t AX5043RXParamGetRXFrequencyDeviation3(uint8_t interfaceID);
void AX5043RXParamSetDeviationDecay0(uint8_t interfaceID, uint8_t decay);
uint8_t AX5043RXParamGetDeviationDecay0(uint8_t interfaceID);
void AX5043RXParamEnableDeviationUpdate0(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled0(uint8_t interfaceID);
void AX5043RXParamSetDeviationDecay1(uint8_t interfaceID, uint8_t decay);
uint8_t AX5043RXParamGetDeviationDecay1(uint8_t interfaceID);
void AX5043RXParamEnableDeviationUpdate1(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled1(uint8_t interfaceID);
void AX5043RXParamSetDeviationDecay2(uint8_t interfaceID, uint8_t decay);
uint8_t AX5043RXParamGetDeviationDecay2(uint8_t interfaceID);
void AX5043RXParamEnableDeviationUpdate2(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled2(uint8_t interfaceID);
void AX5043RXParamSetDeviationDecay3(uint8_t interfaceID, uint8_t decay);
uint8_t AX5043RXParamGetDeviationDecay3(uint8_t interfaceID);
void AX5043RXParamEnableDeviationUpdate3(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043RXParamGetIfDeviationUpdateIsEnabled3(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes0(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes0(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes1(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes1(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes2(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes2(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes2(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes2(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockAOffsetCompRes3(uint8_t interfaceID);
void AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(uint8_t interfaceID, uint8_t resistor);
uint8_t AX5043RXParamGetBasebandGainBlockBOffsetCompRes3(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_RXPARAM_H_ */
