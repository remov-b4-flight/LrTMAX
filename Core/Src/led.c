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
uint32_t period;
uint8_t	LEDColor[LED_COUNT];	// coded LED color value
uint8_t	LEDPulse[TOTAL_BITS];	// Data formed PWM width send to LED
uint8_t	LEDTimer[LED_COUNT];	// Individual LED Timer Counter

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
	{.rgbw = {.r=LMAX,.g=LHLF,.b=LOFF}},//COLOR_ORANGE,
	{.rgbw = {.r=LQTR,.g=LQTR,.b=LQTR}},//COLOR_GLAY,
	{.rgbw = {.r=LDRK,.g=LDRK,.b=LDRK}},//COLOR_DARK,
};

/**
 * @brief	LED Initialize - Sets all LEDs to 'OFF'
 */
void LED_Initialize(){
	memset(LEDColor, LED_COLOR_OFF, LED_COUNT);
	memset(LEDTimer, LED_TIMER_CONSTANT, LED_COUNT);

	LED_SendPulse();
}
/**
 *	@brief	Sets decorative color pattern to LEDs.
 */
void LED_TestPattern(){
	LEDColor[0] = LED_COLOR_WHITE;
	LEDColor[1] = LED_COLOR_RED;
	LEDColor[2] = LED_COLOR_ORANGE;
	LEDColor[3] = LED_COLOR_YELLOW;
	LEDColor[4] = LED_COLOR_GREEN;
	LEDColor[5] = LED_COLOR_BLUE;
	LED_SendPulse();
}
#if 0
/**
 *	@brief	Flush a LED immediately with LEDColor[]
 *	@param	index	index of LEDs.
 *	@param	color	color of LED.
 */
void LED_Set_Quick(uint8_t index, uint8_t color){
	LEDColor[index] = color;
	LED_SendPulse();
}
#endif
/**
 *	@brief	Set single LEDColor[] value to flush LED at loop in main()
 *	@param	index	index of LEDs.
 *	@param	color	color of LED
 * 	@attention	Difference of LED_Set() and LED_Set_Quick() is
 * 	Using LED_Set(), Real flash LED point is pended until return to main().
 * 	Using LED_Set_Quick() , It flashes LEDs immediately.
 */
inline void LED_Set(uint8_t index, uint8_t color){
	LEDColor[index] = color;
	isLEDsendpulse = true;
}

/**
 *	@brief	Make LED flashing by setting LEDTimer[]
 *	@param	index	index of LEDs.
 *	@param	color	color of LED.
 *	@param	pulse	duration of pulse in 4ms unit(i.e. pulse=25 => 100ms).
 */
inline void LED_SetPulse(uint8_t index, uint8_t color, uint8_t pulse){
	LEDColor[index] = color;
    LEDTimer[index] = pulse;	// 4ms unit (i.e. pulse=25 => 100ms)
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
}

/**
 *	@brief	Send PWM pulses to LEDs rely on LEDColor[] array
 *	@pre	LEDPulse[] contains pulse width array.
 */
void LED_SendPulse(){

	//Convert LEDColor[] to LEDPulse[]
	Color2Pulse();

	//Send 'RESET' signal(280us > low data) for LEDs
	Delay_us(LED_RESET_WIDTH);
	//End of RESET

	//Start DMA
	htim3.Instance->CNT = PWM_HI + 1;
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)LEDPulse, TOTAL_BITS);
}

/* ******************************************************* **** END OF FILE****/
