/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file main.c
  * @brief  Main program body
  * @author	remov-b4-flight
  * @copyright	3-Clause BSD License
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "LrCommon.h"
#include "midi.h"
#include "led.h"
#include "bitcount.h"
#include "key_define.h"
#include "usbd_midi_if.h"
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef DEBUG
#define CONN_MSG_D	"%s %2x.%02xD"
#else
#define CONN_MSG	"%2x.%02x"
#endif

#define CC_MSG_3DG	"C%3d = %3d    S%1d"
#define CC_MSG_2DG	"Ch%1d = %3d    S%1d"
#define SPACE_CHAR  ' '
#define SWMASK	0x0F
#define SW1	1
#define SW3	4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;
DMA_HandleTypeDef hdma_i2c2_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim15;
DMA_HandleTypeDef hdma_tim3_ch1_trig;

/* USER CODE BEGIN PV */

//! STM32 TIM3 instance handle
TIM_HandleTypeDef htim3;
extern	USBD_HandleTypeDef hUsbDeviceFS;
extern PCD_HandleTypeDef hpcd_USB_FS;
//! Lr**** USB connection state
uint8_t		LrState;
//! Lr**** Scene index
uint8_t		LrScene;
// keyboard variable
//! If true, ISR detected any Key/Encoder was moved.
bool		isKeyPressed;
//! Key pressed/released status set by timer key scanning.
KEYSCAN     Key_Stat;
//! In key scanning whether Line selected to read for key matrix.
uint8_t		Key_Line;
//! If true, MIDI event previous sent is switch. if false, it's encoder
bool		isPrev_sw;
//! Bit masks for which bit of KEYSCAN variable acts as key.
uint32_t	MaskKey[SCENE_COUNT];
//! Bit masks for which bit of KEYSCAN variable acts as encoder.
uint32_t	MaskEnc[SCENE_COUNT];

// OLED variables
//! Flag set by timer ISR, It makes 'off' OLES contents.
bool 		Msg_Timer_Update;
//! Timer counter ticked by TIM7.
int32_t		Msg_Timer_Count;
//! If true Msg_Timer counting is enabled.
bool		Msg_Timer_Enable;
//! If true, Screen is cleared in main() that is determined on timer interrupt.
bool		Msg_Off_Flag;
//! If true, Screen is flashed by Msg_Buffer[] at main() function.
static	bool	isMsgFlash;
//! If true, frame_buffer[] contents flashes the screen.
static	bool	isRender;

// LED variables
//! If true, LEDs are flashed by LEDColor[] array.
bool		isLEDsendpulse;
//! Flag is set by timer ISR, It makes LED_Timer[] count up in main()
bool		LED_Timer_Update;

// Scene related
extern	KEY_DEFINE keytable[SCENE_COUNT][DEFINES_PER_SCENE];
extern	char *scene_name[SCENE_COUNT];
extern	uint8_t	led_axis_table[DEFINES_PER_SCENE];

extern	uint8_t	LED_Scene[SCENE_COUNT][LED_COUNT];
extern	uint8_t	LEDColor[LED_COUNT];
extern	uint8_t	LEDTimer[LED_COUNT];

//! String message buffer of screen
extern char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];

// MIDI variables
//! MIDI CC message value for each channels.
uint8_t MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];
//! keep previous sent 'Key On' note/channel for release message.
uint8_t prev_note;
//! Instance Handle of USB interface
extern USBD_HandleTypeDef *pInstance;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM14_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief jump into system memory (DFU bootloader)
 * @author ERODF.1
 * @note  Quoted from ST Community and modified.
 */
