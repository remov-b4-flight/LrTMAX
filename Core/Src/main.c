/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file	main.c
  * @brief	Main program body
  * @author	remov-b4-flight
  * @copyright GPLv3
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
#include "midi.h"
#include "usbd_hid.h"
#include "led.h"
#include "bitcount.h"
#include "key_define.h"
#include "usbd_midi_if.h"
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef DEBUG
#define CONN_MSG	"%s %2x.%02xD"
#else
#define CONN_MSG	"%s %2x.%02x"
#endif
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c2;
DMA_HandleTypeDef hdma_i2c2_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim14;
DMA_HandleTypeDef hdma_tim3_ch1_trig;

/* USER CODE BEGIN PV */
#if !(ENC_9R5KQ)
#error "EC11 encoder is not supported."
#endif
//! STM32 TIM3 instance handle
TIM_HandleTypeDef htim3;
extern	USBD_HandleTypeDef hUsbDeviceFS;
//! LrE-6 USB connection state
uint8_t		LrE6State;
//! LrE-6 scene index
uint8_t		LrE6Scene;
// keyboard variable
//! If true, ISR detected any Key/Encoder was moved.
bool		isKeyPressed;
//! Key pressed/released status set by timer key scanning.
KEYSCAN     Key_Stat;
//! In key scanning wheather Line selected to read for key matrix.
uint8_t		Key_Line;
//! If true, MIDI Event/HID packet is sent by key pressed/encoder moved. if false, not sent.
bool		isKeyRelaseSent;
//! If true, MIDI event previous sent is switch. if false, it's encoder
bool		isPrev_sw;
//! Bit masks for which bit of KEYSCAN variable acts as key.
uint32_t	MaskKey[SCENE_COUNT];
//! Bit masks for which bit of KEYSCAN variable acts as encoder.
uint32_t	MaskEnc[SCENE_COUNT];

// LCD variables
//! Timer counter ticked by end of L3 matrix scanning. (16ms interval).
int32_t		Msg_Timer_Count;
//! If true Msg_Timer counting is enabled.
bool		Msg_Timer_Enable;
//! If true, Screen is cleared in main() that is determined on timer interrupt.
bool		Msg_Off_Flag;
//! Indicates 1st Msg_Timer timeout has occured from power on reset.
bool		Msg_1st_timeout;
//! If true, Screen is flashed by Msg_Buffer[] at main() function.
bool		isMsgFlash;
//! If true, frame_buffer[] contents flashes the screen.
bool		isRender;

// LED variables
//! If true, LEDs are flashed by LEDColor[] array.
bool		isLEDsendpulse;
//! Flag is set by timer ISR, It makes LED_Timer[] count up in main()
bool		LED_Timer_Update;

// Scene related
extern	KEY_DEFINE keytable[SCENE_COUNT][KEY_DEFINE_COUNT];
extern	char *scene_name[SCENE_COUNT];
extern uint8_t	led_axis_table[KEY_DEFINE_COUNT];

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
//! USB MIDI message buffer
uint8_t	USBMIDI_Event[4];
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
static void MX_ADC_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */
void EmulateKeyboard();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Delay process in us unit.
 * @param microsec : duration to wait.
 */
void Delay_us(uint32_t microsec){

	htim14.Init.Period = microsec;
	HAL_TIM_Base_Init(&htim14);
	HAL_TIM_Base_Start(&htim14);
	htim14.Instance->SR = 0;

	while((htim14.Instance->SR & TIM_SR_UIF) == 0)	;	//wait until timer up.

	HAL_TIM_Base_Stop(&htim14);
}

static inline void Start_MsgTimer(uint32_t tick){
	Msg_Timer_Count = tick;
	Msg_Timer_Enable = true;
}

static inline void Msg_Print(){
	isMsgFlash = true;
}

/**
 * @brief alter LED contents by scene
 * @param scene	Scene No
 */
