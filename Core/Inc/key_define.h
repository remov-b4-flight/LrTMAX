#ifndef _USB_HID_H
#define _USB_HID_H

/**
 * @brief Key define types whether SWITCH or ROTARY encoder
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
	uint8_t duration;
	char	*message;
} KEY_DEFINE;

//HID key codes HID 1.11

//Not pressed
#define HID_NONE    0x00
//Alphabet
#define HID_a   0x04
#define HID_b   0x05
#define HID_c   0x06
#define HID_d   0x07
#define HID_e   0x08
#define HID_f   0x09
#define HID_g   0x0A
#define HID_h   0x0B
#define HID_i   0x0C
#define HID_j   0x0D
#define HID_k   0x0E
#define HID_l   0x0F
#define HID_m   0x10
#define HID_n   0x11
#define HID_o   0x12
#define HID_p   0x13
#define HID_q   0x14
#define HID_r   0x15
#define HID_s   0x16
#define HID_t   0x17
#define HID_u   0x18
#define HID_v   0x19
#define HID_w   0x1A
#define HID_x   0x1B
#define HID_y   0x1C
#define HID_z   0x1D
//Numeric
#define HID_1   0x1E
#define HID_2   0x1F
#define HID_3   0x20
#define HID_4   0x21
#define HID_5   0x22
#define HID_6   0x23
#define HID_7   0x24
#define HID_8   0x25
#define HID_9   0x26
#define HID_0   0x27
//Control
#define HIDBS   0x2A
#define HIDTAB  0x2B
#define HID_MI  0x2D    //Minus '-'
#define HID_EQ  0x2E    //Equal '='
#define HID_AT  0x2F	//At '@'
#define HID_LA  0x36    //Left Allow '<'
#define HID_CM  0x36    //Comma ','
#define HID_RA  0x37    //Right Allow '>'
#define HID_DT  0x37    //Period '.'
#define HID_QS  0x38
#define HID_UA  0x2E    //Up Arrow '^'
#define HID_RB  0x2F    //Right brace ']'
#define HID_LB  0x30    //Left brace '['
#define HID_SL  0x38    //Slash '/'
//Cursor
#define HID_UP      0x52
#define HID_DOWN    0x51
#define HID_LEFT    0x50
#define HID_RIGHT   0x4F
//Function keys
#define HID_F01 0x3A
#define HID_F02 0x3B
#define HID_F03 0x3C
#define HID_F04 0x3D
#define HID_F05 0x3E
#define HID_F06 0x3F
#define HID_F07 0x40
#define HID_F08 0x41
#define HID_F09 0x42
#define HID_F10 0x43
#define HID_F11 0x44
#define HID_F12 0x45
//Misc.
#define HID_PGUP    0x4B
#define HID_PGDOWN  0x4E

//Modifier codes
#define HID_NONM 0x00
#define HID_GUIM 0x08
#define HID_ALTM 0x04
#define HID_SFTM 0x02
#define HID_CTLM 0x01

#endif /*_USB_HID_H */
