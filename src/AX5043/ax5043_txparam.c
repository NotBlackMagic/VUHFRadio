#include "ax5043_txparam.h"

/**
  * @brief	This function sets the Frequency Shape
  * @param	interfaceID: Which interface (chip) used
  * @param	freqShape: The Frequency Shape
  * @return	None
  */
void AX5043TXParamSetFrequencyShape(uint8_t interfaceID, FreqShape freqShape) {
	uint8_t config = (freqShape & FREQSHAPE_MASK);
	AX5043WriteLongAddress(interfaceID, MODCFGF, &config, 1);
}

/**
  * @brief	This function gets the Frequency Shape
  * @param	interfaceID: Which interface (chip) used
  * @return	The Frequency Shape
  */
FreqShape AX5043TXParamGetFrequencyShape(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGF, &config, 1);
	return (config & FREQSHAPE_MASK);
}

/**
  * @brief	This function sets FSK Frequency Deviation
  * @param	interfaceID: Which interface (chip) used
  * @param	freqShape: The Frequency Shape
  * @return	None
  */
void AX5043TXParamSetFSKFrequencyDeviation(uint8_t interfaceID, uint32_t freqDeviation) {
	uint8_t config;
	config = (freqDeviation) & FSKDEV0_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDEV0, &config, 1);
	config = (freqDeviation >> 8) & FSKDEV1_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDEV1, &config, 1);
	config = (freqDeviation >> 16) & FSKDEV2_MASK;
	AX5043WriteLongAddress(interfaceID, FSKDEV2, &config, 1);
}

/**
  * @brief	This function gets FSK Frequency Deviation
  * @param	interfaceID: Which interface (chip) used
  * @return	The Frequency Shape
  */
uint32_t AX5043TXParamGetFSKFrequencyDeviation(uint8_t interfaceID) {
	uint32_t freqDeviation = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV0, &config, 1);
	freqDeviation = (config & FSKDEV0_MASK);
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	freqDeviation += (config & FSKDEV1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, FSKDEV2, &config, 1);
	freqDeviation += (config & FSKDEV2_MASK) << 16;
	return freqDeviation;
}

/**
  * @brief	This function sets FM ADC Bit Scale ADC Value, generates the FM Frequency Deviation
  * @param	interfaceID: Which interface (chip) used
  * @param	fmShift: The FM ADC Bit Scale ADC Value
  * @return	None
  */
void AX5043TXParamSetFMShift(uint8_t interfaceID, FMShift fmShift) {
	uint8_t config = (fmShift & FMSHIFT_MASK);
	AX5043WriteLongAddress(interfaceID, FSKDEV0, &config, 1);
}

/**
  * @brief	This function gets FM ADC Bit Scale ADC Value
  * @param	interfaceID: Which interface (chip) used
  * @return	The FM ADC Bit Scale ADC Value
  */
FMShift AX5043TXParamGetFMShift(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV0, &config, 1);
	return (config & FMSHIFT_MASK);
}

/**
  * @brief	This function sets the FM Input
  * @param	interfaceID: Which interface (chip) used
  * @param	input: The FM Input
  * @return	None
  */
void AX5043TXParamSetFMInput(uint8_t interfaceID, FMInput input) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	config = (config & ~FMINPUT_MASK) | (input);
	AX5043WriteLongAddress(interfaceID, FSKDEV1, &config, 1);
}

/**
  * @brief	This function gets the FM Input
  * @param	interfaceID: Which interface (chip) used
  * @return	The FM ADC Bit Scale ADC Value
  */
FMShift AX5043TXParamGetFMInput(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	return (config & FMINPUT_MASK);
}

/**
  * @brief	This function sets ADC Sign Extension
  * @param	interfaceID: Which interface (chip) used
  * @param	signExt: The ADC Sign Extension
  * @return	None
  */
void AX5043TXParamSetADCSignExtension(uint8_t interfaceID, uint8_t signExt) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	config = (config & ~FMSEXT_MASK) | (signExt << 6);
	AX5043WriteLongAddress(interfaceID, FSKDEV1, &config, 1);
}

/**
  * @brief	This function gets ADC Sign Extension
  * @param	interfaceID: Which interface (chip) used
  * @return	The ADC Sign Extension
  */
uint8_t AX5043TXParamGetADCSignExtension(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	return ((config & FMSEXT_MASK) >> 6);
}