void Jump2SystemMemory() {
	void (*SysMemBootJump)(void);

	/*
	* Set system memory address.
	* For STM32F072, system memory is on 0x1FFFC800
	*/
	volatile uint32_t addr = 0x1FFFC800;

	// De-initialize all peripherals configured for this Application
	HAL_TIM_Base_DeInit(&htim1);
	HAL_TIM_Base_DeInit(&htim14);
	HAL_TIM_Base_DeInit(&htim15);
	HAL_TIM_PWM_DeInit(&htim3);
	HAL_TIM_Base_DeInit(&htim3);

	HAL_NVIC_DisableIRQ(DMA1_Channel4_5_6_7_IRQn);
	HAL_DMA_DeInit(&hdma_tim3_ch1_trig);

	HAL_I2C_DeInit(&hi2c2);
	HAL_PCD_DeInit(&hpcd_USB_FS);

	// Disable GPIO interrupts
	HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
	HAL_NVIC_DisableIRQ(EXTI2_3_IRQn);
	HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);

	// Disable RCC, set it to default (after reset) settings
	//       Internal clock, no PLL, etc.
	HAL_RCC_DeInit();

	// Disable systick timer and reset it to default values
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	// Disable all interrupts
	__disable_irq();

	/**
	 * Remap system memory to address 0x0000 0000 in address space
	 * For each family registers may be different.
	 * Check reference manual for each family.
	 *
	 * For STM32F0xx, CFGR1 register in SYSCFG is used (bits[1:0])
	 */
	#if defined(STM32F0)
	SYSCFG->CFGR1 = 0x01;
	#endif

	// Set jump memory location for system memory
	// Use address with 4 bytes offset which specifies jump location where program starts
	SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));

	/**
	 * Set main stack pointer.
	 * This step must be done last otherwise local variables in this function
	 * don't have proper value since stack pointer is located on different position
	 *
	 * Set direct address location which specifies stack pointer in SRAM location
	 */
	__set_MSP(*(uint32_t *)addr);

	/**
	 * Call our function to jump to set location
	 * This will start system memory execution
	 */
	SysMemBootJump();
}

/**
 *	@brief	Mask all EXTI lines of encoders
 */
static void Stop_All_Encoders(){
	uint32_t temp = EXTI->IMR;
	temp &= 0xffff0000;
	EXTI->IMR = temp;
}

/**
 * @brief	Release all EXTI lines masked by StopAllEncoders()
 */
static void Start_All_Encoders(){
	uint32_t temp = EXTI->IMR;
	temp |= 0x0000ffff;
	EXTI->IMR = temp;
}

static inline void Start_MsgTimer(uint32_t tick){
	Msg_Off_Flag = false;
	Msg_Timer_Count = tick;
	Msg_Timer_Enable = true;
}

static inline void Msg_Print(){
	isMsgFlash = true;
}

/**
 * @brief Make MaskKey[],MaskRot[] from keytable[](in key_define.c)
 * @return false : there is some configuration error.
 */
static void	MakeMasks(){
	for(uint8_t scn = 0; scn < SCENE_COUNT; scn++){
		for(uint8_t bit = 0; bit < DEFINES_PER_SCENE; bit++){
			uint32_t	or_bit = (1 << bit);
			MaskKey[scn] |= (keytable[scn][bit].type == TYPE_SWITCH)?	or_bit : 0;
			MaskEnc[scn] |= (keytable[scn][bit].type == TYPE_ROTARY)?	or_bit : 0;
		}
	}
}

/**
 *	@brief	Generate MIDI event and Send to host by User interaction.
 *	@return true : function processed any Key/Encoder event.
 *	@pre	isKeyPressed	any key is pressed or not
 *	@pre	Key_Stat		current key status
 */
