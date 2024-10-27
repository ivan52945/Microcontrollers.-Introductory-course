/*
 * parsing_command.c
 *
 *  Created on: Oct 26, 2024
 *      Author: Nemicus
 */

#include <stdio.h>
#include <string.h>
#include "parsing_command.h"
#include <stdint.h>
#include "usbd_cdc_if.h"

static rx_res_t rx_status;

int _write(int file, char* buf, int len)
{
	CDC_Transmit_FS((uint8_t*)buf, len);
	return len;
}

adr_command_t parse_command(const uint8_t command_s[], uint32_t n)
{
	adr_command_t command = {
			.cmd = WRONG_COMMAND,
			.addr = 0,
			.n = 0
	};

	if(!((uint8_t*)strstr((char*)command_s, "get_hex ") - command_s)){ // if command correct and stayed in begining
		unsigned int addr = 0;
		unsigned int n = 0;
		if(sscanf((char*)command_s, "get_hex %x %u\n", &addr, &n) == 2){
			command.cmd = GET_VALUE;
			command.addr = (uint8_t*)addr;
			command.n = n;
			return command;
		}
		puts("Wrong parameters for get_hex command");
		return command;
	}
	puts("Wrong command");
	return command;
}

static uint8_t get_checkSum(char str[], uint32_t n)
{
	uint8_t sum = 0;

	unsigned int byte;

	for(uint32_t i = 1; i < n && str[i]; i += 2){
		sscanf(str + i, "%02X", &byte);
		sum -= byte;
	}

	return sum;
}

static void create_addr_hex(char str[], uint8_t addr[])
{
	uint16_t first = (uint32_t)addr >> 16;

	uint32_t l = sprintf(str, ":02000004%04X", first);

	uint8_t checksum = get_checkSum(str, l);

	sprintf(str + l, "%02X", checksum);
}

static void create_main_data_hex(char str[], uint8_t addr[], uint32_t n)
{
	uint32_t last = (uint32_t)addr & 0xFFFF;

	uint32_t l = sprintf(str, ":%02X%04X00", (unsigned int)n, (unsigned int)last);

	for(uint32_t i = 0; i < n; i++)
		l += sprintf(str + l, "%02X", addr[i]);

	uint8_t checksum = get_checkSum(str, n);

	sprintf(str + l, "%02X", checksum);
}

static void create_finish_hex(char str[]){
	sprintf(str, ":00000001FF");
}

void transmit_intel_hex_values(uint8_t addr[], uint32_t n)
{
	char str[60] = {0};

	uint32_t first_part_addr = 0;
	uint32_t fist_part_add_curr;

	for(int64_t i = n; i > 0; i -= 16){

		fist_part_add_curr = (uint32_t)addr >> 16;

		if(fist_part_add_curr != first_part_addr){
			create_addr_hex(str, addr);
			first_part_addr = fist_part_add_curr;
			printf("%s\n", str);
		}

		create_main_data_hex(str, addr, (i > 16) ? 16 : i);
		printf("%s\n", str);
	}

	create_finish_hex(str);
	printf("%s\n", str);
}

void execute_command(adr_command_t command)
{
	switch(command.cmd){
		case GET_VALUE:
			transmit_intel_hex_values(command.addr, command.n);
			break;
		case WRONG_COMMAND:
			break;
	}
}

rx_res_t* get_rx_status()
{
	return &rx_status;
}
