/*
 * PID_regulator.h
 *
 *  Created on: 21 нояб. 2024 г.
 *      Author: Nemicus
 */

#ifndef INC_PID_REGULATOR_H_
#define INC_PID_REGULATOR_H_

typedef struct {
	float kp;
	float ki;
	float kd;
	int int_part;
	int prew_dif;
	int prd;
	int min;
	int max;
} reg_stat_t;

float range(float input, float min, float max);

int PID_regulation(reg_stat_t* regulator, int target, int feedback, float output);

#endif /* INC_PID_REGULATOR_H_ */
