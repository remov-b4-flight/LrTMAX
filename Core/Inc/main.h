/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file	main.h
  * @brief	Header for main.c file.
  * 		This file contains the common defines of the application.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define USBD_DEVICE_VER_MAJ	0x00
#define USBD_DEVICE_VER_MIN	0x60
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TIM_PERIOD_RGBLED 24576
#define Lr_PID 0xA380
#define TIM_PERIOD_KEY_MTRX 7999
#define TIM_PERIOD_OLED 32767
#define TIM_PERIOD_NPIX 279
#define Lr_PRODUCT "LrTMAX"
#define PWM_HI 38
#define Lr_VENDOR "Ruffles Inc."
#define TIM_PRESC_1uS 47
#define PWM_LO 15
#define PWM_PERIOD 59
#define TIM_PERIOD_DCHAT 2999
#define ENC5B_Pin GPIO_PIN_13
#define ENC5B_GPIO_Port GPIOC
#define ENC5B_EXTI_IRQn EXTI4_15_IRQn
#define ENC3A_Pin GPIO_PIN_14
#define ENC3A_GPIO_Port GPIOC
#define ENC3A_EXTI_IRQn EXTI4_15_IRQn
#define ENC3B_Pin GPIO_PIN_15
#define ENC3B_GPIO_Port GPIOC
#define ENC3B_EXTI_IRQn EXTI4_15_IRQn
#define ENC4A_Pin GPIO_PIN_0
#define ENC4A_GPIO_Port GPIOF
#define ENC4A_EXTI_IRQn EXTI0_1_IRQn
#define ENC4B_Pin GPIO_PIN_1
#define ENC4B_GPIO_Port GPIOF
#define ENC4B_EXTI_IRQn EXTI0_1_IRQn
#define M0_Pin GPIO_PIN_0
#define M0_GPIO_Port GPIOA
#define M1_Pin GPIO_PIN_1
#define M1_GPIO_Port GPIOA
#define M2_Pin GPIO_PIN_2
#define M2_GPIO_Port GPIOA
#define M3_Pin GPIO_PIN_3
#define M3_GPIO_Port GPIOA
#define ENC0A_Pin GPIO_PIN_4
#define ENC0A_GPIO_Port GPIOA
#define ENC0A_EXTI_IRQn EXTI4_15_IRQn
#define ENC0B_Pin GPIO_PIN_5
#define ENC0B_GPIO_Port GPIOA
#define ENC0B_EXTI_IRQn EXTI4_15_IRQn
#define LED_DON_Pin GPIO_PIN_6
#define LED_DON_GPIO_Port GPIOA
#define ENC6A_Pin GPIO_PIN_2
#define ENC6A_GPIO_Port GPIOB
#define ENC6A_EXTI_IRQn EXTI2_3_IRQn
#define ENC2A_Pin GPIO_PIN_10
#define ENC2A_GPIO_Port GPIOB
#define ENC2A_EXTI_IRQn EXTI4_15_IRQn
#define ENC2B_Pin GPIO_PIN_11
#define ENC2B_GPIO_Port GPIOB
#define ENC2B_EXTI_IRQn EXTI4_15_IRQn
#define ENC5A_Pin GPIO_PIN_12
#define ENC5A_GPIO_Port GPIOB
#define ENC5A_EXTI_IRQn EXTI4_15_IRQn
#define SCL_Pin GPIO_PIN_13
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOB
#define L0_Pin GPIO_PIN_9
#define L0_GPIO_Port GPIOA
#define L3_Pin GPIO_PIN_10
#define L3_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define ENC6B_Pin GPIO_PIN_3
#define ENC6B_GPIO_Port GPIOB
#define ENC6B_EXTI_IRQn EXTI2_3_IRQn
#define L1_Pin GPIO_PIN_4
#define L1_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_5
#define L2_GPIO_Port GPIOB
#define ENC7A_Pin GPIO_PIN_6
#define ENC7A_GPIO_Port GPIOB
#define ENC7A_EXTI_IRQn EXTI4_15_IRQn
#define ENC7B_Pin GPIO_PIN_7
#define ENC7B_GPIO_Port GPIOB
#define ENC7B_EXTI_IRQn EXTI4_15_IRQn
#define ENC1A_Pin GPIO_PIN_8
#define ENC1A_GPIO_Port GPIOB
#define ENC1A_EXTI_IRQn EXTI4_15_IRQn
#define ENC1B_Pin GPIO_PIN_9
#define ENC1B_GPIO_Port GPIOB
#define ENC1B_EXTI_IRQn EXTI4_15_IRQn
/* USER CODE BEGIN Private defines */

//! LED TIM3 definitions
#define LED_TIM_RETRY_WAIT	21		//Transfer period for I2C
//! I2C time definitions
#define I2C_RETRY_WAIT		2		//Transfer period for TIM3 PWM

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
