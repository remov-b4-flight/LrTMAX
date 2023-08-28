/**
 * @file	midi.h
 * @brief	header file for USB MIDI function.
 * @author	remov-b4-flight
 * @copyright	3-Clause BSD License
 */

#ifndef INC_MIDI_NOTE_H_
#define INC_MIDI_NOTE_H_

//! Commonly used
#define MIDI_UNUSED			0x00
#define MIDI_MESSAGE_LENGTH	4

//! @defgroup Descriptor types
#define CONFIG				0x02
#define INTERFACE			0x04
#define CS_INTERFACE		0x24
#define ENDPOINT			0x05
#define CS_ENDPOINT			0x25

//! @defgroup Configuration descriptor
#define CONFIG1				0x01
#define BUSPOWERED			0x80
#define REMOTE_WAKEUP		0x20
#define MIDI_POWER			0x64 //=200mA
#define NUM_INTF			0x01

//! @defgroup Interface descriptor
#define INTF0				0x00
#define INTF1				0x01
#define AUDIO				0x01

//! @defgroup Interface descriptor sub-type
#define AUDIO_CONTROL		0x01
#define MIDI_STREAM			0x03

#define ALTER0				0x00

//! CS Interface descriptor
#define HEADER				0x01
#define MS_GENERAL			0x01
#define REFRESH				0x01
#define BULK				0x02
#define INTERVAL			0x00

//! Numbers of Endpoints
#define MS_NUM_EP			0x02

//! @defgroup defining Jacks
#define MIDI_IN_JACK		0x02
#define MIDI_OUT_JACK		0x03
#define MIDI_JTYPE_ENB		0x01
#define MIDI_JTYPE_EXT		0x02

//! @defgroup Note constants
#define MIDI_NT_ON			0x09
#define MIDI_NT_ON_S		0x90
#define MIDI_NT_OFF			0x08
#define MIDI_NT_OFF_S		0x80

//! @defgroup LrTMAX does not use keyboard velocity
#define MIDI_NT_ON_VELOCITY	0x7F
#define MIDI_NT_OFF_VELO	0x40
#define MIDI_CC_HEADER		0x0B
#define MIDI_CC_STATUS		0xB0

//! CC @defgroup constants
//! Used with CC control as button(unused in LrTMAX)
#define MIDI_CC_ON			0x7F
#define MIDI_CC_OFF			0x00

//! CC @defgroup boundaries
#define MIDI_CC_MAX			0x7F
#define MIDI_CC_MIN			0x00
#define MIDI_CC_INITIAL		0x40

//! Others
#define CC_CH_COUNT			128
#define	CC_CH_MAX			(CC_CH_COUNT-1)
#endif /* INC_MIDI_NOTE_H_ */
