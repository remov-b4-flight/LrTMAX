/**
 * @file	EmulateHID.c
 * @brief	functions used in HID keyboard build.
 * @author	remov-b4-flight
 * @copyright	GPLv3
 */

#include <stdbool.h>
#include "main.h"
#include "usbd_hid.h"
#include "led.h"
#include "usbd_hid.h"
#include "bitcount.h"
#include "key_define.h"
#include "EmulateHID.h"
#include "ssd1306.h"

//
extern	bool	isKeyPressed;
extern	int32_t	Msg_Timer_Count;
extern	bool	Msg_Off_Flag;
extern	bool	Msg_Timer_Enable;
extern	bool	isMsgFlash;
extern	USBD_HandleTypeDef	hUsbDeviceFS;
extern	KEYSCAN	Key_Stat;
extern	char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
extern	HID_DEFINE keytable[];

//! HID keyboard input report
KEYBOARD_INPUT_REPORT	In_Report;

static inline void Msg_Print(){
	isMsgFlash = true;
}

/**
 *	@brief	Generate HID packet and Send to host by User interaction.
 */
void EmulateKeyboard(void) {
    uint32_t rkey;
    uint8_t bitpos;
    bool isKeyReport;

    if (isKeyPressed) {
        bitpos = ntz32(Key_Stat.wd);
        rkey = (Key_Stat.wd & MOD_SW_BIT_MASK);
        if ( bitpos < KEY_COUNT + (2 * ROT_COUNT) ){
#if 0
        	if(modifiers[bitpos].element[0] != HID_NONM) SendModifiers(bitpos);
#endif

        	In_Report.modifier = keytable[bitpos].modifier;
            In_Report.keys[HID_RPT_KEY_IDX] = keytable[bitpos].keycode;
            if (keytable[bitpos].message != NULL) {
            	Msg_Off_Flag = false;
        		Msg_Timer_Enable = true;
            	Msg_Timer_Count = MSG_TIMER_DEFAULT;
            	SSD1306_SetScreen(ON);
                strcpy(Msg_Buffer[0], keytable[bitpos].message);
                memset(Msg_Buffer[1],' ',MSG_WIDTH);
            	Msg_Print();
            }
            LED_SetPulse(LED_IDX_ENC0,LED_COLOR_YELLOW,25);

            isKeyReport = true;
		}else if (rkey == 0) {// Keys are released
			In_Report.modifier = In_Report.keys[HID_RPT_KEY_IDX] = HID_NONE;
			isKeyReport = true;
        }else
        	isKeyReport = false;

        if (isKeyReport) {
        	USBD_HID_HandleTypeDef *hhid = hUsbDeviceFS.pClassData;
        	while ( hhid->state != HID_IDLE ){
        		Delay_us(100);
        	}
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&In_Report,sizeof(KEYBOARD_INPUT_REPORT) );
			isKeyReport = false;
        }

        /* Clear the switch pressed flag */
        isKeyPressed = false;
    }
}
#if 0
KEY_MODIFIER modifiers[KEY_COUNT];
void ExpandModifiers() {
	uint8_t mod_index;
	memset(modifiers, 0, sizeof(modifiers));
	for (mod_index = 0; mod_index < KEY_COUNT; mod_index++) {
		uint8_t modifier = keytable[mod_index].modifier;
		uint8_t bitcount = bitcount8(modifier);
		if (modifier != HID_NONM && bitcount > 1) {
			uint8_t dst_index = 0;
			uint8_t pattern = 0;
			if (modifier & HID_GUIM) {
				pattern += HID_GUIM;
				modifiers[mod_index].element[dst_index] = pattern;
				dst_index += 1;
			}
			if (modifier & HID_ALTM) {
				pattern += HID_ALTM;
				modifiers[mod_index].element[dst_index] = pattern;
				dst_index += 1;
			}
			if (modifier & HID_SFTM) {
				pattern += HID_SFTM;
				modifiers[mod_index].element[dst_index] = pattern;
				dst_index += 1;
			}
			if (modifier & HID_CTLM) {
				pattern += HID_CTLM;
				modifiers[mod_index].element[dst_index] = pattern;
			}
		}
	}
}
void SendModifierElement(uint8_t mod) {
	In_Report.modifier = mod;
	In_Report.keys[0] =
	In_Report.keys[1] =
	In_Report.keys[2] =
	In_Report.keys[3] = HID_NONE;
    USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&In_Report,sizeof(KEYBOARD_INPUT_REPORT) );
}

void SendModifiers(uint8_t bitpos) {
	uint8_t i;
	for (i = 0; i < 4; i++) {
		uint8_t mod = modifiers[bitpos].element[i];
		if (mod == HID_NONM) break;
		SendModifierElement(mod);
	}
}
#endif

