/**
 * @file		EmulateMIDI.c
 * @brief		MIDI Emulation of LrTMAX
 * @author		remov-b4-flight
 * @copyright	3-Clause BSD License
 */
#include "EmulateMIDI.h"
#include "queue.h"
#include "stm32f0xx_it.h"

extern	uint8_t	LrScene;
extern	char *scene_name[SCENE_COUNT];
extern	PROF_DEFINE	prof_table[SCENE_COUNT][DEFINES_PER_SCENE];
extern	char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
extern	USBD_HandleTypeDef *pInstance;
//extern	uint8_t	enc_prev[ENC_COUNT];

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
//! If true, ISR detected any Switch was pushed.
bool	isAnyMatrixPushed;
//! If true ISR detected any Encoder was moved.
bool	isAnyEncoderMoved;
//! Switch pressed status set by timer scanning.
MTRX_SCAN	MTRX_Stat;
//! Encoder moved status set by timer scanning.
ENC_SCAN	ENC_Stat;
//! USB MIDI message structure for send
MIDI_MSG	MIDI_TxMessage;
//! Encoder move information
ENC_MOVE	enc_move;

/**
 * @brief	Rise CC message value
 * @param	channel to modify
 */
static bool MIDI_CC_Inc(uint8_t channel) {
	if (MIDI_CC_Value[channel] < MIDI_CC_MAX ) {
		MIDI_CC_Value[channel]++;
		return true;
	} else {
		return false;
	}
}
/**
 * @brief	Fall CC message value
 * @param	channel to modify
 */
static bool MIDI_CC_Dec(uint8_t channel) {
	if (MIDI_CC_Value[channel] >= (MIDI_CC_MIN + 1) ) {
		MIDI_CC_Value[channel]--;
		return true;
	} else {
		return false;
	}
}

/**
 * 	@brief	Initialize MIDI
 */
void EmulateMIDI_Init() {
	isPrev_SwPush = false;
	isPrev_Scene = false;
	memset(MIDI_CC_Value, MIDI_CC_INITIAL, CC_CH_COUNT);
	queue_init(&midi_rx_que);
}

/**
 *	@brief	Generate MIDI message and Send to host by User interaction.
 *	@pre	isAnyMatrixPushed 	any Switches was pressed or not
 *	@pre	isAnyEncodersMoved 	any Encoders was moved or not
 *	@pre	ENCSW_Stat	current Switches/Encoders status
 */
void EmulateMIDI() {
	bool isSendMIDIMessage = false;
	uint8_t		bitpos;
	if (queue_isempty(&midi_rx_que) != true) { // Check MIDI CC message
		CH_VAL rx;
		uint8_t cc_scene = 0;
		do {
			rx.wd = queue_dequeue(&midi_rx_que);
			cc_scene = ((rx.by.ch - CC_CH_OFFSET) / CC_CH_PER_SCENE) & CH_SCENE_MASK;
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
	} else if ( isAnyMatrixPushed == true) {
		uint16_t	rstat = (MTRX_Stat.wd);
		bitpos = ntz16(MTRX_Stat.wd);

		if ( MTRX_Stat.wd != 0) { //Check Matrix switches/encoders
			//Send 'Note On' message from switches/encoders matrix.
			uint8_t	note = ((MTRX_Stat.wd & MASK_ENCPUSH)? NOTE_OFFSET : 0) + (LrScene * NOTES_PER_SCENE) + bitpos;
			if (MTRX_Stat.wd == RESET_SW_PATTERN) {
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
				//Set 'Note On' message
				MIDI_TxMessage.header = MIDI_NT_ON;
				MIDI_TxMessage.status = MIDI_NT_ON_S;
				MIDI_TxMessage.channel = note;
				MIDI_TxMessage.value = MIDI_NT_ON_VELOCITY;

				prev_note = note;
				isPrev_SwPush = true;
			}
		} else if (isPrev_SwPush == true && rstat == 0) {// Is switch/encoder push released?
			//Set 'Note Off' message.
			MIDI_TxMessage.header = MIDI_NT_OFF;
			MIDI_TxMessage.status = MIDI_NT_OFF_S;
			MIDI_TxMessage.channel = prev_note;
			MIDI_TxMessage.value = MIDI_NT_OFF_VELO;

			isSendMIDIMessage = true;
			isPrev_SwPush = false;
		}
		isAnyMatrixPushed = false;
	}else if ( isAnyEncoderMoved == true) { //check encoder movements
		uint8_t	axis = enc_move.bits.axis;
		uint8_t channel = CC_CH_OFFSET + (LrScene * CC_CH_PER_SCENE) + axis;

		bitpos = PROF_ENC1ST + (axis * 2);

		if (enc_move.bits.move == ENC_MOVE_CW){
			isSendMIDIMessage = MIDI_CC_Inc(channel);
		} else if (enc_move.bits.move == ENC_MOVE_CCW){
			isSendMIDIMessage = MIDI_CC_Dec(channel);
			bitpos += 1;
		} else {
			goto rot_stopped_exits;
		}

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


rot_stopped_exits:
		isAnyEncoderMoved = false;
	}
	//Send MIDI message
	if (isSendMIDIMessage == true) {
		//flash LED.
		LED_SetPulse(prof_table[LrScene][bitpos].axis, prof_table[LrScene][bitpos].color, prof_table[LrScene][bitpos].period);
		//Send MIDI message via USB.
		if (USBD_LL_Transmit(pInstance, MIDI_IN_EP, (uint8_t *)&MIDI_TxMessage, MIDI_MESSAGE_LENGTH) == USBD_OK) {
			isSendMIDIMessage = false;
		}
	}

}
