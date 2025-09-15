/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */
  MX_GPIO_Init();
  int state1, state2, counter1, counter2;
  //state: red = 0, green = 1, yellow = 2
  state1 = 0;
  state2 = 1;
  counter1 = counter2 = 0;
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    if(state1 == 0 && counter1 == 5){
        state1 = 1;
        counter1 = 0;
    }
    else if(state1 == 1 && counter1 == 3){
        state1 = 2;
        counter1 = 0;
    }
    else if(state1 == 2 && counter1 == 2){
        state1 = 0;
        counter1 = 0;
    }

    if(state2 == 0 && counter2 == 5){
        state2 = 1;
        counter2 = 0;
    }
    else if(state2 == 1 && counter2 == 3){
        state2 = 2;
        counter2 = 0;
    }
    else if(state2 == 2 && counter2 == 2){
        state2 = 0;
        counter2 = 0;
    }
    
    switch (state1)
    {
    case 0:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7, SET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6, SET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_7, SET);
        break;
    default:
        break;
    }

    switch (state2)
    {
    case 0:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, SET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, SET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_10, SET);
        break;
    default:
        break;
    }
    HAL_Delay(1000);
    counter1++;
    counter2++;
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

/* USER CODE BEGIN 4 */
void MX_GPIO_Init(void){
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef init = {0};
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
  init.Pull = GPIO_PULLDOWN;
  init.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &init);
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
#ifdef USE_FULL_ASSERT
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
