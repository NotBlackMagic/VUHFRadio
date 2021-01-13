#include "timer.h"

#include "radioStateMachine.h"

/**
  * @brief	This function initializes the TIM3, used to read Tracking/Status of AX5043
  * @param	None
  * @return	None
  */
void TIM3Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM3, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM3, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));		//Set pre-scaler to have a TIM Clock Reference of 10kHz
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 1000));	//Calculate ARR register value for clock to be 1kHz
	LL_TIM_EnableARRPreload(TIM3);
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_CC1IF);
	LL_TIM_DisableMasterSlaveMode(TIM3);

	//Configure Interrupts
	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_EnableIRQ(TIM3_IRQn);
	LL_TIM_EnableIT_CC1(TIM3);

	//Enable Timer
	LL_TIM_EnableCounter(TIM3);
}

/**
  * @brief	This function sets the output frequency of TIM3, sets the ARR
  * @param	freq: Desired timer frequency
  * @return	None
  */
void TIM3SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), freq));
}

/**
  * @brief	TIM3 IRQ Handler, get updated tracking/status from AX5043 Radio
  * @param	None
  * @return	None
  */
void TIM3_IRQHandler(void) {
	//Check whether CC1 interrupt is pending
	if(LL_TIM_IsActiveFlag_CC1(TIM3) == 1) {
		RadioTrackingUpdateHandler();

		//Clear the update interrupt flag
		LL_TIM_ClearFlag_CC1(TIM3);
	}
}
