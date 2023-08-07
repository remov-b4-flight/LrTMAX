/**
 * @file	EmulateMIDI.c
 * @author	remov-b4-flight
 * @brief	MIDI Emulation of LrTMAX
 */
#include "EmulateMIDI.h"
#include "queue.h"
#include "stm32f0xx_it.h"

extern	ENCSW_SCAN	ENCSW_Stat;
extern	uint8_t	LrScene;
extern	char *scene_name[SCENE_COUNT];
extern	PROF_DEFINE	prof_table[SCENE_COUNT][DEFINES_PER_SCENE];
extern	char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
//! Instance Handle of USB interface
extern	USBD_HandleTypeDef *pInstance;
extern	uint8_t	enc_prev[ENC_COUNT];
//! keeps previous 'Note On' note number For sending 'Note Off' message.
uint8_t	prev_note;
//! If true, MIDI message previous sent is switch. If false, it's encoder
bool	isPrev_SwPush;
//! Indicate scene name appearing on OLED. need clearing buffers.
bool	isPrev_Scene;

// MIDI variables
//! MIDI CC message value for each channels.
uint8_t	MIDI_CC_Value[CC_CH_COUNT];
//! Queing received MIDI message;
QUEUE	midi_rx_que;
//OLED message buffer
char 	msg_string[MSG_WIDTH + 2];
// keyboard variable
//! If true, ISR detected any Switch/Encoder was moved.
bool	isAnyMoved;
//! Switch pressed/Encoder moved status set by timer scanning.
ENCSW_SCAN	ENCSW_Stat;

/**
 * @brief	Rise CC message value
 * @param	channel to modify
 */
static void MIDI_CC_Inc(uint8_t channel) {
	if (MIDI_CC_Value[channel] < MIDI_CC_MAX ) {
		MIDI_CC_Value[channel]++;
	}
}
/**
 * @brief	Fall CC message value
 * @param	channel to modify
 */
static void MIDI_CC_Dec(uint8_t channel) {
	if (MIDI_CC_Value[channel] >= (MIDI_CC_MIN + 1) ) {
		MIDI_CC_Value[channel]--;
	}
}

/**
 * 	@brief	Initialize MIDI
 */
void EmulateMIDI_Init(){
	isPrev_SwPush = false;
	isPrev_Scene = false;

	//! Initialize all enc_prev[] for current pin value
	enc_prev[Lr_ENC4] = (ENC4_GPIO_Port->IDR) & ENC_MASK;
	enc_prev[Lr_ENC1] = (ENC1_GPIO_Port->IDR >> 8) & ENC_MASK;
	enc_prev[Lr_ENC2] = (ENC2_GPIO_Port->IDR >> 10) & ENC_MASK;
	enc_prev[Lr_ENC6] = (ENC6_GPIO_Port->IDR >> 2) & ENC_MASK;
	enc_prev[Lr_ENC7] = (ENC7_GPIO_Port->IDR >> 6) & ENC_MASK;
	enc_prev[Lr_ENC5] = ( (ENC5A_GPIO_Port->IDR & ENC5A_MASK) | (ENC5B_GPIO_Port->IDR & ENC5B_MASK) ) >> 12;
	enc_prev[Lr_ENC0] = (ENC0_GPIO_Port->IDR >> 4 ) & ENC_MASK;
	enc_prev[Lr_ENC3] = (ENC3_GPIO_Port->IDR >> 14 ) & ENC_MASK;

	memset(MIDI_CC_Value, MIDI_CC_INITIAL, CC_CH_COUNT);
	queue_init(&midi_rx_que);
}

/**
 *	@brief	Generate MIDI message and Send to host by User interaction.
 *	@pre	isAnyMoved	any Switches/Encoders was pressed/moved or not
 *	@pre	ENCSW_Stat	current Switches/Encoders status
 */
