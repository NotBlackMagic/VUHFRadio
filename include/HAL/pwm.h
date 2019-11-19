#ifndef HAL_PWM_H_
#define HAL_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

void PWM1Init();
void PWM2Init();

#ifdef __cplusplus
}
#endif

#endif /* HAL_PWM_H_ */
