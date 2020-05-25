#ifndef AX5043_AX5043_GPIO_H_
#define AX5043_AX5043_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

typedef union {
	struct {
		uint8_t sysClk : 1;
		uint8_t dClk : 1;
		uint8_t data : 1;
		uint8_t irq : 1;
		uint8_t antSel : 1;
		uint8_t pwRamp : 1;
		uint8_t none : 2;
	};
	uint8_t raw;
} AX5043PinState;

//Pin Configuration/Function of SysClk Pin
#define PFSYSCLK_MASK						0x7F	//PFSYSCLK Bit Values Mask (for PinFunctionsSysClk)
#define PUSYSCLK_MASK						0x80	//SYSCLK weak Pullup enable Mask
//PFSYSCLK Bits
typedef enum {
	SysClk_Low = 0,				//SYSCLK Output ‘0’
	SysClk_High = 1,			//SYSCLK Output ‘1’
	SysClk_HighZ = 2,			//SYSCLK Output ‘Z’
	SysClk_Inv_fXtal = 3,		//SYSCLK Output inverted fXTAL
	SysClk_fXtal_div1 = 4,		//SYSCLK Output fXTAL
	SysClk_fXtal_div2 = 5,		//SYSCLK Output fXTAL/2
	SysClk_fXtal_div4 = 6,		//SYSCLK Output fXTAL/4
	SysClk_fXtal_div8 = 7,		//SYSCLK Output fXTAL/8
	SysClk_fXtal_div16 = 8,		//SYSCLK Output fXTAL/16
	SysClk_fXtal_div32 = 9,		//SYSCLK Output fXTAL/32
	SysClk_fXtal_div64 = 10,	//SYSCLK Output fXTAL/64
	SysClk_fXtal_div128 = 11,	//SYSCLK Output fXTAL/128
	SysClk_fXtal_div256 = 12,	//SYSCLK Output fXTAL/256
	SysClk_fXtal_div512 = 13,	//SYSCLK Output fXTAL/512
	SysClk_fXtal_div1024 = 14,	//SYSCLK Output fXTAL/1024
	SysClk_LP_Osci = 15,		//SYSCLK Output Low Power (LP) Oscillator
	SysClk_Test_Ops = 31		//SYSCLK Output Test Observation
} PinFunctionsSysClk;

//Pin Configuration/Function of DCLK Pin
#define PFDCLK_MASK						0x07		//PINFUNCDCLK Bit Values Mask (for PinFunctionsDCLK)
#define PIDCLK_MASK						0x40		//DCLK inversion Mask
#define PUDCLK_MASK						0x80		//DCLK weak Pullup enable Mask
//PFDCLK Bits
typedef enum {
	DCLK_Low = 0,						//DCLK Output ‘0’
	DCLK_High = 1,						//DCLK Output ‘1’
	DCLK_HighZ = 2,						//DCLK Output ‘Z’
	DCLK_Modem_Data_Clk_Input = 3,		//DCLK Output Modem Data Clock Input; use when inputting/outputting framing data on DATA
	DCLK_Modem_Data_Clk_Output = 4,		//DCLK Output Modem Data Clock Output; use when observing modem data on DATA
	DCLK_Modem_Data_Clk_Output_2 = 5,	//DCLK Output Modem Data Clock Output; use when inputting/outputting framing data on DATA, and you do not want to generate a clock yourself
	DCLK_Test_Obs = 7					//DCLK Output Test Observation
} PinFunctionsDCLK;

//Pin Configuration/Function of DATA Pin
#define PFDATA_MASK						0x0F		//PINFUNCDATA Bit Values Mask (for PinFunctionsDATA)
#define PIDATA_MASK						0x40		//DATA inversion Mask
#define PUDATA_MASK						0x80		//DATA weak Pullup enable Mask
//PFDATA Bits
typedef enum {
	DATA_Low = 0,					//DATA Output ‘0’
	DATA_High = 1,					//DATA Output ‘1’
	DATA_HighZ = 2,					//DATA Output ‘Z’
	DATA_IO_Framing_Data = 3,		//DATA Input/Output Framing Data
	DATA_IO_Modem_Data = 4,			//DATA Input/Output Modem Data
	DATA_IO_Async_Modem_Data = 5,	//DATA Input/Output Async Modem Data
	DATA_Modem_Data_Output = 7,		//DATA Output Modem Data
	DATA_Test_Obs = 15				//DATA Output Test Observation
} PinFunctionsDATA;

