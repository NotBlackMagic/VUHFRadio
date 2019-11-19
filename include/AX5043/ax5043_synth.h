#ifndef AX5043_AX5043_SYNTHESIZER_H_
#define AX5043_AX5043_SYNTHESIZER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of PLLLOOP Register
#define PLLLOOP_FLT_MASK					0x03	//FLT Bit Values Mask (for PLLLoopFilter)
#define PLLLOOP_FILTEN_MASK					0x04	//Enable External Filter Pin
#define PLLLOOP_DIRECT_MASK					0x08	//Bypass External Filter Pin
#define PLLLOOP_FRQSEL_MASK					0x80	//Frequency Register Selection; 0 = use FREQA, 1 = use FREQB
//PLLLOOP Filter Bits
typedef enum {
	PLLLoop_ExtLoopFilter = 0,		//External Loop Filter
	PLLLoop_Filter100kHz = 1,		//Internal Loop Filter, BW = 100 kHz for ICP = 68 uA
	PLLLoop_Filter200kHz = 2,		//Internal Loop Filter x2, BW = 200 kHz for ICP = 272 mA
	PLLLoop_Filter500kHz = 3		//Internal Loop Filter x5, BW = 500 kHz for ICP = 1.7 mA
} PLLLoopFilter;

//Register Configuration of PLLLOOPBOOST Register
#define PLLLOOPBOOST_FLT_MASK					0x03	//FLTBOOST Bit Values Mask (for PLLLoopBoostFilter)
#define PLLLOOPBOOST_FILTEN_MASK				0x04	//Enable External Filter Pin
#define PLLLOOPBOOST_DIRECT_MASK				0x08	//Bypass External Filter Pin
#define PLLLOOPBOOST_FRQSEL_MASK				0x80	//Frequency Register Selection; 0 = use FREQA, 1 = use FREQB
//PLLLOOPBOOST Bits
typedef enum {
	PLLLoopBoost_ExtLoopFilter = 0,	//External Loop Filter
	PLLLoopBoost_Filter100kHz = 1,	//Internal Loop Filter, BW = 100 kHz for ICP = 68 uA
	PLLLoopBoost_Filter200kHz = 2,	//Internal Loop Filter x2, BW = 200 kHz for ICP = 272 mA
	PLLLoopBoost_Filter500kHz = 3	//Internal Loop Filter x5, BW = 500 kHz for ICP = 1.7 mA
} PLLLoopBoostFilter;

//Register Configuration of PLLCPI Register
#define PLLCPI_MASK							0xFF	//Charge pump current in multiples of 8.5uA

//Register Configuration of PLLCPIBOOST Register
#define PLLCPIBOOST_MASK					0xFF	//Charge pump current in multiples of 8.5uA

//Register Configuration of PLLVCODIV Register
#define PLLVCODIV_REFDIV_MASK				0x03	//REFDIV Bit Value Mask (for PLLCodivRefrenceDivider)
#define PLLVCODIV_RFDIV_MASK				0x04	//RF divider: 0 = no RF divider, 1 = divide RF by 2
#define PLLVCODIV_VCOSEL					0x10	//0 = fully internal VCO1, 1 = internal VCO2 with external inductor or external VCO, depending on VCO2INT
#define PLLVCODIV_VCO2INT					0x20	//1 = internal VCO2 with external Inductor, 0 = external VCO
//PLLVCODIV Reference divider Bits
typedef enum {
	PllCodiv_fXtal_div1 = 0,		//fPD = fXTAL
	PllCodiv_fXtal_div2 = 1,		//fPD = fXTAL/2
	PllCodiv_fXtal_div4 = 2,		//fPD = fXTAL/4
	PllCodiv_fXtal_div8 = 3			//fPD = fXTAL/8
} PLLCodivRefrenceDivider;

//Register Configuration of PLLRANGINGA Register
#define PLLRANGINGA_VCORA_MASK				0x0F	//VCO Range; depending on bit FREQSEL of PLLLOOP, VCORA is used
#define PLLRANGINGA_RNGSTART_MASK			0x10	//PLL Autoranging; Write 1 to start autoranging, bit clears when autoranging done. Autoranging always applies to the VCOR selected by FREQSEL of PLLLOOP.
#define PLLRANGINGA_RNGERR_MASK				0x20	//Ranging Error; Set when RNG START transitions from 1 to 0 and the programmed frequency cannot be achieved
#define PLLRANGINGA_PLLLOCK_MASK			0x40	//PLL is locked if 1
#define PLLRANGINGA_STICKYLOCK				0x80	//If 0, PLL lost lock after last read of PLLRANGINGA register

//Register Configuration of PLLRANGINGB Register
#define PLLRANGINGB_VCORB_MASK				0x0F	//VCO Range; depending on bit FREQSEL of PLLLOOP, VCORB is used
#define PLLRANGINGB_RNGSTART_MASK			0x10	//PLL Autoranging; Write 1 to start autoranging, bit clears when autoranging done. Autoranging always applies to the VCOR selected by FREQSEL of PLLLOOP.
#define PLLRANGINGB_RNGERR_MASK				0x20	//Ranging Error; Set when RNG START transitions from 1 to 0 and the programmed frequency cannot be achieved
#define PLLRANGINGB_PLLLOCK_MASK			0x40	//PLL is locked if 1
#define PLLRANGINGB_STICKYLOCK				0x80	//If 0, PLL lost lock after last read of PLLRANGINGB register

