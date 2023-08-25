/**
 * @file		prof_define.h
 * @brief		definitions for prof_define.c
 * @author		remov-b4-flight
 * @copyright	3-Clause BSD License
 */
#ifndef _PROF_DEFINE_H
#define _PROF_DEFINE_H
#include <stdint.h>

/**
 * @brief prof definition structure.
 */
typedef struct enc_sw_define_t {
	uint8_t	axis;
	uint8_t color;
	uint8_t period;
} PROF_DEFINE;

#define MASK_ENCPUSH	0xff00
#define PROF_ENC1ST		16

#endif /* _PROF_DEFINE_H */
