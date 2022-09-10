#include "gpio.h"

/**
  * @brief	This function initializes the GPIO that don't use a peripheral (ADC/UART/SPI etc)
  * @param	None
  * @return	None
  */
void GPIOInit() {
	//Enable Port Clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

	//Enable EXTI/AFIO Clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

	//Enable PC14 and PC15 as general IO
//	PWR->CR |= 1<<8;
//	RCC->BDCR &= 0xFFFFFFFE;
//	BKP->CR &= 0xFFFFFFFE;
//	PWR->CR &= 0xFFFFFEFF;

	//Set Generic Output GPIO's
	GPIOSetPinMode(GPIO_OUT_LVSH_EN, GPIO_Mode_Output);	//Output Level-Shift Enable

	//Set Generic Input GPIO's
	GPIOSetPinMode(GPIO_IN_UART_WAKE, GPIO_Mode_Input);	//Input UART Wake pin

	//Set Generic ADC Input GPIO's
	GPIOSetPinMode(GPIO_ADC_Q, GPIO_Mode_Analog);		//ADC Input Q Signal from AX Radio
	GPIOSetPinMode(GPIO_ADC_I, GPIO_Mode_Analog);		//ADC Input I Signal from AX Radio
	GPIOSetPinMode(GPIO_ADC_DAC, GPIO_Mode_Analog);		//ADC Input DAC from AX Radio

	//Set AX Radio Output GPIO's
	GPIOSetPinMode(GPIO_OUT_CS_AX, GPIO_Mode_Output);	//Output CS of AX Radio
	//Set AX Radio Input GPIO's
	GPIOSetPinMode(GPIO_IN_DCLK_AX, GPIO_Mode_Input);		//Input DCLK of AX Radio
	GPIOSetPinMode(GPIO_IN_DATA_AX, GPIO_Mode_Input);		//Input DATA of AX Radio

	//Set Output Pins to Initial State
	GPIOWrite(GPIO_OUT_CS_AX, 1);

	//Set Input Pins Interrupts
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE0);		//IRQ of AX Radio
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_0);

//	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE11);	//IRQ DCLK AX Radio
//	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_11);
//	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_11);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 1);
//	NVIC_EnableIRQ(EXTI15_10_IRQn);
//	NVIC_SetPriority(EXTI15_10_IRQn, 1);
}

/**
  * @brief	This function sets the output mode type of a pin
  * @param	gpio: Pin to define output mode
  * @param	mode: Output mode of this pin
  * @return	None
  */
void GPIOSetPinMode(uint8_t gpio, GPIOOutputMode mode) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	LL_GPIO_SetPinMode(gpioPorts[port], gpioPins[pin], gpioOutputMode[mode]);
}

/**
  * @brief	This function sets the output of a pin
  * @param	gpio: Pin to set output
  * @param	on: 1 output is set high, 0 output is set low
  * @return	None
  */
void GPIOWrite(uint8_t gpio, uint8_t on) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	if(on == 1) {
		LL_GPIO_SetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
	else {
		LL_GPIO_ResetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
}

/**
  * @brief	This function gets the input state of a pin
  * @param	gpio: Pin to set output
  * @return	1 input is set high, 0 input is set low
  */
uint8_t GPIORead(uint8_t gpio) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	return LL_GPIO_IsInputPinSet(gpioPorts[port], gpioPins[pin]);
}

/**
  * @brief	This function is the Handler for GPIO2s
  * @param	None
  * @return	None
  */
void EXTI2_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO3s
  * @param	None
  * @return	None
  */
void EXTI3_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO4s
  * @param	None
  * @return	None
  */
void EXTI4_IRQHandler(void) {

}
