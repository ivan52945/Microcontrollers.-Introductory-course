/*
 * button.c
 *
 *  Created on: Oct 13, 2024
 *      Author: Nemicus
 */
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "button.h"

void init_button(GPIO_TypeDef* port, uint16_t pin)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else
		__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}


