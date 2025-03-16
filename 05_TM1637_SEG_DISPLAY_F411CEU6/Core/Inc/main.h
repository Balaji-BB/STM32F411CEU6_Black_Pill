/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ON_BOARD_LED_Pin GPIO_PIN_13
#define ON_BOARD_LED_GPIO_Port GPIOC
#define DOWN_BTN_Pin GPIO_PIN_1
#define DOWN_BTN_GPIO_Port GPIOA
#define DOWN_BTN_EXTI_IRQn EXTI1_IRQn
#define UP_BTN_Pin GPIO_PIN_2
#define UP_BTN_GPIO_Port GPIOA
#define UP_BTN_EXTI_IRQn EXTI2_IRQn
#define CENTER_BTN_Pin GPIO_PIN_3
#define CENTER_BTN_GPIO_Port GPIOA
#define CENTER_BTN_EXTI_IRQn EXTI3_IRQn
#define LEFT_BTN_Pin GPIO_PIN_4
#define LEFT_BTN_GPIO_Port GPIOA
#define LEFT_BTN_EXTI_IRQn EXTI4_IRQn
#define RIGHT_BTN_Pin GPIO_PIN_5
#define RIGHT_BTN_GPIO_Port GPIOA
#define RIGHT_BTN_EXTI_IRQn EXTI9_5_IRQn
#define CS_Pin GPIO_PIN_12
#define CS_GPIO_Port GPIOA
#define TM1637_CLK_Pin GPIO_PIN_8
#define TM1637_CLK_GPIO_Port GPIOB
#define TM1637_DIO_Pin GPIO_PIN_9
#define TM1637_DIO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
