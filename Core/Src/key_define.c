/**
* @file key_define.c
* @brief HID key definition & MIDI channel definition
* @details This file defines 'key code' sent to PC on HID build OR MIDI Control Change(CC) / Note ON-OFF event on MIDI build.
* LrE-6 has 6 encoder as enc0~5, and 10 individual switch(SW) as SW1~10 and SW on encoder as 'enc0~5 push'
* In MIDI use , users can send individual CC/Note event channel per switch and encoder.
* At switches, LrTMAX sends Note message has velocity= 127 when switch on, and sends velocity = 0 when switch off.
* At encoder, LrTMAX sends CC message every encoders move,values are increase/decrease by towards.
* LrE-6 MIDI can use 'Scene'. Users can alter all SW/Encoder definition. To alter Scene, push SW10.
* Users can use up to 4 Scenes. SW10 is fixed for Scene function.
*
* Scene / CC event channel definition (by Encoders)
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
const char *scene_name[SCENE_COUNT] = {
/*		 0123456789ABCDEF */
		"Library",
		"Basic Edits",
		"Tone Curve",
		"Color Balance",
};
//! LED patterns that set by switching scenes.
const uint8_t LED_Scene[SCENE_COUNT][LED_COUNT] = {
	//0					1					2					3					4					5				6				7
	{LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene0
	{LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,		LED_COLOR_OFF,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene1
	{LED_COLOR_OFF,		LED_COLOR_DARK,		LED_COLOR_GLAY,		LED_COLOR_WHITE,	LED_COLOR_HILIGHT,	LED_COLOR_OFF,	LED_COLOR_OFF,	LED_COLOR_OFF	},	//Scene2
	{LED_COLOR_OFF,		LED_COLOR_RED,		LED_COLOR_ORANGE,	LED_COLOR_YELLOW,	LED_COLOR_GREEN,	LED_COLOR_CYAN,	LED_COLOR_BLUE,	LED_COLOR_MAGENTA},	//Scene3
};

//! @union Key/encoder configuration table
const KEY_DEFINE keytable[SCENE_COUNT][KEY_DEFINE_COUNT] = {
	{	//Scene0 Button (Library Tab)                                                                   			0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate 0"},			//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate 1"},			//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate 2"},			//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate 3"},			//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Rate 4"},			//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "2nd Monitor"},		//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Undo"},				//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_LONG,		.message = "Scene 0"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Reject"},			//L2M0	enc0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Rate reset"},		//L2M1	enc1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Flag reset"},		//L2M2	enc2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = NULL},				//L2M3	enc3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Add Quick Colle."},	//L3M0	enc4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Zoom reset"},		//L3M1	enc5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "A6p"},				//L3M2	enc6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "A7p"},				//L3M3	enc7 push
		//Scence0 Encoders																							0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Next \x7b"},		//enc0 CW cursor right
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Prev. \x7c"},		//enc0 CCW cursor left
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Rate \x7d"},		//enc1 CW
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Rate \x7e"},		//enc1 CCW
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Flag \x7d"},		//enc2 CW
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Flag \x7e"},		//enc2 CCW
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Rotate \x7b"},		//enc3 CW
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Rotate \x7c"},		//enc3 CCW
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Scroll \x7e"},		//enc4 CW
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Scroll \x7d"},		//enc4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Zoom In"},			//enc5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Zoom Out"},			//enc5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7b"},			//enc6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7c"},			//enc6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A7\x7b"},			//enc7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A7\x7c"},			//enc7 CCW
	},{	//Scene1 Button	(Basic Edits)																				0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "W/B Auto"},			//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Auto Tone"},		//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_DEFAULT,	.message = "DayLight"},			//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Tungsten"},			//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_DEFAULT,	.message = "Fluorescent"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "W/B Cloud"},		//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Undo"},				//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_LONG,		.message = "Scene 1"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Reject"},			//L2M0	enc0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_DEFAULT,	.message = "C-temp. reset"},	//L2M1	enc1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_DEFAULT,	.message = "Tint reset"},		//L2M2	enc2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_DEFAULT,	.message = "Expo. reset"},		//L2M3	enc3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_DEFAULT,	.message = "Contra. reset"},	//L3M0	enc4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_DEFAULT,	.message = "Vibra. reset"},		//L3M1	enc5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_DEFAULT,	.message = "A6p"},				//L3M2	enc6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "A7p"},				//L3M3	enc7 push
		//Scence1 Encoders																							0123456879ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Next \x7b"},		//enc0 CW
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Prev. \x7d"},		//enc0 CCW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Color-Temp. \x7d"},	//enc1 CW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_HALF,		.message = "Color-Temp. \x7e"},	//enc1 CCW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_HALF,		.message = "Magenta"},			//enc2 CW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Green"},			//enc2 CCW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_GLAY,	.duration = LED_TIMER_HALF,		.message = "Exposure \x7d"},	//enc3 CW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "Exposure \x7e"},	//enc3 CCW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_GLAY,	.duration = LED_TIMER_HALF,		.message = "Contrast \x7d"},	//enc4 CW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "Contrast \x7e"},	//enc4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_GLAY,	.duration = LED_TIMER_HALF,		.message = "Vibrance \x7d"},	//enc5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "Vibrance \x7e"},	//enc5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7b"},			//enc6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7c"},			//enc6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_DEFAULT,	.message = "A7\x7b"},			//enc7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "A7\x7c"},			//enc7 CCW
	},{	//Scene2 Button	(Tone Curve)																				0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword1"},			//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword2"},			//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword3"},			//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword4"},			//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword5"},			//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Keyword6"},			//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Undo"},				//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_LONG,		.message = "Scene 2"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Reject"},			//L2M0	enc0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Black reset"},		//L2M1	enc1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Shadows reset"},	//L2M2	enc2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Hilights reset"},	//L2M3	enc3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "White reset"},		//L3M0	enc4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_GLAY,	.duration = LED_TIMER_DEFAULT,	.message = "A5p"},				//L3M1	enc5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_DEFAULT,	.message = "A6p"},				//L3M2	enc6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "A7p"},				//L3M3	enc7 push
		//Scence2 Encoders																							0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Next \x7b"},		//enc0 CW cursor right
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Prev. \x7c"},		//enc0 CCW cursor left
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_HALF,		.message = "Black \x7d"},		//enc1 CW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "Black \x7e"},		//enc1 CCW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "Shadows \x7d"},		//enc2 CW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_DARK,	.duration = LED_TIMER_HALF,		.message = "Shadows \x7e"},		//enc2 CCW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_HILIGHT,	.duration = LED_TIMER_HALF,		.message = "HiLights \x7d"},	//enc3 CW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "HiLights \x7e"},	//enc3 CCW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_HILIGHT,	.duration = LED_TIMER_HALF,		.message = "White \x7d"},		//enc4 CW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_HALF,		.message = "White \x7e"},		//enc4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "A5\x7b"},			//enc5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_HALF,		.message = "A5\x7c"},			//enc5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7b"},			//enc6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "A6\x7c"},			//enc6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_DEFAULT,	.message = "A7\x7b"},			//enc7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "A7\x7c"},			//enc7 CCW
	},{	//Scene3 Button	(Color Balance)																				0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Enable Detail"},	//L0M0	SW1
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "RedEye"},			//L0M1	SW2
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Lens Colle."},		//L0M2	SW3
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Upright Full"},		//L0M3	SW4
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Auto Upright"},		//L1M0	SW5
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_DEFAULT,	.message = "Upright Horizon"},	//L1M1	SW6
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_OFF,		.duration = LED_TIMER_DEFAULT,	.message = "Upright Vert."},	//L1M2	SW7
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_LONG,		.message = "Scene 3"},			//L1M3	SW8 [SCENE]
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Reject"},			//L2M0	enc0 push
		{.type = TYPE_SWITCH,	.axis = 1,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_DEFAULT,	.message = "Red reset"},		//L2M1	enc1 push
		{.type = TYPE_SWITCH,	.axis = 2,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Orange reset"},		//L2M2	enc2 push
		{.type = TYPE_SWITCH,	.axis = 3,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Yellow reset"},		//L2M3	enc3 push
		{.type = TYPE_SWITCH,	.axis = 4,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Green reset"},		//L3M0	enc4 push
		{.type = TYPE_SWITCH,	.axis = 5,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Cyan reset"},		//L3M1	enc5 push
		{.type = TYPE_SWITCH,	.axis = 6,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Blue reset"},		//L3M2	enc6 push
		{.type = TYPE_SWITCH,	.axis = 7,	.color = LED_COLOR_WHITE,	.duration = LED_TIMER_DEFAULT,	.message = "Magenta reset"},	//L3M3	enc7 push
		//Scence3 Encoders																							0123456789ABCDEF
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Next \x7b"},		//enc0 CW cursor right
		{.type = TYPE_SWITCH,	.axis = 0,	.color = LED_COLOR_RED,		.duration = LED_TIMER_DEFAULT,	.message = "Prev. \x7c"},		//enc0 CCW cursor left
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_RED,		.duration = LED_TIMER_HALF,		.message = "Red \x7d"},			//enc1 CW
		{.type = TYPE_ROTARY,	.axis = 1,	.color = LED_COLOR_RED,		.duration = LED_TIMER_HALF,		.message = "Red \x7e"},			//enc1 CCW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Orange \x7d"},		//enc2 CW
		{.type = TYPE_ROTARY,	.axis = 2,	.color = LED_COLOR_ORANGE,	.duration = LED_TIMER_HALF,		.message = "Orange \x7e"},		//enc2 CCW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Yellow \x7d"},		//enc3 CW
		{.type = TYPE_ROTARY,	.axis = 3,	.color = LED_COLOR_YELLOW,	.duration = LED_TIMER_HALF,		.message = "Yellow \x7e"},		//enc3 CCW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Green \x7d"},		//enc4 CW
		{.type = TYPE_ROTARY,	.axis = 4,	.color = LED_COLOR_GREEN,	.duration = LED_TIMER_HALF,		.message = "Green \x7e"},		//enc4 CCW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_HALF,		.message = "Cyan \x7d"},		//enc5 CW
		{.type = TYPE_ROTARY,	.axis = 5,	.color = LED_COLOR_CYAN,	.duration = LED_TIMER_HALF,		.message = "Cyan \x7e"},		//enc5 CCW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Blue \x7d"},		//enc6 CW
		{.type = TYPE_ROTARY,	.axis = 6,	.color = LED_COLOR_BLUE,	.duration = LED_TIMER_DEFAULT,	.message = "Blue \x7e"},		//enc6 CCW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "Magenta \x7d"},		//enc7 CW
		{.type = TYPE_ROTARY,	.axis = 7,	.color = LED_COLOR_MAGENTA,	.duration = LED_TIMER_DEFAULT,	.message = "Magenta \x7e"},		//enc7 CCW
	}
};
#endif
/* ******************************************************* **** END OF FILE****/
