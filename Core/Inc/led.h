/**
 * 	@file		led.h
 *	@brief		(WS2812B style) RGB LEDs control functions.
 *	@author		remov-b4-flight
 *	@copyright	3-Clause BSD License
 */

#ifndef _LED_H    /* Guard against multiple inclusion */
#define _LED_H

#include <stdint.h>
#include <stdbool.h>
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

//! constants for expressing LED light color.
enum led_color_t {
	LED_OFF = 0,//!< LED_COLOR_OFF
	LED_RED,	//!< LED_COLOR_RED
	LED_BLUE,	//!< LED_COLOR_BLUE
	LED_GREEN,	//!< LED_COLOR_GREEN
	LED_WHITE,	//!< LED_COLOR_WHITE
	LED_YELLOW,	//!< LED_COLOR_YELLOW
	LED_MAGENTA,//!< LED_COLOR_MAGENTA
	LED_CYAN,	//!< LED_COLOR_CYAN
	LED_ORANGE,	//!< LED_COLOR_ORANGE
	LED_GLAY,	//!< LED_COLOR_GLAY
	LED_DARK,	//!< LED_COLOR_DARK
	LED_HILIGHT,//!< LED_COLOR_HILIGHT
	LED_PINK,
	LED_MINT,
};
#define COLOR_MAX 14

//! @defgroup LrTMAX board definition
#define LED_COUNT		8
#define BITS_PER_LED	24  // (RGB) 3 * 8bit
#define TOTAL_BITS		(LED_COUNT * BITS_PER_LED)

//! @defgroup LED intensity definition
#define LHIL	0xC0
#define LBRIGHT	0x80
#define LMAX	0x78
#define L43		0x58
#define LHLF	0x38
#define LQTR	0x20
#define LDRK	0x10
#define LMIN	0x08
#define LOFF	0x00

//! LED counter value to constantly 'on'
#define LED_TIMER_CONSTANT	0xFF

#define	LED_IDX_ENC0	0
//! timer constant for LED reset.
#define LED_RESET_WIDTH	330	//in usec.(more than 280)

/**
 * @typedef RGB LED intensity definition
 * @brief used for set RGB LED intensity definition.
 * this is union used for set values as .rgbw form in your codes.
 * in the codes that makes data for RGB LEDs, .n 32bit numeric is used.
 */
typedef union leddata_t {
	uint32_t	n;
	struct	rgbw_t {
		uint8_t	padding;
		uint8_t	b;
		uint8_t	r;
		uint8_t g;
	}	rgbw;
} LEDDATA;

/* Exported functions prototypes ---------------------------------------------*/
	void LED_Initialize();
	void LED_TestPattern();
	void LED_SetPulse(uint8_t index, uint8_t color,uint8_t pulse);
	bool LED_SendPulse();
	void LED_SetScene(uint8_t scene);
	/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _LED_H */

/* *****************************************************************************
 End of File
 */