static void LED_SetScene(uint8_t scene){
	memcpy(LEDColor, LED_Scene[scene], LED_COUNT);
	LED_SendPulse();
}
/**
 * @brief Make MaskKey[],MaskRot[] from keytable
 * @return false : there is some configuration error.
 */
static bool	MakeMasks(){
	bool ret = true;
	for(uint8_t scn = 0; scn < SCENE_COUNT; scn++){
		for(uint8_t bit = 0; bit < KEY_DEFINE_COUNT; bit++){
			uint32_t	or_bit = (1 << bit);
			MaskKey[scn] |= (keytable[scn][bit].type == TYPE_SWITCH)?	or_bit : 0;
			MaskEnc[scn] |= (keytable[scn][bit].type == TYPE_ROTARY)?	or_bit : 0;
		}
	}
	return ret;
}

/**
 *	@brief	Generate MIDI event and Send to host by User interaction.
 *	@return true : function processed any Key/Encoder event.
 *	@pre	isKeyPressed	any key is pressed or not
 *	@pre	Key_Stat		current key status
 */
static void EmulateMIDI(){
	char msg_string[MSG_WIDTH];

	if (isKeyPressed) {
    	//Send 'Note On' Event from key matrix
        uint8_t		bitpos = ntz32(Key_Stat.wd);
        uint32_t	rkey = (Key_Stat.wd & MOD_SW_BIT_MASK);
        bool 		isKeyReport = false;

        if ( Key_Stat.wd & MaskKey[LrE6Scene] ) { //Matrix switches
        	uint8_t	note = (LrE6Scene * NOTES_PER_SCENE) + bitpos;
        	if (bitpos == SCENE_BIT) { //[SCENE] switch?
               	//Move to next Scene.
            	LrE6Scene++;
            	if(LrE6Scene >= SCENE_COUNT){
            		LrE6Scene = LrE6_SCENE0;
            	}
        		LED_SetScene(LrE6Scene);
        		strcpy(msg_string, scene_name[LrE6Scene]);
            }else{
                LED_SetPulse(keytable[LrE6Scene][bitpos].axis, keytable[LrE6Scene][bitpos].color, keytable[LrE6Scene][bitpos].period);
            	sprintf(msg_string, "Note: %3d    S%1d", note, (LrE6Scene % SCENE_COUNT) );
            }
        	isKeyReport = true;

            //Print Message to LCD & LED
            if (keytable[LrE6Scene][bitpos].message != NULL) {
            	SSD1306_SetScreen(ON);

        		strcpy(Msg_Buffer[0], keytable[LrE6Scene][bitpos].message);
        		strcpy(Msg_Buffer[1], msg_string);
        		Msg_Print();

            	Msg_Off_Flag = false;
            	Start_MsgTimer(MSG_TIMER_DEFAULT);
            }

            if (isKeyReport == true) {
				//Set 'Note ON
				USBMIDI_Event[MIDI_EV_IDX_HEADER] = MIDI_NT_ON;
				USBMIDI_Event[MIDI_EV_IDX_STATUS] = MIDI_NT_ON_S;
				USBMIDI_Event[MIDI_EV_IDX_CHANNEL] = note;
				USBMIDI_Event[MIDI_EV_IDX_VALUE] = MIDI_VELOCITY;

				prev_note = note;
				isPrev_sw = true;
            }
        }else if( Key_Stat.wd & MaskEnc[LrE6Scene] ) {
        	//Send CC Event from encoder
        	uint8_t axis = (bitpos - KEY_COUNT) / 2;
        	uint8_t val = MIDI_CC_Value[LrE6Scene][axis];
        	uint8_t channel = (LrE6Scene * CC_CH_PER_SCENE) + axis;

            USBMIDI_Event[MIDI_EV_IDX_HEADER] = MIDI_CC_HEADER;
            USBMIDI_Event[MIDI_EV_IDX_STATUS] = MIDI_CC_STATUS;
            USBMIDI_Event[MIDI_EV_IDX_CHANNEL] = channel;
            USBMIDI_Event[MIDI_EV_IDX_VALUE] = val;
            isPrev_sw = false;

            //Print Message to LCD & LED
            if (keytable[LrE6Scene][bitpos].message != NULL) {
            	SSD1306_SetScreen(ON);
                sprintf(msg_string,
                	((channel > 99)? "C%3d = %3d    S%1d":"Ch%1d = %3d    S%1d"), channel, val, LrE6Scene);
                strcpy(Msg_Buffer[0], keytable[LrE6Scene][bitpos].message);
            	strcpy(Msg_Buffer[1], msg_string);
            	Msg_Print();

            	Msg_Off_Flag = false;
            	Start_MsgTimer(MSG_TIMER_DEFAULT);
            }
            LED_SetPulse(keytable[LrE6Scene][bitpos].axis, keytable[LrE6Scene][bitpos].color, keytable[LrE6Scene][bitpos].period);
            isKeyReport = true;

        }else if(isPrev_sw == true && rkey == 0) {// Switch is released
			//Send 'Note Off' Event
			USBMIDI_Event[MIDI_EV_IDX_HEADER] = MIDI_NT_OFF;
			USBMIDI_Event[MIDI_EV_IDX_STATUS] = MIDI_NT_OFF_S;
			USBMIDI_Event[MIDI_EV_IDX_CHANNEL] = prev_note;
			USBMIDI_Event[MIDI_EV_IDX_VALUE] = 0;

			isKeyReport = true;
			isPrev_sw = false;
        }

        if(isKeyReport == true){
			//Send MIDI event via USB
		    USBD_LL_Transmit (pInstance, MIDI_IN_EP, USBMIDI_Event, MIDI_EVENT_LENGTH);
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  Key_Line = L0;
  Msg_Off_Flag = false;
  Msg_Timer_Enable = false;
  Msg_Timer_Count = MSG_TIMER_DEFAULT;
  Msg_1st_timeout = true;
  isMsgFlash = false;
  isRender = true;

  LrE6State = LRE6_RESET;
  LrE6Scene	= LrE6_SCENE0;

  isPrev_sw = false;
  isKeyRelaseSent = true;
  isLEDsendpulse = false;
#if 0
  ExpandModifiers();
#endif
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
  MX_ADC_Init();
#if 1
  MX_USB_MIDI_INIT();
#else
  MX_USB_DEVICE_Init();
#endif
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  //Initialize Switch matrix
  HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, GPIO_PIN_SET);	//Initialize L0-3.
  HAL_TIM_Base_Start_IT(&htim1);		//Start Switch matrix timer.
  MakeMasks();

  //Initialze series of WS2812C
  GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_0;	//Pull up PA6 (WS2812C-2020 workaround)
  GPIOA->ODR |= GPIO_PIN_6;				//'RESET' state
  //AF -> GPIO
  GPIOA->MODER &= ~(GPIO_MODER_MODER6_1);
  GPIOA->MODER |=	GPIO_MODER_MODER6_0;

  LED_Initialize();						//Set all LEDs to 'OFF'

  //Initialize SSD1306 OLED
  HAL_Delay(SSD1306_PWRUP_WAIT);		//Wait for LCD module power up.
  SSD1306_Initialize();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  const uint16_t ts_cal110 = *TEMP110_CAL_ADDR;
  const uint16_t ts_cal30 = *TEMP30_CAL_ADDR;
#ifdef DEBUG
  const int16_t k = (110 - 30) * 1000 / (ts_cal110 - ts_cal30);
#else
  const float k = (110.0 - 30.0) / (ts_cal110 - ts_cal30);
#endif

  Start_MsgTimer(MSG_TIMER_DEFAULT);
  Msg_Off_Flag = false;
  LrE6State = LRE6_USB_NOLINK;

  memset(MIDI_CC_Value, MIDI_CC_INITIAL, SCENE_COUNT * ENC_COUNT);

  //Main loop
  while (1) {
	if (LrE6State == LRE6_USB_LINKUP) {
		//USB device configured by host
		LED_SetScene(LrE6Scene);
		SSD1306_SetScreen(ON);
		sprintf(Msg_Buffer[0], CONN_MSG, LrE6_PRODUCT ,USBD_DEVICE_VER_MAJ, USBD_DEVICE_VER_MIN);

#ifdef DEBUG
		Msg_Print();
#else
		SSD1306_LoadBitmap();
		SSD1306_RenderBanner(Msg_Buffer[0], 12, 12, INP);
		SSD1306_FlashScreen();
#endif
		Msg_Off_Flag = false;
		Start_MsgTimer(MSG_TIMER_DEFAULT);
		LED_SetPulse(LED_IDX_ENC0, LED_PINK, LED_TIM_CONNECT);
		LrE6State = LRE6_USB_LINKED;

	} else if (LrE6State == LRE6_USB_LINKED) {
		//Operate as MIDI Instruments.
		EmulateMIDI();
	} else if(LrE6State == LRE6_USB_LINK_LOST) {
		LED_TestPattern();
		Msg_1st_timeout = false;
		Start_MsgTimer(MSG_TIMER_DEFAULT);
		LrE6State = LRE6_USB_NOLINK;

	} else if(LrE6State == LRE6_USB_NOLINK) {
		//USB Not initially configured.
		if (Msg_Off_Flag == true) {
			if (Msg_1st_timeout == true) {
				LrE6State = LRE6_USB_LINK_LOST;
			} else {

				HAL_ADC_Start(&hadc);
				//get value from ADC and display it...
				while (HAL_ADC_PollForConversion(&hadc, 100) != HAL_OK)	; //wait until ADC OK

				uint32_t inner_sensor_val = HAL_ADC_GetValue(&hadc);
				int16_t m = inner_sensor_val - ts_cal30;
#ifdef DEBUG
				uint16_t temp = (k * m) / 100 + 30;
				sprintf(Msg_Buffer[0], "%10d", temp);
//				sprintf(Msg_Buffer[0], "%10ld", inner_sensor_val);
#else
				float temp = (k * (float)m) + 30.0;

				int tempf = (temp * 100);
				int8_t temp_i = tempf / 100;
				int8_t temp_s = tempf % 100;

				sprintf(Msg_Buffer[0], "%02d.%02d degC", temp_i, temp_s);
#endif
				SSD1306_SetScreen(ON);

				Msg_Print();

				//Restart LCD timer.
				Msg_Off_Flag = false;
				Start_MsgTimer(MSG_TIMER_UPDATE);

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
	}// LrE6State

	//LED Timer
	if (LED_Timer_Update == true){ //4x4ms = 16ms interval
		for (uint8_t i = 0; i < LED_COUNT; i++){
			if (LEDTimer[i] != LED_TIMER_CONSTANT && --LEDTimer[i] == 0) {
				LED_SetPulse(i, LED_Scene[LrE6Scene][i], LED_TIMER_CONSTANT);
		 	}
		}
		LED_Timer_Update = false;
		continue;
	}

	//Flashing LEDs
	if (isLEDsendpulse == true) {
		if (LED_SendPulse() == true){
			isLEDsendpulse = false;
		}else{
			HAL_Delay(LED_TIM_RETRY_WAIT);	// i2c is busy, retry with interval
		}
		continue;
	}

	if(Msg_Off_Flag == true){
		Msg_Off_Flag = false;
		SSD1306_SetScreen(OFF);
		SSD1306_ClearBuffer();
		continue;
	}

	//Flashing LCD.
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

	// Enter sleep until next interrupt.
	if(	hdma_tim3_ch1_trig.State != HAL_DMA_STATE_BUSY
		&& hdma_i2c2_tx.State != HAL_DMA_STATE_BUSY) {
		HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
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
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  htim1.Init.Period = TIM_PERIOD_4mS;
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
  htim14.Init.Period = TIM_PERIOD_125uS;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
