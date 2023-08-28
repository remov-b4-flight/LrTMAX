/*
 * @file		EmulateMIDI.h
 * @brief		Definitions	for EmulateMIDI() function
 * @author		remov-b4-flight
 * @copyright	3-Clause BSD License
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

//! define switch combination to invoke reset
#define RESET_SW_PATTERN	0x81	//[Undo]+[Scene]
//! @defgroup CC message display format on OLED.
#define CC_MSG_2DG	"Ch%2u = %3u    S%1u"
#define CC_MSG_3DG	"C%3u = %3u    S%1u"

//! @defgroup number of cc channels that LrTMAX controls.
#define CC_COUNT_INUSE	(ENC_COUNT * SCENE_COUNT)
#define CC_MAX_INUSE	(CC_CH_OFFSET + CC_COUNT_INUSE)
#define CC_MIN_INUSE	CC_CH_OFFSET

//! Received from MIDI channel-value pair
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