//Register Configuration of FREQA Register
#define FREQA0_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQA1_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQA2_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQA3_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)

//Register Configuration of FREQB Register
#define FREQB0_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQB1_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQB2_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)
#define FREQB3_MASK							0xFF	//Frequency = (fCarrier/FXtal * 2^24 + 1/2)

void AX5043SynthSetPLLLoopEnableExtFilter(uint8_t interfaceID, uint8_t enableExtFilter);
uint8_t AX5043SynthGetPLLLoopEnableExtFilter(uint8_t interfaceID);
void AX5043SynthSetPLLLoopBoostEnableExtFilter(uint8_t interfaceID, uint8_t enableExtFilter);
uint8_t AX5043SynthGetPLLLoopBoostEnableExtFilter(uint8_t interfaceID);
void AX5043SynthSetPLLLoopBypassExtFilter(uint8_t interfaceID, uint8_t bypassExtFilter);
uint8_t AX5043SynthGetPLLLoopBypassExtFilter(uint8_t interfaceID);
void AX5043SynthSetPLLLoopBoostBypassExtFilter(uint8_t interfaceID, uint8_t bypassExtFilter);
uint8_t AX5043SynthGetPLLLoopBoostBypassExtFilter(uint8_t interfaceID);
void AX5043SynthSetPLLLoopSelectFrequency(uint8_t interfaceID, uint8_t freqSelection);
uint8_t AX5043SynthGetPLLLoopSelectFrequency(uint8_t interfaceID);
void AX5043SynthSetPLLLoopBoostSelectFrequency(uint8_t interfaceID, uint8_t freqSelection);
uint8_t AX5043SynthGetPLLLoopBoostSelectFrequency(uint8_t interfaceID);
void AX5043SynthSetPLLLoopFilter(uint8_t interfaceID, PLLLoopFilter pllLoopFilter);
PLLLoopFilter AX5043SynthGetPLLLoopFilter(uint8_t interfaceID);
void AX5043SynthSetPLLLoopBoostFilter(uint8_t interfaceID, PLLLoopBoostFilter pllLoopFilter);
PLLLoopBoostFilter AX5043SynthGetPLLLoopBoostFilter(uint8_t interfaceID);
void AX5043SynthSetPLLChargePumpCurrent(uint8_t interfaceID, uint8_t current);
uint8_t AX5043SynthGetPLLChargePumpCurrent(uint8_t interfaceID);
void AX5043SynthSetPLLBoostChargePumpCurrent(uint8_t interfaceID, uint8_t current);
uint8_t AX5043SynthGetPLLBoostChargePumpCurrent(uint8_t interfaceID);
void AX5043SynthSetPLLVCOEnableRefDivider(uint8_t interfaceID, uint8_t enableRefDivider);
uint8_t AX5043SynthGetPLLVCOEnableRefDivider(uint8_t interfaceID);
void AX5043SynthSetPLLVCOSelection(uint8_t interfaceID, uint8_t selectVCO);
uint8_t AX5043SynthGetPLLVCOSelection(uint8_t interfaceID);
void AX5043SynthSetPLLVCO2Internal(uint8_t interfaceID, uint8_t internalVCO2);
uint8_t AX5043SynthGetPLLVCO2Internal(uint8_t interfaceID);
void AX5043SynthSetPLLRefDivider(uint8_t interfaceID, PLLCodivRefrenceDivider pllRefDivider);
PLLCodivRefrenceDivider AX5043SynthGetPLLRefDivider(uint8_t interfaceID);
void AX5043SynthSetVCORangeA(uint8_t interfaceID, uint8_t vcoRange);
uint8_t AX5043SynthGetVCORangeA(uint8_t interfaceID);
void AX5043SynthSetVCORangeB(uint8_t interfaceID, uint8_t vcoRange);
uint8_t AX5043SynthGetVCORangeB(uint8_t interfaceID);
void AX5043SynthStartAutoRangingA(uint8_t interfaceID);
uint8_t AX5043SynthGetAutoRangingA(uint8_t interfaceID);
void AX5043SynthStartAutoRangingB(uint8_t interfaceID);
uint8_t AX5043SynthGetAutoRangingB(uint8_t interfaceID);
uint8_t AX5043SynthGetAutoRangingErrorA(uint8_t interfaceID);
uint8_t AX5043SynthGetAutoRangingErrorB(uint8_t interfaceID);
uint8_t AX5043SynthGetPLLLockA(uint8_t interfaceID);
uint8_t AX5043SynthGetPLLLockB(uint8_t interfaceID);
uint8_t AX5043SynthGetPLLLockStickyA(uint8_t interfaceID);
uint8_t AX5043SynthGetPLLLockStickyB(uint8_t interfaceID);
void AX5043SynthSetFrequencyA(uint8_t interfaceID, uint32_t frequency);
uint32_t AX5043SynthGetFrequencyA(uint8_t interfaceID);
void AX5043SynthSetFrequencyB(uint8_t interfaceID, uint32_t frequency);
uint32_t AX5043SynthGetFrequencyB(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_SYNTHESIZER_H_ */
