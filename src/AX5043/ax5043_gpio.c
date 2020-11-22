#include "ax5043_gpio.h"

/**
  * @brief	This function returns the GPIO Pin state of the AX5043 (if High or Low)
  * @param	interfaceID: Which interface (chip) used
  * @return	AX5043PinState: Status of each GPIO of the AX5043
  */
AX5043PinState AX5043GPIOPinState(uint8_t interfaceID) {
	AX5043PinState state;
	AX5043ReadShortAddress(interfaceID, PINSTATE, &state.raw, 1);
	return state;
}

/**
  * @brief	This function configures the SysClk GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgSysClk(uint8_t interfaceID, PinFunctionsSysClk pinFunction, uint8_t pullup) {
	uint8_t config = (pinFunction & PFSYSCLK_MASK) | (pullup << 7);
	AX5043WriteShortAddress(interfaceID, PINFUNCSYSCLK, &config, 1);
}

/**
  * @brief	This function configures the DCLK GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	inversion: Enables logic output inversion
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgDCLK(uint8_t interfaceID, PinFunctionsDCLK pinFunction, uint8_t inversion, uint8_t pullup) {
	uint8_t config = (pinFunction & PFDCLK_MASK) | (pullup << 7) | (inversion << 6);
	AX5043WriteShortAddress(interfaceID, PINFUNCDCLK, &config, 1);
}

/**
  * @brief	This function configures the DATA GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	inversion: Enables logic output inversion
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgDATA(uint8_t interfaceID, PinFunctionsDATA pinFunction, uint8_t inversion, uint8_t pullup) {
	uint8_t config = (pinFunction & PFDATA_MASK) | (pullup << 7) | (inversion << 6);
	AX5043WriteShortAddress(interfaceID, PINFUNCDATA, &config, 1);
}

/**
  * @brief	This function configures the IRQ GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	inversion: Enables logic output inversion
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgIRQ(uint8_t interfaceID, PinFunctionsIRQ pinFunction, uint8_t inversion, uint8_t pullup) {
	uint8_t config = (pinFunction & PFIRQ_MASK) | (pullup << 7) | (inversion << 6);
	AX5043WriteShortAddress(interfaceID, PINFUNCIRQ, &config, 1);
}

/**
  * @brief	This function configures the AntSel GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	inversion: Enables logic output inversion
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgAntSel(uint8_t interfaceID, PinFunctionsAntSel pinFunction, uint8_t inversion, uint8_t pullup) {
	uint8_t config = (pinFunction & PFANTSEL_MASK) | (pullup << 7) | (inversion << 6);
	AX5043WriteShortAddress(interfaceID, PINFUNCANTSEL, &config, 1);
}

/**
  * @brief	This function configures the PwrRamp GPIO
  * @param	interfaceID: Which interface (chip) used
  * @param	pinFunction: Which Function this GPIO will perform
  * @param	inversion: Enables logic output inversion
  * @param	pullup: Enables weak pullup on this GPIO
  * @return	None
  */
void AX5043GPIOCnfgPwrRamp(uint8_t interfaceID, PinFunctionsPwrRamp pinFunction, uint8_t inversion, uint8_t pullup) {
	uint8_t config = (pinFunction & PFPWRAMP_MASK) | (pullup << 7) | (inversion << 6);
	AX5043WriteShortAddress(interfaceID, PINFUNCPWRAMP, &config, 1);
}

/**
  * @brief	This function Enables ADC Isolate Channels. Done by sampling common mode between channels
  * @param	interfaceID: Which interface (chip) used
  * @param	isolateChannel: Enables ADC Isolate Channels
  * @return	None
  */
void AX5043GPIOSetEnableADCIsolateChannel(uint8_t interfaceID, uint8_t isolateChannel) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	config = (config & ~CHISL_MASK) | (isolateChannel);
	AX5043WriteLongAddress(interfaceID, GPADCCTRL, &config, 1);
}

