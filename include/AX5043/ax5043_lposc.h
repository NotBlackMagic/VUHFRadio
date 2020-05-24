#ifndef AX5043_AX5032_LPOSC_H_
#define AX5043_AX5032_LPOSC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of LPOSCCONFIG Register
#define LPOSC_ENA_MASK						0x01	//Enable the Low Power Oscillator. If 0, it is disabled
#define LPOSC_FAST_MASK						0x02	//Select the Frequency of the Low Power Oscillator. 0 = 640 Hz, 1 = 10.24 kHz
#define LPOSC_IRQR_MASK						0x04	//Enable LP Oscillator Interrupt on the Rising Edge
#define LPOSC_IRQF_MASK						0x08	//Enable LP Oscillator Interrupt on the Falling Edge
#define LPOSC_CALIBF_MASK					0x10	//Enable LP Oscillator Calibration on the Falling Edge
#define LPOSC_CALIBR_MASK					0x20	//Enable LP Oscillator Calibration on the Rising Edge
#define LPOSC_OSC_DOUBLE_MASK				0x40	//Enable LP Oscillator Calibration Reference Oscillator Doubling
#define LPOSC_OSC_INV_MASK					0x80	//Invert LP Oscillator Clock

//Register Configuration of LPOSCSTATUS Register
#define LPOSCSTATUS_MASK					0x03
//LPOSCSTATUS Bits
typedef union {
	struct {
		uint8_t lposcedge : 1;		//Enabled Low Power Oscillator Edge detected
		uint8_t lposcirq : 1;		//Low Power Oscillator Interrupt Active
		uint8_t lposcnone : 6;
	};
	uint8_t raw;
} LPOscStatus;

//Register Configuration of LPOSCKFILT Register
#define LPOSCKFILT0_MASK					0xFF	//kFILT (Low Power Oscillator Calibration Filter Constant), kfilt = (21333 * 2^20) / fxtal
#define LPOSCKFILT1_MASK					0xFF	//kFILT (Low Power Oscillator Calibration Filter Constant), kfilt = (21333 * 2^20) / fxtal

//Register Configuration of LPOSCREF Register
#define LPOSCREF0_MASK						0xFF	//LP Oscillator Reference Frequency Divider; set to: fxtal / 640
#define LPOSCREF1_MASK						0xFF	//LP Oscillator Reference Frequency Divider; set to: fxtal / 640

//Register Configuration of LPOSCFREQ Register
#define LPOSCFREQ0_MASK						0xF0	//LP Oscillator Frequency Tune Value; in 1/32 %
#define LPOSCFREQ1_MASK						0xFF	//LP Oscillator Frequency Tune Value; in 1/32 %

//Register Configuration of LPOSCPER Register
#define LPOSCPER0_MASK						0xFF	//Last measured LP Oscillator Period
#define LPOSCPER1_MASK						0xFF	//Last measured LP Oscillator Period

void AX5043LPOSCEnable(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabled(uint8_t interfaceID);
void AX5043LPOSCSetFrequncy(uint8_t interfaceID, uint8_t fast);
uint8_t AX5043LPOSCGetFrequncy(uint8_t interfaceID);
void AX5043LPOSCEnableInterrruptRising(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabledInterruptRising(uint8_t interfaceID);
void AX5043LPOSCEnableInterrruptFalling(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabledInterruptFalling(uint8_t interfaceID);
void AX5043LPOSCEnableCalibrationFalling(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabledCalibrationFalling(uint8_t interfaceID);
void AX5043LPOSCEnableCalibrationRising(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabledCalibrationRising(uint8_t interfaceID);
void AX5043LPOSCEnableFrequencyDoubling(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043LPOSCIsEnabledFrequencyDoubling(uint8_t interfaceID);
void AX5043LPOSCInvertClock(uint8_t interfaceID, uint8_t invert);
uint8_t AX5043LPOSCIsInvertClock(uint8_t interfaceID);
LPOscStatus AX5043LPOSCStatus(uint8_t interfaceID);
void AX5043LPOSCSetFilter(uint8_t interfaceID, uint16_t kFilter);
uint16_t AX5043LPOSCGetFilter(uint8_t interfaceID);
void AX5043LPOSCSetFrequencyDivider(uint8_t interfaceID, uint16_t freqDivider);
uint16_t AX5043LPOSCGetFrequencyDivider(uint8_t interfaceID);
void AX5043LPOSCSetFrequencyTune(uint8_t interfaceID, uint16_t tune);
uint16_t AX5043LPOSCGetFrequencyTune(uint8_t interfaceID);
uint16_t AX5043LPOSCGetPeriod(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5032_LPOSC_H_ */
