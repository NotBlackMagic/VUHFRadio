#ifndef UART_H_
#define UART_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"

void UART1Init(void);
void UART2Init(void);
void UART1Write(uint8_t ch);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
