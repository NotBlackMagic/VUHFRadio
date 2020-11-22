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
	GPIOSetPinMode(GPIO_OUT_LED0, GPIO_Mode_Output);	//Output LED 0
	GPIOSetPinMode(GPIO_OUT_LED1, GPIO_Mode_Output);	//Output LED 1
	GPIOSetPinMode(GPIO_OUT_LED2, GPIO_Mode_Output);	//Output LED 2
	GPIOSetPinMode(GPIO_OUT_LED3, GPIO_Mode_Output);	//Output LED 3
	GPIOSetPinMode(GPIO_OUT_LED4 ,GPIO_Mode_Output);	//Output LED 4
	GPIOSetPinMode(GPIO_OUT_LED5 ,GPIO_Mode_Output);	//Output LED 5

	//Set Generic ADC Input GPIO's
	GPIOSetPinMode(GPIO_ADC_I_VCC_U, GPIO_Mode_Analog);	//ADC Input Current AX5043 UHF Radio
	GPIOSetPinMode(GPIO_ADC_I_VCC_V, GPIO_Mode_Analog);	//ADC Input Current AX5043 VHF Radio
	GPIOSetPinMode(GPIO_ADC_I_VCC_M, GPIO_Mode_Analog);	//ADC Input Current MCU/Amps
	GPIOSetPinMode(GPIO_ADC_I_5V, GPIO_Mode_Analog);	//ADC Input Current USB/5V

	//Set AX5043 Output GPIO's
	GPIOSetPinMode(GPIO_OUT_CS_U, GPIO_Mode_Output);	//Output CS of UHF
	GPIOSetPinMode(GPIO_OUT_CS_V, GPIO_Mode_Output);	//Output CS of VHF
	//Set AX5043 Input GPIO's
	GPIOSetPinMode(GPIO_IN_PTT_V, GPIO_Mode_Input);		//Input PTT of VHF	(PA10)
	GPIOSetPinMode(GPIO_IN_PTT_U, GPIO_Mode_Input);		//Input PTT of UHF	(PA15)
	GPIOSetPinMode(GPIO_IN_IRQ_U, GPIO_Mode_Input);		//Input IRQ of UHF	(PB0)
	GPIOSetPinMode(GPIO_IN_IRQ_V, GPIO_Mode_Input);		//Input IRQ of VHF	(PB1)
	GPIOSetPinMode(GPIO_IN_DCLK_U, GPIO_Mode_Input);	//Input DCLK of UHF	(PB11)
	GPIOSetPinMode(GPIO_IN_DCLK_V, GPIO_Mode_Input);	//Input DCLK of VHF (PA8)
	GPIOSetPinMode(GPIO_IN_DATA_U, GPIO_Mode_Input);	//Input DATA of UHF (PB10)
	GPIOSetPinMode(GPIO_IN_DATA_V, GPIO_Mode_Input);	//Input DATA of VHF (PA9)

	//Set Debbug Output GPIO's
	GPIOSetPinMode(45, GPIO_Mode_Output);	//Output LED Blue Pill Dev. Board

	//Set Output Pins to Initial State
	GPIOWrite(GPIO_OUT_LED0, 0);
	GPIOWrite(GPIO_OUT_LED1, 0);
	GPIOWrite(GPIO_OUT_LED2, 0);
	GPIOWrite(GPIO_OUT_LED3, 0);
	GPIOWrite(GPIO_OUT_LED4, 0);
	GPIOWrite(GPIO_OUT_LED5, 0);
	GPIOWrite(GPIO_OUT_CS_U, 1);
	GPIOWrite(GPIO_OUT_CS_V, 1);

	//Set Input Pins Interrupts
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE0);		//IRQ of UHF
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
	LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_0);

	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE1);		//IRQ of UHF
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1);
	LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_1);

	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE11);	//IRQ DCLK of UHF
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_11);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_11);

	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE8);		//IRQ DCLK of VHF
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_8);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_8);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
	NVIC_SetPriority(EXTI9_5_IRQn, 0);
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
  * @brief	This function is the Handler for GPIO0s
  * @param	None
  * @return	None
  */
void EXTI0_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_0) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) == 0x01) {
		//Interrupt for IRQ of UHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);

		RadioIRQUHFHandler();
	}
}

/**
  * @brief	This function is the Handler for GPIO1s
  * @param	None
  * @return	None
  */
void EXTI1_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_1) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) == 0x01) {
		//Interrupt for IRQ of VHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);

		RadioIRQVHFHandler();
	}
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

/**
  * @brief	This function is the Handler for GPIO5s to GPIO9s
  * @param	None
  * @return	None
  */
void EXTI9_5_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8) == 0x01) {
		//Interrupt for DCLK of VHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);

		RadioDCLKVHFHandler();
	}
}

/**
  * @brief	This function is the Handler for GPIO10s to GPIO15s
  * @param	None
  * @return	None
  */
void EXTI15_10_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == 0x01) {
		//Interrupt for DCLK of UHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);

		RadioDCLKUHFHandler();
	}
}