void EmulateMIDI() {
	if (queue_isempty(&midi_rx_que) != true) {
		CH_VAL rx;
		uint8_t cc_scene = 0;
		do {
			rx.wd = queue_dequeue(&midi_rx_que);
			cc_scene = ((rx.by.ch - CC_CH_OFFSET) / CC_CH_PER_SCENE) & 0x07;
			if ( CC_MIN_INUSE <= rx.by.ch && rx.by.ch < CC_MAX_INUSE ) {
				MIDI_CC_Value[rx.by.ch] = rx.by.val;
			}
		} while  (queue_isempty(&midi_rx_que) != true);
		SSD1306_SetScreen(ON);
		sprintf(Msg_Buffer[0], ((rx.by.ch <= 99)? CC_MSG_2DG:CC_MSG_3DG), rx.by.ch, rx.by.val, cc_scene);
		if (isPrev_Scene == true) {
			memset(Msg_Buffer[1], (int)SPACE_CHAR, MSG_WIDTH );
			isPrev_Scene = false;
		}
		Msg_Print();
		Start_MsgTimer(MSG_TIMER_DEFAULT);
	} else if (isAnyMoved) {
		//! USB MIDI message structure for send
		MIDI_MSG	MIDI_TxMessage;
		uint32_t	rstat = (ENCSW_Stat.wd);
		uint8_t		bitpos = ntz32(ENCSW_Stat.wd);
		bool 		isSendMIDIMessage = false;

		if ( ENCSW_Stat.wd & MASK_ENC_SW ) { //Check Matrix switches
			//Send 'Note On' message from switches/encoders matrix.
			uint8_t	note = ((ENCSW_Stat.wd & MASK_ENCPUSH)? NOTE_OFFSET : 0) + (LrScene * NOTES_PER_SCENE) + bitpos;
			if (ENCSW_Stat.wd == RESET_SW_PATTERN) {
				HAL_NVIC_SystemReset();
			}else if (bitpos == SCENE_BIT) { //is [SCENE] switch pressed?
			   	//Move to next Scene.
				if ( (++LrScene) >= SCENE_COUNT ) {
					LrScene = Lr_SCENE0;
				}
				LED_SetScene(LrScene);
				sprintf(Msg_Buffer[0], "Scene %1d",LrScene);
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
				MIDI_TxMessage.header = MIDI_NT_ON;
				MIDI_TxMessage.status = MIDI_NT_ON_S;
				MIDI_TxMessage.channel = note;
				MIDI_TxMessage.value = MIDI_NT_ON_VELOCITY;

				prev_note = note;
				isPrev_SwPush = true;
			}
		}else if( ENCSW_Stat.wd & MASK_ENC ) { //Check encoder's movements
			//Send CC message from encoders.
			uint8_t axis = (bitpos - ENC_SW_COUNT) / 2;
			uint8_t channel = CC_CH_OFFSET + (LrScene * CC_CH_PER_SCENE) + axis;
			(bitpos % 2) ? MIDI_CC_Dec(channel):MIDI_CC_Inc(channel);

			MIDI_TxMessage.header = MIDI_CC_HEADER;
			MIDI_TxMessage.status = MIDI_CC_STATUS;
			MIDI_TxMessage.channel = channel;
			MIDI_TxMessage.value = MIDI_CC_Value[channel];

			isPrev_SwPush = false;

			//Print Message to OLED & LEDs.
			SSD1306_SetScreen(ON);
			sprintf(msg_string, CC_MSG_2DG, channel, MIDI_CC_Value[channel], LrScene & 0x3);
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
			MIDI_TxMessage.header = MIDI_NT_OFF;
			MIDI_TxMessage.status = MIDI_NT_OFF_S;
			MIDI_TxMessage.channel = prev_note;
			MIDI_TxMessage.value = MIDI_NT_OFF_VELO;

			isSendMIDIMessage = true;
			isPrev_SwPush = false;
		}

		if (isSendMIDIMessage == true) {
			//Send MIDI message via USB.
			USBD_LL_Transmit (pInstance, MIDI_IN_EP, (uint8_t *)&MIDI_TxMessage, MIDI_MESSAGE_LENGTH);
			isSendMIDIMessage = false;
		}

		/* Clear the switch pressed flag */
		isAnyMoved = false;
	}
}
