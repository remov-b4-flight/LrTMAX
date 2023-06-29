#ifndef _USB_HID_H
#define _USB_HID_H

/**
 * @brief key definition structure.
 */
typedef struct key_define_t {
#if 0
	uint8_t	axis;
#endif
	uint8_t color;
	uint8_t period;
	char	*message;
} KEY_DEFINE;

#define RIGHTA	"\x7b"
#define LEFTA	"\x7c"
#define UPA		"\x7d"
#define DOWNA	"\x7e"

#define MASK_KEY	0x0000ffff
#define MASK_ENC	0xffff0000

#endif /*_USB_HID_H */
