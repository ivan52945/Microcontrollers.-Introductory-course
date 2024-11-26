/*
 * segment_indicator.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Nemicus
 */

#include <stdint.h>
#include "segment_indicator.h"
#include "stm32f4xx_hal.h"
#include "gpio_custom.h"

/*
 * @brief Init segment indicator ports and pins
 * @param Segment special structure, that stores ports, masks, dictionary for segments and array of rank pins
 *
 * @retval None
 */
void init_indicator(segments_status_t* segment)
{
	segment->ranks_mask = 0;

	for (uint32_t i = 0; i < segment->ranks_n; i++){
		segment->ranks_mask |= segment->ranks_pins[i];
	}

	segment->digits_mask = 0;

	for (uint32_t i = 0; i < segment->digits_n; i++){
		segment->digits_mask |= segment->digits_pins[i];
	}

	segment->digits_mask |= segment->point_pin;

	init_gpio_out(segment->ranks_port, segment->ranks_mask);

	init_gpio_out(segment->digits_port, segment->digits_mask);
}

/*
 * @brief Additional function for dividing numbers into digits and converting digits into sets of required pins
 * @param num Divided number
 * @param divided_num Struct, that contains current displayed number and array of pin sets
 * @param segment Structure, contained dictionary for converting digits to pin sets
 *
 * @retval None
 */
void divide_num(uint32_t num, divided_num_t* divided_num, segments_status_t* segment)
{
	if(num == divided_num->cur_num)
		return;

	divided_num->cur_num = num;

	for (uint32_t i = 0; i < divided_num->ranks_n; i++){
		divided_num->converted_digits[i] = segment->digits_pins[num % 10];
		num /= 10;
	}
}

/*
 * @brief Additional function for dividing float numbers into digits and converting digits into sets of required pins
 * @param acc num of digits after point
 * @param num Divided number
 * @param divided_num Struct, that contains current displayed number and array of pin sets
 * @param segment Structure, contained dictionary for converting digits to pin sets
 *
 * @retval None
 */
void divide_num_f(float num, uint32_t acc, divided_num_t* divided_num, segments_status_t* segment)
{
	for(int i = 0; i < acc; i++)
		num *= 10;

	divide_num(num, divided_num, segment);
	divided_num->num_type = FLOAT;

	if(acc > 0 && acc < divided_num->ranks_n)
		divided_num->converted_digits[acc] |= segment->point_pin;
}

/*
 * @brief Display converted digit on selected rank
 * @param segment Structure, that contained all necessary data about segment indicator
 * @param converted_digit Digit, that has been converted to set of pins
 * @param rank Selected for displaying rank
 *
 * @retval None
 */
void display_digit(segments_status_t* segment, uint16_t converted_digit, uint16_t rank)
{
	HAL_GPIO_WritePin(segment->ranks_port, segment->ranks_mask, 0);
	HAL_GPIO_WritePin(segment->digits_port, segment->digits_mask, 0);
	HAL_GPIO_WritePin(segment->digits_port, converted_digit, 1);
	HAL_GPIO_WritePin(segment->ranks_port, segment->ranks_pins[rank], 1);
}

/*
 * @brief Display full number on segment indicator
 * @param segment Structure, that contained all necessary data about segment indicator
 * @param num Necessary number for displaying
 * @param divided_num Current displayed number and array of pin sets
 *
 * @retval None
 */
void display_num(segments_status_t* segment, uint32_t num, divided_num_t* divided_num)
{
	divide_num(num, divided_num, segment);

	for(uint32_t i = 0; i < divided_num->ranks_n; i++){
		display_digit(segment, divided_num->converted_digits[i], segment->ranks_pins[i]);
		HAL_Delay(5);
	}
}
