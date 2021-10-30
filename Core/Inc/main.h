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
#define USBD_DEVICE_VER_MIN	0x53
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef union keyscan_t {
    uint32_t wd;
    struct ks_bit_t {
        unsigned char n0:4;		//Switch Line0
        unsigned char n1:4;		//Switch Line1
        unsigned char n2:4;		//Switch Line2
		unsigned char n3:4;		//Switch Line3
		unsigned char enc0:2;	//Rotary encoder
		unsigned char enc1:2;	//Rotary encoder
		unsigned char enc2:2;	//Rotary encoder
		unsigned char enc3:2;	//Rotary encoder
		unsigned char enc4:2;	//Rotary encoder
		unsigned char enc5:2;	//Rotary encoder
        unsigned char enc6:2;	//Rotary encoder
        unsigned char enc7:2;	//Rotary encoder
    } nb;
} KEYSCAN;
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
#define TIM_PRESC_1uS 47
#define TIM_PRESC_100uS 4799
#define TIM_PERIOD_8mS 8000
#define TIM_PERIOD_1SEC 10000
#define TIM_PERIOD_125uS 125

#define LrE6_PID 0xA380
#define Lr_PRODUCT "LrTMAX"
#define LrE6_VENDOR "Ruffles Inc."
#define PWM_PERIOD 59	//1.25 us
#define PWM_HI 38 //791ns
#define PWM_LO 15 //312ns
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
#undef	LrE6_PID
#undef	Lr_PRODUCT
#define LrE6_PID 0xA380
#define Lr_PRODUCT "LrTMAX"
#define LrE6_VENDOR "Ruffles Inc."

//! LrTMAX Ports on Board
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

//! Lr**** Hardware definition
#define KEY_COUNT	16
#define	ENC_COUNT	8

//! Lr**** States
enum lre6_state_t {
	LRE6_RESET,        //!< LRE6_RESET
	LRE6_USB_NOLINK,   //!< LRE6_USB_NOLINK
	LRE6_USB_LINKUP,   //!< LRE6_USB_LINKUP
	LRE6_USB_LINKED,   //!< LRE6_USB_LINKED
	LRE6_USB_LINK_LOST,//!< LRE6_USB_LINK_LOST
};

//! Key matrix lines
enum {
	L0 = 0,
	L1,
	L2,
	L3
};

//! Scene definition in MIDI
enum {
	LrE6_SCENE0 = 0,
	LrE6_SCENE1 = 1,
	LrE6_SCENE2 = 2,
	LrE6_SCENE3 = 3,
};

//! Encoder definitions
enum {
	LrE6_ENC0 = 0,
	LrE6_ENC1,
	LrE6_ENC2,
	LrE6_ENC3,
	LrE6_ENC4,
	LrE6_ENC5,
	LrE6_ENC6,
	LrE6_ENC7,
};

#define SCENE_COUNT		4
//! Define key that designated for scene change.
#define SCENE_BIT		7
#define KEY_PER_SCENE	(KEY_COUNT)
#define	CC_CH_PER_SCENE	16
#define NOTES_PER_SCENE	32
//! Key define structure
#define KEY_DEFINE_COUNT	( KEY_COUNT + (ENC_COUNT * 2) )

#define LxMASK	0x0F
//
#define PRMASK_R0	0x0030
#define PRMASK_R1	0x0300
#define PRMASK_R2	0x0C00
#define PRMASK_R3	0xC000
#define PRMASK_R4	0x0003
#define PRMASK_R5	0x3000
#define PRMASK_R6	0x000C
#define PRMASK_R7	0x00C0

// Screen timer definitions
#define MSG_TIMER_DEFAULT	600		//4.8Sec (1 tick=8ms)
#define MSG_TIMER_INIT		10		//80ms SSD1306 initialize time
#define MSG_TIMER_UPDATE	200		//1.6Sec (OLED update in USB not connected)

// LED timer definitions
#define LED_TIM_NORM		20		//640ms (1 tick=32ms)
#define LED_TIM_HALF		10		//320ms
#define LED_TIM_LONG		40		//1.28Sec
#define	LED_TIM_CONNECT		100		//3.2Sec
//! LED TIM3 definitions
#define LED_TIM_RETRY_WAIT	21		//Transfer period for I2C

#define ENC_NOT_MOVE        0
#define ENC_MOVE_CW         1
#define ENC_MOVE_CCW        2
#define ENC_MASK			0x03

//! I2C time definitions
#define I2C_RETRY_WAIT		2		//Transfer period for TIM3 PWM
#if 0
//! For temperature calculator
#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define VDD_CALIB ((uint16_t) (330))
#define VDD_APPLI ((uint16_t) (300))
#endif
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
