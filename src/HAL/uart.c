#include "uart.h"

#define UART_RX_BUFFER_SIZE									128
#define UART_TX_BUFFER_SIZE									128

uint16_t uart1RXBufferIndex;
uint16_t uart1RXBufferLength;
uint8_t uart1RXBuffer[UART_RX_BUFFER_SIZE];
uint16_t uart1TXBufferIndex;
uint16_t uart1TXBufferLength;
uint8_t uart1TXBuffer[UART_TX_BUFFER_SIZE];

/**
  * @brief	This function initializes the UART1 interface, also sets the respective GPIO pins
  * @param	baud: UART Baud rate to use
  * @return	None
  */
void UART1Init(uint32_t baud) {
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
	LL_USART_SetBaudRate(USART1, SystemCoreClock, baud);

	//Configure UART Interrupts
	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);
	LL_USART_EnableIT_RXNE(USART1);
	LL_USART_EnableIT_IDLE(USART1);
//	LL_USART_EnableIT_TXE(USART1);

	//Enable UART
	LL_USART_Enable(USART1);
}

/**
  * @brief	This function sets the UART1 Baudrate
  * @param	baudrate: The baudrate to use/set
  * @return	None
  */
void UART1SetBaudrate(uint32_t baudrate) {
	LL_USART_SetBaudRate(USART1, SystemCoreClock, baudrate);
}


/**
  * @brief	This function sends data over UART1
  * @param	data: data array to transmit
  * @param	length: length of the transmit data array
  * @return	0 -> if all good, no errors; 1 -> TX Buffer is full
  */
uint8_t UART1Write(uint8_t* data, uint16_t length) {
	if(uart1TXBufferLength == 0x00) {
		uint16_t i;
		for(i = 0; i < length; i++) {
			uart1TXBuffer[i] = data[i];
		}

		uart1TXBufferLength = length;
		uart1TXBufferIndex = 0;

		LL_USART_TransmitData8(USART1, uart1TXBuffer[uart1TXBufferIndex++]);

		LL_USART_EnableIT_TXE(USART1);
	}
	else {
		//Buffer full, return error
		return 1;
	}

	return 0;
}

/**
  * @brief	This function reads the UART1 RX buffer
  * @param	data: data array to where the received data should be copied to
  * @param	length: length of the received array, is set in this function
  * @return	Returns 0 if no new data, 1 if new data
  */
uint8_t UART1Read(uint8_t* data, uint16_t* length) {
	if(uart1RXBufferLength > 0) {
		uint16_t i;
		for(i = 0; i < uart1RXBufferLength; i++) {
			data[i] = uart1RXBuffer[i];
		}

		*length = uart1RXBufferLength;

		uart1RXBufferLength = 0;
		uart1RXBufferIndex = 0;

		return 1;
	}
	else {
		return 0;
	}
}

/**
  * @brief	UART1 IRQ Handler
  * @param	None
  * @return	None
  */
void USART1_IRQHandler(void) {
	if(LL_USART_IsEnabledIT_TXE(USART1) == 0x01 && LL_USART_IsActiveFlag_TXE(USART1) == 0x01) {
		if(uart1TXBufferIndex >= uart1TXBufferLength) {
			//Transmission complete
			uart1TXBufferLength = 0;
			uart1TXBufferIndex = 0;

			//Disable TX done interrupt
			LL_USART_DisableIT_TXE(USART1);
		}
		else {
			//Transmit another byte
			LL_USART_TransmitData8(USART1, uart1TXBuffer[uart1TXBufferIndex++]);
		}
	}

	if(LL_USART_IsActiveFlag_RXNE(USART1) == 0x01) {
		if(uart1RXBufferLength != 0x00) {
			//RX Buffer full, has a complete frame in it
			uint8_t dummy = LL_USART_ReceiveData8(USART1);
		}
		else if(uart1RXBufferIndex >= UART_RX_BUFFER_SIZE) {
			//RX Buffer overflow
			uint8_t dummy = LL_USART_ReceiveData8(USART1);

			uart1RXBufferIndex = 0;
		}
		else {
			//All good, read received byte to RX buffer
			uart1RXBuffer[uart1RXBufferIndex++] = LL_USART_ReceiveData8(USART1);
		}
	}

	if(LL_USART_IsActiveFlag_IDLE(USART1) == 0x01) {
		//End of frame transmission, detected by receiver timeout
		uart1RXBufferLength = uart1RXBufferIndex;

		//Clear IDLE Flag
		LL_USART_ClearFlag_IDLE(USART1);
	}
}
