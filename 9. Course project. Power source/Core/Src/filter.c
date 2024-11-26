/*
 * filter.c
 *
 *  Created on: 22 нояб. 2024 г.
 *      Author: Nemicus
 */

#include "stdint.h"
#include "filter.h"

uint16_t filter(filter_stat_t* status, uint16_t input)
{
	float k = status->k_l;

	status->curr = (1 - k) * status->curr + k * input;

	return status->curr ;
}


