/*
 * segment_indicator.h
 *
 *  Created on: Oct 14, 2024
 *      Author: Nemicus
 */

#ifndef INC_SEGMENT_INDICATOR_H_
#define INC_SEGMENT_INDICATOR_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef enum {
	INT,
	FLOAT
} number_type;

/*
 * @brief Structure, contains cached number and array of pin sets
 */
typedef struct {
	number_type num_type;           // type of displayed number
	uint32_t cur_num;				// cached number
	uint16_t* converted_digits;		// array of bit sets
	uint32_t ranks_n;				// number of ranks
} divided_num_t;

/*
 * @brief Structure, contains info about ports and pins for segments, and dictionary of digits
 */
typedef struct {
	GPIO_TypeDef* ranks_port;	// rank port

	uint32_t ranks_n;			// count of ranks
	uint16_t* ranks_pins;		// array of rank pins
	uint16_t ranks_mask;		// all rank pins. Used for erasing ranks

	GPIO_TypeDef* digits_port;	// digits port

	uint32_t digits_n;			// number of used digits
	uint16_t point_pin;
	uint16_t* digits_pins;		// array, used for converting digits into pins
	uint16_t digits_mask;		// all digits_pins. Used for erasing digits
} segments_status_t;

void init_indicator(segments_status_t* segment);

void display_digit(segments_status_t* segment, uint16_t converted_digit, uint16_t rank);

void divide_num(uint32_t num, divided_num_t* divided_num, segments_status_t* segment);

void divide_num_f(float num, uint32_t acc, divided_num_t* divided_num, segments_status_t* segment);

void display_num(segments_status_t* segment, uint32_t num, divided_num_t* divided_num);

#endif /* INC_SEGMENT_INDICATOR_H_ */
