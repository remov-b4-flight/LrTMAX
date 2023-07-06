/**
* @file prof_define.c
* @brief MIDI channel/note definition
* @details This file defines MIDI Control Change(CC) / Note ON-OFF message on MIDI.
* LrTMAX has 8 encoder as enc0~7, and 8 individual switch(SW) as SW1~8 and SW on encoder as 'enc0~7 push'
* In MIDI use , users can send individual CC message channel per switch and encoder.
* At switches, LrTMAX sends Note message has velocity= 127 when switch on, and sends velocity = 0 when switch off.
* At encoder, LrTMAX sends CC message every encoders move,values are increase/decrease by towards.
* LrTMAX MIDI can use 'Scene'. Users can alter all SW/Encoder definition. To alter Scene, push SW10.
* Users can use up to 4 Scenes. SW10 is fixed for Scene function.
*
* Scene / CC message channel definition (by Encoder rotations)
* Scene0	ch. 40~47
* Scene1	ch. 48~55
* Scene2	ch. 56~63
* Scene3	ch. 64~71
*
* Scene / Note definition (by Encoder push)
* Scene0	Note 40~47
* Scene1	Note 48~55
* Scene2	Note 56~53
* Scene3	Note 64~71
*
* Scene / Note definition (by SWs)
* Scene0	Note 0~7
* Scene1	Note 8~15
* Scene2	Note 16~23
* Scene3	Note 24~31
*/

/* Includes ------------------------------------------------------------------*/
#include <prof_define.h>
#include "main.h"
#include "LrCommon.h"
#include "led.h"

