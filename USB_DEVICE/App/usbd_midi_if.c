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
*	@note This file is modified by remov-b4-flight for use with LrE-6.
*	Original headers are up.
*	Unneeded parts of original source are excluded by #if 0
*	@author modified by remov-b4-flight
*	@copyright CC BY 4.0
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_midi_if.h"
#include "stm32f0xx_hal.h"
#include "midi.h"

// basic MIDI RX/TX functions
#if MIDI
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length);
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length);
#endif

extern uint8_t MIDI_CC_Value[SCENE_COUNT][ROT_COUNT];
extern uint8_t LrE6Scene;

// for Cure Series
#if 0 //Unused for LrE-6
#define MIDI_BUFFER_SIZ (512)//FIFO buffer byte size for midi message buffer
RingBufferU8 rbuf_usb_rx[MIDI_OUT_JACK_NUM]; //for input from USB
RingBufferU8 rbuf_jack_rx[MIDI_IN_JACK_NUM];  //for input from MIDI-IN jack


//for receiving midi data from jack

MidiAnalysisStatus analyzed_status[MIDI_IN_JACK_NUM];
MIDIEvent midi_event[MIDI_IN_JACK_NUM];	//received midi data
uint8_t rx_midi_msg[MIDI_IN_JACK_NUM];

FUNC_STATUS midiInit()
{
	uint32_t i,j;

	for(i=0; i<MIDI_OUT_JACK_NUM; i++){
		if(BUFFER_SUCCESS != cureRingBufferU8Init(&rbuf_usb_rx[i], MIDI_BUFFER_SIZ))
		{
			return FUNC_ERROR;
		}
	}
	for(i=0; i<MIDI_IN_JACK_NUM; i++){
		if(BUFFER_SUCCESS != cureRingBufferU8Init(&rbuf_jack_rx[i], MIDI_BUFFER_SIZ))
		{
			return FUNC_ERROR;
		}
	}

	//Init RX
	for(i=0; i<MIDI_IN_JACK_NUM; i++){

		rx_midi_msg[i] = 0x00;
		analyzed_status[i].data_idx = 0;
		midi_event[i].length = 0;

		for(j=0; j<MIDI_SENDDATA_MAX; j++){
			midi_event[i].midi_byte[j] = 0x00;
		}
	}
	return FUNC_SUCCESS;
}

FUNC_STATUS midiGetFromUsbRx(uint8_t cable_num, uint8_t* dat)
{
	if(BUFFER_SUCCESS != cureRingBufferU8Dequeue(&rbuf_usb_rx[cable_num], dat))
	{
		return FUNC_ERROR;
	}

	return FUNC_SUCCESS;
}

FUNC_STATUS midiGetFromJackRx(uint8_t cable_num)
{
	if(BUFFER_SUCCESS != cureRingBufferU8Dequeue(&rbuf_jack_rx[cable_num], &rx_midi_msg[cable_num]))
	{
		return FUNC_ERROR;
	}

	return FUNC_SUCCESS;
}

FUNC_STATUS midiSetFromJackRx(uint8_t cable_num, uint8_t* dat)
{
	if(BUFFER_SUCCESS != cureRingBufferU8Enqueue(&rbuf_jack_rx[cable_num], dat))
	{
		return FUNC_ERROR;
	}

	return FUNC_SUCCESS;
}


bool isUsbRxBufEmpty(uint8_t cable_num)
{
	if( 0 != _cureRingBufferU8GetUsedSize(&rbuf_usb_rx[cable_num]) ){
		return false;
	}

	return true;
}

bool isJackRxBufEmpty(uint8_t cable_num)
{
	if( 0 != _cureRingBufferU8GetUsedSize(&rbuf_jack_rx[cable_num]) ){
		return false;
	}

	return true;
}

bool isRxBufEmpty()
{
	uint32_t i;

	for(i=0; i<MIDI_OUT_JACK_NUM; i++){
		if(0 != _cureRingBufferU8GetUsedSize(&rbuf_usb_rx[i]))
		{
			return false;
		}
	}

	for(i=0; i<MIDI_IN_JACK_NUM; i++){
		if(0 != _cureRingBufferU8GetUsedSize(&rbuf_jack_rx[i]))
		{
			return false;
		}
	}
	return true;
}
#endif//Unused for LrE-6

#if MIDI
/**
 *	@brief	Array of callback function pointer with MIDI.
 */
USBD_MIDI_ItfTypeDef USBD_Interface_fops_FS =
{
  MIDI_DataRx,
  MIDI_DataTx
};

/**
 *	@brief	MIDI event receive callback function.
 *	@param	*msg	Pointer to received MIDI event.
 *	@param	length	Length of received data.
 */
static uint16_t MIDI_DataRx(uint8_t *msg, uint16_t length){
#if 1
  uint8_t code_idx_num = msg[MIDI_EV_IDX_HEADER] & 0x0F;
  uint8_t cc_channel = msg[MIDI_EV_IDX_CHANNEL];
  uint8_t value = msg[MIDI_EV_IDX_VALUE];
  uint8_t cc_scene = cc_channel / CC_CH_PER_SCENE;
  uint8_t channel = cc_channel % CC_CH_PER_SCENE;
  if(length % MIDI_EVENT_LENGTH != 0){
	  return 0;
  }

  if (code_idx_num == MIDI_CC_HEADER){
	  MIDI_CC_Value[cc_scene][channel] = value;
  }
#endif
  return 0;
}

