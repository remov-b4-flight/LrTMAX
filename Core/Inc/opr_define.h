/**
 * @file		opr_define.h
 * @brief		definitions for opr_define.c
 * @author		remov-b4-flight
 * @copyright	3-Clause BSD License
 */
#ifndef _PROF_DEFINE_H
#define _PROF_DEFINE_H
#include <stdint.h>

/**
 * @brief prof. definition structure.
 */
typedef struct enc_sw_define_t {
	uint8_t	axis;	//! < axis to light
	uint8_t color;	//! < color to light
	uint8_t period;	//! < light period
} PROF_DEFINE;

//! Bit mask pattern for Encoder push
#define MASK_ENCPUSH	0xff00
//! Bit position for 1st encoder
#define PROF_ENC1ST		16

#endif /* _PROF_DEFINE_H */
