#ifndef AX5043_AX5043_RXTRACKING_H_
#define AX5043_AX5043_RXTRACKING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of TRKDATARATE Register
#define TRKDATARATE0_MASK					0xFF
#define TRKDATARATE1_MASK					0xFF
#define TRKDATARATE2_MASK					0xFF

//Register Configuration of TRKAMPL Register
#define TRKAMPL0_MASK						0xFF
#define TRKAMPL1_MASK						0xFF

//Register Configuration of TRKPHASE Register
#define TRKPHASE0_MASK						0xFF
#define TRKPHASE1_MASK						0x0F

//Register Configuration of TRKRFFREQ Register
#define TRKRFFREQ0_MASK						0xFF
#define TRKRFFREQ1_MASK						0xFF
#define TRKRFFREQ2_MASK						0x0F

//Register Configuration of TRKFREQ Register
#define TRKFREQ0_MASK						0xFF
#define TRKFREQ1_MASK						0xFF

//Register Configuration of TRKFSKDEMOD Register
#define TRKFSKDEMOD0_MASK					0xFF
#define TRKFSKDEMOD1_MASK					0x3F

//Register Configuration of TRKAFSKDEMOD Register
#define TRKAFSKDEMOD0_MASK					0xFF
#define TRKAFSKDEMOD1_MASK					0xFF

//Register Resets Bits, writes to TRKAMPL0, TRKAMPL1, TRKPHASE0, TRKPHASE1, TRKPHASE0, TRKPHASE1 or TRKPHASE2
#define DTRKRESET_BIT						0x08	//Writing 1 clears the Datarate Tracking Register
#define ATRKRESET_BIT						0x10	//Writing 1 clears the Amplitude Tracking Register
#define PTRKRESET_BIT						0x10	//Writing 1 clears the Phase Tracking Register
#define RTRKRESET_BIT						0x10	//Writing 1 clears the RF Frequency Tracking Register
#define FTRKRESET_BIT						0x10	//Writing 1 clears the Frequency Tracking Register

uint32_t AX5043RXTrackingDatarate(uint8_t interfaceID);
uint16_t AX5043RXTrackingAmplitude(uint8_t interfaceID);
uint16_t AX5043RXTrackingPhase(uint8_t interfaceID);
void AX5043RXTrackingSetRFFrequency(uint8_t interfaceID, uint32_t trackRFFreq);
int32_t AX5043RXTrackingGetRFFrequency(uint8_t interfaceID);
void AX5043RXTrackingSetFrequency(uint8_t interfaceID, uint32_t trackFreq);
int16_t AX5043RXTrackingGetFrequency(uint8_t interfaceID);
uint16_t AX5043RXTrackingFSKDemodulation(uint8_t interfaceID);
//uint16_t AX5043RXTrackingAFSKDemodulation(uint8_t interfaceID);
void AX5043RXTrackingResetDatarate(uint8_t interfaceID);
void AX5043RXTrackingResetAmplitude(uint8_t interfaceID);
void AX5043RXTrackingResetPhase(uint8_t interfaceID);
void AX5043RXTrackingResetRFFrequency(uint8_t interfaceID);
void AX5043RXTrackingResetFrequency(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_RXTRACKING_H_ */
