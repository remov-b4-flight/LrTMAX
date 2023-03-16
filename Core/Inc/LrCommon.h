/*
 * @file	LrCommon.h
 * @brief	Common definitions on Lr****
 * @author	remov-b4-flight
 * @copyright	3-Clause BSD License
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
		uint8_t n0:4;	//Switch Line0
		uint8_t n1:4;	//Switch Line1
		uint8_t n2:4;	//Switch Line2
		uint8_t n3:4;	//Switch Line3
		uint8_t enc0:2;	//Rotary encoder
		uint8_t enc1:2;	//Rotary encoder
		uint8_t enc2:2;	//Rotary encoder
		uint8_t enc3:2;	//Rotary encoder
		uint8_t enc4:2;	//Rotary encoder
		uint8_t enc5:2;	//Rotary encoder
		uint8_t enc6:2;	//Rotary encoder
		uint8_t enc7:2;	//Rotary encoder
    } nb;
} KEYSCAN;

//! Lr**** State definition
enum lr_state_t {
	LR_RESET,			//!< LR_RESET
	LR_USB_NOLINK,		//!< LR_USB_NOLINK
	LR_USB_LINKUP,		//!< LR_USB_LINKUP
	LR_USB_LINKED,		//!< LR_USB_LINKED
	LR_USB_LINK_LOST,	//!< LR_USB_LINK_LOST
	LR_USB_DFU,
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
//!
enum lr_matrix_t {
	Lr_MATRIX_STOP = 0,
	Lr_MATRIX_START = 1,
};
//! number of scene
#define	SCENE_COUNT		4
//! Key define structure
#define DEFINES_PER_SCENE	( KEY_COUNT + (ENC_COUNT * 2) )
//! Assigned notes per scene.
#define NOTES_PER_SCENE		32
//! Define key that designated for scene change.
#define SCENE_BIT			7
//! number of cc channels that Lr**** controls.
#define CC_COUNT			(ENC_COUNT * SCENE_COUNT)
// LED timer definitions
#define LED_TIM_NORM		21		//500ms (1 tick=24ms)
#define	LED_TIM_SHORT		4		//100ms
#define LED_TIM_HALF		11		//250ms
#define LED_TIM_LONG		42		//1.0Sec
#define LED_TIM_CONNECT		64		//1.5Sec

// Screen timer definitions
#define MSG_TIMER_DEFAULT	122		//4Sec (1 tick=32.7ms)
#define MSG_TIMER_NOLINK	31		//1Sec (OLED update in USB not connected)

#endif /* INC_LRCOMMON_H_ */
