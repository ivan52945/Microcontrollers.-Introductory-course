/*
 * parsing_command.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Nemicus
 */

#ifndef INC_PARSING_COMMAND_H_
#define INC_PARSING_COMMAND_H_

#include <stdint.h>

#define RX_BUFF_LEN 30

typedef struct{
	uint8_t* RxBuff;
	uint8_t isRxCplt;
} rx_res_t;

typedef enum{
	GET_VALUE,
	WRONG_COMMAND
} adr_com_code_t;

typedef struct
{
	adr_com_code_t cmd;
	uint8_t* addr;
	uint16_t n;
} adr_command_t;

adr_command_t parse_command(const uint8_t command_s[], uint32_t n);

void transmit_intel_hex_values(uint8_t addr[], uint32_t n);

void execute_command(adr_command_t command);

rx_res_t* get_rx_status();

#endif /* INC_PARSING_COMMAND_H_ */
