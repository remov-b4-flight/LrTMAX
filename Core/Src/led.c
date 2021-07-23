/**
 *	@file	led.c
 *	@brief (WS2812B style) RGB LEDs control functions
 *	@author	remov-b4-flight
 *	@copyright	GPLv3
*/

#include <string.h>
#include "main.h"
#include "led.h"

extern TIM_HandleTypeDef htim3;
extern bool	isLEDsendpulse;
uint8_t		LEDColor[LED_COUNT];	// coded LED color value
uint16_t	LEDPulse[TOTAL_BITS + 1];	// Data formed PWM width send to LED
uint8_t		LEDTimer[LED_COUNT];	// Individual LED Timer Counter

/**
 * @brief RGB LED intensity table
 * @details define Light intensity for each R,G,B
 * values forms array indexed by LED_COLOR_XXX (in enum led_color_t)
 */
const LEDDATA LEDTable[COLOR_MAX] = {
	//			R		G		B
	{.rgbw = {.r=LOFF,.g=LOFF,.b=LOFF}},//COLOR_OFF,
	{.rgbw = {.r=LMAX,.g=LOFF,.b=LOFF}},//COLOR_RED,
	{.rgbw = {.r=LOFF,.g=LOFF,.b=LMAX}},//COLOR_BLUE,
	{.rgbw = {.r=LOFF,.g=LMAX,.b=LOFF}},//COLOR_GREEN,
	{.rgbw = {.r=LMAX,.g=LMAX,.b=LMAX}},//COLOR_WHITE,
	{.rgbw = {.r=LHLF,.g=LHLF,.b=LOFF}},//COLOR_YELLOW,
	{.rgbw = {.r=LHLF,.g=LOFF,.b=LHLF}},//COLOR_MAGENTA,
	{.rgbw = {.r=LOFF,.g=LHLF,.b=LHLF}},//COLOR_CYAN,
	{.rgbw = {.r=LMAX,.g=LQTR,.b=LOFF}},//COLOR_ORANGE,
	{.rgbw = {.r=LQTR,.g=LQTR,.b=LQTR}},//COLOR_GLAY,
	{.rgbw = {.r=LDRK,.g=LDRK,.b=LDRK}},//COLOR_DARK,
	{.rgbw = {.r=LHIL,.g=LHIL,.b=LHIL}},//COLOR_HILIGHT,
	{.rgbw = {.r=LMAX,.g=LHLF,.b=LMAX}},//COLOR_PINK,
};

/**
 * @brief	LED Initialize - Sets all LEDs to 'OFF'
 * @pre		TIM3 Initialized.
 */
void LED_Initialize(){
	memset(LEDColor, LED_OFF, LED_COUNT);
	memset(LEDTimer, LED_TIMER_CONSTANT, LED_COUNT);
	LED_SendPulse();
}
/**
 *	@brief	Sets decorative color pattern to LEDs.
 */
void LED_TestPattern(){
	LEDColor[0] = LED_WHITE;
	LEDColor[1] = LED_RED;
	LEDColor[2] = LED_ORANGE;
	LEDColor[3] = LED_YELLOW;
	LEDColor[4] = LED_GREEN;
	LEDColor[5] = LED_CYAN;
	LEDColor[6] = LED_BLUE;
	LEDColor[7] = LED_MAGENTA;

	LED_SendPulse();
}
/**
 *	@brief	Make LED flashing by setting LEDTimer[]
 *	@param	index	index of LEDs.
 *	@param	color	color of LED.
 *	@param	pulse	duration of pulse in 4ms unit(i.e. pulse=25 => 100ms).
 */
inline void LED_SetPulse(uint8_t index, uint8_t color, uint8_t pulse){
	LEDColor[index] = color;
    LEDTimer[index] = pulse;	// 16ms unit (i.e. pulse=25 => 400ms)
	isLEDsendpulse = true;
}

/**
 *	@brief	make LEDPulse[] from LEDColor[]
 *	@pre	LEDColor[] contains LED color setting.
 */
static void Color2Pulse(){
	uint8_t	pulse = 0;
	LEDDATA	leddata;

	for(uint8_t	led = 0; led < LED_COUNT; led++){
		uint8_t c = LEDColor[led];
		leddata.n = LEDTable[c].n;
		for (uint32_t mask = 0x80000000; mask > 0x80; mask >>= 1){
			LEDPulse[pulse++] = (leddata.n & mask)? PWM_HI:PWM_LO;
		}
	}
	LEDPulse[TOTAL_BITS] = 0;//(PWM_PERIOD + 1);
}

/**
 *	@brief	Send PWM pulses to LEDs rely on LEDColor[] array
 *	@pre	LEDPulse[] contains pulse width array.
 *	@return	result of Send
 */
bool LED_SendPulse(){

	bool r = true;
	//Convert LEDColor[] to LEDPulse[]
	Color2Pulse();

	//Send 'RESET' signal(280us > low data) for LEDs
	GPIOA->ODR |= GPIO_PIN_6;	//'RESET' state
	//AF -> GPIO
	GPIOA->MODER &= ~(GPIO_MODER_MODER6_1);
	GPIOA->MODER |=	GPIO_MODER_MODER6_0;
#if 0
	Delay_us(LED_RESET_WIDTH);
#else
	HAL_Delay(1);
#endif
	//GPIO -> AF
	GPIOA->MODER ^= (GPIO_MODER_MODER6_1|GPIO_MODER_MODER6_0);
	htim3.Instance->CNT = (PWM_PERIOD);

	//Start DMA
	if (HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)LEDPulse, TOTAL_BITS + 1) != HAL_OK){
		r = false;
	}
	return r;
}

/* ******************************************************* **** END OF FILE****/