/**
  * @brief	This function sets ADC Offset Subtract
  * @param	interfaceID: Which interface (chip) used
  * @param	adcSubtraction: The ADC Offset Subtract
  * @return	None
  */
void AX5043TXParamSetADCOffsetSubtraciont(uint8_t interfaceID, uint8_t adcSubtraction) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	config = (config & ~FMOFFS_MASK) | (adcSubtraction << 7);
	AX5043WriteLongAddress(interfaceID, FSKDEV1, &config, 1);
}

/**
  * @brief	This function gets ADC Offset Subtract
  * @param	interfaceID: Which interface (chip) used
  * @return	The ADC Offset Subtract
  */
uint8_t AX5043TXParamGetADCOffsetSubtraciont(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FSKDEV1, &config, 1);
	return ((config & FMOFFS_MASK) >> 7);
}

/**
  * @brief	This function Enables the Differential Transmitter
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enabled, 0 -> Disabled
  * @return	None
  */
void AX5043TXParamEnableDiffTransmitter(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~TXDIFF_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets if the Differential Transmitter is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enabled, 0 -> Disabled
  */
uint8_t AX5043TXParamIsDiffTransmitterEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return (config & TXDIFF_MASK);
}

/**
  * @brief	This function Enables the Single Ended Transmitter
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enabled, 0 -> Disabled
  * @return	None
  */
void AX5043TXParamEnableSingleEndedTransmitter(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~TXSE_MASK) | (enable << 1);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets if the Single Ended Transmitter is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enabled, 0 -> Disabled
  */
uint8_t AX5043TXParamIsSingleEndedTransmitterEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return ((config & TXSE_MASK) >> 1);
}

/**
  * @brief	This function sets the Amplitude Shape
  * @param	interfaceID: Which interface (chip) used
  * @param	shape: 0 -> Unshapped, 1 -> Raised Cosine
  * @return	None
  */
void AX5043TXParamSetAmplitudeShape(uint8_t interfaceID, uint8_t shape) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~AMPLSHAPE_MASK) | (shape << 2);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets the Amplitude Shape
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> Unshapped, 1 -> Raised Cosine
  */
uint8_t AX5043TXParamGetAmplitudeShape(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return ((config & AMPLSHAPE_MASK) >> 2);
}

/**
  * @brief	This function sets the Slow Ramp
  * @param	interfaceID: Which interface (chip) used
  * @param	slowRamp: The Slow Ramp
  * @return	None
  */
void AX5043TXParamSetSlowRamp(uint8_t interfaceID, SlowRamp slowRamp) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~AMPLSHAPE_MASK) | (slowRamp << 4);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets the Slow Ramp
  * @param	interfaceID: Which interface (chip) used
  * @return	The Slow Ramp
  */
SlowRamp AX5043TXParamGetSlowRamp(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return (SlowRamp)((config & SLOWRAMP_MASK) >> 4);
}

/**
  * @brief	This function enables disable transmitter if PLL looses lock
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enabled, 0 -> Disabled
  * @return	None
  */
void AX5043TXParamSetDisbleTransitterOnPLLLose(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~PTTLCKGATE_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets if disable transmitter if PLL looses lock is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enabled, 0 -> Disabled
  */
uint8_t AX5043TXParamGetDisbleTransitterOnPLLLose(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return ((config & PTTLCKGATE_MASK) >> 6);
}

/**
  * @brief	This function enables disable transmitter if Brown Out is Detected
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enabled, 0 -> Disabled
  * @return	None
  */
void AX5043TXParamSetDisbleTransitterOnBrownOut(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	config = (config & ~BROWNGATE_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, MODCFGA, &config, 1);
}

/**
  * @brief	This function gets if disable transmitter if Brown Out is Detected is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enabled, 0 -> Disabled
  */
uint8_t AX5043TXParamGetDisbleTransitterOnBrownOut(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGA, &config, 1);
	return ((config & BROWNGATE_MASK) >> 7);
}

/**
  * @brief	This function sets Transmitter Datarate, TXRATE = (BITRATE / fxtal) * 2^24 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @param	datarate: The Transmitter Datarate
  * @return	None
  */
void AX5043TXParamSetTXDatarate(uint8_t interfaceID, uint32_t datarate) {
	uint8_t config;
	config = (datarate) & TXRATE0_MASK;
	AX5043WriteLongAddress(interfaceID, TXRATE0, &config, 1);
	config = (datarate >> 8) & TXRATE1_MASK;
	AX5043WriteLongAddress(interfaceID, TXRATE1, &config, 1);
	config = (datarate >> 16) & TXRATE2_MASK;
	AX5043WriteLongAddress(interfaceID, TXRATE2, &config, 1);
}

