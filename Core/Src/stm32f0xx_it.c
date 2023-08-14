/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include "LrCommon.h"
#include "midi.h"
#include "bitcount.h"
#include "stm32f0xx_hal_tim.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t previous_mtrx = 0;
uint16_t previous_push = 0;
uint16_t current_push = 0;
//! Value of scanned from key matrix.
MTRX_SCAN current_scan;
uint8_t	enc_prev[ENC_COUNT];
uint8_t	enc_current[ENC_COUNT];

const uint8_t enc_table[4][4] = {
//now =	0			1				2				3
	{ENC_INVALID,	ENC_MOVE_CW,	ENC_MOVE_CCW,	ENC_INVALID,	},//prev = 0
	{ENC_STOPPED,	ENC_INVALID,	ENC_INVALID,	ENC_STOPPED,	},//prev = 1
	{ENC_STOPPED,	ENC_INVALID,	ENC_INVALID,	ENC_STOPPED,	},//prev = 2
	{ENC_INVALID,	ENC_MOVE_CCW,	ENC_MOVE_CW,	ENC_INVALID,	},//prev = 3
};
ENC_SCAN current_enc;
uint16_t previous_enc;
uint16_t previous_move;
uint16_t current_move;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern DMA_HandleTypeDef hdma_i2c2_tx;
extern I2C_HandleTypeDef hi2c2;
extern DMA_HandleTypeDef hdma_tim3_ch1_trig;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim3;
extern uint8_t	ENCSW_Line;
extern bool		isAnyMatrixPushed;
extern bool		isAnyEncoderMoved;
extern MTRX_SCAN	MTRX_Stat;
extern ENC_SCAN	ENC_Stat;
extern char		*Msg_Buffer[];
extern bool		LED_Timer_Update;
extern bool		Msg_Timer_Update;
extern ENC_MOVE	enc_move;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 4, 5, 6 and 7 interrupts.
  */
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 0 */
  if(DMA1->ISR & DMA_ISR_TCIF4){
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);

	GPIOA->ODR |= GPIO_PIN_6;	//'RESET' state
	//Set PA6 AF -> GPIO
	GPIOA->MODER &= ~(GPIO_MODER_MODER6_1);
	GPIOA->MODER |=	GPIO_MODER_MODER6_0;

  }
  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_i2c2_tx);
  HAL_DMA_IRQHandler(&hdma_tim3_ch1_trig);
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 1 */

  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */
	uint8_t r;

	//keyboard matrix
	switch(ENCSW_Line) {
		case L0:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n0 = (r);
			ENCSW_Line++;
			HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, GPIO_PIN_SET);
			break;
		case L1:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n1 = (r);
			ENCSW_Line++;
			HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, GPIO_PIN_SET);
			break;
		case L2:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n2 = (r);
			ENCSW_Line++;
			HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, GPIO_PIN_SET);
			break;
		case L3:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n3 = (r);
			HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, GPIO_PIN_SET);
			ENCSW_Line = L0;

			//Switch detection
			if (previous_mtrx == current_scan.wd){
				current_push = current_scan.wd;
				uint16_t dif = current_push ^ previous_push;
				MTRX_Stat.wd = current_push;
				if (dif != 0){
					previous_push = current_push;
					isAnyMatrixPushed = true;
				}
			}
			previous_mtrx = current_scan.wd;
			break;
	}
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

	//GPIOA reading
	current_enc.nb.enc0 = enc_current[Lr_ENC0] = ((ENC0_GPIO_Port->IDR) >> 4 ) & ENC_MASK;
	//GPIOB reading
	current_enc.nb.enc1 = enc_current[Lr_ENC1] = ((ENC1_GPIO_Port->IDR) >> 8) & ENC_MASK;
	current_enc.nb.enc2 = enc_current[Lr_ENC2] = (ENC2_GPIO_Port->IDR >> 10 ) & ENC_MASK;
	current_enc.nb.enc6 = enc_current[Lr_ENC6] = (ENC6_GPIO_Port->IDR >> 2) & ENC_MASK;
	current_enc.nb.enc7 = enc_current[Lr_ENC7] = ((ENC7_GPIO_Port->IDR) >> 6 ) & ENC_MASK;
	//GPIOC reading
	current_enc.nb.enc3 = enc_current[Lr_ENC3] = ( (ENC3_GPIO_Port->IDR) >> 14 ) & ENC_MASK;
	current_enc.nb.enc4 = enc_current[Lr_ENC4] = (ENC4_GPIO_Port->IDR) & ENC_MASK;
	//GPIO B&C reading
	current_enc.nb.enc5 = enc_current[Lr_ENC5] = ( (ENC5A_GPIO_Port->IDR & ENC5A_MASK) | (ENC5B_GPIO_Port->IDR & ENC5B_MASK) ) >> 12;

	if (previous_enc == current_enc.wd) { // Encoder signals are stable
		current_move = current_enc.wd;
		uint16_t dif = previous_move ^ current_move;
		if (dif != 0) { // If any encoder has moved.
			previous_move = current_move;

			uint8_t	movedbits = ntz16(dif);
			uint8_t	axis = movedbits / 2;

			enc_move.bits.move = enc_table[enc_prev[axis]] [enc_current[axis]];
			enc_move.bits.axis = axis;

			enc_prev[axis] = enc_current[axis];
			isAnyEncoderMoved = true;
		}
	} else {
		previous_enc = current_enc.wd;
	}
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global and DAC channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
  LED_Timer_Update = true;
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
  Msg_Timer_Update = true;
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles I2C2 global interrupt.
  */
