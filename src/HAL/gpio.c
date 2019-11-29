#include "gpio.h"

/**
  * @brief	This function initializes the GPIO that don't use a peripheral (ADC/UART/SPI etc)
  * @param	None
  * @return	None
  */
void GPIOInit() {
	//Init Port Clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

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
	GPIOSetPinMode(GPIO_IN_PTT_V, GPIO_Mode_Input);	//Input PTT of VHF
	GPIOSetPinMode(GPIO_IN_PTT_U, GPIO_Mode_Input);	//Input PTT of UHF
	GPIOSetPinMode(GPIO_IN_IRQ_U, GPIO_Mode_Input);	//Input IRQ of UHF
	GPIOSetPinMode(GPIO_IN_IRQ_V, GPIO_Mode_Input);	//Input IRQ of VHF

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
