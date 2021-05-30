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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern uint8_t	Key_Line;
extern bool		isKeyPressed;
extern bool		isKeyRelaseSent;
extern KEYSCAN	Key_Stat;

extern bool		Msg_Off_Flag;
extern bool		Msg_Timer_Enable;
extern int32_t	Msg_Timer_Count;
extern char		*Msg_Buffer[];

extern uint8_t	LEDColor[];
extern uint8_t	LEDTimer[];
extern bool		LED_Timer_Update;

uint32_t previous_scan = 0;
uint32_t previous_key = 0;
uint32_t current_key = 0;
//! Value of scanned from key matrix.
KEYSCAN current_scan;

//! previous value of rotator 0
uint8_t     rot0_prev;
//! previous value of rotator 1
uint8_t     rot1_prev;
//! previous value of rotator 2
uint8_t     rot2_prev;
//! previous value of rotator 3
uint8_t     rot3_prev;
//! previous value of rotator 4
uint8_t     rot4_prev;
//! previous value of rotator 5
uint8_t     rot5_prev;
//! previous value of rotator 6
uint8_t     rot6_prev;
//! previous value of rotator 7
uint8_t     rot7_prev;

#ifdef MIDI
extern uint8_t MIDI_CC_Value[SCENE_COUNT][ROT_COUNT];
extern uint8_t LrE6Scene;
#endif

static inline void MIDI_CC_Inc(uint8_t rot){
#if MIDI
	if (MIDI_CC_Value[LrE6Scene][rot] < MIDI_CC_MAX ) MIDI_CC_Value[LrE6Scene][rot]++;
#endif
}

