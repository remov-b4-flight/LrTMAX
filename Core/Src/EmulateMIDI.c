/**
 * @file	EmulateMIDI.c
 * @author	remov-b4-flight
 * @brief	MIDI Emulation of LrTMAX
 */
#include "EmulateMIDI.h"
extern	KEYSCAN	Key_Stat;
extern	uint8_t	LrScene;
extern	char *scene_name[SCENE_COUNT];
extern	KEY_DEFINE	keytable[SCENE_COUNT][DEFINES_PER_SCENE];
extern	char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
//! Instance Handle of USB interface
extern	USBD_HandleTypeDef *pInstance;
//! keep previous sent 'Key On' note/channevoid EmulateMIDI_init()l for release message.
extern bool isKeyPressed;

uint8_t	prev_note;
//! If true, MIDI event previous sent is switch. if false, it's encoder
bool	isPrev_sw;
// MIDI variables
//! MIDI CC message value for each channels.
uint8_t MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];

void Start_MsgTimer(uint32_t tick);
void Msg_Print();

/**
 * @brief	get axis to flash LED.
 * @param	bit position
 * @return	axis number.
 * */
uint8_t get_axis(uint8_t bitpos){
	if (bitpos < SW_COUNT){
		return 0;
	} else if(bitpos < KEY_COUNT) {
		return (bitpos & 0x07);
	} else {
		return (bitpos / 2);
	}
}
/**
 * 	@brief	Initialize MIDI
 */
void EmulateMIDI_Init(){
	isPrev_sw = false;
	memset(MIDI_CC_Value, MIDI_CC_INITIAL, CC_COUNT);
}
/**
 *	@brief	Generate MIDI event and Send to host by User interaction.
 *	@return true : function processed any Key/Encoder event.
 *	@pre	isKeyPressed	any key is pressed or not
 *	@pre	Key_Stat		current key status
 */
void EmulateMIDI() {
	//! USB MIDI message structure for send
	MIDI_EVENT	USBMIDI_TxEvent;

	if (isKeyPressed) {
		char 		msg_string[MSG_WIDTH + 1];
		uint8_t		bitpos = ntz32(Key_Stat.wd);
		uint32_t	rkey = (Key_Stat.wd);
		bool 		isSendMIDIEvent = false;

		if ( Key_Stat.wd & MASK_KEY ) { //Check Matrix switches
			//Send 'Note On' Event from key matrix
			uint8_t	note = (LrScene * NOTES_PER_SCENE) + bitpos;
			if (Key_Stat.wd == RESET_KEY_PATTERN) {
				HAL_NVIC_SystemReset();
			}else if (bitpos == SCENE_BIT) { //is [SCENE] switch pressed?
			   	//Move to next Scene.
				if((++LrScene) >= SCENE_COUNT){
					LrScene = Lr_SCENE0;
				}
				LED_SetScene(LrScene);
				strcpy(msg_string, scene_name[LrScene]);
			}else{
#if 0
				LED_SetPulse(keytable[LrScene][bitpos].axis, keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
#else
				LED_SetPulse(get_axis(bitpos), keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
#endif
				sprintf(msg_string, "Note: %3d    S%1d", note, (LrScene % SCENE_COUNT) );
			}
			isSendMIDIEvent = true;

			//Print Message to OLED & LED
			if (keytable[LrScene][bitpos].message != NULL) {
				SSD1306_SetScreen(ON);

				strcpy(Msg_Buffer[0], keytable[LrScene][bitpos].message);
				strcpy(Msg_Buffer[1], msg_string);
				Msg_Print();

				Start_MsgTimer(MSG_TIMER_DEFAULT);
			}

			if (isSendMIDIEvent == true) {
				//Set 'Note ON
				USBMIDI_TxEvent.header = MIDI_NT_ON;
				USBMIDI_TxEvent.status = MIDI_NT_ON_S;
				USBMIDI_TxEvent.channel = note;
				USBMIDI_TxEvent.value = MIDI_NT_ON_VELOCITY;

				prev_note = note;
				isPrev_sw = true;
			}
		}else if( Key_Stat.wd & MASK_ENC ) { //Check encoder's move
			//Send CC Event from encoder
			uint8_t axis = (bitpos - KEY_COUNT) / 2;
			uint8_t val = MIDI_CC_Value[LrScene][axis];
			uint8_t channel = CC_CH_OFFSET + (LrScene * CC_CH_PER_SCENE) + axis;

			USBMIDI_TxEvent.header = MIDI_CC_HEADER;
			USBMIDI_TxEvent.status = MIDI_CC_STATUS;
			USBMIDI_TxEvent.channel = channel;
			USBMIDI_TxEvent.value = val;

			isPrev_sw = false;

			//Print Message to OLED & LED
			if (keytable[LrScene][bitpos].message != NULL) {
				SSD1306_SetScreen(ON);
				sprintf(msg_string,
					((channel > 99)? CC_MSG_3DG : CC_MSG_2DG), channel, val, LrScene);
				strcpy(Msg_Buffer[0], keytable[LrScene][bitpos].message);
				strcpy(Msg_Buffer[1], msg_string);
				Msg_Print();

				Start_MsgTimer(MSG_TIMER_DEFAULT);
			}
#if 0
			LED_SetPulse(keytable[LrScene][bitpos].axis, keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
#else
			LED_SetPulse(get_axis(bitpos), keytable[LrScene][bitpos].color, keytable[LrScene][bitpos].period);
#endif
			isSendMIDIEvent = true;

		} else if (isPrev_sw == true && rkey == 0) {// Switch is released
			//Send 'Note Off' Event
			USBMIDI_TxEvent.header = MIDI_NT_OFF;
			USBMIDI_TxEvent.status = MIDI_NT_OFF_S;
			USBMIDI_TxEvent.channel = prev_note;
			USBMIDI_TxEvent.value = MIDI_NT_OFF_VELO;

			isSendMIDIEvent = true;
			isPrev_sw = false;
		}

		if (isSendMIDIEvent == true) {
			//Send MIDI event via USB
			USBD_LL_Transmit (pInstance, MIDI_IN_EP, (uint8_t *)&USBMIDI_TxEvent, MIDI_EVENT_LENGTH);
			isSendMIDIEvent = false;
		}

		/* Clear the switch pressed flag */
		isKeyPressed = false;
	}
}