/**
 * @brief Unused callback function
 */
static uint16_t MIDI_DataTx(uint8_t *msg, uint16_t length){
#if 0
	uint32_t i = 0;
  while (i < length) {
    APP_Rx_Buffer[APP_Rx_ptr_in] = *(msg + i);
    APP_Rx_ptr_in++;
    i++;
    if (APP_Rx_ptr_in == APP_RX_DATA_SIZE) {
      APP_Rx_ptr_in = 0;
    }
  }
#endif
  return USBD_OK;
}
#endif //MIDI

#if 0 //Unused for LrE-6
void sendMidiMessage(uint8_t *msg, uint16_t size){
  if(size == 4){
//	APP_Rx_Buffer[0] = msg[0];
//	APP_Rx_Buffer[1] = msg[1];
//	APP_Rx_Buffer[2] = msg[2];
//	APP_Rx_Buffer[3] = msg[3];
//    USBD_MIDI_SendData(&hUsbDeviceFS, APP_Rx_Buffer, size);
    MIDI_DataTx(msg, size);
  }
}
bool midiEventIsGenerated(uint8_t cable_num)
{
	uint8_t upper_half_byte= (rx_midi_msg[cable_num]) & 0xF0;

	if( upper_half_byte & 0x80 ){//0x80-0xFF:status byte

		switch(upper_half_byte){

			case 0xF0://0xF0-0xFF:system message
				switch(rx_midi_msg[cable_num]){

					case 0xF0://SysEx Start
						analyzed_status[cable_num].data_idx = 0;
						midi_event[cable_num].midi_byte[ analyzed_status[cable_num].data_idx++ ] = rx_midi_msg[cable_num];
						analyzed_status[cable_num].type = MSG_SYSEX;
						analyzed_status[cable_num].stat = WAIT_SYSTEM_DATA;
						break;

					case 0xF7://SysEx End
						midi_event[cable_num].midi_byte[ analyzed_status[cable_num].data_idx++ ] = rx_midi_msg[cable_num];
						midi_event[cable_num].length = analyzed_status[cable_num].data_idx;
						analyzed_status[cable_num].stat = END_ANALYSIS;
						break;

					case 0xF2://Song Position
						midi_event[cable_num].midi_byte[0] = rx_midi_msg[cable_num];
						analyzed_status[cable_num].type = MSG_THREE_BYTE;
						analyzed_status[cable_num].stat = WAIT_DATA1;
						break;

					case 0xF1://Time Code
					case 0xF3://Song Select
						midi_event[cable_num].midi_byte[0] = rx_midi_msg[cable_num];
						analyzed_status[cable_num].type = MSG_TWO_BYTE;
						analyzed_status[cable_num].stat = WAIT_DATA1;
						break;

					case 0xF4://Undefined
					case 0xF5://Undefined
					case 0xF6://Tune request
					case 0xF8://Timing clock
					case 0xF9://Undefined
					case 0xFA://Start
					case 0xFB://Continue
					case 0xFC://Stop
					case 0xFD://Undefined
					case 0xFE://Active Sensing
					case 0xFF://Reset
						midi_event[cable_num].midi_byte[0] = rx_midi_msg[cable_num];
						midi_event[cable_num].length = 1;
						analyzed_status[cable_num].type = MSG_ONE_BYTE;
						analyzed_status[cable_num].stat = END_ANALYSIS;
						break;
				}
				analyzed_status[cable_num].is_system_common = true;
				break;

			case 0x80://Note Off
			case 0x90://Note On
			case 0xA0://Polyphonic key-pressure
			case 0xB0://ControlChange
			case 0xE0://PitchBend
				midi_event[cable_num].midi_byte[0] = rx_midi_msg[cable_num];
				analyzed_status[cable_num].type = MSG_THREE_BYTE;
				analyzed_status[cable_num].stat = WAIT_DATA1;
				analyzed_status[cable_num].is_system_common = false;
				break;

			case 0xC0://Program Change
			case 0xD0://Channel pressure
				midi_event[cable_num].midi_byte[0] = rx_midi_msg[cable_num];
				analyzed_status[cable_num].type = MSG_TWO_BYTE;
				analyzed_status[cable_num].stat = WAIT_DATA1;
				analyzed_status[cable_num].is_system_common = false;
				break;

			default:
				analyzed_status[cable_num].type = MSG_NOTHING;
				analyzed_status[cable_num].stat = START_ANALYSIS;
				analyzed_status[cable_num].is_system_common = false;
				break;
		}

	}else{//0x00-0x7F:data byte

		switch(analyzed_status[cable_num].stat){

			case WAIT_DATA1:
				midi_event[cable_num].midi_byte[1] = rx_midi_msg[cable_num];

				if(MSG_THREE_BYTE == analyzed_status[cable_num].type ){
					analyzed_status[cable_num].stat = WAIT_DATA2;
				}else if( MSG_TWO_BYTE == analyzed_status[cable_num].type ){
					midi_event[cable_num].length = 2;
					analyzed_status[cable_num].stat = END_ANALYSIS;
				}else{
					analyzed_status[cable_num].stat = START_ANALYSIS;
				}
				break;

			case WAIT_DATA2:
				if(MSG_THREE_BYTE == analyzed_status[cable_num].type ){
					midi_event[cable_num].midi_byte[2] = rx_midi_msg[cable_num];
					midi_event[cable_num].length = 3;
					analyzed_status[cable_num].stat = END_ANALYSIS;
				}else{
					analyzed_status[cable_num].stat = START_ANALYSIS;
				}
				break;

			case WAIT_SYSTEM_DATA:
				midi_event[cable_num].midi_byte[ analyzed_status[cable_num].data_idx++ ] = rx_midi_msg[cable_num];

				if(analyzed_status[cable_num].data_idx > (MIDI_SENDDATA_MAX - 1) ){
					analyzed_status[cable_num].stat = END_ANALYSIS;
				}
				break;

			case END_ANALYSIS://running status:When status byte is omitted.
				midi_event[cable_num].midi_byte[1] = rx_midi_msg[cable_num];
				if(MSG_THREE_BYTE == analyzed_status[cable_num].type){
					analyzed_status[cable_num].stat = WAIT_DATA2;
				}else if(MSG_TWO_BYTE == analyzed_status[cable_num].type){
					midi_event[cable_num].length = 2;
					analyzed_status[cable_num].stat = END_ANALYSIS;
				}
				break;

			case START_ANALYSIS:
				break;

			default:
				break;
		}
	}

	if(END_ANALYSIS == analyzed_status[cable_num].stat){
		return true;
	}else{
		return false;
	}

}