//Pin Configuration/Function of IRQ Pin
#define PFIRQ_MASK						0x07		//PINFUNCIRQ Bit Values Mask (for PinFunctionsIRQ)
#define PIIRQ_MASK						0x40		//IRQ inversion Mask
#define PUIRQ_MASK						0x80		//IRQ weak Pullup enable Mask
//PFIRQ Bits
typedef enum {
	IRQ_Low = 0,					//IRQ Output ‘0’
	IRQ_High = 1,					//IRQ Output ‘1’
	IRQ_HighZ = 2,					//IRQ Output ‘Z’
	IRQ_Int_Req = 3,				//IRQ Output Interrupt Request
	IRQ_Test_Obs = 7				//IRQ Output Test Observation
} PinFunctionsIRQ;

//Pin Configuration/Function of AntSel Pin
#define PFANTSEL_MASK						0x07	//PINFUNCANTSEL Bit Values Mask (for PinFunctionsAntSel)
#define PIANTSEL_MASK						0x40	//ANTSEL inversion Mask
#define PUANTSEL_MASK						0x80	//ANTSEL weak Pullup enable Mask
//PFIRQ Bits
typedef enum {
	AntSel_Low = 0,					//ANTSEL Output ‘0’
	AntSel_High = 1,				//ANTSEL Output ‘1’
	AntSel_HighZ = 2,				//ANTSEL Output ‘Z’
	AntSel_Baseband_Tune_Clk = 3,	//ANTSEL Output Baseband Tune Clock
	AntSel_Ext_TCXO_Enable = 4,		//ANTSEL Output External TCXO Enable
	AntSel_DAC_Output = 5,			//ANTSEL Output DAC
	AntSel_Ant_Div_Sel = 6,			//ANTSEL Output Diversity Antenna Select
	AntSel_Test_Obs = 7				//ANTSEL Output Test Observation
} PinFunctionsAntSel;

//Pin Configuration/Function of PwrRamp Pin
#define PFPWRAMP_MASK						0x0F	//PINFUNCPWRAMP Bit Values Mask (for PinFunctionsPwrRamp)
#define PIPWRAMP_MASK						0x40	//PWRAMP inversion Mask
#define PUPWRAMP_MASK						0x80	//PWRAMP weak Pullup enable Mask
//PFIRQ Bits
typedef enum {
	PwrRamp_Low = 0,					//PWRAMP Output ‘0’
	PwrRamp_High = 1,					//PWRAMP Output ‘1’
	PwrRamp_HighZ = 2,					//PWRAMP Output ‘Z’
	PwrRamp_DiBit_Sync_Input = 3,		//PWRAMP Input DiBit Synchronization (4-FSK); use when inputting/outputting 4-FSK framing data on DATA
	PwrRamp_DiBit_Sync_Output = 4,		//PWRAMP Output DiBit Synchronization (4-FSK); use when observing 4-FSK modem data on DATA
	PwrRamp_DAC_Output = 5,				//PWRAMP Output DAC
	PwrRamp_PA_Control = 6,				//PWRAMP Output Power Amplifier Control
	PwrRamp_Ext_TCXO_Enable = 7,		//PWRAMP Output External TCXO Enable
	PwrRamp_Test_Obs = 15				//PWRAMP Output Test Observation
} PinFunctionsPwrRamp;

//Register Configuration of GPADCCTRL Register
#define CHISL_MASK							0x01	//Isolate Channels by sampling common mode between channels
#define CONT_MASK							0x02	//Enable Continuous Sampling (period according to GPADCPERIOD)
#define GPADC13_MASK						0x04	//Enable Sampling GPADC1-GPADC3
#define BUSY_MASK							0x80	//Conversion ongoing when 1; when writing 1, a single conversion is started

//Register Configuration of GPADCPERIOD Register
#define GPADCPERIOD_MASK					0xFF	//GPADC Sampling Period, fsr = fxtal / (32 * GPADCPERIOD)

//Register Configuration of GPADC13VALUE Register
#define GPADC13VALUE0_MASK					0xFF	//GPADC13 Value
#define GPADC13VALUE1_MASK					0x03	//GPADC13 Value

