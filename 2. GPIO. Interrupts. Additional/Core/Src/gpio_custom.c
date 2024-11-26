/*
 * gpio_custom.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Nemicus
 */
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "gpio_custom.h"

/*
 * @brief Init pin or group of pins  on gpio in output mode
 * @param port with necessary bit or bits
 * @param selected pin or pin
 *
 * @retval None
 */

void init_gpio_out(GPIO_TypeDef* port, uint16_t pins)
{
	if(port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else // Аналогично init_led ??
		__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(port, pins, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = pins;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}
