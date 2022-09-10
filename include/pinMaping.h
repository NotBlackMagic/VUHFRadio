#ifndef PINMAPING_H_
#define PINMAPING_H_

#ifdef __cplusplus
extern "C" {
#endif

//Input Pin Mapping
#define GPIO_IN_IRQ_AX						16		//Input IRQ of AX Radio
#define GPIO_IN_DCLK_AX						27		//Input DCLK of AX Radio
#define GPIO_IN_DATA_AX						26		//Input DATA of AX Radio
#define GPIO_IN_UART_WAKE					8		//Input UART Wake

//Output Pin Mapping
#define GPIO_OUT_LVSH_EN					17		//Output Level-Shift Enable
#define GPIO_OUT_CS_AX						15		//Output CS of AX Radio

//SAI TDM Pin Mapping
#define GPIO_TDM_LRCLK						28		//SAI TDM LRCLK of AX Radio (Input)
#define GPIO_TDM_BCLK						29		//SAI TDM BLCK of AX Radio (Input)
#define GPIO_TDM_DIN						30		//SAI TDM DIN of AX Radio (Input)
#define GPIO_TDM_DOUT						31		//SAI TDM DOUT of AX Radio (Output)

//ADC Pin Mapping
#define	GPIO_ADC_Q							4		//ADC Input of AX Radio Q Signal
#define	GPIO_ADC_I							5		//ADC Input of AX Radio I Signal
#define GPIO_ADC_DAC						6		//ADC Input of AX Radio DAC Output

//DAC Pin Mapping
#define GPIO_DAC_GPADC2						4		//ADC Input of AX Radio GPADC2
#define GPIO_DAC_GPADC1						5		//ADC Input of AX Radio GPADC1

//ADC Channel Mapping
#define ADC_CH_Q							4
#define ADC_CH_I							5
#define ADC_CH_DAC							6


#ifdef __cplusplus
}
#endif

#endif /* PINMAPING_H_ */
