/*
 * led.c
 *
 *  Created on: 13 окт. 2024 г.
 *      Author: Nemicus
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "led.h"

void init_led(GPIO_TypeDef* port, uint16_t pin)
{
	if(port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else // А что — иначе? Наверное, имеет смысл либо возвращать ошибку, либо ничего не делать, либо инициализировать оставшийся порт.
		__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


