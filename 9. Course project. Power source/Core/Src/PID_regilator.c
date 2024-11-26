/*
 * PID_regilator.c
 *
 *  Created on: 21 нояб. 2024 г.
 *      Author: Nemicus
 */
#include "stdint.h"
#include "PID_regulator.h"

float range(float input, float min, float max)
{
	if(input < min)
		return min;
	if(input > max)
		return max;
	return input;
}

int PID_regulation(reg_stat_t* regulator, int target, int feedback, float output)
{
	int min = regulator->min;
	int max = regulator->max;

	int diff = target - feedback;

	float result = output + regulator->kp * diff;

	regulator->int_part += diff * regulator->ki * regulator->prd;

	regulator->int_part = range(regulator->int_part, min, max);

	float diff_error = regulator->kd *(diff - regulator->prew_dif);

	diff_error = range(diff_error, min, max);

	regulator->prew_dif = diff;

	result += regulator->int_part;

	result += diff_error;

	result = range(result, min, max) + 0.5;

	return result;
}
