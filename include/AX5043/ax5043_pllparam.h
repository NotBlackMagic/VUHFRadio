#ifndef AX5043_AX5043_PLLPARAM_H_
#define AX5043_AX5043_PLLPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of PLLVCOI Register
#define VCOI_MASK							0x3F	//This field sets the bias current for both VCOs. The increment is 50 uA for VCO1 and 10 uA for VCO2
#define VCOIE_MASK							0x80	//Enable manual VCOI

//Register Configuration of PLLVCOIR Register
#define VCOIR_MASK							0x3F	//This field reflects the actual VCO current selected

//Register Configuration of PLLLOCKDET Register
#define LOCKDETDLY_MASK						0x03	//LOCKDETDLY Bit Values Mask (for LockDetectorDelay)
#define LOCKDETDLYM_MASK					0x04	//0 -> Automatic Lock Delay, 1 -> Manual Lock Delay
#define LOCKDETDLYR_MASK					0xC0	//Lock Detect Read Back (not valid in power down mode)
//LOCKDETDLY Bits
typedef enum {
	LockDetectDelay_6ns = 0,		//Lock Detector Delay 6ns
	LockDetectDelay_9ns = 1,		//Lock Detector Delay 9ns
	LockDetectDelay_12ns = 2,		//Lock Detector Delay 12ns
	LockDetectDelay_14ns = 3		//Lock Detector Delay 14ns
} LockDetectorDelay;

//Register Configuration of PLLRNGCLK Register
#define PLLRNGCLK_MASK						0x07	//PLLRNGCLK Bit Values Mask (for PLLRangingClock)
//PLLRNGCLK Bits
typedef enum {
	PLLRangingClock_8 = 0,			//PLL Ranging Clock. fpllrng = fxtal / 2^8
	PLLRangingClock_9 = 1,			//PLL Ranging Clock. fpllrng = fxtal / 2^9
	PLLRangingClock_10 = 2,			//PLL Ranging Clock. fpllrng = fxtal / 2^10
	PLLRangingClock_11 = 3,			//PLL Ranging Clock. fpllrng = fxtal / 2^11
	PLLRangingClock_12 = 4,			//PLL Ranging Clock. fpllrng = fxtal / 2^12
	PLLRangingClock_13 = 5,			//PLL Ranging Clock. fpllrng = fxtal / 2^13
	PLLRangingClock_14 = 6,			//PLL Ranging Clock. fpllrng = fxtal / 2^14
	PLLRangingClock_15 = 7			//PLL Ranging Clock. fpllrng = fxtal / 2^15
} PLLRangingClock;

void AX5043PLLParamSetVCOBias(uint8_t interfaceID, uint8_t biasCurrent);
uint8_t AX5043PLLParamGetVCOBias(uint8_t interfaceID);
void AX5043PLLParamEnableManualVCOI(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PLLParamIsManualVCOIEnabled(uint8_t interfaceID);
uint8_t AX5043PLLParamGetActualVCOBias(uint8_t interfaceID);
void AX5043PLLParamSetLockDetectDelay(uint8_t interfaceID, LockDetectorDelay delay);
LockDetectorDelay AX5043PLLParamGetLockDetectDelay(uint8_t interfaceID);
void AX5043PLLParamEnableManualLockDelay(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PLLParamIsManualLockDelayEnabled(uint8_t interfaceID);
LockDetectorDelay AX5043PLLParamGetActualLockDetectDelay(uint8_t interfaceID);
void AX5043PLLParamSetPLLRangingClock(uint8_t interfaceID, PLLRangingClock clock);
PLLRangingClock AX5043PLLParamGetPLLRangingClock(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_PLLPARAM_H_ */
