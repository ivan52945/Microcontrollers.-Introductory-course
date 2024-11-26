/*
 * ram_disk.h
 *
 *  Created on: Nov 6, 2024
 *      Author: Nemicus
 */

#ifndef INC_RAM_DISK_H_
#define INC_RAM_DISK_H_

#include <stdint.h>

#define SECTOR_N 74
#define SECTOR_L 512

uint8_t (*get_ram_disk(void))[SECTOR_L];

void format_ram_disk();

void read_ram_disk(uint8_t target[], int sector, int count);

void write_ram_disk(const uint8_t src[], int sector, int count);

#endif /* INC_RAM_DISK_H_ */