static void EmulateMIDI() {
	//! USB MIDI message structure for send
	MIDI_EVENT	USBMIDI_TxEvent;

	if (isKeyPressed) {
		char 		msg_string[MSG_WIDTH + 1];
		uint8_t		bitpos = ntz32(Key_Stat.wd);
		uint32_t	rkey = (Key_Stat.wd);
		bool 		isKeyReport = false;

		if ( Key_Stat.wd & MaskKey[LrScene] ) { //Check Matrix switches
			//Send 'Note On' Event from key matrix
			uint8_t	note = (LrScene * NOTES_PER_SCENE) + bitpos;
			if (bitpos == SCENE_BIT) { //is [SCENE] switch pressed?
			   	//Move to next Scene.
				if((++LrScene) >= SCENE_COUNT){
					LrScene = Lr_SCENE0;
				}
				LED_SetScene(LrScene);
				strcpy(msg_string, scene_name[LrScene]);
			}else{
				LED_SetPulse(keytable[LrScene][bitpos].axis, keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
				sprintf(msg_string, "Note: %3d    S%1d", note, (LrScene % SCENE_COUNT) );
			}
			isKeyReport = true;

			//Print Message to OLED & LED
			if (keytable[LrScene][bitpos].message != NULL) {
				SSD1306_SetScreen(ON);

				strcpy(Msg_Buffer[0], keytable[LrScene][bitpos].message);
				strcpy(Msg_Buffer[1], msg_string);
				Msg_Print();

				Start_MsgTimer(MSG_TIMER_DEFAULT);
			}

			if (isKeyReport == true) {
				//Set 'Note ON
				USBMIDI_TxEvent.header = MIDI_NT_ON;
				USBMIDI_TxEvent.status = MIDI_NT_ON_S;
				USBMIDI_TxEvent.channel = note;
				USBMIDI_TxEvent.value = MIDI_NT_VELOCITY;

				prev_note = note;
				isPrev_sw = true;
			}
		}else if( Key_Stat.wd & MaskEnc[LrScene] ) { //Check encoder's move
			//Send CC Event from encoder
			uint8_t axis = (bitpos - KEY_COUNT) / 2;
			uint8_t val = MIDI_CC_Value[LrScene][axis];
			uint8_t channel = CC_CH_OFFSET + (LrScene * CC_CH_PER_SCENE) + axis;

			USBMIDI_TxEvent.header = MIDI_CC_HEADER;
			USBMIDI_TxEvent.status = MIDI_CC_STATUS;
			USBMIDI_TxEvent.channel = channel;
			USBMIDI_TxEvent.value = val;

			isPrev_sw = false;

			//Print Message to OLED & LED
			if (keytable[LrScene][bitpos].message != NULL) {
				SSD1306_SetScreen(ON);
				sprintf(msg_string,
					((channel > 99)? CC_MSG_3DG : CC_MSG_2DG), channel, val, LrScene);
				strcpy(Msg_Buffer[0], keytable[LrScene][bitpos].message);
				strcpy(Msg_Buffer[1], msg_string);
				Msg_Print();

				Start_MsgTimer(MSG_TIMER_DEFAULT);
			}
			LED_SetPulse(keytable[LrScene][bitpos].axis, keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
			isKeyReport = true;

		} else if (isPrev_sw == true && rkey == 0) {// Switch is released
			//Send 'Note Off' Event
			USBMIDI_TxEvent.header = MIDI_NT_OFF;
			USBMIDI_TxEvent.status = MIDI_NT_OFF_S;
			USBMIDI_TxEvent.channel = prev_note;
			USBMIDI_TxEvent.value = MIDI_NT_VELOCITY;

			isKeyReport = true;
			isPrev_sw = false;
		}

		if (isKeyReport == true) {
			//Send MIDI event via USB
			USBD_LL_Transmit (pInstance, MIDI_IN_EP, (uint8_t *)&USBMIDI_TxEvent, MIDI_EVENT_LENGTH);
			isKeyReport = false;
		}

		/* Clear the switch pressed flag */
		isKeyPressed = false;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//! Indicates 1st Msg_Timer timeout has occurred from power on reset.
	bool Msg_1st_timeout = true;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	Key_Line = L0;
	Msg_Off_Flag = false;
	Msg_Timer_Enable = false;
	Msg_Timer_Count = MSG_TIMER_DEFAULT;
	isMsgFlash = false;
	isRender = true;

	LrState = LR_RESET;
	LrScene = Lr_SCENE0;

	isPrev_sw = false;
	isLEDsendpulse = false;
	Msg_Timer_Update = false;
	LED_Timer_Update = false;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM14_Init();
//MX_USB_DEVICE_Init();
  MX_I2C2_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */
	//Stop All Encoders until USB link up
	Stop_All_Encoders();
	//Initialize Switch matrix
	HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, GPIO_PIN_SET);	//Initialize L0-3.
	MakeMasks();

	//Initialize series of WS2812C
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_0;	//Pull up PA6 (WS2812C-2020 workaround)
	GPIOA->ODR |= GPIO_PIN_6;				//'RESET' state
	//AF -> GPIO
	GPIOA->MODER &= ~(GPIO_MODER_MODER6_1);
	GPIOA->MODER |=	GPIO_MODER_MODER6_0;

	LED_Initialize();						//Set all LEDs to 'OFF'

	//Initialize SSD1306 OLED
	HAL_Delay(SSD1306_PWRUP_WAIT);		//Wait for OLED module power up.
	SSD1306_Initialize();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint32_t	nc_count = 0;

	HAL_TIM_Base_Start_IT(&htim6);		//Start LED timer.
	HAL_TIM_Base_Start_IT(&htim7);		//Start Message timer.
	Start_MsgTimer(MSG_TIMER_DEFAULT);
	LrState = LR_USB_NOLINK;

	//Check SW1 and SW3 at Power On
	if ((GPIOA->IDR & SWMASK) == (SW1)){
		LrState = LR_USB_DFU;
	} else {
		MX_USB_DEVICE_Init();
	}

	//Initialize CC Value table
	memset(MIDI_CC_Value, MIDI_CC_INITIAL, CC_COUNT);

	//LED Initialize
	LED_SetScene(LrScene);

	//Main loop
	while (1) {
	if (LrState == LR_USB_LINKUP) {
		//USB device configured by host
		SSD1306_SetScreen(ON);
		HAL_TIM_Base_Start_IT(&htim1);		//Start Switch matrix timer.
		htim15.Instance->CNT = TIM_PERIOD_DCHAT;
		HAL_TIM_Base_Start(&htim15);      //Start De-chatter timer.
		Start_All_Encoders();				//Start rotary encoder.

#ifdef DEBUG
		sprintf(Msg_Buffer[0], CONN_MSG_D, Lr_PRODUCT, USBD_DEVICE_VER_MAJ, USBD_DEVICE_VER_MIN);
		memset(Msg_Buffer[1], (int)SPACE_CHAR, MSG_WIDTH );
		Msg_Print();
#else
		SSD1306_LoadBitmap();
		sprintf(Msg_Buffer[0], CONN_MSG, USBD_DEVICE_VER_MAJ, USBD_DEVICE_VER_MIN);
		SSD1306_RenderBanner(Msg_Buffer[0], 88, 16);
		SSD1306_FlashScreen();
#endif
		Start_MsgTimer(MSG_TIMER_DEFAULT);
		memcpy(LEDColor,LED_Scene[LrScene],LED_COUNT);
		LED_SetPulse(LED_IDX_ENC0, LED_MINT, LED_TIM_CONNECT);
		LrState = LR_USB_LINKED;

	} else if (LrState == LR_USB_LINKED) {
		//Operate as MIDI Instruments.
		EmulateMIDI();
	} else if (LrState == LR_USB_LINK_LOST) {
		LrScene	= Lr_SCENE0;
		Stop_All_Encoders();
		HAL_TIM_Base_Stop(&htim1);

		LED_TestPattern();
		Msg_1st_timeout = false;
		Start_MsgTimer(MSG_TIMER_DEFAULT);
		nc_count = 0;
		LrState = LR_USB_NOLINK;

	} else if (LrState == LR_USB_NOLINK) {
		//USB can't be configured or disconnected by host.
		if (Msg_Off_Flag == true) {
			if (Msg_1st_timeout == true) {
				LrState = LR_USB_LINK_LOST;
			} else { // 2nd or more
				sprintf(Msg_Buffer[0], "%12ld", nc_count++);
				SSD1306_SetScreen(ON);

				Msg_Print();

				//Restart OLED timer.
				Start_MsgTimer(MSG_TIMER_NOLINK);

				//Rotate LED colors
				uint8_t	tempcolor = LEDColor[7];
				LEDColor[7] = LEDColor[6];
				LEDColor[6] = LEDColor[5];
				LEDColor[5] = LEDColor[4];
				LEDColor[4] = LEDColor[3];
				LEDColor[3] = LEDColor[2];
				LEDColor[2] = LEDColor[1];
				LEDColor[1] = LEDColor[0];
				LEDColor[0] = tempcolor;

				isLEDsendpulse = true;
			}
		}// Msg_Off_Flag
	} else if (LrState == LR_USB_DFU) {
		if (Msg_Off_Flag == true) {
			if (nc_count == 0){
				strcpy(Msg_Buffer[0], "DFU Bootloader.");
				SSD1306_SetScreen(ON);
				Msg_Print();
				nc_count++;
			}else if(nc_count == 1){
				LED_TestPattern();
				nc_count++;
			}else if (nc_count <= 2){
				Jump2SystemMemory();
			}
			Start_MsgTimer(MSG_TIMER_NOLINK/2);
		}

	}// LrState

	//LED Timer
	if (LED_Timer_Update == true) { //24ms interval
		for (uint8_t i = 0; i < LED_COUNT; i++){
			if (LEDTimer[i] != LED_TIMER_CONSTANT && --LEDTimer[i] == 0) {
				LED_SetPulse(i, LED_Scene[LrScene][i], LED_TIMER_CONSTANT);
			}
		}
		LED_Timer_Update = false;
		continue;
	}

	//Flashing LEDs
	if (isLEDsendpulse == true) {
		if (LED_SendPulse() == true) {
			isLEDsendpulse = false;
		} else {
			HAL_Delay(LED_TIM_RETRY_WAIT);	// i2c is busy, retry with interval
		}
		continue;
	}

	//OLED timer
	if (Msg_Timer_Update == true) {	//32.7ms interval
		if (Msg_Timer_Enable == true && (--Msg_Timer_Count) <= 0) {
			Msg_Timer_Enable = false;
			Msg_Off_Flag = true;
		}
		Msg_Timer_Update = false;
		continue;
	}

	//OLED off Timer
	if (Msg_Off_Flag == true) {
		Msg_Off_Flag = false;
		SSD1306_SetScreen(OFF);
		SSD1306_ClearBuffer();
		continue;
	}

	//Flashing OLED.
	if (isMsgFlash == true) {
		if (isRender == true) {
			SSD1306_Render2Buffer();
			isRender = false;
		}
		if (SSD1306_FlashScreen() == true) {
			isMsgFlash = false;	// success to flash
			isRender = true;
		} else {
			HAL_Delay(I2C_RETRY_WAIT);	// i2c is busy, retry with interval
		}
		continue;
	}
#ifndef DEBUG
	HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
#endif
  /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x0090194B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = TIM_PRESC_1uS;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = TIM_PERIOD_KEY_MTRX;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = PWM_PERIOD;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
	hdma_tim3_ch1_trig.Instance->CCR &= ~(DMA_CCR_HTIE | DMA_CCR_TEIE);		//Disable DMA1 half or error transfer interrupt(for LEDs).
  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = TIM_PRESC_1uS;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = TIM_PERIOD_RGBLED;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = TIM_PRESC_1uS;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = TIM_PERIOD_OLED;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = TIM_PRESC_1uS;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = TIM_PERIOD_NPIX;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */
  htim14.Instance->CR1 |= TIM_CR1_OPM;
  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = TIM_PRESC_100uS;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = TIM_PERIOD_DCHAT;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */
  htim15.Instance->CR1 |= TIM_CR1_OPM;
  /* USER CODE END TIM15_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_5_6_7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, L0_Pin|L3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L1_Pin|L2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENC5B_Pin ENC3A_Pin ENC3B_Pin */
  GPIO_InitStruct.Pin = ENC5B_Pin|ENC3A_Pin|ENC3B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC4A_Pin ENC4B_Pin */
  GPIO_InitStruct.Pin = ENC4A_Pin|ENC4B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : M0_Pin M1_Pin M2_Pin M3_Pin */
  GPIO_InitStruct.Pin = M0_Pin|M1_Pin|M2_Pin|M3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC0A_Pin ENC0B_Pin */
  GPIO_InitStruct.Pin = ENC0A_Pin|ENC0B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC6A_Pin ENC2A_Pin ENC2B_Pin ENC5A_Pin
                           ENC6B_Pin ENC7A_Pin ENC7B_Pin ENC1A_Pin
                           ENC1B_Pin */
  GPIO_InitStruct.Pin = ENC6A_Pin|ENC2A_Pin|ENC2B_Pin|ENC5A_Pin
                          |ENC6B_Pin|ENC7A_Pin|ENC7B_Pin|ENC1A_Pin
                          |ENC1B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : L0_Pin L3_Pin */
  GPIO_InitStruct.Pin = L0_Pin|L3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : L1_Pin L2_Pin */
  GPIO_InitStruct.Pin = L1_Pin|L2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

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
	strcpy(Msg_Buffer[0], "Error");
	Msg_Print();
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
