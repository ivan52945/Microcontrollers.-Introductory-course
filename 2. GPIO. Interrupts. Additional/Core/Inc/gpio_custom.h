/*
 * gpio_custom.h
 *
 *  Created on: Oct 14, 2024
 *      Author: Nemicus
 */

#ifndef INC_GPIO_CUSTOM_H_
#define INC_GPIO_CUSTOM_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

void init_gpio_out(GPIO_TypeDef* port, uint16_t pins);

#endif /* INC_GPIO_CUSTOM_H_ */
