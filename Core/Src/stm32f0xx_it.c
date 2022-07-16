/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include "LrCommon.h"
#include "midi.h"
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
static inline void MIDI_CC_Inc(uint8_t enc);
static inline void MIDI_CC_Dec(uint8_t enc);
static inline void TIM15_Restart();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t previous_scan = 0;
uint32_t previous_key = 0;
uint32_t current_key = 0;
//! Value of scanned from key matrix.
KEYSCAN current_scan;
uint8_t	enc_prev[ENC_COUNT];
uint8_t	enc_timer[ENC_COUNT];

const uint8_t enc_table[4][4] = {
//now =	0			1				2				3
	{ENC_INVALID,	ENC_MOVE_CW,	ENC_MOVE_CCW,	ENC_INVALID,	},//prev = 0
	{ENC_STOPPED,	ENC_INVALID,	ENC_INVALID,	ENC_STOPPED,	},//prev = 1
	{ENC_STOPPED,	ENC_INVALID,	ENC_INVALID,	ENC_STOPPED,	},//prev = 2
	{ENC_INVALID,	ENC_MOVE_CCW,	ENC_MOVE_CW,	ENC_INVALID,	},//prev = 3
};

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern DMA_HandleTypeDef hdma_i2c2_tx;
extern I2C_HandleTypeDef hi2c2;
extern DMA_HandleTypeDef hdma_tim3_ch1_trig;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim15;
extern uint8_t	Key_Line;
extern bool		isKeyPressed;
extern KEYSCAN	Key_Stat;
extern char		*Msg_Buffer[];
extern bool		LED_Timer_Update;
extern bool		Msg_Timer_Update;
extern uint8_t	MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];
extern uint8_t	LrScene;
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
  strcpy(Msg_Buffer[0],"Hard Fault");
  SSD1306_Render2Buffer();
  SSD1306_FlashScreen();
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
  * @brief This function handles EXTI line 0 and 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
	uint32_t pr = EXTI->PR;

	// Encoder 4 (EXTI[0:1] / PF[0:1])
	if( pr & PRMASK_E4 ){
		uint8_t	r4 = (ENC4_GPIO_Port->IDR) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC4]][r4];
		enc_prev[Lr_ENC4] = r4;

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc4 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC4);
				isKeyPressed = true;
				TIM15_Restart();
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc4 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC4);
				isKeyPressed = true;
				TIM15_Restart();
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc4 = ENC_STOPPED;
			isKeyPressed = true;
		}else{
			Key_Stat.nb.enc4 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC4A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC4B_Pin);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 2 and 3 interrupts.
  */
