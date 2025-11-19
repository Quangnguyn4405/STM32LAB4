/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "software_timer.h"
#include "global.h"

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
// Task IDs
uint32_t taskID_ReadButtons;
uint32_t taskID_RunFSM;
uint32_t taskID_Update7SEG;
uint32_t taskID_TimerRun;
uint32_t taskID_TestLED;

// Demo task IDs
uint32_t taskID_500ms;
uint32_t taskID_1000ms;
uint32_t taskID_1500ms;
uint32_t taskID_2000ms;
uint32_t taskID_2500ms;


int SEG_index = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
// Task function prototypes
void Task_ReadButtons(void);
void Task_RunFSM(void);
void Task_Update7SEG(void);
void Task_TimerRun(void);
void Task_TestLED(void);

// Demo task prototypes
void Task_500ms(void);
void Task_1000ms(void);
void Task_1500ms(void);
void Task_2000ms(void);
void Task_2500ms(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * Task đọc nút nhấn - chạy mỗi 10ms
 */
void Task_ReadButtons(void) {
    getKeyInput();
}

/**
 * Task chạy FSM - chạy mỗi 10ms
 */
void Task_RunFSM(void) {
    if (status == INIT || status == RED_GREEN || status == RED_AMBER ||
        status == GREEN_RED || status == AMBER_RED) {
        fsm_automatic_run();
    } else if (status == RED_MODE || status == AMBER_MODE || status == GREEN_MODE) {
        fsm_manual_run();
    }
}

/**
 * Task update 7-segment
 */
void Task_Update7SEG(void) {
    // Reset index
    if (SEG_index == 0 || SEG_index == 2) {
        clearENs();
    }
    // Update
    update7SEG(SEG_index);

    SEG_index++;
    if (SEG_index >= 4) {
        SEG_index = 0;
    }
}

/**
 * Task chạy software timer
 */
void Task_TimerRun(void) {
    timerRun();
}

/**
 * Task test LED
 */
void Task_TestLED(void) {
    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

/**
 * Demo Task 1: Chạy mỗi 500ms
 */
void Task_500ms(void) {
    static uint32_t counter = 0;
    counter++;
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
}

/**
 * Demo Task 2: Chạy mỗi 1000ms
 */
void Task_1000ms(void) {
    static uint32_t counter = 0;
    counter++;
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
}

/**
 * Demo Task 3: Chạy mỗi 1500ms
 */
void Task_1500ms(void) {
    static uint32_t counter = 0;
    counter++;
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
}

/**
 * Demo Task 4: Chạy mỗi 2000ms
 */
void Task_2000ms(void) {
    static uint32_t counter = 0;
    counter++;
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

/**
 * Demo Task 5: Chạy mỗi 2500ms
 */
void Task_2500ms(void) {
    static uint32_t counter = 0;
    counter++;
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}

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
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  // Khởi tạo scheduler
  SCH_Init();

  // Task đọc button - chạy mỗi 100ms (1 tick)
  taskID_ReadButtons = SCH_Add_Task(Task_ReadButtons, 0, 1);

  // Task chạy FSM - chạy mỗi 100ms (1 tick)
  taskID_RunFSM = SCH_Add_Task(Task_RunFSM, 0, 1);

  // Task update 7-segment - chạy mỗi 100ms (1 ticks)
  taskID_Update7SEG = SCH_Add_Task(Task_Update7SEG, 0, 1);

  // Task timer run - chạy mỗi 10ms (1 tick)
  taskID_TimerRun = SCH_Add_Task(Task_TimerRun, 0, 1);

  // Task test LED - chạy mỗi 1000ms (10 ticks)
  taskID_TestLED = SCH_Add_Task(Task_TestLED, 0, 10);

  // Task 1: 500ms = 5 ticks
  taskID_500ms = SCH_Add_Task(Task_500ms, 0, 5);

  // Task 2: 1000ms = 10 ticks
  taskID_1000ms = SCH_Add_Task(Task_1000ms, 1, 10);

  // Task 3: 1500ms = 15 ticks
  taskID_1500ms = SCH_Add_Task(Task_1500ms, 2, 15);

  // Task 4: 2000ms = 20 ticks
  taskID_2000ms = SCH_Add_Task(Task_2000ms, 3, 20);

  // Task 5: 2500ms = 25 ticks
  taskID_2500ms = SCH_Add_Task(Task_2500ms, 4, 25);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    SCH_Dispatch_Tasks();

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

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;  // 8MHz/8000 = 1kHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;         // 1kHz/10 = 100Hz = 10ms
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|RED_1_Pin|AMBER_1_Pin|GREEN_1_Pin
                          |RED_2_Pin|AMBER_2_Pin|GREEN_2_Pin|EN0_Pin
                          |EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG2_3_Pin
                          |SEG2_4_Pin|SEG2_5_Pin|SEG2_6_Pin|SEG1_3_Pin
                          |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin|SEG2_0_Pin
                          |SEG2_1_Pin|SEG2_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUTTON_0_Pin */
  GPIO_InitStruct.Pin = BUTTON_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_1_Pin BUTTON_2_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin|BUTTON_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin RED_1_Pin AMBER_1_Pin GREEN_1_Pin
                           RED_2_Pin AMBER_2_Pin GREEN_2_Pin EN0_Pin
                           EN1_Pin EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|RED_1_Pin|AMBER_1_Pin|GREEN_1_Pin
                          |RED_2_Pin|AMBER_2_Pin|GREEN_2_Pin|EN0_Pin
                          |EN1_Pin|EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG1_0_Pin SEG1_1_Pin SEG1_2_Pin SEG2_3_Pin
                           SEG2_4_Pin SEG2_5_Pin SEG2_6_Pin SEG1_3_Pin
                           SEG1_4_Pin SEG1_5_Pin SEG1_6_Pin SEG2_0_Pin
                           SEG2_1_Pin SEG2_2_Pin */
  GPIO_InitStruct.Pin = SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG2_3_Pin
                          |SEG2_4_Pin|SEG2_5_Pin|SEG2_6_Pin|SEG1_3_Pin
                          |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin|SEG2_0_Pin
                          |SEG2_1_Pin|SEG2_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
 * Timer interrupt callback - Gọi SCH_Update mỗi 10ms
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2) {
        SCH_Update();
    }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