/* Variables ----------------------------------------------------------------*/
//! User-friendly scene names appears on OLED display.
const char *scene_name[SCENE_COUNT] = {
/*		 0123456789ABCDEF */
		"Library",
		"Basic Edits",
		"Tone Curve",
		"Color Balance",
};
//! LED patterns that set by switching scenes.
const uint8_t LED_Scene[SCENE_COUNT][LED_COUNT] = {
	//0			1			2			3			4			5			6			7
	{LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF	},	//Scene0
	{LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF,	LED_OFF	},	//Scene1
	{LED_OFF,	LED_DARK,	LED_GLAY,	LED_WHITE,	LED_HILIGHT,LED_OFF,	LED_OFF,	LED_OFF	},	//Scene2
	{LED_OFF,	LED_RED,	LED_ORANGE,	LED_YELLOW,	LED_GREEN,	LED_CYAN,	LED_BLUE,	LED_MAGENTA},//Scene3
};
//! @union Switches/Encoders configuration table
const ENC_SW_DEFINE prof_table[SCENE_COUNT][DEFINES_PER_SCENE] = {
	{	//Scene0 switches/encoders push	(Library Tab)
/*N00*/	{.axis = 0,	.color = LED_BLUE,		.period = LED_TIM_HALF},	//L0M0	SW1 'UNDO'
/*N01*/	{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M1	SW2
/*N02*/	{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M3	SW4
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M1	SW6
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M2	SW7
/*N07*/	{.axis = 0,	.color = LED_PINK,		.period = LED_TIM_LONG},	//L1M3	SW8 [SCENE]
/*N40*/	{.axis = 0,	.color = LED_RED,		.period = LED_TIM_NORM},	//L2M0	enc0 push 'reject'
		{.axis = 1,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M1	enc1 push
		{.axis = 2,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M2	enc2 push
		{.axis = 3,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M3	enc3 push
		{.axis = 4,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M1	enc5 push
		{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M2	enc6 push
/*N47*/	{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M3	enc7 push
		//Scence0 encoders rotate
/*C40*/	{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CW
		{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CCW
/*C41*/	{.axis = 1,	.color = LED_GREEN,		.period = LED_TIM_NORM},	//enc1 CW
		{.axis = 1,	.color = LED_GREEN,		.period = LED_TIM_NORM},	//enc1 CCW
/*C42*/	{.axis = 2,	.color = LED_BLUE,		.period = LED_TIM_NORM},	//enc2 CW
		{.axis = 2,	.color = LED_BLUE,		.period = LED_TIM_NORM},	//enc2 CCW
/*C43*/	{.axis = 3,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//enc3 CW
		{.axis = 3,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//enc3 CCW
/*C44*/	{.axis = 4,	.color = LED_CYAN,		.period = LED_TIM_NORM},	//enc4 CW
		{.axis = 4,	.color = LED_CYAN,		.period = LED_TIM_NORM},	//enc4 CCW
/*C45*/	{.axis = 5,	.color = LED_ORANGE,	.period = LED_TIM_NORM},	//enc5 CW
		{.axis = 5,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc5 CCW
/*C46*/	{.axis = 6,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc6 CW
		{.axis = 6,	.color = LED_DARK,		.period = LED_TIM_NORM},	//enc6 CCW
/*C47*/	{.axis = 7,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc7 CW
		{.axis = 7,	.color = LED_DARK,		.period = LED_TIM_NORM},	//enc7 CCW
	},{	//Scene1 switches/encoders push	(Basic Edits)
/*N16*/	{.axis = 0,	.color = LED_BLUE,		.period = LED_TIM_HALF},	//L0M0	SW1 'UNDO'
/*N17*/	{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M1	SW2
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M3	SW4
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M1	SW6
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M2	SW7
/*N23*/	{.axis = 0,	.color = LED_PINK,		.period = LED_TIM_LONG},	//L1M3	SW8 [SCENE]
/*N48*/	{.axis = 0,	.color = LED_RED,		.period = LED_TIM_NORM},	//L2M0	enc0 push 'reject'
		{.axis = 1,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M1	enc1 push
		{.axis = 2,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M2	enc2 push
		{.axis = 3,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M3	enc3 push
		{.axis = 4,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M1	enc5 push
		{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M2	enc6 push
/*N55*/	{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M3	enc7 push
		//Scence1 encoders rotate
/*C48*/	{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CW
		{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CCW
/*C49*/	{.axis = 1,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//enc1 CW
		{.axis = 1,	.color = LED_BLUE,		.period = LED_TIM_NORM},	//enc1 CCW
/*C50*/	{.axis = 2,	.color = LED_MAGENTA,	.period = LED_TIM_NORM},	//enc2 CW
		{.axis = 2,	.color = LED_GREEN,		.period = LED_TIM_NORM},	//enc2 CCW
/*C51*/	{.axis = 3,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc3 CW
		{.axis = 3,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//enc3 CCW
/*C52*/	{.axis = 4,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc4 CW
		{.axis = 4,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//enc4 CCW
/*C53*/	{.axis = 5,	.color = LED_ORANGE,	.period = LED_TIM_NORM},	//enc5 CW
		{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_HALF},	//enc5 CCW
/*C54*/	{.axis = 6,	.color = LED_BLUE,		.period = LED_TIM_NORM},	//enc6 CW
		{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_HALF},	//enc6 CCW
/*C55*/	{.axis = 7,	.color = LED_MAGENTA,	.period = LED_TIM_NORM},	//enc7 CW
		{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_HALF},	//enc7 CCW
	},{	//Scene2 switches/encoders push	(Tone Curve)
/*N32*/	{.axis = 0,	.color = LED_BLUE,		.period = LED_TIM_HALF},	//L0M0	SW1 'UNDO'
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M1	SW2
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M3	SW4
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M1	SW6
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M2	SW7
/*N40*/	{.axis = 0,	.color = LED_PINK,		.period = LED_TIM_LONG},	//L1M3	SW8 [SCENE]
/*N56*/	{.axis = 0,	.color = LED_RED,		.period = LED_TIM_NORM},	//L2M0	enc0 push 'reject'
		{.axis = 1,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M1	enc1 push
		{.axis = 2,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M2	enc2 push
		{.axis = 3,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M3	enc3 push
		{.axis = 4,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M1	enc5 push
		{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M2	enc6 push
/*N63*/	{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M3	enc7 push
		//Scence2 encoders rotate
/*C56*/	{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CW
		{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CCW
/*C57*/	{.axis = 1,	.color = LED_DARK,		.period = LED_TIM_NORM},	//enc1 CW
		{.axis = 1,	.color = LED_OFF,		.period = LED_TIM_HALF},	//enc1 CCW
/*C58*/	{.axis = 2,	.color = LED_WHITE,		.period = LED_TIM_NORM},	//enc2 CW
		{.axis = 2,	.color = LED_DARK,		.period = LED_TIM_HALF},	//enc2 CCW
/*C59*/	{.axis = 3,	.color = LED_HILIGHT,	.period = LED_TIM_NORM},	//enc3 CW
		{.axis = 3,	.color = LED_WHITE,		.period = LED_TIM_HALF},	//enc3 CCW
/*C60*/	{.axis = 4,	.color = LED_HILIGHT,	.period = LED_TIM_NORM},	//enc4 CW
		{.axis = 4,	.color = LED_WHITE,		.period = LED_TIM_HALF},	//enc4 CCW
/*C61*/	{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//enc5 CW
		{.axis = 5,	.color = LED_DARK,		.period = LED_TIM_HALF},	//enc5 CCW
/*C62*/	{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//enc6 CW
		{.axis = 6,	.color = LED_DARK,		.period = LED_TIM_HALF},	//enc6 CCW
/*C63*/	{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//enc7 CW
		{.axis = 7,	.color = LED_DARK,		.period = LED_TIM_HALF},	//enc7 CCW
	},{	//Scene3 switches/endcoders push	(Color Balance)
/*N48*/	{.axis = 0,	.color = LED_BLUE,		.period = LED_TIM_HALF},	//L0M0	SW1 'UNDO'
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M1	SW2
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L0M3	SW4
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M1	SW6
		{.axis = 0,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//L1M2	SW7
/*N64*/	{.axis = 0,	.color = LED_PINK,		.period = LED_TIM_LONG},	//L1M3	SW8 [SCENE]
		{.axis = 0,	.color = LED_RED,		.period = LED_TIM_NORM},	//L2M0	enc0 push 'reject'
		{.axis = 1,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M1	enc1 push
		{.axis = 2,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M2	enc2 push
		{.axis = 3,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L2M3	enc3 push
		{.axis = 4,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M1	enc5 push
/*N70*/	{.axis = 6,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M2	enc6 push
/*N71*/	{.axis = 7,	.color = LED_GLAY,		.period = LED_TIM_NORM},	//L3M3	enc7 push
		//Scence3 encoders rotate
/*C64*/	{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CW
		{.axis = 0,	.color = LED_MINT,		.period = LED_TIM_SHORT},	//enc0 CCW
/*C65*/	{.axis = 1,	.color = LED_RED,		.period = LED_TIM_NORM},	//enc1 CW
		{.axis = 1,	.color = LED_RED,		.period = LED_TIM_HALF},	//enc1 CCW
/*C66*/	{.axis = 2,	.color = LED_ORANGE,	.period = LED_TIM_NORM},	//enc2 CW
		{.axis = 2,	.color = LED_ORANGE,	.period = LED_TIM_HALF},	//enc2 CCW
/*C67*/	{.axis = 3,	.color = LED_YELLOW,	.period = LED_TIM_NORM},	//enc3 CW
		{.axis = 3,	.color = LED_YELLOW,	.period = LED_TIM_HALF},	//enc3 CCW
/*C68*/	{.axis = 4,	.color = LED_GREEN,		.period = LED_TIM_NORM},	//enc4 CW
		{.axis = 4,	.color = LED_GREEN,		.period = LED_TIM_HALF},	//enc4 CCW
/*C69*/	{.axis = 5,	.color = LED_CYAN,		.period = LED_TIM_NORM},	//enc5 CW
		{.axis = 5,	.color = LED_CYAN,		.period = LED_TIM_HALF},	//enc5 CCW
/*C70*/	{.axis = 6,	.color = LED_BLUE,		.period = LED_TIM_NORM},	//enc6 CW
		{.axis = 6,	.color = LED_BLUE,		.period = LED_TIM_HALF},	//enc6 CCW
/*C71*/	{.axis = 7,	.color = LED_MAGENTA,	.period = LED_TIM_NORM},	//enc7 CW
		{.axis = 7,	.color = LED_MAGENTA,	.period = LED_TIM_HALF},	//enc7 CCW
	}
};
/* ******************************************************* **** END OF FILE****/