/**
  * @brief	This function gets if ADC Isolate Channels is used
  * @param	interfaceID: Which interface (chip) used
  * @return	If Isolate Channels is enabled
  */
uint8_t AX5043GPIOGetADCIsolateChannel(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	return ((config & CHISL_MASK));
}

/**
  * @brief	This function Enables Continuous Sampling
  * @param	interfaceID: Which interface (chip) used
  * @param	contSampling: Enables Continuous Sampling
  * @return	None
  */
void AX5043GPIOSetEnableADCContinuousSampling(uint8_t interfaceID, uint8_t contSampling) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	config = (config & ~CONT_MASK) | (contSampling << 1);
	AX5043WriteLongAddress(interfaceID, GPADCCTRL, &config, 1);
}

/**
  * @brief	This function gets if ADC Continuous Sampling is used
  * @param	interfaceID: Which interface (chip) used
  * @return	If Continuous Sampling is used
  */
uint8_t AX5043GPIOGetADCContinuousSampling(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	return ((config & CONT_MASK) >> 1);
}

/**
  * @brief	This function Enables Sampling GPADC1-GPADC3
  * @param	interfaceID: Which interface (chip) used
  * @param	enSampling: Enables Sampling GPADC1-GPADC3
  * @return	None
  */
void AX5043GPIOSetEnableSamplingADCGPADC13(uint8_t interfaceID, uint8_t enSampling) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	config = (config & ~GPADC13_MASK) | (enSampling << 2);
	AX5043WriteLongAddress(interfaceID, GPADCCTRL, &config, 1);
}

/**
  * @brief	This function gets if Sampling GPADC1-GPADC3 is used
  * @param	interfaceID: Which interface (chip) used
  * @return	If Sampling GPADC1-GPADC3 is used
  */
uint8_t AX5043GPIOGetSamplingADCGPADC13(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	return ((config & GPADC13_MASK) >> 2);
}

/**
  * @brief	This function triggers a single conversion
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043GPIOADCTriggerConversion(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	config = (config & BUSY_MASK);
	AX5043WriteLongAddress(interfaceID, GPADCCTRL, &config, 1);
}

/**
  * @brief	This function gets if the Conversion is ongoing, ADC Busy
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> If Busy, 0 -> if not
  */
uint8_t AX5043GPIOGetADCBusy(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCCTRL, &config, 1);
	return ((config & BUSY_MASK) >> 7);
}

/**
  * @brief	This function sets the ADC Continuous Sample Period
  * @param	interfaceID: Which interface (chip) used
  * @param	period: Sample Periode, fsr = fxtal / (32 * GPADCPERIOD)
  * @return	None
  */
void AX5043GPIOSetADCSamplingPeriod(uint8_t interfaceID, uint8_t period) {
	AX5043WriteLongAddress(interfaceID, GPADCPERIOD, &period, 1);
}

/**
  * @brief	This function gets the ADC Continuous Sample Period
  * @param	interfaceID: Which interface (chip) used
  * @return	Sample Periode, fsr = fxtal / (32 * GPADCPERIOD)
  */
uint8_t AX5043GPIOGetADCSamplingPeriod(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADCPERIOD, &config, 1);
	return config;
}

/**
  * @brief	This function gets the ADC GPADC13 Value
  * @param	interfaceID: Which interface (chip) used
  * @return	ADC GPADC13 Value
  */
uint16_t AX5043GPIOGetADCGPADC13Value(uint8_t interfaceID) {
	uint16_t value = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, GPADC13VALUE0, &config, 1);
	value = (config & GPADC13VALUE0_MASK);
	AX5043ReadLongAddress(interfaceID, GPADC13VALUE1, &config, 1);
	value += (config & GPADC13VALUE1_MASK) << 8;
	return value;
}

/**
  * @brief	This function sets the DAC Value to output
  * @param	interfaceID: Which interface (chip) used
  * @param	value: DAC Value to output
  * @return	None
  */
