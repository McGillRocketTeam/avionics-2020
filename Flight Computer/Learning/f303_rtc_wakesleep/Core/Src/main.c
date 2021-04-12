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
#include <stdio.h>
#include <string.h>
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
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
// rtc variables
RTC_DateTypeDef sdatestructureget;
RTC_TimeTypeDef stimestructureget;
RTC_AlarmTypeDef sAlarmA;
RTC_AlarmTypeDef sAlarmB;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
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
  MX_USART2_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  // reset LED
  HAL_GPIO_WritePin(LED_Output_GPIO_Port, LED_Output_Pin, RESET);

  /** Set the RTC Time and Date		 */
    stimestructureget.Hours = 0x11;
    stimestructureget.Minutes = 0x11;
    stimestructureget.Seconds = 0x00;
    stimestructureget.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    stimestructureget.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &stimestructureget, RTC_FORMAT_BCD) != HAL_OK)
    {
  	  Error_Handler();
    }
    sdatestructureget.WeekDay = RTC_WEEKDAY_MONDAY;
    sdatestructureget.Month = RTC_MONTH_APRIL;
    sdatestructureget.Date = 0x12;
    sdatestructureget.Year = 0x21;

    if (HAL_RTC_SetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BCD) != HAL_OK)
    {
  	  Error_Handler();
    }

    /** Enable the Alarm A */
    sAlarmA.AlarmTime.Hours = 0x11;
    sAlarmA.AlarmTime.Minutes = 0x11;
    sAlarmA.AlarmTime.Seconds = 0x30;
    sAlarmA.AlarmTime.SubSeconds = 0x0;
    sAlarmA.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarmA.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarmA.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY; // make alarm occur every day at specified time
    sAlarmA.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    sAlarmA.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarmA.AlarmDateWeekDay = 0x1;
    sAlarmA.Alarm = RTC_ALARM_A;
    if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarmA, RTC_FORMAT_BCD) != HAL_OK)
    {
  	Error_Handler();
    }
    /** Enable the Alarm B */
    sAlarmB.AlarmTime.Hours = 0x11;
    sAlarmB.AlarmTime.Minutes = 0x11;
    sAlarmB.AlarmTime.Seconds = 0x45;
    sAlarmB.AlarmTime.SubSeconds = 0x0;
    sAlarmB.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarmB.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarmB.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY; // make alarm occur every day at specified time
    sAlarmB.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    sAlarmB.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarmB.AlarmDateWeekDay = 0x1;
    sAlarmB.Alarm = RTC_ALARM_B;
    if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarmB, RTC_FORMAT_BCD) != HAL_OK)
    {
  	  Error_Handler();
    }

    /** Enable the WakeUp */
    if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
    {
  	  Error_Handler();
    }






//  HAL_RTC_SetAlarm_IT(&hrtc, sAlarm, Format);

  // necessary functions (HAL manual p319 ish, section 33)
//  HAL_PWR_EnterSTANDBYMode(); // use wfi = wait for interrupt. intention is to use rtc alarm to wake/sleep
//  HAL_RTC_SetAlarm_IT();
//  HAL_RTC_ReadAlarm();

//  if (__HAL_PWR_GET_FLAG(PWR_FLAG_WU)) {
//	  uint8_t msg = "woke from low power mode";
//	  HAL_UART_Transmit(&huart3, msg, strlen((char const *)msg), 1000);
//  }

//  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU); // clear the wakeup flag

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // if this loop is entered, blink led really fast
	  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
	  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);

	  uint8_t tx_buffer[1000];
	  sprintf((char *)tx_buffer, "TIME -- Hour:%hu\t\t Minute:%hu\t Second:%hu\n\n", (uint16_t)stimestructureget.Hours, (uint16_t)stimestructureget.Minutes, (uint16_t)stimestructureget.Seconds);
	  HAL_UART_Transmit(&huart2, tx_buffer, strlen((char const *) tx_buffer), 1000);
	  HAL_GPIO_TogglePin(LED_Output_GPIO_Port, LED_Output_Pin);
	  HAL_Delay(100);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */
#ifdef	NEVER_DEF
  /** Initialize RTC and set the Time and Date
  */
  stimestructureget.Hours = 0x0;
  stimestructureget.Minutes = 0x15;
  stimestructureget.Seconds = 0x22;
  stimestructureget.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  stimestructureget.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &stimestructureget, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sdatestructureget.WeekDay = RTC_WEEKDAY_MONDAY;
  sdatestructureget.Month = RTC_MONTH_APRIL;
  sdatestructureget.Date = 0x12;
  sdatestructureget.Year = 0x21;

  if (HAL_RTC_SetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm A
  */
  sAlarmA.AlarmTime.Hours = 0x0;
  sAlarmA.AlarmTime.Minutes = 0x30;
  sAlarmA.AlarmTime.Seconds = 0x0;
  sAlarmA.AlarmTime.SubSeconds = 0x0;
  sAlarmA.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarmA.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarmA.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarmA.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarmA.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarmA.AlarmDateWeekDay = 0x1;
  sAlarmA.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarmA, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm B
  */
  sAlarmB.AlarmTime.Hours = 0x12;
  sAlarmB.AlarmTime.Minutes = 0x0;
  sAlarmB.Alarm = RTC_ALARM_B;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarmB, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_Output_GPIO_Port, LED_Output_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Output_Pin */
  GPIO_InitStruct.Pin = LED_Output_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_Output_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

// Callbacks
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
	// transmit over UART2 to indicate callback happened
	uint8_t msg[100];
	sprintf((char *)msg, "Alarm A callback entered\n");
	for (int i = 0; i < 5; i++)
		HAL_UART_Transmit(&huart2, msg, strlen((char const *)msg), 1000);
	//HAL_Delay(1000); // wait one second
}

void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc) {
	// transmit over UART2 to indicate callback happened
	uint8_t msg[100];
	sprintf((char *)msg, "Alarm B callback entered\n");
	for (int i = 0; i < 5; i++)
		HAL_UART_Transmit(&huart2, msg, strlen((char const *)msg), 1000);
	//HAL_Delay(1000); // wait one second
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
