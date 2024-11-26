/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <math.h>
#include "segment_indicator.h"
#include "filter.h"
#include "PID_regulator.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define RANKS_N 3
#define DIGITS_N 10
#define SEGMENTS_GPIO_Port GPIOB
#define SEGMENT_PINS 0x00FF
#define MAX_ADC_VALUE 0xFFF
#define RANKS_GPIO_Port GPIOA

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

int target = 0;

segments_status_t segment = {0};
divided_num_t num_divided = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  uint16_t RANKS[] ={
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12
  };

  uint16_t DIGITS[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

  uint16_t converted_digits[RANKS_N] = {0};

  segment.digits_port = SEGMENTS_GPIO_Port;
  segment.ranks_port = RANKS_GPIO_Port;

  segment.ranks_n = RANKS_N;
  segment.digits_n = DIGITS_N;

  segment.ranks_pins = RANKS;
  segment.digits_pins = DIGITS;
  segment.point_pin = 1 << 7;

  num_divided.cur_num = 0 - 1;
  num_divided.converted_digits = converted_digits;
  num_divided.ranks_n = RANKS_N;

  init_indicator(&segment);

  ADC1_Start_IT();
  TIM4_Base_Start_IT();
  TIM3_PWM_Start();
  TIM1_Encoder_Start();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	static int prew_cnt = -1;
	if(TIM1->CNT != prew_cnt){
		target = (TIM1->CNT / 2 * 100 * MAX_ADC_VALUE) / 3300;
		prew_cnt = TIM1->CNT;
	}
	divide_num_f(round(ADC1_GetValue() * 33.0f / MAX_ADC_VALUE) / 10.0, 1, &num_divided, &segment);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  return 0;
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t rank = 0;

	display_digit(&segment, num_divided.converted_digits[rank],  rank);

	rank = (rank + 1) % num_divided.ranks_n;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	static filter_stat_t filter_stat = {
      .k_l = 0.2f,
	  .curr = 0
	};

    static reg_stat_t regulator = {
      .prew_dif = 0,
      .int_part = 0,
      .kp = 0.040000f,
	  .ki = 0.000000f,
	  .kd = 0.000000f,
      .min = 0,
      .max = 0
	};

    regulator.max = TIM3->ARR + 1;
    regulator.prd = TIM3->ARR + 1;

	uint32_t input =  ADC1_GetValue();

	int filtered = filter(&filter_stat, input);

	TIM3->CCR1 = PID_regulation(&regulator, target, filtered, TIM3->CCR1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
