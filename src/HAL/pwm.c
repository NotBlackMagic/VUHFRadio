#include "pwm.h"
#include "gpio.h"
#include "rcc.h"

void PWM1Init() {
	//Init PWM using Timer 1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	//Configure GPIOs
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);

	//Configure the NVIC to handle TIM interrupt
	NVIC_SetPriority(TIM1_UP_IRQn, 0);
	NVIC_EnableIRQ(TIM1_UP_IRQn);

	//Configure Timer
	LL_TIM_SetClockDivision(TIM1, LL_TIM_CLOCKDIVISION_DIV1);
	LL_TIM_SetPrescaler(TIM1, 0);
	LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetAutoReload(TIM1, 720);
	LL_TIM_EnableARRPreload(TIM1);

	//Configure Timer output
	LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
	LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_LOW);
	LL_TIM_OC_SetCompareCH1(TIM1, 360);
	LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);

	//Configure Timer Interrupts
	LL_TIM_EnableIT_UPDATE(TIM1);

	//Enable Timer and PWM Output
	LL_TIM_EnableAllOutputs(TIM1);
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_GenerateEvent_UPDATE(TIM1);
}

void PWM2Init() {
	//Init PWM using Timer 1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

	//Configure GPIOs
	LL_GPIO_AF_RemapPartial2_TIM2();
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL);

	//Configure the NVIC to handle TIM interrupt
	NVIC_SetPriority(TIM2_IRQn, 0);
	NVIC_EnableIRQ(TIM2_IRQn);

	//Configure Timer
	LL_TIM_SetClockDivision(TIM2, LL_TIM_CLOCKDIVISION_DIV1);
	LL_TIM_SetPrescaler(TIM2, 0);
	LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetAutoReload(TIM2, 720);
	LL_TIM_EnableARRPreload(TIM2);

	//Configure Timer output
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);
	LL_TIM_OC_SetPolarity(TIM2, LL_TIM_CHANNEL_CH4, LL_TIM_OCPOLARITY_LOW);
	LL_TIM_OC_SetCompareCH4(TIM2, 360);
	LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH4);
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH4);

	//Configure Timer Interrupts
	LL_TIM_EnableIT_UPDATE(TIM2);

	//Enable Timer and PWM Output
	LL_TIM_EnableAllOutputs(TIM2);
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_GenerateEvent_UPDATE(TIM2);
}

uint8_t pin = 0;
void TIM1_UP_IRQHandler() {
	//Check whether CC1 interrupt is pending
	if(LL_TIM_IsActiveFlag_UPDATE(TIM1) == 1) {
		//Clear the update interrupt flag
		LL_TIM_ClearFlag_UPDATE(TIM1);
	}
}

void TIM2_IRQHandler() {
	//Check whether CC1 interrupt is pending
	if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == 1) {
		//Clear the update interrupt flag
		LL_TIM_ClearFlag_UPDATE(TIM2);

		GPIOWrite(0, pin);
		pin = !pin;
	}
}
