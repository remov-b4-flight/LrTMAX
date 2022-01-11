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
#include "usbd_midi_if.h"
#include "stm32f0xx_hal.h"
#include "midi.h"

// basic MIDI RX/TX functions
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length);
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length);

extern uint8_t MIDI_CC_Value[SCENE_COUNT][ENC_COUNT];
extern uint8_t LrScene;

/**
 *	@brief	Array of callback function pointer with MIDI.
 */
USBD_MIDI_ItfTypeDef USBD_Interface_fops_FS =
{
  MIDI_DataRx,
  MIDI_DataTx	//Unused
};

/**
 *	@brief	MIDI event receive callback function.
 *	@param	*msg	Pointer to received MIDI event.
 *	@param	length	Length of received data.
 */
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length){

  uint8_t code_idx_num = msg[MIDI_EV_IDX_HEADER] & 0x0F;
  uint8_t cc_channel = msg[MIDI_EV_IDX_CHANNEL] - CC_CH_OFFSET;
  uint8_t value = msg[MIDI_EV_IDX_VALUE];
  uint8_t cc_scene = cc_channel / CC_CH_PER_SCENE;
  uint8_t channel = cc_channel % CC_CH_PER_SCENE;
  if(length % MIDI_EVENT_LENGTH != 0){
	  return 0;
  }

  if (code_idx_num == MIDI_CC_HEADER){
	  MIDI_CC_Value[cc_scene][channel] = value;
  }

  return USBD_OK;
}

/**
 * @brief Unused callback function
 */
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length){
  return USBD_OK;
}

