/*
 * led.h
 *
 *  Created on: 13 окт. 2024 г.
 *      Author: Nemicus
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#define LED_Pin GPIO_PIN_10
#define LED_GPIO_Port GPIOA
#define BTN_Pin GPIO_PIN_11
#define BTN_GPIO_Port GPIOA

void init_led(GPIO_TypeDef* port, uint16_t pin);

#endif /* INC_LED_H_ */
