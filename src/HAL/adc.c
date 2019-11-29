#include "adc.h"

#include "rcc.h"

/**
  * @brief	This function initializes the ADC and respective GPIOs
  * @param	None
  * @return	None
  */
void ADC1Init() {
	//Enable bus clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	//Configure the ADC
//	LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);
//	LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_DISABLE);
//	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);
//	LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_MULTI_INDEPENDENT);
	LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
	LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
//	LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);
//	LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);

	//Enable ADC
	LL_ADC_Enable(ADC1);

	Delay(100);

	//Run ADC self calibration
	LL_ADC_StartCalibration(ADC1);
	while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0);

	//Configure Input Channel
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_4);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4, LL_ADC_SAMPLINGTIME_7CYCLES_5);		//Used for 12bits resolution
}


/**
  * @brief	This function reads ADC Channel and returns value
  * @param	channel: ADC Channel number to read
  * @return	ADC Read Value (12 bits)
  */
uint16_t ADC1Read(uint8_t channel) {
	switch(channel) {
		case 4:
			LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_4);
			LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4, LL_ADC_SAMPLINGTIME_7CYCLES_5);	//Set the input channel
			LL_ADC_REG_StartConversionSWStart(ADC1);	//Start the conversion
			break;
		case 5:
			LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_5);
			LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_5, LL_ADC_SAMPLINGTIME_7CYCLES_5);	//Set the input channel
			LL_ADC_REG_StartConversionSWStart(ADC1);	//Start the conversion
			break;
		case 6:
			LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_6);
			LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_7CYCLES_5);	//Set the input channel
			LL_ADC_REG_StartConversionSWStart(ADC1);	//Start the conversion
			break;
		case 7:
			LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_7);
			LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_7, LL_ADC_SAMPLINGTIME_7CYCLES_5);	//Set the input channel
			LL_ADC_REG_StartConversionSWStart(ADC1);	//Start the conversion
			break;
	}

	//Wait until conversion completion
	while (LL_ADC_IsActiveFlag_EOS(ADC1) == 0);
	//Get the conversion value
	return LL_ADC_REG_ReadConversionData12(ADC1);
}
