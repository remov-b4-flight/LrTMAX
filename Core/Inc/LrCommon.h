/*
 * @file LrCommon.h
 * @brief Common definitions on Lr****
 *  Created on: 2022/02/26
 *      Author: jenoki
 */

#ifndef INC_LRCOMMON_H_
#define INC_LRCOMMON_H_
#include <stdint.h>

//! Lr**** Hardware definition
#define KEY_COUNT	16
#define ENC_COUNT	8

typedef union keyscan_t {
    uint32_t wd;
    struct ks_bit_t {
		unsigned char n0:4;		//Switch Line0
		unsigned char n1:4;		//Switch Line1
		unsigned char n2:4;		//Switch Line2
		unsigned char n3:4;		//Switch Line3
		unsigned char enc0:2;	//Rotary encoder
		unsigned char enc1:2;	//Rotary encoder
		unsigned char enc2:2;	//Rotary encoder
		unsigned char enc3:2;	//Rotary encoder
		unsigned char enc4:2;	//Rotary encoder
		unsigned char enc5:2;	//Rotary encoder
        unsigned char enc6:2;	//Rotary encoder
        unsigned char enc7:2;	//Rotary encoder
    } nb;
} KEYSCAN;

//! Lr**** State definition
enum lr_state_t {
	LR_RESET,        //!< LR_RESET
	LR_USB_NOLINK,   //!< LRE6_USB_NOLINK
	LR_USB_LINKUP,   //!< LR_USB_LINKUP
	LR_USB_LINKED,   //!< LR_USB_LINKED
	LR_USB_LINK_LOST,//!< LR_USB_LINK_LOST
};

//! Key matrix lines
enum {
	L0 = 0,
	L1,
	L2,
	L3
};

//! Encoder definitions
enum lr_enc_t {
	Lr_ENC0 = 0,
	Lr_ENC1,
	Lr_ENC2,
	Lr_ENC3,
	Lr_ENC4,
	Lr_ENC5,
	Lr_ENC6,
	Lr_ENC7,
};

//! Scene definition in MIDI
enum lr_scene_t {
	Lr_SCENE0 = 0,
	Lr_SCENE1 = 1,
	Lr_SCENE2 = 2,
	Lr_SCENE3 = 3,
};
#define	SCENE_COUNT		4
//! Key define structure
#define DEFINES_PER_SCENE	( KEY_COUNT + (ENC_COUNT * 2) )
//! Assigned notes per scene.
#define NOTES_PER_SCENE		32
//! Define key that designated for scene change.
#define SCENE_BIT			7

// LED timer definitions
#define LED_TIM_NORM		21		//500ms (1 tick=24ms)
#define LED_TIM_HALF		11		//250ms
#define LED_TIM_LONG		42		//1Sec
#define LED_TIM_CONNECT		83		//2Sec

// Screen timer definitions
#define MSG_TIMER_DEFAULT	122		//4Sec (1 tick=32.7ms)
#define MSG_TIMER_NOLINK	31		//1Sec (OLED update in USB not connected)

#endif /* INC_LRCOMMON_H_ */
