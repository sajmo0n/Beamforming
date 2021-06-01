/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
uint16_t Reflection1_detected = 0;
uint16_t Reflection2_detected = 0;
uint16_t Reflection3_detected = 0;
uint16_t Reflection1_time = 0;
uint16_t Reflection2_time = 0;
uint16_t Reflection3_time = 0;
uint16_t TempDelay = 0;
uint16_t Transmitter_delay = 0;
uint8_t First_left_transmitter = 1;
float Distance1 = 0;
float Distance2 = 0;
float Distance3 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim1, 0);  // set the counter value a 0
	while ((uint16_t) __HAL_TIM_GET_COUNTER(&htim1) < us)
		;  // wait for the counter to reach the us input in the parameter
	TempDelay = (uint16_t) __HAL_TIM_GET_COUNTER(&htim1);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim3);
	HAL_Delay(3000);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		if (First_left_transmitter == 1) {
			if (Transmitter_delay == 0) {
				HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
				delay_us(10);
				HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_RESET);
			} else {
				if (Transmitter_delay > 0 && Transmitter_delay <= 10) {
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
					delay_us(Transmitter_delay);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
					delay_us(10 - Transmitter_delay);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin,
							GPIO_PIN_RESET);
					delay_us(Transmitter_delay);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin,
							GPIO_PIN_RESET);
				}
				if (Transmitter_delay > 10) {
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
					delay_us(10);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin,
							GPIO_PIN_RESET);
					delay_us(Transmitter_delay - 10);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
					delay_us(10);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin,
							GPIO_PIN_RESET);
				}

			}
		} else {
			if (Transmitter_delay == 0) {
				HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
				delay_us(10);
				HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_RESET);
			} else {
				if (Transmitter_delay > 0 && Transmitter_delay <= 10) {
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
					delay_us(Transmitter_delay);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
					delay_us(10 - Transmitter_delay);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin,
							GPIO_PIN_RESET);
					delay_us(Transmitter_delay);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin,
							GPIO_PIN_RESET);
				}
				if (Transmitter_delay > 10) {
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
					delay_us(10);
					HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin,
							GPIO_PIN_RESET);
					delay_us(Transmitter_delay - 10);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
					delay_us(10);
					HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin,
							GPIO_PIN_RESET);

				}

			}

		}
		HAL_Delay(1000);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void) {

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 79;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 65535;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 79;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 79;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, TRIG1_Pin | TRIG2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : TRIG1_Pin TRIG2_Pin */
	GPIO_InitStruct.Pin = TRIG1_Pin | TRIG2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : ECHO1_Pin */
	GPIO_InitStruct.Pin = ECHO1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ECHO1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : ECHO2_Pin */
	GPIO_InitStruct.Pin = ECHO2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ECHO2_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	if (GPIO_Pin == ECHO1_Pin) {
//		__HAL_TIM_SET_COUNTER(&htim2, 0);
//		Reflection1_detected = 1;
//		while (HAL_GPIO_ReadPin(ECHO1_GPIO_Port, ECHO1_Pin) == GPIO_PIN_SET)
//			;
//		Reflection1_time = __HAL_TIM_GET_COUNTER(&htim2);
//		Distance1 = (Reflection1_time * 34) / 1000 / 2;
//		Reflection1_detected = 0;
//
//	}
//	if (GPIO_Pin == ECHO2_Pin) {
//		__HAL_TIM_SET_COUNTER(&htim3, 0);
//		Reflection2_detected = 1;
//		while (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == GPIO_PIN_SET)
//			;
//		Reflection2_time = __HAL_TIM_GET_COUNTER(&htim3);
//		Distance2 = (Reflection2_time * 34) / 1000 / 2;
//		Reflection2_detected = 0;
//
//	}

	if (GPIO_Pin == ECHO1_Pin) {
		if (HAL_GPIO_ReadPin(ECHO1_GPIO_Port, ECHO1_Pin) == GPIO_PIN_SET) {
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			Reflection1_detected = 1;
		}
		if (HAL_GPIO_ReadPin(ECHO1_GPIO_Port, ECHO1_Pin) == GPIO_PIN_RESET) {
			Reflection1_time = __HAL_TIM_GET_COUNTER(&htim2);
			Distance1 = (Reflection1_time * 34) / 1000 / 2;
			Reflection1_detected = 0;
		}
	}

	if (GPIO_Pin == ECHO2_Pin) {
		if (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == GPIO_PIN_SET) {
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			Reflection2_detected = 1;
		}
		if (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == GPIO_PIN_RESET) {
			Reflection2_time = __HAL_TIM_GET_COUNTER(&htim3);
			Distance2 = (Reflection2_time * 34) / 1000 / 2;
			Reflection2_detected = 0;
		}
	}
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
