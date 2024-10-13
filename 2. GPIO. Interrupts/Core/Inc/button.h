/*
 * button.h
 *
 *  Created on: 13 окт. 2024 г.
 *      Author: Nemicus
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#define BTN_Pin GPIO_PIN_9
#define BTN_GPIO_Port GPIOA

void init_button(GPIO_TypeDef* port, uint16_t pin);

#endif /* INC_BUTTON_H_ */
