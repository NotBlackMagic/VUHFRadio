#ifndef HAL_TIM_H_
#define HAL_TIM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

void TIM3Init();

void TIM3SetFreq(uint32_t freq);

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIM_H_ */
