#ifndef HAL_SPI_H_
#define HAL_SPI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_spi.h"

void SPI1Init();
uint8_t SPI1ReadWrite(uint8_t txByte);
void SPI2Init();
uint8_t SPI2ReadWrite(uint8_t txByte);

#ifdef __cplusplus
}
#endif

#endif /* HAL_SPI_H_ */
