/**
* @file key_define.c
* @brief MIDI channel/note definition
* @details This file defines MIDI Control Change(CC) / Note ON-OFF event on MIDI build.
* LrTMAX has 8 encoder as enc0~7, and 8 individual switch(SW) as SW1~8 and SW on encoder as 'enc0~7 push'
* In MIDI use , users can send individual CC event channel per switch and encoder.
* At switches, LrTMAX sends Note message has velocity= 127 when switch on, and sends velocity = 0 when switch off.
* At encoder, LrTMAX sends CC message every encoders move,values are increase/decrease by towards.
* Lr**** MIDI can use 'Scene'. Users can alter all SW/Encoder definition. To alter Scene, push SW10.
* Users can use up to 4 Scenes. SW10 is fixed for Scene function.
*
* Scene / CC event channel definition (by Encoders)
* Scene0	ch. 0~7
* Scene1	ch. 8~15
* Scene2	ch. 16~23
* Scene3	ch. 24~31
*
* Scene / Note definition (by SWs)
* Scene0	Note 0~15
* Scene1	Note 16~31
* Scene2	Note 32~47
* Scene3	Note 48~63
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "LrCommon.h"
#include "key_define.h"
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
#if 1
//! @union Key/encoder configuration table
const KEY_DEFINE keytable[SCENE_COUNT][DEFINES_PER_SCENE] = {
	{	//Scene0 Switches	(Library Tab)									0123456789ABCDEF
/*N00*/	{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
/*N01*/	{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Rate 1"},			//L0M1	SW2
/*N02*/	{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Rate 2"},			//L0M2	SW3
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Dev. Copy"},		//L0M3	SW4
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Dev. Paste"},		//L1M0	SW5
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Add Quick Colle."},	//L1M1	SW6
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "2nd Moni. On/Off"},	//L1M2	SW7
/*N07*/	{.color = LED_BLUE,		.period = LED_TIM_LONG,	.message = "Scene 0"},			//L1M3	SW8 [SCENE]
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Rate reset"},		//L2M1	enc1 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Flag reset"},		//L2M2	enc2 push
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A3p"},				//L2M3	enc3 push
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A4p"},				//L3M0	enc4 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Zoom reset"},		//L3M1	enc5 push
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A6p"},				//L3M2	enc6 push
/*N15*/	{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence0 Encoders													0123456789ABCDEF
/*C00*/	{.color = LED_RED,		.period = LED_TIM_SHORT,.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.color = LED_RED,		.period = LED_TIM_SHORT,.message = "Prev. " LEFTA},		//enc0 CCW cursor left
		{.color = LED_BLUE,		.period = LED_TIM_HALF,	.message = "Rate " UPA},		//enc1 CW
		{.color = LED_BLUE,		.period = LED_TIM_HALF,	.message = "Rate " DOWNA},		//enc1 CCW
		{.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Flag " UPA},		//enc2 CW
		{.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Flag " DOWNA},		//enc2 CCW
		{.color = LED_YELLOW,	.period = LED_TIM_HALF,	.message = "Rotate " RIGHTA},	//enc3 CW
		{.color = LED_YELLOW,	.period = LED_TIM_HALF,	.message = "Rotate " LEFTA},	//enc3 CCW
		{.color = LED_OFF,		.period = LED_TIM_HALF,	.message = "A4" RIGHTA},		//enc4 CW
		{.color = LED_OFF,		.period = LED_TIM_HALF,	.message = "A4" LEFTA},			//enc4 CCW
		{.color = LED_ORANGE,	.period = LED_TIM_HALF,	.message = "Zoom In"},			//enc5 CW
		{.color = LED_ORANGE,	.period = LED_TIM_HALF,	.message = "Zoom Out"},			//enc5 CCW
/*C06*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Quick Expo. " UPA},	//enc6 CW
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Quick Expo. " DOWNA},//enc6 CCW
/*C07*/	{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Quick C-Temp. " RIGHTA},//enc7 CW
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Quick C-Temp. " LEFTA},//enc7 CCW
	},{	//Scene1 Switches	(Basic Edits)									0123456789ABCDEF
/*N16*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
/*N17*/	{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Auto Tone"},		//L0M1	SW2
		{.color = LED_ORANGE,	.period = LED_TIM_NORM,	.message = "DayLight"},			//L0M2	SW3
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Tungsten"},			//L0M3	SW4
		{.color = LED_GREEN,	.period = LED_TIM_NORM,	.message = "Fluorescent"},		//L1M0	SW5
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "W/B Auto"},			//L1M1	SW6
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "W/B As Shot"},		//L1M2	SW7
/*N23*/	{.color = LED_BLUE,		.period = LED_TIM_LONG,	.message = "Scene 1"},			//L1M3	SW8 [SCENE]
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "C-temp. reset"},	//L2M1	enc1 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Tint reset"},		//L2M2	enc2 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Expo. reset"},		//L2M3	enc3 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Contra. reset"},	//L3M0	enc4 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Vibra. reset"},		//L3M1	enc5 push
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Nat-Vibra. reset"},	//L3M2	enc6 push
/*N31*/	{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence1 Encoders													0123456879ABCDEF
/*C08*/	{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW
		{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW
/*C09*/	{.color = LED_YELLOW,	.period = LED_TIM_HALF,	.message = "Color-Temp. " UPA},	//enc1 CW
		{.color = LED_BLUE,		.period = LED_TIM_HALF,	.message = "Color-Temp. "DOWNA},//enc1 CCW
		{.color =LED_MAGENTA,	.period = LED_TIM_HALF,	.message = "Magenta"},			//enc2 CW
		{.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green"},			//enc2 CCW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Exposure " UPA},	//enc3 CW
		{.color = LED_GLAY,		.period = LED_TIM_HALF,	.message = "Exposure " DOWNA},	//enc3 CCW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Contrast " UPA},	//enc4 CW
		{.color = LED_GLAY,		.period = LED_TIM_HALF,	.message = "Contrast " DOWNA},	//enc4 CCW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Vibrance " UPA},	//enc5 CW
		{.color = LED_GLAY,		.period = LED_TIM_HALF,	.message = "Vibrance " DOWNA},	//enc5 CCW
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Local Texture " UPA},	//enc6 CW
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Local Texture " DOWNA},	//enc6 CCW
/*C15*/	{.color =LED_MAGENTA,	.period = LED_TIM_NORM,	.message = "Loc. Clearity " UPA},	//enc7 CW
		{.color =LED_MAGENTA,	.period = LED_TIM_NORM,	.message = "Loc. Clearity" DOWNA},	//enc7 CCW
	},{	//Scene2 Switches	(Tone Curve)									0123456789ABCDEF
/*N32*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword1"},			//L0M1	SW2
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword2"},			//L0M2	SW3
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword3"},			//L0M3	SW4
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword4"},			//L1M0	SW5
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword5"},			//L1M1	SW6
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Keyword6"},			//L1M2	SW7
/*N40*/	{.color = LED_RED,		.period = LED_TIM_LONG,	.message = "Scene 2"},			//L1M3	SW8 [SCENE]
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Dark reset"},		//L2M1	enc1 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Shadow reset"},		//L2M2	enc2 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "light reset"},		//L2M3	enc3 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Hilight reset"},	//L3M0	enc4 push
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A5p"},				//L3M1	enc5 push
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A6p"},				//L3M2	enc6 push
/*N47*/	{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence2 Encoders													0123456789ABCDEF
/*C16*/	{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW cursor left
/*C17*/	{.color = LED_DARK,		.period = LED_TIM_HALF,	.message = "Dark " UPA},		//enc1 CW
		{.color = LED_OFF,		.period = LED_TIM_HALF,	.message = "Dark " DOWNA},		//enc1 CCW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Shadow " UPA},		//enc2 CW
		{.color = LED_DARK,		.period = LED_TIM_HALF,	.message = "Shadow " DOWNA},	//enc2 CCW
		{.color =LED_HILIGHT,	.period = LED_TIM_HALF,	.message = "Light " UPA},		//enc3 CW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Light " DOWNA},		//enc3 CCW
		{.color =LED_HILIGHT,	.period = LED_TIM_HALF,	.message = "Hilight " UPA},		//enc4 CW
		{.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Hilight " DOWNA},	//enc4 CCW
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A5" RIGHTA},		//enc5 CW
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A5" LEFTA},			//enc5 CCW
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A6" RIGHTA},		//enc6 CW
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A6" LEFTA},			//enc6 CCW
/*C23*/	{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A7" RIGHTA},		//enc7 CW
		{.color = LED_OFF,		.period = LED_TIM_NORM,	.message = "A7" LEFTA},			//enc7 CCW
	},{	//Scene3 Switches	(Color Balance)									0123456789ABCDEF
/*N48*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "RedEye"},			//L0M1	SW2
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Lens Colle."},		//L0M2	SW3
		{.color = LED_DARK,		.period = LED_TIM_NORM,	.message = "Upright Full"},		//L0M3	SW4
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Auto Upright"},		//L1M0	SW5
		{.color = LED_YELLOW,	.period = LED_TIM_NORM,	.message = "Upright Horizon"},	//L1M1	SW6
		{.color = LED_GREEN,	.period = LED_TIM_NORM,	.message = "Upright Vert."},	//L1M2	SW7
/*N56*/	{.color = LED_BLUE,		.period = LED_TIM_LONG,	.message = "Scene 3"},			//L1M3	SW8 [SCENE]
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Red reset"},		//L2M1	enc1 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Orange reset"},		//L2M2	enc2 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Yellow reset"},		//L2M3	enc3 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Green reset"},		//L3M0	enc4 push
		{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Cyan reset"},		//L3M1	enc5 push
/*N62*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Blue reset"},		//L3M2	enc6 push
/*N63*/	{.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Magenta reset"},	//L3M3	enc7 push
		//Scence3 Encoders													0123456789ABCDEF
/*C24*/	{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.color = LED_RED,		.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW cursor left
/*C25*/	{.color = LED_RED,		.period = LED_TIM_HALF,	.message = "Red " UPA},			//enc1 CW
		{.color = LED_RED,		.period = LED_TIM_HALF,	.message = "Red " DOWNA},		//enc1 CCW
		{.color = LED_ORANGE,	.period = LED_TIM_HALF,	.message = "Orange " UPA},		//enc2 CW
		{.color = LED_ORANGE,	.period = LED_TIM_HALF,	.message = "Orange " DOWNA},	//enc2 CCW
		{.color = LED_YELLOW,	.period = LED_TIM_HALF,	.message = "Yellow " UPA},		//enc3 CW
		{.color = LED_YELLOW,	.period = LED_TIM_HALF,	.message = "Yellow " DOWNA},	//enc3 CCW
		{.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green " UPA},		//enc4 CW
		{.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green " DOWNA},		//enc4 CCW
		{.color = LED_CYAN,		.period = LED_TIM_HALF,	.message = "Cyan " UPA},		//enc5 CW
		{.color = LED_CYAN,		.period = LED_TIM_HALF,	.message = "Cyan " DOWNA},		//enc5 CCW
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Blue " UPA},		//enc6 CW
		{.color = LED_BLUE,		.period = LED_TIM_NORM,	.message = "Blue " DOWNA},		//enc6 CCW
/*C31*/	{.color =LED_MAGENTA,	.period = LED_TIM_NORM,	.message = "Magenta " UPA},		//enc7 CW
		{.color =LED_MAGENTA,	.period = LED_TIM_NORM,	.message = "Magenta " DOWNA},	//enc7 CCW
	}
};
#else
//! @union Key/encoder configuration table
const KEY_DEFINE keytable[SCENE_COUNT][DEFINES_PER_SCENE] = {
	{	//Scene0 Switches	(Library Tab)									0123456789ABCDEF
/*N00*/	{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
/*N01*/	{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Rate 1"},			//L0M1	SW2
/*N02*/	{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Rate 2"},			//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Dev. Copy"},		//L0M3	SW4
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Dev. Paste"},		//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Add Quick Colle."},	//L1M1	SW6
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "2nd Moni. On/Off"},	//L1M2	SW7
/*N07*/	{.axis = 0,	.color = LED_BLUE,	.period = LED_TIM_LONG,	.message = "Scene 0"},			//L1M3	SW8 [SCENE]
		{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.axis = 1,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Rate reset"},		//L2M1	enc1 push
		{.axis = 2,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Flag reset"},		//L2M2	enc2 push
		{.axis = 3,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A3p"},				//L2M3	enc3 push
		{.axis = 4,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A4p"},				//L3M0	enc4 push
		{.axis = 5,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Zoom reset"},		//L3M1	enc5 push
		{.axis = 6,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A6p"},				//L3M2	enc6 push
/*N15*/	{.axis = 7,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence0 Encoders													0123456789ABCDEF
/*C00*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_SHORT,.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.axis = 0,	.color = LED_RED,	.period = LED_TIM_SHORT,.message = "Prev. " LEFTA},		//enc0 CCW cursor left
		{.axis = 1,	.color = LED_BLUE,	.period = LED_TIM_HALF,	.message = "Rate " UPA},		//enc1 CW
		{.axis = 1,	.color = LED_BLUE,	.period = LED_TIM_HALF,	.message = "Rate " DOWNA},		//enc1 CCW
		{.axis = 2,	.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Flag " UPA},		//enc2 CW
		{.axis = 2,	.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Flag " DOWNA},		//enc2 CCW
		{.axis = 3,	.color = LED_YELLOW,.period = LED_TIM_HALF,	.message = "Rotate " RIGHTA},	//enc3 CW
		{.axis = 3,	.color = LED_YELLOW,.period = LED_TIM_HALF,	.message = "Rotate " LEFTA},	//enc3 CCW
		{.axis = 4,	.color = LED_OFF,	.period = LED_TIM_HALF,	.message = "A4" RIGHTA},		//enc4 CW
		{.axis = 4,	.color = LED_OFF,	.period = LED_TIM_HALF,	.message = "A4" LEFTA},			//enc4 CCW
		{.axis = 5,	.color = LED_ORANGE,.period = LED_TIM_HALF,	.message = "Zoom In"},			//enc5 CW
		{.axis = 5,	.color = LED_ORANGE,.period = LED_TIM_HALF,	.message = "Zoom Out"},			//enc5 CCW
/*C06*/	{.axis = 6,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Quick Expo. " UPA},	//enc6 CW
		{.axis = 6,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Quick Expo. " DOWNA},//enc6 CCW
/*C07*/	{.axis = 7,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Quick C-Temp. " RIGHTA},//enc7 CW
		{.axis = 7,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Quick C-Temp. " LEFTA},//enc7 CCW
	},{	//Scene1 Switches	(Basic Edits)									0123456789ABCDEF
/*N16*/	{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
/*N17*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Auto Tone"},		//L0M1	SW2
		{.axis = 0,	.color = LED_ORANGE,.period = LED_TIM_NORM,	.message = "DayLight"},			//L0M2	SW3
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Tungsten"},			//L0M3	SW4
		{.axis = 0,	.color = LED_GREEN,	.period = LED_TIM_NORM,	.message = "Fluorescent"},		//L1M0	SW5
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "W/B Auto"},			//L1M1	SW6
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "W/B As Shot"},		//L1M2	SW7
/*N23*/	{.axis = 0,	.color = LED_BLUE,	.period = LED_TIM_LONG,	.message = "Scene 1"},			//L1M3	SW8 [SCENE]
		{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.axis = 1,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "C-temp. reset"},	//L2M1	enc1 push
		{.axis = 2,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Tint reset"},		//L2M2	enc2 push
		{.axis = 3,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Expo. reset"},		//L2M3	enc3 push
		{.axis = 4,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Contra. reset"},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Vibra. reset"},		//L3M1	enc5 push
		{.axis = 6,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Nat-Vibra. reset"},	//L3M2	enc6 push
/*N31*/	{.axis = 7,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence1 Encoders													0123456879ABCDEF
/*C08*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW
		{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW
/*C09*/	{.axis = 1,	.color = LED_YELLOW,.period = LED_TIM_HALF,	.message = "Color-Temp. " UPA},	//enc1 CW
		{.axis = 1,	.color = LED_BLUE,	.period = LED_TIM_HALF,	.message = "Color-Temp. "DOWNA},//enc1 CCW
		{.axis = 2,	.color =LED_MAGENTA,.period = LED_TIM_HALF,	.message = "Magenta"},			//enc2 CW
		{.axis = 2,	.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green"},			//enc2 CCW
		{.axis = 3,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Exposure " UPA},	//enc3 CW
		{.axis = 3,	.color = LED_GLAY,	.period = LED_TIM_HALF,	.message = "Exposure " DOWNA},	//enc3 CCW
		{.axis = 4,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Contrast " UPA},	//enc4 CW
		{.axis = 4,	.color = LED_GLAY,	.period = LED_TIM_HALF,	.message = "Contrast " DOWNA},	//enc4 CCW
		{.axis = 5,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Vibrance " UPA},	//enc5 CW
		{.axis = 5,	.color = LED_GLAY,	.period = LED_TIM_HALF,	.message = "Vibrance " DOWNA},	//enc5 CCW
		{.axis = 6,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Local Texture " UPA},	//enc6 CW
		{.axis = 6,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Local Texture " DOWNA},	//enc6 CCW
/*C15*/	{.axis = 7,	.color =LED_MAGENTA,.period = LED_TIM_NORM,	.message = "Loc. Clearity " UPA},	//enc7 CW
		{.axis = 7,	.color =LED_MAGENTA,.period = LED_TIM_NORM,	.message = "Loc. Clearity" DOWNA},	//enc7 CCW
	},{	//Scene2 Switches	(Tone Curve)									0123456789ABCDEF
/*N32*/	{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword1"},			//L0M1	SW2
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword2"},			//L0M2	SW3
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword3"},			//L0M3	SW4
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword4"},			//L1M0	SW5
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword5"},			//L1M1	SW6
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Keyword6"},			//L1M2	SW7
/*N40*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_LONG,	.message = "Scene 2"},			//L1M3	SW8 [SCENE]
		{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.axis = 1,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Dark reset"},		//L2M1	enc1 push
		{.axis = 2,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Shadow reset"},		//L2M2	enc2 push
		{.axis = 3,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "light reset"},		//L2M3	enc3 push
		{.axis = 4,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Hilight reset"},	//L3M0	enc4 push
		{.axis = 5,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A5p"},				//L3M1	enc5 push
		{.axis = 6,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A6p"},				//L3M2	enc6 push
/*N47*/	{.axis = 7,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A7p"},				//L3M3	enc7 push
		//Scence2 Encoders													0123456789ABCDEF
/*C16*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW cursor left
/*C17*/	{.axis = 1,	.color = LED_DARK,	.period = LED_TIM_HALF,	.message = "Dark " UPA},		//enc1 CW
		{.axis = 1,	.color = LED_OFF,	.period = LED_TIM_HALF,	.message = "Dark " DOWNA},		//enc1 CCW
		{.axis = 2,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Shadow " UPA},		//enc2 CW
		{.axis = 2,	.color = LED_DARK,	.period = LED_TIM_HALF,	.message = "Shadow " DOWNA},	//enc2 CCW
		{.axis = 3,	.color =LED_HILIGHT,.period = LED_TIM_HALF,	.message = "Light " UPA},		//enc3 CW
		{.axis = 3,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Light " DOWNA},		//enc3 CCW
		{.axis = 4,	.color =LED_HILIGHT,.period = LED_TIM_HALF,	.message = "Hilight " UPA},		//enc4 CW
		{.axis = 4,	.color = LED_WHITE,	.period = LED_TIM_HALF,	.message = "Hilight " DOWNA},	//enc4 CCW
		{.axis = 5,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A5" RIGHTA},		//enc5 CW
		{.axis = 5,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A5" LEFTA},			//enc5 CCW
		{.axis = 6,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A6" RIGHTA},		//enc6 CW
		{.axis = 6,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A6" LEFTA},			//enc6 CCW
/*C23*/	{.axis = 7,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A7" RIGHTA},		//enc7 CW
		{.axis = 7,	.color = LED_OFF,	.period = LED_TIM_NORM,	.message = "A7" LEFTA},			//enc7 CCW
	},{	//Scene3 Switches	(Color Balance)									0123456789ABCDEF
/*N48*/	{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Undo"},				//L0M0	SW1
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "RedEye"},			//L0M1	SW2
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Lens Colle."},		//L0M2	SW3
		{.axis = 0,	.color = LED_DARK,	.period = LED_TIM_NORM,	.message = "Upright Full"},		//L0M3	SW4
		{.axis = 0,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Auto Upright"},		//L1M0	SW5
		{.axis = 0,	.color = LED_YELLOW,.period = LED_TIM_NORM,	.message = "Upright Horizon"},	//L1M1	SW6
		{.axis = 0,	.color = LED_GREEN,	.period = LED_TIM_NORM,	.message = "Upright Vert."},	//L1M2	SW7
/*N56*/	{.axis = 0,	.color = LED_BLUE,	.period = LED_TIM_LONG,	.message = "Scene 3"},			//L1M3	SW8 [SCENE]
		{.axis = 0,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Reject"},			//L2M0	enc0 push
		{.axis = 1,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Red reset"},		//L2M1	enc1 push
		{.axis = 2,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Orange reset"},		//L2M2	enc2 push
		{.axis = 3,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Yellow reset"},		//L2M3	enc3 push
		{.axis = 4,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Green reset"},		//L3M0	enc4 push
		{.axis = 5,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Cyan reset"},		//L3M1	enc5 push
/*N62*/	{.axis = 6,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Blue reset"},		//L3M2	enc6 push
/*N63*/	{.axis = 7,	.color = LED_WHITE,	.period = LED_TIM_NORM,	.message = "Magenta reset"},	//L3M3	enc7 push
		//Scence3 Encoders													0123456789ABCDEF
/*C24*/	{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Next " RIGHTA},		//enc0 CW cursor right
		{.axis = 0,	.color = LED_RED,	.period = LED_TIM_NORM,	.message = "Prev. " LEFTA},		//enc0 CCW cursor left
/*C25*/	{.axis = 1,	.color = LED_RED,	.period = LED_TIM_HALF,	.message = "Red " UPA},			//enc1 CW
		{.axis = 1,	.color = LED_RED,	.period = LED_TIM_HALF,	.message = "Red " DOWNA},		//enc1 CCW
		{.axis = 2,	.color = LED_ORANGE,.period = LED_TIM_HALF,	.message = "Orange " UPA},		//enc2 CW
		{.axis = 2,	.color = LED_ORANGE,.period = LED_TIM_HALF,	.message = "Orange " DOWNA},	//enc2 CCW
		{.axis = 3,	.color = LED_YELLOW,.period = LED_TIM_HALF,	.message = "Yellow " UPA},		//enc3 CW
		{.axis = 3,	.color = LED_YELLOW,.period = LED_TIM_HALF,	.message = "Yellow " DOWNA},	//enc3 CCW
		{.axis = 4,	.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green " UPA},		//enc4 CW
		{.axis = 4,	.color = LED_GREEN,	.period = LED_TIM_HALF,	.message = "Green " DOWNA},		//enc4 CCW
		{.axis = 5,	.color = LED_CYAN,	.period = LED_TIM_HALF,	.message = "Cyan " UPA},		//enc5 CW
		{.axis = 5,	.color = LED_CYAN,	.period = LED_TIM_HALF,	.message = "Cyan " DOWNA},		//enc5 CCW
		{.axis = 6,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Blue " UPA},		//enc6 CW
		{.axis = 6,	.color = LED_BLUE,	.period = LED_TIM_NORM,	.message = "Blue " DOWNA},		//enc6 CCW
/*C31*/	{.axis = 7,	.color =LED_MAGENTA,.period = LED_TIM_NORM,	.message = "Magenta " UPA},		//enc7 CW
		{.axis = 7,	.color =LED_MAGENTA,.period = LED_TIM_NORM,	.message = "Magenta " DOWNA},	//enc7 CCW
	}
};
#endif
/* ******************************************************* **** END OF FILE****/
