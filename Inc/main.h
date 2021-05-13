/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f3xx_hal.h"

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
#define R_SS_G_Pin GPIO_PIN_13
#define R_SS_G_GPIO_Port GPIOC
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOF
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOF
#define B_SS_A_Pin GPIO_PIN_0
#define B_SS_A_GPIO_Port GPIOC
#define B_SS_B_Pin GPIO_PIN_1
#define B_SS_B_GPIO_Port GPIOC
#define B_SS_C_Pin GPIO_PIN_2
#define B_SS_C_GPIO_Port GPIOC
#define B_SS_D_Pin GPIO_PIN_3
#define B_SS_D_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define BLUE_BUZZ_BP_Pin GPIO_PIN_1
#define BLUE_BUZZ_BP_GPIO_Port GPIOA
#define BLUE_BUZZ_BP_EXTI_IRQn EXTI1_IRQn
#define RED_BUZZ_BP_Pin GPIO_PIN_2
#define RED_BUZZ_BP_GPIO_Port GPIOA
#define RED_BUZZ_BP_EXTI_IRQn EXTI2_TSC_IRQn
#define YELLOW_BUZZ_BP_Pin GPIO_PIN_3
#define YELLOW_BUZZ_BP_GPIO_Port GPIOA
#define YELLOW_BUZZ_BP_EXTI_IRQn EXTI3_IRQn
#define GREEN_BUZZ_BP_Pin GPIO_PIN_4
#define GREEN_BUZZ_BP_GPIO_Port GPIOA
#define GREEN_BUZZ_BP_EXTI_IRQn EXTI4_IRQn
#define BLUE_BUZZ_LED_Pin GPIO_PIN_6
#define BLUE_BUZZ_LED_GPIO_Port GPIOA
#define RED_BUZZ_LED_Pin GPIO_PIN_7
#define RED_BUZZ_LED_GPIO_Port GPIOA
#define B_SS_E_Pin GPIO_PIN_4
#define B_SS_E_GPIO_Port GPIOC
#define B_SS_F_Pin GPIO_PIN_5
#define B_SS_F_GPIO_Port GPIOC
#define YELLOW_BUZZ_LED_Pin GPIO_PIN_0
#define YELLOW_BUZZ_LED_GPIO_Port GPIOB
#define GREEN_BUZZ_LED_Pin GPIO_PIN_1
#define GREEN_BUZZ_LED_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_8
#define LD4_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_9
#define LD3_GPIO_Port GPIOE
#define LD5_Pin GPIO_PIN_10
#define LD5_GPIO_Port GPIOE
#define LD7_Pin GPIO_PIN_11
#define LD7_GPIO_Port GPIOE
#define LD9_Pin GPIO_PIN_12
#define LD9_GPIO_Port GPIOE
#define LD10_Pin GPIO_PIN_13
#define LD10_GPIO_Port GPIOE
#define LD8_Pin GPIO_PIN_14
#define LD8_GPIO_Port GPIOE
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOE
#define OK_SINGLE_BP_Pin GPIO_PIN_12
#define OK_SINGLE_BP_GPIO_Port GPIOB
#define OK_SINGLE_BP_EXTI_IRQn EXTI15_10_IRQn
#define OK_DOUBLE_BP_Pin GPIO_PIN_13
#define OK_DOUBLE_BP_GPIO_Port GPIOB
#define OK_DOUBLE_BP_EXTI_IRQn EXTI15_10_IRQn
#define KO_BP_Pin GPIO_PIN_14
#define KO_BP_GPIO_Port GPIOB
#define KO_BP_EXTI_IRQn EXTI15_10_IRQn
#define CANCEL_BP_Pin GPIO_PIN_15
#define CANCEL_BP_GPIO_Port GPIOB
#define CANCEL_BP_EXTI_IRQn EXTI15_10_IRQn
#define G_SS_B_Pin GPIO_PIN_8
#define G_SS_B_GPIO_Port GPIOD
#define G_SS_C_Pin GPIO_PIN_9
#define G_SS_C_GPIO_Port GPIOD
#define G_SS_D_Pin GPIO_PIN_10
#define G_SS_D_GPIO_Port GPIOD
#define G_SS_E_Pin GPIO_PIN_11
#define G_SS_E_GPIO_Port GPIOD
#define G_SS_F_Pin GPIO_PIN_12
#define G_SS_F_GPIO_Port GPIOD
#define G_SS_G_Pin GPIO_PIN_13
#define G_SS_G_GPIO_Port GPIOD
#define B_SS_G_Pin GPIO_PIN_6
#define B_SS_G_GPIO_Port GPIOC
#define R_SS_A_Pin GPIO_PIN_7
#define R_SS_A_GPIO_Port GPIOC
#define R_SS_B_Pin GPIO_PIN_8
#define R_SS_B_GPIO_Port GPIOC
#define R_SS_C_Pin GPIO_PIN_9
#define R_SS_C_GPIO_Port GPIOC
#define DM_Pin GPIO_PIN_11
#define DM_GPIO_Port GPIOA
#define DP_Pin GPIO_PIN_12
#define DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define R_SS_D_Pin GPIO_PIN_10
#define R_SS_D_GPIO_Port GPIOC
#define R_SS_E_Pin GPIO_PIN_11
#define R_SS_E_GPIO_Port GPIOC
#define R_SS_F_Pin GPIO_PIN_12
#define R_SS_F_GPIO_Port GPIOC
#define Y_SS_A_Pin GPIO_PIN_0
#define Y_SS_A_GPIO_Port GPIOD
#define Y_SS_B_Pin GPIO_PIN_1
#define Y_SS_B_GPIO_Port GPIOD
#define Y_SS_C_Pin GPIO_PIN_2
#define Y_SS_C_GPIO_Port GPIOD
#define Y_SS_D_Pin GPIO_PIN_3
#define Y_SS_D_GPIO_Port GPIOD
#define Y_SS_E_Pin GPIO_PIN_4
#define Y_SS_E_GPIO_Port GPIOD
#define Y_SS_F_Pin GPIO_PIN_5
#define Y_SS_F_GPIO_Port GPIOD
#define Y_SS_G_Pin GPIO_PIN_6
#define Y_SS_G_GPIO_Port GPIOD
#define G_SS_A_Pin GPIO_PIN_7
#define G_SS_A_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
