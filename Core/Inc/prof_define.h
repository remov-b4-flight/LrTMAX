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

#define RIGHTA	"\x7b"
#define LEFTA	"\x7c"
#define UPA		"\x7d"
#define DOWNA	"\x7e"

#define MASK_ENC_SW		0x0000ffff
#define MASK_ENC		0xffff0000
#define MASK_ENCPUSH	0x0000ff00

#endif /* _PROF_DEFINE_H */
