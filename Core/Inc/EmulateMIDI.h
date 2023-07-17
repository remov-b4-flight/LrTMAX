/*
 * EmulateMIDI.h
 *
 *  Created on: Jun 26, 2023
 *      Author: jenoki
 */

#ifndef INC_EMULATEMIDI_H_
#define INC_EMULATEMIDI_H_
#include <prof_define.h>
#include "main.h"
#include "midi.h"
#include "usbd_midi_if.h"
#include "bitcount.h"
#include "ssd1306.h"
#include "led.h"
//! deine switch combination to invoke reset
#define RESET_SW_PATTERN	0x81	//[Undo]+[Scene]
#define CC_MSG_2DG	"Ch%2u = %3u    S%1u"

//! recived channel-value pair
typedef union ch_val_t {
	uint16_t	wd;
	struct cval_t {
		uint8_t	ch;
		uint8_t	val;
	} by;
}CH_VAL;

void EmulateMIDI();
void EmulateMIDI_Init();

#endif /* INC_EMULATEMIDI_H_ */