void EXTI2_3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_3_IRQn 0 */
	uint32_t pr = EXTI->PR;

	// Encoder 6 (EXTI[2:3] / PB[2:3])
	if( pr & PRMASK_E6 ){
		uint8_t	r6 = (ENC6_GPIO_Port->IDR >> 2) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC6]][r6];
		enc_prev[Lr_ENC6] = r6;

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc6 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC6);
				isKeyPressed = true;
				TIM15_Restart();
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc6 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC6);
				isKeyPressed = true;
				TIM15_Restart();
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc6 = ENC_STOPPED;
			isKeyPressed = true;
		}else{
			Key_Stat.nb.enc6 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

  /* USER CODE END EXTI2_3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC6A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC6B_Pin);
  /* USER CODE BEGIN EXTI2_3_IRQn 1 */

  /* USER CODE END EXTI2_3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
	uint32_t pr = EXTI->PR;

	// Encoder 0 (EXTI[4:5] / PA[4:5]
	if(pr & PRMASK_E0){
		uint8_t	r0 = ((ENC0_GPIO_Port->IDR) >> 4 ) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC0]][r0];
		enc_prev[Lr_ENC0] = r0;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc0 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC0);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc0 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC0);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc0 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc0 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

	// Encoder 7 (EXTI[6:7] / PB[6:7])
	if(pr & PRMASK_E7){
		uint8_t	r7 = ((ENC7_GPIO_Port->IDR) >> 6 ) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC7]][r7];
		enc_prev[Lr_ENC7] = r7;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc7 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC7);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc7 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC7);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc7 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc7 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

	//Encoder 1 (EXTI[8:9] / PB[8:9])
	if(pr & PRMASK_E1){
		uint8_t	r1 = ((ENC1_GPIO_Port->IDR) >> 8) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC1]][r1];
		enc_prev[Lr_ENC1] = r1;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc1 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC1);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc1 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC1);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc1 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc1 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

	//Encoder 2 (EXTI[10:11] / PB[10:11])
	if( pr & PRMASK_E2 ){
		uint8_t	r2 = (ENC2_GPIO_Port->IDR >> 10 ) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC2]][r2];
		enc_prev[Lr_ENC2] = r2;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc2 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC2);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc2 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC2);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc2 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc2 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

	//Encoder 5 (EXTI[12:13] / PA[12],PC[13])
	if( pr & PRMASK_E5 ){
 		uint8_t r5 = ( (ENC5A_GPIO_Port->IDR & ENC5A_MASK) | (ENC5B_GPIO_Port->IDR & ENC5B_MASK) ) >> 12;
		uint8_t op = enc_table[enc_prev[Lr_ENC5]][r5];
		enc_prev[Lr_ENC5] = r5;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc5 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC5);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc5 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC5);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc5 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc5 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

	//Encoder 3 (EXTI[14:15] / PC[14:15])
	if(pr & PRMASK_E3){ //EXTI14&15
		uint8_t	r3 = ( (ENC3_GPIO_Port->IDR) >> 14 ) & ENC_MASK;
		uint8_t op = enc_table[enc_prev[Lr_ENC3]][r3];
		enc_prev[Lr_ENC3] = r3;
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);

		if (op == ENC_MOVE_CW) {
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc3 = ENC_MOVE_CW;
				MIDI_CC_Inc(Lr_ENC3);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_MOVE_CCW){
			if ( htim15.Instance->SR & TIM_SR_UIF) {
				Key_Stat.nb.enc3 = ENC_MOVE_CCW;
				MIDI_CC_Dec(Lr_ENC3);
				isKeyPressed = true;
				TIM15_Restart();
				return;
			}
		}else if(op == ENC_STOPPED){
			Key_Stat.nb.enc3 = ENC_STOPPED;
			isKeyPressed = true;
			return;
		}else{
			Key_Stat.nb.enc3 = ENC_STOPPED;
			isKeyPressed = false;
		}
	}

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC0A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC0B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC7A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC7B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC1A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC1B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC2A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC2B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC5A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC5B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC3A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC3B_Pin);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

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
	switch(Key_Line){
		case L0:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n0 = (r);
			Key_Line++;
			HAL_GPIO_WritePin(L0_GPIO_Port,L0_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L1_GPIO_Port,L1_Pin,GPIO_PIN_SET);
			break;
		case L1:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n1 = (r);
			Key_Line++;
			HAL_GPIO_WritePin(L1_GPIO_Port,L1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L2_GPIO_Port,L2_Pin,GPIO_PIN_SET);
			break;
		case L2:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n2 = (r);
			Key_Line++;
			HAL_GPIO_WritePin(L2_GPIO_Port,L2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L3_GPIO_Port,L3_Pin,GPIO_PIN_SET);
			break;
		case L3:
			r = (Mx_GPIO_Port->IDR) & LxMASK;
			current_scan.nb.n3 = (r);
			HAL_GPIO_WritePin(L3_GPIO_Port,L3_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(L0_GPIO_Port,L0_Pin,GPIO_PIN_SET);
			Key_Line = L0;

			//Key detection
			if (previous_scan == current_scan.wd){
				current_key = current_scan.wd;
				uint32_t dif = current_key ^ previous_key;
				Key_Stat.wd = current_key;
				if (dif != 0){
					previous_key = current_key;
					isKeyPressed = true;
				}
			}
			previous_scan = current_scan.wd;
			break;
	}
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
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
static inline void MIDI_CC_Inc(uint8_t enc){
	if (MIDI_CC_Value[LrScene][enc] < MIDI_CC_MAX ) MIDI_CC_Value[LrScene][enc]++;
}

static inline void MIDI_CC_Dec(uint8_t enc){
	if (MIDI_CC_Value[LrScene][enc] >= (MIDI_CC_MIN + 1) ) MIDI_CC_Value[LrScene][enc]--;
}

static inline void TIM15_Restart(){
	htim15.Instance->CNT = 0;
	htim15.Instance->SR &= ~TIM_SR_UIF;
	htim15.Instance->CR1 |= TIM_CR1_CEN;
}
/* USER CODE END 1 */