/**
  * @brief	This function gets Transmitter Datarate, TXRATE = (BITRATE / fxtal) * 2^24 + 1/2
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmitter Datarate
  */
uint32_t AX5043TXParamGetTXDatarate(uint8_t interfaceID) {
	uint32_t datarate = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXRATE0, &config, 1);
	datarate = (config) & TXRATE0_MASK;
	AX5043ReadLongAddress(interfaceID, TXRATE1, &config, 1);
	datarate += (config & TXRATE1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, TXRATE2, &config, 1);
	datarate += (config & TXRATE2_MASK) << 16;
	return datarate;
}

/**
  * @brief	This function sets the Transmit Predistortion coefficient A. TXPWRCOEFFA = a0 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @param	coeff: The Transmit Predistortion coefficient
  * @return	None
  */
void AX5043TXParamSetTXPredistortionCoeffA(uint8_t interfaceID, uint16_t coeff) {
	uint8_t config;
	config = (coeff) & TXPWRCOEFFA0_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFA0, &config, 1);
	config = (coeff >> 8) & TXPWRCOEFFA1_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFA1, &config, 1);
}

/**
  * @brief	This function gets the Transmit Predistortion coefficient A. TXPWRCOEFFA = a0 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmit Predistortion coefficient
  */
uint16_t AX5043TXParamGetTXPredistortionCoeffA(uint8_t interfaceID) {
	uint32_t coeff = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFA0, &config, 1);
	coeff = (config & TXPWRCOEFFA0_MASK);
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFA1, &config, 1);
	coeff += (config & TXPWRCOEFFA1_MASK) << 8;
	return coeff;
}

/**
  * @brief	This function sets the Transmit Predistortion coefficient B. TXPWRCOEFFA = a1 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @param	coeff: The Transmit Predistortion coefficient
  * @return	None
  */
void AX5043TXParamSetTXPredistortionCoeffB(uint8_t interfaceID, uint16_t coeff) {
	uint8_t config;
	config = (coeff) & TXPWRCOEFFB0_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFB0, &config, 1);
	config = (coeff >> 8) & TXPWRCOEFFB1_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFB1, &config, 1);
}

/**
  * @brief	This function gets the Transmit Predistortion coefficient A. TXPWRCOEFFA = a1 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmit Predistortion coefficient
  */
uint16_t AX5043TXParamGetTXPredistortionCoeffB(uint8_t interfaceID) {
	uint32_t coeff = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFB0, &config, 1);
	coeff = (config & TXPWRCOEFFB0_MASK);
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFB1, &config, 1);
	coeff += (config & TXPWRCOEFFB1_MASK) << 8;
	return coeff;
}

/**
  * @brief	This function sets the Transmit Predistortion coefficient C. TXPWRCOEFFC = a2 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @param	coeff: The Transmit Predistortion coefficient
  * @return	None
  */
void AX5043TXParamSetTXPredistortionCoeffC(uint8_t interfaceID, uint16_t coeff) {
	uint8_t config;
	config = (coeff & TXPWRCOEFFC0_MASK);
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFC0, &config, 1);
	config = (coeff >> 8) & TXPWRCOEFFC1_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFC1, &config, 1);
}

/**
  * @brief	This function gets the Transmit Predistortion coefficient C. TXPWRCOEFFC = a2 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmit Predistortion coefficient
  */
uint16_t AX5043TXParamGetTXPredistortionCoeffC(uint8_t interfaceID) {
	uint32_t coeff = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFC0, &config, 1);
	coeff = (config & TXPWRCOEFFC0_MASK);
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFC1, &config, 1);
	coeff += (config & TXPWRCOEFFC1_MASK) << 8;
	return coeff;
}

/**
  * @brief	This function sets the Transmit Predistortion coefficient D. TXPWRCOEFFD = a3 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @param	coeff: The Transmit Predistortion coefficient
  * @return	None
  */
void AX5043TXParamSetTXPredistortionCoeffD(uint8_t interfaceID, uint16_t coeff) {
	uint8_t config;
	config = (coeff & TXPWRCOEFFD0_MASK);
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFD0, &config, 1);
	config = (coeff >> 8) & TXPWRCOEFFD1_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFD1, &config, 1);
}

