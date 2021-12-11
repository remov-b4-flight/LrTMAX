/**
 * @file	midi.h
 * @brief	header file for USB MIDI function.
 * @author	remov-b4-flight
 * @copyright	3-Clause BSD License
 */

#ifndef INC_MIDI_NOTE_H_
#define INC_MIDI_NOTE_H_

//! MIDI event offsets
enum midi_event_index {
	MIDI_EV_IDX_HEADER = 0,
	MIDI_EV_IDX_STATUS = 1,
	MIDI_EV_IDX_CHANNEL = 2,
	MIDI_EV_IDX_VALUE = 3,
};

//! Commonly used
#define MIDI_UNUSED		0x00
#define MIDI_EVENT_LENGTH	4
//! Descriptor types
#define CONFIG			0x02
#define INTERFACE		0x04
#define CS_INTERFACE	0x24
#define ENDPOINT		0x05
#define	CS_ENDPOINT		0x25

//! Configuration descriptor
#define CONFIG1			0x01
#define BUSPOWERED		0x80
#define MIDI_POWER		0x64 //=200mA

//! Interface descriptor
#define INTF0			0x00
#define AUDIO			0x01
#define AUDIO_CONTROL	0x01
#define MIDI_STREAM		0x03

//! CS Interface descriptor
#define HEADER			0x01

//! defining Jacks
#define MIDI_IN_JACK	0x02
#define MIDI_OUT_JACK	0x03
#define MIDI_JACK_ENB	0x01
#define MIDI_JACK_EXT	0x02

#define MS_GENERAL		0x01
#define REFRESH			0x01

#define MIDI_CC_HEADER	0x0B
#define MIDI_CC_STATUS	0xB0

#define	MIDI_CC_ON		0x7F
#define	MIDI_CC_OFF		0x00

#define	MIDI_NT_ON		0x09
#define MIDI_NT_ON_S	0x90

#define MIDI_NT_OFF		0x08
#define MIDI_NT_OFF_S	0x80

#define MIDI_CC_MAX		0x7F
#define MIDI_CC_MIN		0x00
#define MIDI_CC_INITIAL	0x40

#define MIDI_VELOCITY	0x7F

//! Others

#endif /* INC_MIDI_NOTE_H_ */
