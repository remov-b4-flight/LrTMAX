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
#include "queue.h"

// basic MIDI RX/TX functions
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length);
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length);

extern uint8_t MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];
extern QUEUE midi_rx_que;

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
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length) {

	uint8_t	message_count = length / MIDI_MESSAGE_LENGTH;
	MIDI_MESSAGE *rx_message = (MIDI_MESSAGE *)msg;
	for (uint8_t i = 0; i < message_count; i++,rx_message++) {
		if ( (rx_message->header & 0x0F) != MIDI_CC_HEADER
				|| rx_message->channel < CC_CH_OFFSET
				|| CC_CH_MAX < rx_message->channel ) {
			continue;
		}
#if 1
		CH_VAL rx;
		rx.by.ch = rx_message->channel;
		rx.by.val = rx_message->value;
#else
		uint16_t value = (rx_message->channel<< 8) + rx_message->value;
#endif
		if(queue_enqueue(&midi_rx_que, rx.wd) == false) {
			return USBD_FAIL;
		}
	}
	return USBD_OK;
}

/**
 * @brief Unused callback function
 */
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length){
	return USBD_OK;
}