void midiGenerateUsbPacket(uint8_t cable_num)
{
	uint8_t msg_buf[4] = {0x00,0x00,0x00,0x00};
	uint32_t cnt_remain=0, cnt_length;

	switch(analyzed_status[cable_num].type){

		case MSG_ONE_BYTE:
			//byte 0: cable number + code index number
			msg_buf[0] = (cable_num << 4) + ((midi_event[cable_num].midi_byte[0] & 0xF0) >> 4);

			sendMidiMessage(msg_buf,4);
			break;

		case MSG_TWO_BYTE:
		case MSG_THREE_BYTE:
			//byte 0: cable number + code index number
			if(analyzed_status[cable_num].is_system_common){
				msg_buf[0] = (cable_num << 4) + midi_event[cable_num].length;
			}else{
				msg_buf[0] = (cable_num << 4) + ((midi_event[cable_num].midi_byte[0] & 0xF0) >> 4);
			}

			//byte 1-3
			for(uint32_t i=0; i<midi_event[cable_num].length; i++){
				msg_buf[i+1] = midi_event[cable_num].midi_byte[i];
			}

			sendMidiMessage(msg_buf,4);
			break;

		case MSG_SYSEX:
			for(cnt_length = 0; cnt_length < midi_event[cable_num].length; cnt_length++){
				if( 0xF7 !=midi_event[cable_num].midi_byte[cnt_length] ){
					if(2 == cnt_remain){
						msg_buf[3] = midi_event[cable_num].midi_byte[cnt_length];
						msg_buf[0] = (cable_num << 4) + 0x4;	//SysEx starts or continues
						sendMidiMessage(msg_buf,4);
					}else{
						msg_buf[1 + cnt_remain] = midi_event[cable_num].midi_byte[cnt_length];
					}


				}else{

					switch (cnt_remain) {
						case 0:
							msg_buf[0] = (cable_num << 4) + 0x5;	//SysEx ends with following single byte
							msg_buf[1] = 0xF7;
							msg_buf[2] = msg_buf[3] = 0x00;
							sendMidiMessage(msg_buf,4);
							break;

						case 1:
							msg_buf[0] = (cable_num << 4) + 0x6;	//SysEx ends with following two bytes.
							msg_buf[2] = 0xF7;
							msg_buf[3] = 0x00;
							sendMidiMessage(msg_buf,4);
							break;

						case 2:
							msg_buf[0] = (cable_num << 4) + 0x7;	//SysEx ends with following three bytes.
							msg_buf[3] = 0xF7;
							sendMidiMessage(msg_buf,4);
							break;
						default:
							break;
					}
				}

				cnt_remain++;
				if(cnt_remain >=3){
					cnt_remain = 0;
				}
			}
			break;

		default:
			break;
	}
	USBD_MIDI_SendPacket();
}

void midiProcess(){

	for(uint32_t cable_num=0; cable_num<MIDI_IN_JACK_NUM; cable_num++){
		while( FUNC_SUCCESS == midiGetFromJackRx(cable_num) ){
			if( midiEventIsGenerated(cable_num) ){// Generate MIDI event from UART buffer.
				//Analyze MIDI Message.
				midiGenerateUsbPacket(cable_num);
			}
		}
	}
}
#endif //Unused for LrE-6
