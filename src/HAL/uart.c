#include "uart.h"

/**
  * @brief	This function initializes the UART1 interface, also sets the respective GPIO pins
  * @param	None
  * @return	None
  */
void UART1Init(void) {
	//Enable bus clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

	//Configure GPIOs
	LL_GPIO_AF_EnableRemap_USART1();	//Remap UART1 GPIOs to Alternative GPIOs
	//Set UART1 TX (PB6) as AF push-pull
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
	//Set UART1 RX (PB7) as input floating
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);

	//Configure UART Interface
	LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);
	LL_USART_ConfigCharacter(USART1, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
	LL_USART_SetHWFlowCtrl(USART1, LL_USART_HWCONTROL_NONE);
	LL_USART_SetBaudRate(USART1, SystemCoreClock, 115200);

	//Configure UART Interrupts
//	LL_USART_EnableIT_ERROR(USART1);
//	LL_USART_EnableIT_RXNE(USART1);
//	LL_USART_EnableIT_TC(USART1);
//	LL_USART_EnableIT_TXE(USART1);

	//Enable UART
	LL_USART_Enable(USART1);
}


void UART1Write(uint8_t ch) {
	LL_USART_TransmitData8(USART1, (uint8_t) ch);
    //Loop until the end of transmission
    while(!LL_USART_IsActiveFlag_TC(USART1));
}
