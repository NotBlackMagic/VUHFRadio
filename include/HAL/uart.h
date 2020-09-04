#ifndef UART_H_
#define UART_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"

void UART1Init(uint32_t baud);
void UART1SetBaudrate(uint32_t baudrate);
uint8_t UART1Write(uint8_t* data, uint16_t length);
uint8_t UART1Read(uint8_t* data, uint16_t* length);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
