#ifndef _USB_HID_H
#define _USB_HID_H

/**
 * @brief Key define types whether SWITCH or rotary ENCODER
 */
enum define_type_t {
	TYPE_SWITCH = 0,//!< TYPE_SWITCH
	TYPE_ROTARY = 1,//!< TYPE_ROTARY
};

/**
 * @brief define key definiton structure.
 */
typedef struct key_define_t {
	uint8_t	type;
	uint8_t	axis;
	uint8_t color;
	uint8_t period;
	char	*message;
} KEY_DEFINE;

#define RIGHTA	"\x7b"
#define LEFTA	"\x7c"
#define UPA		"\x7d"
#define DOWNA	"\x7e"

#endif /*_USB_HID_H */
