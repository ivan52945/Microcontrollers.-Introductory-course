/*
 * text_comand.c
 *
 *  Created on: Oct 23, 2024
 *      Author: Nemicus
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "comand.h"
#include <string.h>

comand_out_t parse_text_comand(uint8_t comand[], uint32_t n)
{
	if(!strncmp((char*)comand, "led on\n", n)){
		return LED_ON;
	}
	if(!strncmp((char*)comand, "led off\n", n)){
		return LED_OFF;
	}
	if(!strncmp((char*)comand, "led toggle\n", n)){
		return LED_TOGGLE;
	}
	return NO_OP;
}

void execute_comand(comand_out_t comand)
{
	switch(comand){
		case LED_ON:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			break;
		case LED_OFF:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			break;
		case LED_TOGGLE:
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
		case NO_OP:
			break;
	}
}
