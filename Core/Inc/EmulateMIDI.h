/*
 * EmulateMIDI.h
 *
 *  Created on: Jun 26, 2023
 *      Author: jenoki
 */

#ifndef INC_EMULATEMIDI_H_
#define INC_EMULATEMIDI_H_
#include "midi.h"
#include "usbd_midi_if.h"
#include "bitcount.h"
#include "key_define.h"
#include "ssd1306.h"
#include "led.h"
//! deine Key combination to invoke reset
#define RESET_KEY_PATTERN	0x81	//[Undo]+[Scene]
#define CC_MSG_3DG	"C%3u = %3u    S%1u"
#define CC_MSG_2DG	"Ch%2u = %3u    S%1u"

void EmulateMIDI();
void EmulateMIDI_Init();

#endif /* INC_EMULATEMIDI_H_ */
