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

	switch(pin){
		case GPIO_PIN_0:
			HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);
			break;
		case GPIO_PIN_1:
			HAL_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI1_IRQn);
			break;
		case GPIO_PIN_2:
			HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI2_IRQn);
			break;
		case GPIO_PIN_3:
			HAL_NVIC_SetPriority(EXTI3_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI3_IRQn);
			break;
		case GPIO_PIN_4:
			HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI4_IRQn);
			break;
		case GPIO_PIN_5:
		case GPIO_PIN_6:
		case GPIO_PIN_7:
		case GPIO_PIN_8:
		case GPIO_PIN_9:
			HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
			break;
		case GPIO_PIN_10:
		case GPIO_PIN_11:
		case GPIO_PIN_12:
		case GPIO_PIN_13:
		case GPIO_PIN_14:
		case GPIO_PIN_15:
			HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
			HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
			break;
	}
}


