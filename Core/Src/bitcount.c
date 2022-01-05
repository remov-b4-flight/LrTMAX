/**
 *	@file	bitcount.c
 *	@brief 'bit count' functions
 *	@author	remov-b4-flight
 *	@copyright	3-Clause BSD Licence
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "bitcount.h"

/* User code -----------------------------------------------------------------*/
/**
 * @brief	count number of bits is '1'
 * @param 	b8	number to count bits
 * @return	count of bit '1'
 */
uint8_t bitcount8(uint8_t b8){
	uint8_t count = ( ((b8 & 0xAA) >> 1) + (b8 & 0x55) );
	count = ( ((count & 0xCC) >> 2) + (count & 0x33) );
	return ( ((count & 0xF0) >> 4) + (count & 0x0F) );
}

/**
 * @brief	count number of bits is '1'
 * @param 	b16	number to count bits
 * @return	count of bit '1'
 */
uint8_t bitcount16(uint16_t b16) {
    uint16_t count = (b16 & 0x5555) + ((b16 >> 1) & 0x5555);
    count = (count & 0x3333) + ((count >> 2) & 0x3333);
    count = (count & 0x0f0f) + ((count >> 4) & 0x0f0f);
    return (count & 0x00ff) + ((count >> 8) & 0x00ff);
}

/**
 * @brief	count number of bits is '1'
 * @param 	b32	number to count bits
 * @return	count of bit '1'
 */
int bitcount32(uint32_t b32)
{
    uint32_t count = (b32 & 0x55555555) + (b32 >> 1 & 0x55555555);
    count = (count & 0x33333333) + (count >> 2 & 0x33333333);
    count = (count & 0x0f0f0f0f) + (count >> 4 & 0x0f0f0f0f);
    count = (count & 0x00ff00ff) + (count >> 8 & 0x00ff00ff);
    return (count & 0x0000ffff) + (count >>16 & 0x0000ffff);
}

/**
 *	@brief	compute first bit position bit is '1'
 *	@param 	v	number to computes
 *	@return	bit number (0-15)
 */
uint8_t ntz16(uint16_t v){
    uint16_t w = (v & (-v)) - 1;
    return bitcount16(w);
}

/**
 *	@brief	figures first bit position bit is '1'
 *	@param	v	number to computes
 *	@return	bit number (0-31)
 */
uint8_t ntz32(uint32_t v){
    uint32_t w = (v & (-v)) - 1;
    return bitcount32(w);
}     
/* ******************************************************* **** END OF FILE****/
