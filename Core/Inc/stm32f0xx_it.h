/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

 //! @def LrTMAX Ports on Board
#define Mx_GPIO_Port GPIOA
#define ENC0_GPIO_Port GPIOA
#define ENC1_GPIO_Port GPIOB
#define ENC2_GPIO_Port GPIOB
#define ENC3_GPIO_Port GPIOC
#define ENC4_GPIO_Port GPIOF

#define ENC5A_GPIO_Port GPIOB
#define ENC5B_GPIO_Port GPIOC

#define ENC6_GPIO_Port GPIOB
#define ENC7_GPIO_Port GPIOB

//! @def Definitions for Encoders
#define PRMASK_E0	0x0030
#define PRMASK_E1	0x0300
#define PRMASK_E2	0x0C00
#define PRMASK_E3	0xC000
#define PRMASK_E4	0x0003
#define PRMASK_E5	0x3000
#define PRMASK_E6	0x000C
#define PRMASK_E7	0x00C0

 //! @enum Encoder condition
enum enc_move_t {
	ENC_STOPPED = 0,
	ENC_MOVE_CW,
	ENC_MOVE_CCW,
	ENC_INVALID,
};

#define ENC_MASK	0x03
#define ENC5A_MASK	0x1000
#define ENC5B_MASK	0x2000

//! @def Definitions for Matrix
#define LxMASK	0x0F
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void DMA1_Channel4_5_6_7_IRQHandler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void I2C2_IRQHandler(void);
void USB_IRQHandler(void);
/* USER CODE BEGIN EFP */
void ENC_Init();
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_IT_H */
