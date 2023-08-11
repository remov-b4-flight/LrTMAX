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

#define MASK_ENCPUSH	0xff00
#define PROF_ENC1ST		16

#endif /* _PROF_DEFINE_H */