/**
  * @brief	This function gets the Transmit Predistortion coefficient D. TXPWRCOEFFD = a3 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmit Predistortion coefficient
  */
uint16_t AX5043TXParamGetTXPredistortionCoeffD(uint8_t interfaceID) {
	uint32_t coeff = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFD0, &config, 1);
	coeff = (config & TXPWRCOEFFD0_MASK);
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFD1, &config, 1);
	coeff += (config & TXPWRCOEFFD1_MASK) << 8;
	return coeff;
}

/**
  * @brief	This function sets the Transmit Predistortion coefficient E. TXPWRCOEFFE = a4 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @param	coeff: The Transmit Predistortion coefficient
  * @return	None
  */
void AX5043TXParamSetTXPredistortionCoeffE(uint8_t interfaceID, uint16_t coeff) {
	uint8_t config;
	config = (coeff & TXPWRCOEFFE0_MASK);
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFE0, &config, 1);
	config = (coeff >> 8) & TXPWRCOEFFE1_MASK;
	AX5043WriteLongAddress(interfaceID, TXPWRCOEFFE1, &config, 1);
}

/**
  * @brief	This function gets the Transmit Predistortion coefficient E. TXPWRCOEFFE = a4 * 2^12 + 1/2
  * Amplitude shape for raised cosine is f(x) = a4*x^4 + a3*x^3 + a2*x^2 + a1*x^1 + a0
  * @param	interfaceID: Which interface (chip) used
  * @return	The Transmit Predistortion coefficient
  */
uint16_t AX5043TXParamGetTXPredistortionCoeffE(uint8_t interfaceID) {
	uint32_t coeff = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFE0, &config, 1);
	coeff = (config & TXPWRCOEFFE0_MASK);
	AX5043ReadLongAddress(interfaceID, TXPWRCOEFFE1, &config, 1);
	coeff += (config & TXPWRCOEFFE1_MASK) << 8;
	return coeff;
}

/**
  * @brief	This function sets the PSK Pulse Length
  * @param	interfaceID: Which interface (chip) used
  * @param	pulseLength: The PSK Pulse Length
  * @return	None
  */
void AX5043TXParamSetPSKPulseLength(uint8_t interfaceID, PSKPulseLength pulseLength) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	config = (config & ~PSKPULSELEN_MASK) | (pulseLength);
	AX5043WriteLongAddress(interfaceID, MODCFGP, &config, 1);
}

/**
  * @brief	This function gets the PSK Pulse Length
  * @param	interfaceID: Which interface (chip) used
  * @return	The PSK Pulse Length
  */
PSKPulseLength AX5043TXParamGetPSKPulseLength(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	return (config & PSKPULSELEN_MASK);
}

/**
  * @brief	This function sets the PSK Pulse Polarity
  * @param	interfaceID: Which interface (chip) used
  * @param	pulsePolarity: The PSK Pulse Polarity
  * @return	None
  */
void AX5043TXParamSetPSKPulsePolarity(uint8_t interfaceID, PSKPulsePolarity pulsePolarity) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	config = (config & ~PSKPULSECFG_MASK) | (pulsePolarity << 3);
	AX5043WriteLongAddress(interfaceID, MODCFGP, &config, 1);
}

/**
  * @brief	This function gets the PSK Pulse Polarity
  * @param	interfaceID: Which interface (chip) used
  * @return	The PSK Pulse Polarity
  */
PSKPulsePolarity AX5043TXParamGetPSKPulsePolarity(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	return ((config & PSKPULSECFG_MASK) >> 3);
}

/**
  * @brief	This function sets the PSK Pulse Boost
  * @param	interfaceID: Which interface (chip) used
  * @param	pulseBoost: The PSK Pulse Boost
  * @return	None
  */
void AX5043TXParamSetPSKPulseBoost(uint8_t interfaceID, PSKPulseBoost pulseBoost) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	config = (config & ~PSKPULSEBOST_MASK) | (pulseBoost << 5);
	AX5043WriteLongAddress(interfaceID, MODCFGP, &config, 1);
}

/**
  * @brief	This function gets the PSK Pulse Boost
  * @param	interfaceID: Which interface (chip) used
  * @return	The PSK Pulse Boost
  */
PSKPulseBoost AX5043TXParamGetPSKPulseBoost(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MODCFGP, &config, 1);
	return ((config & PSKPULSEBOST_MASK) >> 5);
}