static inline void MIDI_CC_Dec(uint8_t rot){
#if MIDI
	if (MIDI_CC_Value[LrE6Scene][rot] >= (MIDI_CC_MIN + 1) ) MIDI_CC_Value[LrE6Scene][rot]--;
#endif
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern DMA_HandleTypeDef hdma_i2c2_tx;
extern I2C_HandleTypeDef hi2c2;
extern DMA_HandleTypeDef hdma_tim3_ch1_trig;
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim3;
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

	// Rotator 4 (EXTI[0:1] / PF[0:1])
	if( pr & PRMASK_R4 ){
		uint8_t	r4 = (ENC4_GPIO_Port->IDR) & ROT_MASK;
    	if ( r4 == ENC_MV0 || r4 ==ENC_MV3 ) { //Stopped
			if( rot4_prev == ENC_MV1 || rot4_prev == ENC_MV2 ){
				Key_Stat.nb.rot4 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r4 == ENC_MV1 ){ //Moved
			if( rot4_prev == ENC_MV0 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CW;
	          	MIDI_CC_Inc(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot4_prev == ENC_MV3 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CCW;
	          	MIDI_CC_Dec(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r4 == ENC_MV2 ){ //Moved
			if( rot4_prev == ENC_MV0 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CCW;
	          	MIDI_CC_Dec(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot4_prev == ENC_MV3 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CW;
	            MIDI_CC_Inc(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
    	rot4_prev = r4;
	}

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
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

	// Rotator 6 (EXTI[2:3] / PB[2:3])
	if( pr & PRMASK_R6 ){
		uint8_t	r6 = (ENC6_GPIO_Port->IDR >> 2) & ROT_MASK;
    	if ( r6 == ENC_MV0 || r6 ==ENC_MV3 ) { //Stopped
			if( rot6_prev == ENC_MV1 || rot6_prev == ENC_MV2 ){
				Key_Stat.nb.rot6 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r6 == ENC_MV1 ){ //Moved
			if( rot6_prev == ENC_MV0 ){
				Key_Stat.nb.rot6 = ROT_MOVE_CW;
	          	MIDI_CC_Inc(LrE6_ROT6);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot6_prev == ENC_MV3 ){
				Key_Stat.nb.rot6 = ROT_MOVE_CCW;
	          	MIDI_CC_Dec(LrE6_ROT6);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r6 == ENC_MV2 ){ //Moved
			if( rot6_prev == ENC_MV0 ){
				Key_Stat.nb.rot6 = ROT_MOVE_CCW;
	          	MIDI_CC_Dec(LrE6_ROT6);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot6_prev == ENC_MV3 ){
				Key_Stat.nb.rot6 = ROT_MOVE_CW;
	            MIDI_CC_Inc(LrE6_ROT6);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
    	rot6_prev = r6;
	}

  /* USER CODE END EXTI2_3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
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

    // Rotator0 (EXTI[4:5] / PA[4:5]
    if(pr & PRMASK_R0){
        uint8_t	r0 = ((ENC0_GPIO_Port->IDR) >> 4 );
    	if ( r0 == ENC_MV0 || r0 == ENC_MV3 ) { //Stopped
			if( rot0_prev == ENC_MV1 || rot0_prev == ENC_MV2 ){
				Key_Stat.nb.rot0 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r0 == ENC_MV1 ){ //Moved
			if(rot0_prev == ENC_MV0){
				Key_Stat.nb.rot0 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT0);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot0_prev == ENC_MV3 ){
				Key_Stat.nb.rot0 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT0);
		        isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r0 == ENC_MV2 ){ //Moved
			if( rot0_prev == ENC_MV0 ){
				Key_Stat.nb.rot0 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT0);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot0_prev == ENC_MV3 ){
				Key_Stat.nb.rot0 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT0);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
	    rot0_prev = r0;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		if (isKeyPressed)
			  return;
    }

    // Rotator 7 (EXTI[6:7] / PB[6:7])
    if(pr & PRMASK_R7){
        uint8_t	r7 = ((ENC7_GPIO_Port->IDR) >> 6 );
    	if ( r7 == ENC_MV0 || r7 == ENC_MV3 ) { //Stopped
			if( rot7_prev == ENC_MV1 || rot7_prev == ENC_MV2 ){
				Key_Stat.nb.rot7 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r7 == ENC_MV1 ){ //Moved
			if(rot7_prev == ENC_MV0){
				Key_Stat.nb.rot7 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT7);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot7_prev == ENC_MV3 ){
				Key_Stat.nb.rot7 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT7);
		        isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r7 == ENC_MV2 ){ //Moved
			if( rot7_prev == ENC_MV0 ){
				Key_Stat.nb.rot7 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT7);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot7_prev == ENC_MV3 ){
				Key_Stat.nb.rot7 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT7);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
	    rot7_prev = r7;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
		if (isKeyPressed)
			  return;
    }

    //Rotator 1 (EXTI[8:9] / PB[8:9])
    if(pr & PRMASK_R1){
    	uint8_t	r1 = ((ENC1_GPIO_Port->IDR) >> 8) & ROT_MASK;
    	if ( r1 == ENC_MV0 || r1 == ENC_MV3 ) { //Stopped
			if( rot1_prev == ENC_MV1 || rot1_prev == ENC_MV2 ){
				Key_Stat.nb.rot1 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r1 == ENC_MV1 ){ //Moved
			if( rot1_prev == ENC_MV0 ){
				Key_Stat.nb.rot1 = ROT_MOVE_CW;
				MIDI_CC_Inc(LrE6_ROT1);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot1_prev == ENC_MV3 ){
				Key_Stat.nb.rot1 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT1);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r1 == ENC_MV2 ){ //Moved
			if( rot1_prev == ENC_MV0 ){
				Key_Stat.nb.rot1 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT1);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot2_prev == ENC_MV3 ){
				Key_Stat.nb.rot1 = ROT_MOVE_CW;
				MIDI_CC_Inc(LrE6_ROT1);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
		rot1_prev = r1;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
		if(isKeyPressed)
			return;
    }

    //Rotator 2 (EXTI[10:11] / PB[10:11])
	if( pr & PRMASK_R2 ){
		uint8_t	r2 = (ENC2_GPIO_Port->IDR >> 10 ) & ROT_MASK;
    	if ( r2 == ENC_MV0 || r2 == ENC_MV3 ) { //Stopped
			if( rot2_prev == ENC_MV1 || rot2_prev == ENC_MV2 ){
				Key_Stat.nb.rot2 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r2 == ENC_MV1 ){ //Moved
			if( rot2_prev == ENC_MV0 ){
				Key_Stat.nb.rot2 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT2);

				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot2_prev == ENC_MV3 ){
				Key_Stat.nb.rot2 = ROT_MOVE_CCW;
				MIDI_CC_Dec(LrE6_ROT2);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r2 == ENC_MV2 ){ //Moved
			if( rot2_prev == ENC_MV0 ){
				Key_Stat.nb.rot2 = ROT_MOVE_CCW;
				MIDI_CC_Dec(LrE6_ROT2);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot2_prev == ENC_MV3 ){
				Key_Stat.nb.rot2 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT2);

				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
	    rot2_prev = r2;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
		if(isKeyPressed)
			return;
	}

    //Rotator 5 (EXTI[12:13] / PA[12],PC[13])
    if( pr & PRMASK_R3 ){
    	uint8_t	r5 = (ENC5_GPIO_PortA->IDR | ENC5_GPIO_PortA->IDR) >> 12;
    			r5 &= ROT_MASK;
    	if ( r5 == ENC_MV0 || r5 == ENC_MV3 ) { //Stopped
			if( rot0_prev == ENC_MV1 || rot0_prev == ENC_MV2 ){
				Key_Stat.nb.rot5 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r5 == ENC_MV1 ){ //Moved
			if( rot5_prev == ENC_MV0 ){
				Key_Stat.nb.rot5 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT5);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot5_prev == ENC_MV3 ){
				Key_Stat.nb.rot5 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT5);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r5 == ENC_MV2 ){ //Moved
			if( rot5_prev == ENC_MV0 ){
				Key_Stat.nb.rot5 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT5);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot5_prev == ENC_MV3 ){
				Key_Stat.nb.rot5 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT5);
		        isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
	    rot5_prev = r5;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
		if(isKeyPressed)
			return;

    }

    //Rotator 3 (EXTI[14:15] / PC[14:15])
    if(pr & PRMASK_R3){ //EXTI14&15
    	uint8_t	r4 = ( (ENC4_GPIO_Port->IDR) >> 14 ) & ROT_MASK;
    	if ( r4 == ENC_MV0 || r4 == ENC_MV3 ) { //Stopped
			if(rot4_prev == ENC_MV1 || rot4_prev == ENC_MV2){
				Key_Stat.nb.rot4 = ROT_NOT_MOVE;
				isKeyPressed = true;
				isKeyRelaseSent = true;
			}
		}else if( r4 == ENC_MV1 ){ //Moved
			if( rot4_prev == ENC_MV0 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot4_prev == ENC_MV3 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}else if( r4 == ENC_MV2 ){ //Moved
			if( rot4_prev == ENC_MV0 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CCW;
		        MIDI_CC_Dec(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}else if( rot4_prev == ENC_MV3 ){
				Key_Stat.nb.rot4 = ROT_MOVE_CW;
		        MIDI_CC_Inc(LrE6_ROT4);
				isKeyPressed = true;
				isKeyRelaseSent = false;
			}
		}
	    rot4_prev = r4;

		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
		if(isKeyPressed)
			return;
    }

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
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
            LED_Timer_Update = true;
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

            if(isKeyRelaseSent == false){
            	current_key = 0;
                isKeyPressed = true;
            }

            previous_scan = current_scan.wd;
            break;
    }

    //LCD timer
    if(Msg_Timer_Enable == true && (--Msg_Timer_Count) <= 0){
    	Msg_Timer_Enable = false;
        Msg_Off_Flag = true;
    }


  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
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

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