void AX5043GPIOSetDACValue(uint8_t interfaceID, uint16_t value) {
	uint8_t config;
	config = (value & DACVALUE0_MASK);
	AX5043WriteLongAddress(interfaceID, DACVALUE0, &config, 1);
	config = (value >> 8) & DACVALUE1_MASK;
	AX5043WriteLongAddress(interfaceID, DACVALUE1, &config, 1);
}

/**
  * @brief	This function gets the DAC Value to output
  * @param	interfaceID: Which interface (chip) used
  * @return	DAC Value being output
  */
uint16_t AX5043GPIOGetDACValue(uint8_t interfaceID) {
	uint16_t value = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACVALUE0, &config, 1);
	value = (config & DACVALUE0_MASK);
	AX5043ReadLongAddress(interfaceID, DACVALUE1, &config, 1);
	value += (config & DACVALUE1_MASK) << 8;
	return value;
}

/**
  * @brief	This function sets the DAC Input shift
  * @param	interfaceID: Which interface (chip) used
  * @param	shift: DAC Input Shift
  * @return	None
  */
void AX5043GPIOSetDACInputShift(uint8_t interfaceID, uint16_t shift) {
	uint8_t config;
	config = (shift & DACSHIFT_MASK);
	AX5043WriteLongAddress(interfaceID, DACVALUE0, &config, 1);
}

/**
  * @brief	This function gets the DAC Input shift
  * @param	interfaceID: Which interface (chip) used
  * @return	DAC Input Shift
  */
uint8_t AX5043GPIOGetDACInputShift(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACVALUE0, &config, 1);
	return (config & DACSHIFT_MASK);
}

/**
  * @brief	This function sets the DAC Input
  * @param	interfaceID: Which interface (chip) used
  * @param	input: DAC Input
  * @return	None
  */
void AX5043GPIOSetDACInput(uint8_t interfaceID, DACInputSelection input) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	config = (config & ~DACINPUT_MASK) | (input);
	AX5043WriteLongAddress(interfaceID, DACCONFIG, &config, 1);
}

/**
  * @brief	This function gets the DAC Input
  * @param	interfaceID: Which interface (chip) used
  * @return	Selected DAC Input
  */
DACInputSelection AX5043GPIOGetDACInput(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	return (DACInputSelection)(config & DACINPUT_MASK);
}

/**
  * @brief	This function sets/enables DAC Clock Doubling
  * @param	interfaceID: Which interface (chip) used
  * @param	doubling: 1 -> Clock Doubling, 0 -> No Clock Doubling
  * @return	None
  */
void AX5043GPIOSetDACClockDoubling(uint8_t interfaceID, uint8_t doubling) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	config = (config & ~DACCLKX2_MASK) | (doubling << 6);
	AX5043WriteLongAddress(interfaceID, DACCONFIG, &config, 1);
}

/**
  * @brief	This function gets if DAC Clock Doubling is set/enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Clock Doubling, 0 -> No Clock Doubling
  */
uint8_t AX5043GPIOGetDACClockDoubling(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	return ((config & DACCLKX2_MASK) >> 6);
}

/**
  * @brief	This function sets the DAC Output Mode
  * @param	interfaceID: Which interface (chip) used
  * @param	mode: 1 -> PWM Mode, 0 -> SumDelta Mode
  * @return	None
  */
void AX5043GPIOSetDACOutputMode(uint8_t interfaceID, uint8_t mode) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	config = (config & ~DACPWM_MASK) | (mode << 7);
	AX5043WriteLongAddress(interfaceID, DACCONFIG, &config, 1);
}

/**
  * @brief	This function gets the DAC Output Mode
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> PWM Mode, 0 -> SumDelta Mode
  */
uint8_t AX5043GPIOGetDACOutputMode(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, DACCONFIG, &config, 1);
	return ((config & DACPWM_MASK) >> 7);
}
