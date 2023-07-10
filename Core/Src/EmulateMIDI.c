/**
 * @file	EmulateMIDI.c
 * @author	remov-b4-flight
 * @brief	MIDI Emulation of LrTMAX
 */
#include "EmulateMIDI.h"
extern	ENC_SW_SCAN	ENCSW_Stat;
extern	uint8_t	LrScene;
extern	char *scene_name[SCENE_COUNT];
extern	ENC_SW_DEFINE	prof_table[SCENE_COUNT][DEFINES_PER_SCENE];
extern	char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
extern	bool isAnyMoved;
//! Instance Handle of USB interface
extern	USBD_HandleTypeDef *pInstance;

//! keeps previous 'Note On' note number For sending 'Note Off' message.
uint8_t	prev_note;
//! If true, MIDI message previous sent is switch. If false, it's encoder
bool	isPrev_SwPush;
//! Indicate scene name appearing on OLED. need clearing buffers.
bool	isPrev_Scene;

// MIDI variables
//! MIDI CC message value for each channels.
uint8_t	MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];

/**
 * 	@brief	Initialize MIDI
 */
void EmulateMIDI_Init(){
	isPrev_SwPush = false;
	isPrev_Scene = false;
	memset(MIDI_CC_Value, MIDI_CC_INITIAL, CC_COUNT);
}
/**
 *	@brief	Generate MIDI message and Send to host by User interaction.
 *	@pre	isAnyMoved	any Switches/Encoders was pressed/moved or not
 *	@pre	ENCSW_Stat	current Switches/Encoders status
 */
void EmulateMIDI() {
	//! USB MIDI message structure for send
	MIDI_MESSAGE	USBMIDI_TxMessage;

	if (isAnyMoved) {
		char 		msg_string[MSG_WIDTH + 2];
		uint8_t		bitpos = ntz32(ENCSW_Stat.wd);
		uint32_t	rstat = (ENCSW_Stat.wd);
		bool 		isSendMIDIMessage = false;

		if ( ENCSW_Stat.wd & MASK_ENC_SW ) { //Check Matrix switches
			//Send 'Note On' message from switches/encoders matrix.
			uint8_t	note = ((ENCSW_Stat.wd & MASK_ENCPUSH)? NOTE_OFFSET : 0) + (LrScene * NOTES_PER_SCENE) + bitpos;
			if (ENCSW_Stat.wd == RESET_SW_PATTERN) {
				HAL_NVIC_SystemReset();
			}else if (bitpos == SCENE_BIT) { //is [SCENE] switch pressed?
			   	//Move to next Scene.
				if((++LrScene) >= SCENE_COUNT){
					LrScene = Lr_SCENE0;
				}
				LED_SetScene(LrScene);
				sprintf(msg_string, "Scene %1d",LrScene);
				strcpy(Msg_Buffer[0], msg_string);
				strcpy(msg_string, scene_name[LrScene]);
				isPrev_Scene = true;
			}else{
				LED_SetPulse(prof_table[LrScene][bitpos].axis, prof_table[LrScene][bitpos].color, prof_table[LrScene][bitpos].period);
				memset(Msg_Buffer[0], (int)SPACE_CHAR, MSG_WIDTH );
				sprintf(msg_string, "Note: %3d    S%1d", note, (LrScene % SCENE_COUNT) );
			}
			isSendMIDIMessage = true;

			//Print Message to OLED & LED
			SSD1306_SetScreen(ON);
			strcpy(Msg_Buffer[1], msg_string);
			Msg_Print();
			Start_MsgTimer(MSG_TIMER_DEFAULT);

			if (isSendMIDIMessage == true) {
				//Set 'Note ON'
				USBMIDI_TxMessage.header = MIDI_NT_ON;
				USBMIDI_TxMessage.status = MIDI_NT_ON_S;
				USBMIDI_TxMessage.channel = note;
				USBMIDI_TxMessage.value = MIDI_NT_ON_VELOCITY;

				prev_note = note;
				isPrev_SwPush = true;
			}
		}else if( ENCSW_Stat.wd & MASK_ENC ) { //Check encoder's movements
			//Send CC message from encoders.
			uint8_t axis = (bitpos - ENC_SW_COUNT) / 2;
			uint8_t val = MIDI_CC_Value[LrScene][axis];
			uint8_t channel = CC_CH_OFFSET + (LrScene * CC_CH_PER_SCENE) + axis;

			USBMIDI_TxMessage.header = MIDI_CC_HEADER;
			USBMIDI_TxMessage.status = MIDI_CC_STATUS;
			USBMIDI_TxMessage.channel = channel;
			USBMIDI_TxMessage.value = val;

			isPrev_SwPush = false;

			//Print Message to OLED & LEDs.
			SSD1306_SetScreen(ON);
			sprintf(msg_string, CC_MSG_2DG, channel, val, LrScene & 0x3);
			if (isPrev_Scene == true) {
				memset(Msg_Buffer[0], (int)SPACE_CHAR, MSG_WIDTH );
				isPrev_Scene = false;
			}
			strcpy(Msg_Buffer[1], msg_string);
			Msg_Print();

			Start_MsgTimer(MSG_TIMER_DEFAULT);

			LED_SetPulse(prof_table[LrScene][bitpos].axis, prof_table[LrScene][bitpos].color, prof_table[LrScene][bitpos].period);
			isSendMIDIMessage = true;

		} else if (isPrev_SwPush == true && rstat == 0) {// Is switch/encoder push released?
			//Send 'Note Off' message.
			USBMIDI_TxMessage.header = MIDI_NT_OFF;
			USBMIDI_TxMessage.status = MIDI_NT_OFF_S;
			USBMIDI_TxMessage.channel = prev_note;
			USBMIDI_TxMessage.value = MIDI_NT_OFF_VELO;

			isSendMIDIMessage = true;
			isPrev_SwPush = false;
		}

		if (isSendMIDIMessage == true) {
			//Send MIDI message via USB.
			USBD_LL_Transmit (pInstance, MIDI_IN_EP, (uint8_t *)&USBMIDI_TxMessage, MIDI_MESSAGE_LENGTH);
			isSendMIDIMessage = false;
		}

		/* Clear the switch pressed flag */
		isAnyMoved = false;
	}
}
