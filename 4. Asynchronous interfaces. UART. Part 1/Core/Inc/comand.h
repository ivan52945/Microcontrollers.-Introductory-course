/*
 * comand.h
 *
 *  Created on: Oct 24, 2024
 *      Author: Nemicus
 */

#ifndef INC_COMAND_H_
#define INC_COMAND_H_

#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB

typedef enum {
	LED_ON = 0,
	LED_OFF = 1,
	LED_TOGGLE = 2,
	NO_OP
} comand_out_t;

comand_out_t parse_text_comand(uint8_t comand[], uint32_t n);

void execute_comand(comand_out_t comand);

#endif /* INC_COMAND_H_ */
