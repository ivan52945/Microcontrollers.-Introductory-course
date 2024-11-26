/*
 * ram_disk.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Nemicus
 */

#include "ram_disk.h"
#include <stdint.h>
#include <string.h>

static uint8_t ram_disk[SECTOR_N][SECTOR_L] = {0};

uint8_t (*get_ram_disk(void))[SECTOR_L]
{
	return ram_disk;
}

void format_ram_disk()
{
	uint8_t* clean_fs = (uint8_t*)0x8020000;

	memcpy(ram_disk, clean_fs, SECTOR_N * SECTOR_L);
}

void read_ram_disk(uint8_t target[], int sector, int count)
{
	memcpy(target, &ram_disk[sector], SECTOR_L * count);
}

void write_ram_disk(const uint8_t src[], int sector, int count)
{
	memcpy(&ram_disk[sector], src, SECTOR_L * count);
}
