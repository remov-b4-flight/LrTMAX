/**
* @file key_define.c
* @brief HID key definition & MIDI channel definition
* @details This file defines 'key code' sent to PC on HID build OR MIDI Control Change(CC) / Note ON-OFF event on MIDI build.
* LrE-6 has 6 rotator as rot0~5, and 10 individual switch(SW) as SW1~10 and SW on rotator as 'rot0~5 push'
* In MIDI use , users can send individual CC/Note event channel per switch and rotator.
* At switches, LrTMAX sends Note message has velocity= 127 when switch on, and sends velocity = 0 when switch off.
* At rotator, LrTMAX sends CC message every rotators move,values are increase/decrease by towards.
* LrE-6 MIDI can use 'Scene'. Users can alter all SW/Rotator definition. To alter Scene, push SW10.
* Users can use up to 4 Scenes. SW10 is fixed for Scene function.
*
* Scene / CC event channel definition (by Rotators)
* ch. 0~15		Scene0
* ch. 16~31		Scene1
* ch. 32~47		Scene2
* ch. 48~64		Scene3
* Scene / Note definition (by SWs)
* Note	0~15	Scene0
* Note	16~31	Scene1
* Note	32~47	Scene2
* Note	48~64	Scene3
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "key_define.h"
#include "EmulateHID.h"
#include "led.h"

/* Variables ----------------------------------------------------------------*/
#if MIDI
//! User-friendly scene names appears on LCD.
const char *scene_name[SCENE_COUNT] = { "Library", "Tone Curve",  "Color Saturation", "Sharpen", };
//! LED patterns that set by switching scenes.
const uint8_t LED_Scene[SCENE_COUNT][LED_COUNT] = {
	//0					1					2					3					4					5				6				7
	{LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene0
	{LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_DARK,		LED_COLOR_GLAY,		LED_COLOR_WHITE,	LED_COLOR_OFF,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene1
	{LED_COLOR_RED,		LED_COLOR_ORANGE,	LED_COLOR_YELLOW,	LED_COLOR_GREEN,	LED_COLOR_CYAN,		LED_COLOR_BLUE,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene2
	{LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_WHITE,	LED_COLOR_MAGENTA,LED_COLOR_OFF,LED_COLOR_OFF	},	//Scene3
};

//! @union Key/rotator configuration table
const KEY_DEFINE keytable[SCENE_COUNT][KEY_DEFINE_COUNT] = {
	{	//Scene0 Button (Library Tab)                                                                   0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate = 1"},			//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate = 2"},			//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate = 3"},			//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate = 4"},			//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "2nd Monitor"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate = 0"},			//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Add Quick Colle."},	//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_LONG,		.message = "Scene 0"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Reject"},			//L2M0	rot0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Rate reset"},		//L2M1	rot1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Flag reset"},		//L2M2	rot2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L2M3	rot3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Grid View"},		//L3M0	rot4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "People View"},		//L3M1	rot5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M2	rot6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M3	rot7 push
		//Scence0 Rotators																				0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Next \x80"},		//rot0 CW cursor right
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Prev. \x81"},		//rot0 CCW cursor left
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Rate \x82"},		//rot1 CW
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Rate \x83"},		//rot1 CCW
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Flag \x82"},		//rot2 CW
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Flag \x83"},		//rot2 CCW
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Rotate \x80"},		//rot3 CW
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Rotate \x81"},		//rot3 CCW
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Scroll \x82"},		//rot4 CW
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Scroll \x83"},		//rot4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Zoom In"},			//rot5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Zoom Out"},			//rot5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CCW
	},{	//Scene1 Button																					0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "W/B Auto"},			//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Auto Tone"},		//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_DEFAULT,	.message = "DayLight"},			//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Tungsten"},			//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_DEFAULT,	.message = "Fluorescent"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "W/B Cloud"},		//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "W/B Shade"},		//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_LONG,		.message = "Scene 1"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear W/B"},		//L2M0	rot0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Clear Shadow"},		//L2M1	rot1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Dark"},		//L2M2	rot2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Light"},		//L2M3	rot3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Hi-Light"},	//L3M0	rot4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear C-Temp."},	//L3M1	rot5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M2	rot6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M3	rot7 push
		//Scence1 Rotators																				0123456879ABCDEF
		{.type = TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Magenta"},			//rot0 CW
		{.type = TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Green"},			//rot0 CCW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Shadows \x82"},		//rot1 CW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Shadows \x83"},		//rot1 CCW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Darks \x82"},		//rot2 CW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Darks \x83"},		//rot2 CCW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_GLAY,	.duration = LED_TIMER_HALF,		.message = "Lights \x82"},		//rot3 CW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Lights \x83"},		//rot3 CCW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "Hi-Light \x82"},	//rot4 CW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Hi-Light \x83"},	//rot4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Color-Temp. \x82"},	//rot5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Color-Temp. \x83"},	//rot5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CCW
	},{	//Scene2 Button																					0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 1"},		//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 2"},		//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 3"},		//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 4"},		//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 6"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword 7"},		//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "GrayScale"},		//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_LONG,		.message = "Scene 2"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Sat Red"},	//L2M0	rot0 push
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clr Sat. Orange"},	//L2M1	rot1 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clr Sat. Yellow"},	//L2M2	rot2 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clr Sat. Green"},	//L2M3	rot3 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Sat. Cyan"},	//L3M0	rot4 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Sat. Blue"},	//L3M1	rot5 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M2	rot6 push
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M3	rot7 push
		//Scence2 Rotators																				0123456789ABCDEF
		{.type = TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Red \x82"},		//rot0 CW
		{.type = TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Red \x83"},		//rot0 CCW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Orange \x82"},	//rot1 CW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Orange \x83"},	//rot1 CCW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Yellow \x82"},	//rot2 CW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Yellow \x83"},	//rot2 CCW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Green \x82"},	//rot3 CW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Green \x83"},	//rot3 CCW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Cyan \x82"},	//rot4 CW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Cyan \x83"},	//rot4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Blue \x82"},	//rot5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Blue \x83"},	//rot5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CCW
	},{	//Scene3 Button																					0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Enable Detail"},	//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "RedEye"},			//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Lens Collection"},	//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Upright Full"},		//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Auto Upright"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Upright Horizon"},	//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Upright Vertical"},	//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_LONG,		.message = "Scene 3"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Sharp"},		//L2M0	rot0 push
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Tilt"},		//L2M1	rot1 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Vibrancy"},	//L2M2	rot2 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear DeHaze"},		//L2M3	rot3 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clear Sat. All"},	//L3M0	rot4 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Clr.Sat. Magenta"},	//L3M1	rot5 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M2	rot6 push
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L3M3	rot7 push
		//Scence3 Rotators																				0123456789ABCDEF
		{.type =TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Sharpen \x82"},		//rot0 CW
		{.type =TYPE_ROTARY,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Sharpen \x83"},		//rot0 CCW
		{.type =TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_HALF,		.message = "Tilt \x80"},		//rot1 CW
		{.type =TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Tilt \x81"},		//rot1 CCW
		{.type =TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_RED,		.duration = LED_TIMER_HALF,		.message = "Vibrancy \x82"},	//rot2 CW
		{.type =TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Vibrancy \x83"},	//rot2 CCW
		{.type =TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "De-Haze \x82"},		//rot3 CW
		{.type =TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "De-Haze \x83"},		//rot3 CCW
		{.type =TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.All \x82"},		//rot4 CW
		{.type =TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.All \x83"},		//rot4 CCW
		{.type =TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Magnta \x82"},	//rot5 CW
		{.type =TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Sat.Magnta \x83"},	//rot5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = NULL},				//rot7 CCW
	}
};
#endif
/* ******************************************************* **** END OF FILE****/
