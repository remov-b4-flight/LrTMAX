/**
 * @file	bitcount.h
 * @brief	header file for 'bit count' functions.
 * @author	remov-b4-flight
 * @copyright	3-Clause BSD License
 */

#ifndef BITCOUNT_H
#define	BITCOUNT_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
uint8_t bitcount8(uint8_t b8);
uint8_t bitcount16(uint16_t b16);
uint8_t ntz16(uint16_t v);
uint8_t ntz32(uint32_t v);

#ifdef	__cplusplus
}
#endif

#endif	/* BITCOUNT_H */
