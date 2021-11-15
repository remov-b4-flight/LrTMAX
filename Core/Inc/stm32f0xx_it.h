/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
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
#ifndef __STM32F0xx_IT_H
#define __STM32F0xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

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

 // Definitions for Encoders

#define PRMASK_R0	0x0030
#define PRMASK_R1	0x0300
#define PRMASK_R2	0x0C00
#define PRMASK_R3	0xC000
#define PRMASK_R4	0x0003
#define PRMASK_R5	0x3000
#define PRMASK_R6	0x000C
#define PRMASK_R7	0x00C0

//! 9R5KQ type Encoder
enum enc9R5_t {
	ENC_MV3 =	3,
	ENC_MV2	=	2,
	ENC_MV1	=	1,
	ENC_MV0	=	0,
};

enum enc_move_t {
	ENC_STOPPED = 0,
	ENC_MOVE_CW,
	ENC_MOVE_CCW,
	ENC_INVALID,
};

#define ENC_MASK	0x03
#define ENC5A_MASK	0x1000
#define ENC5B_MASK	0x2000

#define ENC_TIMER_MAX	3

// Definitions for Matrix
#define LxMASK	0x0F

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void DMA1_Channel4_5_6_7_IRQHandler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void I2C2_IRQHandler(void);
void USB_IRQHandler(void);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
