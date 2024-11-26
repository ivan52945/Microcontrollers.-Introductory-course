/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_SPI1_Init(void);
void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */

HAL_StatusTypeDef MX_SPI2_Receive_IT(uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef MX_SPI1_Transmit(uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef MX_SPI1_Transmit_IT(uint8_t *pData, uint16_t Size);

SPI_HandleTypeDef* SPI1_Struct(void);

SPI_HandleTypeDef* SPI2_Struct(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

