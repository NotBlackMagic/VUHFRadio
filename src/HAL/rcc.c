#include "rcc.h"

volatile uint32_t sysTickCnt = 0;			//Used for the Delay function

/**
  * @brief	This function initializes the system clocks and ADC and USB clocks
  * @param	None
  * @return	None
  */
void SystemClockInit() {
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

	if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2) {
		//Error_Handler();
	}

	//LL_RCC_HSE_EnableCSS();
	LL_RCC_HSE_EnableBypass();
	LL_RCC_HSE_Enable();
	while(LL_RCC_HSE_IsReady() != 1);		//Wait till HSE is ready

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_2, LL_RCC_PLL_MUL_9);
	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1);		//Wait till PLL is ready

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);		//Wait till System clock is ready

	LL_SetSystemCoreClock(72000000);
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);				//Set ADC Clock
	LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);				//Set USB Clock
}

/**
  * @brief	This function initializes the Systick timer
  * @param	None
  * @return	None
  */
void SystemTickInit() {
	//Set systick to 1ms in using frequency set to 72MHz
	LL_Init1msTick(72000000);

	//Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function)
	LL_SetSystemCoreClock(72000000);

	LL_SYSTICK_EnableIT();
}

/**
  * @brief	This function delays/blocks for set amount (ms)
  * @param	ms: Ms to wait/delay
  * @return	None
  */
void Delay(uint32_t ms) {
	uint32_t timeStamp = sysTickCnt;
	while(timeStamp + ms >= sysTickCnt);
}

/**
  * @brief	This function gets the current SysTick Value
  * @param	None
  * @return	SysTick Value
  */
uint32_t GetSysTick() {
	return sysTickCnt;
}

void GetSysTickAsTime(uint8_t* hour, uint8_t* min, uint8_t* sec, uint16_t* ms) {
	uint32_t tempSysTickCnt = GetSysTick();

	*hour = (tempSysTickCnt / 3600000);
	tempSysTickCnt -= (*hour) * 3600000;
	*min = (tempSysTickCnt / 60000);
	tempSysTickCnt -= (*min) * 60000;
	*sec = (tempSysTickCnt / 1000);
	tempSysTickCnt -= (*sec) * 1000;
	*ms = tempSysTickCnt;
}

/**
  * @brief	ISR: Used for the delay function and other timed events, this interrupt occurs every 1 ms
  * @param	None
  * @return	None
  */
void SysTick_Handler(void) {
	sysTickCnt += 1;
}