//Register Configuration of DACVALUE0 & DACVALUE1 Register
#define DACVALUE0_MASK						0xFF	//DAC Value (signed) (if DACINPUT = 0000)
#define DACVALUE1_MASK						0x0F	//DAC Value (signed) (if DACINPUT = 0000)
#define DACSHIFT_MASK						0x0F	//DAC Input Shift (if DACINPUT ! = 0000)

//Register Configuration of DACCONFIG Register
#define DACINPUT_MASK						0x0F	//DAC Input Multiplexer Mask (for )
#define DACCLKX2_MASK						0x40	//Enable DAC Clock Doubler if set to 1
#define DACPWM_MASK							0x80	//Select PWM mode if 1, otherwise SumDelta mode
//DACINPUT Bits
typedef enum {
	DACInput_ValueR = 0,
	DACInput_TRKAmplitude = 1,
	DACInput_TRKRFFrequency = 2,
	DACInput_TRFrequency = 3,
	DACInput_FSKDemodulator = 4,
	DACInput_AFSKDemodulator = 5,
	DACInput_RXSoftData = 6,
	DACInput_RSSI = 7,
	DACInput_SampleRotI = 8,
	DACInput_SampleRotQ = 9,
	DACInput_GPADC13 = 12
} DACInputSelection;

AX5043PinState AX5043GPIOPinState(uint8_t interfaceID);
void AX5043GPIOCnfgSysClk(uint8_t interfaceID, PinFunctionsSysClk pinFunction, uint8_t pullup);
void AX5043GPIOCnfgDCLK(uint8_t interfaceID, PinFunctionsDCLK pinFunction, uint8_t inversion, uint8_t pullup);
void AX5043GPIOCnfgDATA(uint8_t interfaceID, PinFunctionsDATA pinFunction, uint8_t inversion, uint8_t pullup);
void AX5043GPIOCnfgIRQ(uint8_t interfaceID, PinFunctionsIRQ pinFunction, uint8_t inversion, uint8_t pullup);
void AX5043GPIOCnfgAntSel(uint8_t interfaceID, PinFunctionsAntSel pinFunction, uint8_t inversion, uint8_t pullup);
void AX5043GPIOCnfgPwrRamp(uint8_t interfaceID, PinFunctionsPwrRamp pinFunction, uint8_t inversion, uint8_t pullup);
void AX5043GPIOSetEnableADCIsolateChannel(uint8_t interfaceID, uint8_t isolateChannel);
uint8_t AX5043GPIOGetADCIsolateChannel(uint8_t interfaceID);
void AX5043GPIOSetEnableADCContinuousSampling(uint8_t interfaceID, uint8_t contSampling);
uint8_t AX5043GPIOGetADCContinuousSampling(uint8_t interfaceID);
void AX5043GPIOSetEnableSamplingADCGPADC13(uint8_t interfaceID, uint8_t enSampling);
uint8_t AX5043GPIOGetSamplingADCGPADC13(uint8_t interfaceID);
void AX5043GPIOADCTriggerConversion(uint8_t interfaceID);
uint8_t AX5043GPIOGetADCBusy(uint8_t interfaceID);
void AX5043GPIOSetADCtSamplingPeriod(uint8_t interfaceID, uint8_t period);
uint8_t AX5043GPIOGetADCSamplingPeriod(uint8_t interfaceID);
uint16_t AX5043GPIOGetADCGPADC13Value(uint8_t interfaceID);
void AX5043GPIOSetDACValue(uint8_t interfaceID, uint16_t value);
uint16_t AX5043GPIOGetDACValue(uint8_t interfaceID);
void AX5043GPIOSetDACInputShift(uint8_t interfaceID, uint16_t shift);
uint8_t AX5043GPIOGetDACInputShift(uint8_t interfaceID);
void AX5043GPIOSetDACInput(uint8_t interfaceID, DACInputSelection input);
DACInputSelection AX5043GPIOGetDACInput(uint8_t interfaceID);
void AX5043GPIOSetDACClockDoubling(uint8_t interfaceID, uint8_t doubling);
uint8_t AX5043GPIOGetDACClockDoubling(uint8_t interfaceID);
void AX5043GPIOSetDACOutputMode(uint8_t interfaceID, uint8_t mode);
uint8_t AX5043GPIOGetDACOutputMode(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_GPIO_H_ */
