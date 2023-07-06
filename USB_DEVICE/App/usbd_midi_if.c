/**
	******************************************************************************
	* @file	usbd_midi_if.c
	* @brief	USB MIDI class implement functions.
	******************************************************************************
		(CC at)2016 by D.F.Mac. @@TripArts Music
	******************************************************************************

		Modified by keshikan (www.keshikan.net) 2018
		The license is (CC BY 4.0), and takes over from original usbd_midi_if.h/c.

		See also original source code page.
		https://github.com/mimuz/mimuz-tuch/blob/master/STM32/

	******************************************************************************
 */

/**
*	@note This file is modified by remov-b4-flight for use with LrTMAX.
*	Original headers are above.
*	Un-needed parts of original source are removed.
*	@author modified by remov-b4-flight
*	@copyright CC BY 4.0
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "LrCommon.h"
#include "usbd_midi_if.h"
#include "stm32f0xx_hal.h"
#include "midi.h"
#include "EmulateMIDI.h"

// basic MIDI RX/TX functions
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length);
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length);

extern uint8_t MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];
extern char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
extern bool isPrev_scene;
/**
 *	@brief	Array of callback function pointer with MIDI.
 */
USBD_MIDI_ItfTypeDef USBD_Interface_fops_FS =
{
	MIDI_DataRx,
	MIDI_DataTx	//Unused
};

/**
 *	@brief	MIDI message receive callback function.
 *	@param	*msg	Pointer to received MIDI message.
 *	@param	length	Length of received data.
 */
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length){
	char 		msg_string[MSG_WIDTH + 1];
	uint8_t	message_count = length / MIDI_MESSAGE_LENGTH;
	MIDI_EVENT *rx_message = (MIDI_EVENT *)msg;

	for (uint8_t i = 0; i < message_count; i++,rx_message++){
		if ( (rx_message->header & 0x0F) != MIDI_CC_HEADER
				|| rx_message->channel < CC_CH_OFFSET
				|| CC_CH_MAX < rx_message->channel ) {
			continue;
		}
		uint8_t cc_index = rx_message->channel - CC_CH_OFFSET;

		uint8_t cc_scene = (cc_index / CC_CH_PER_SCENE) & 0x03;
		uint8_t cc_axis = (cc_index % CC_CH_PER_SCENE) & 0x7f;
		MIDI_CC_Value[cc_scene][cc_axis] = rx_message->value;
		SSD1306_SetScreen(ON);
		sprintf(msg_string, CC_MSG_2DG, rx_message->channel, rx_message->value, cc_scene);
		strcpy(Msg_Buffer[0], msg_string);
		if (isPrev_scene == true) {
			memset(Msg_Buffer[1], (int)SPACE_CHAR, MSG_WIDTH );
		}
		Msg_Print();

		Start_MsgTimer(MSG_TIMER_DEFAULT);
	}
	return USBD_OK;
}

/**
 * @brief Unused callback function
 */
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length){
	return USBD_OK;
}

