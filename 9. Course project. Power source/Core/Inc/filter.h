/*
 * filter.h
 *
 *  Created on: 22 нояб. 2024 г.
 *      Author: Nemicus
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

typedef struct {
	float k_l;
	uint16_t curr;
} filter_stat_t;

uint16_t filter(filter_stat_t* status, uint16_t input);

#endif /* INC_FILTER_H_ */