void I2C2_IRQHandler(void)
{
  /* USER CODE BEGIN I2C2_IRQn 0 */

  /* USER CODE END I2C2_IRQn 0 */
  if (hi2c2.Instance->ISR & (I2C_FLAG_BERR | I2C_FLAG_ARLO | I2C_FLAG_OVR)) {
    HAL_I2C_ER_IRQHandler(&hi2c2);
  } else {
    HAL_I2C_EV_IRQHandler(&hi2c2);
  }
  /* USER CODE BEGIN I2C2_IRQn 1 */

  /* USER CODE END I2C2_IRQn 1 */
}

/**
  * @brief This function handles USB global interrupt / USB wake-up interrupt through EXTI line 18.
  */
void USB_IRQHandler(void)
{
  /* USER CODE BEGIN USB_IRQn 0 */

  /* USER CODE END USB_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_IRQn 1 */

  /* USER CODE END USB_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/**
 * @brief Initialize Encoders.
 */
void ENC_Init() {
	//! Initialize all enc_prev[] for current pin value
	enc_prev[Lr_ENC4] = current_enc.nb.enc4 = (ENC4_GPIO_Port->IDR) & ENC_MASK;
	enc_prev[Lr_ENC1] = current_enc.nb.enc1 = (ENC1_GPIO_Port->IDR >> 8) & ENC_MASK;
	enc_prev[Lr_ENC2] = current_enc.nb.enc2 = (ENC2_GPIO_Port->IDR >> 10) & ENC_MASK;
	enc_prev[Lr_ENC6] = current_enc.nb.enc6 = (ENC6_GPIO_Port->IDR >> 2) & ENC_MASK;
	enc_prev[Lr_ENC7] = current_enc.nb.enc7 = (ENC7_GPIO_Port->IDR >> 6) & ENC_MASK;
	enc_prev[Lr_ENC5] = current_enc.nb.enc5 = ( (ENC5A_GPIO_Port->IDR & ENC5A_MASK) | (ENC5B_GPIO_Port->IDR & ENC5B_MASK) ) >> 12;
	enc_prev[Lr_ENC0] = current_enc.nb.enc0 = (ENC0_GPIO_Port->IDR >> 4 ) & ENC_MASK;
	enc_prev[Lr_ENC3] = current_enc.nb.enc3 = (ENC3_GPIO_Port->IDR >> 14 ) & ENC_MASK;

	previous_move = previous_enc = current_enc.wd;
}
/* USER CODE END 1 */
