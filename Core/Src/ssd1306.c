/**
 * @file	ssd1306.c
 * @brief	SSD1306 OLED Library Source.
 * @author	totally modified by remov-b4-flight
 * @copyright	MIT License
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 * @attention constants in this program is for 128*32 OLED module.
 */
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "ssd1306.h"

extern uint8_t Font8x16[];
extern uint8_t connect_bitmap[];

//! @brief string buffer to render for Frame_Buffer[].
char Msg_Buffer[MSG_LINES][MSG_WIDTH + 1];
//! @brief SSD1306 OLED frame buffer
static uint8_t Frame_Buffer[SSD1306_WIDTH * (MAX_PAGE+1)];

/**
 * @brief Write SSD1306 command register
 * @param cmd	:	command to write
 */
static inline void SSD1306_WriteCommand(uint8_t cmd) {
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, SSD1306_CMD, 1, &cmd, 1, HAL_MAX_DELAY);
}

#if !(SSD1306_USE_DMA)
/**
 * @brief Write SSD1306 data register
 * @param buffer	:	pointer to data buffer
 * @param buff_size	:	write size
 */
static inline void SSD1306_WriteData(uint8_t* buffer, size_t buff_size) {
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, SSD1306_DATA, 1, buffer, buff_size, HAL_MAX_DELAY);
}
#endif

/**
 * @brief Initialize SSD1306 OLED module
 */
void SSD1306_Initialize(void) {

    SSD1306_WriteCommand(CMD_DISPLAY_OFF); 		// Display off

    SSD1306_WriteCommand(CMD_SET_ADDRESS_MD); 	// Set Memory Addressing Mode
    SSD1306_WriteCommand(VAL_HORIZON_ADDRSS);	// Horizontal paging mode

    SSD1306_WriteCommand(CMD_SET_PAGE_RANGE);	// Set page range
    SSD1306_WriteCommand(VAL_START_PAGE);		// Start page
    SSD1306_WriteCommand(VAL_END_PAGE_32L);		// End page

#ifdef SSD1306_MIRROR_VERT
    SSD1306_WriteCommand(CMD_SET_NON_VMIRROR);	// Mirror vertically
#else
    SSD1306_WriteCommand(CMD_SET_VMIRROR);		// Set COM Output Scan Direction
#endif

    SSD1306_WriteCommand(CMD_SET_START_LINE);	// Set start line address

    SSD1306_WriteCommand(CMD_SET_CONTRAST);		// Set contrast control register
    SSD1306_WriteCommand(VAL_CONTRAST_MAX);

#ifdef SSD1306_MIRROR_HORIZ
    SSD1306_WriteCommand(CMD_NON_MIRROR);		// Mirror horizontally
#else
    SSD1306_WriteCommand(CMD_MIRROR);			// Set segment re-map 0 to 127 - CHECK
#endif

    SSD1306_WriteCommand(CMD_NON_INVERT);		// Set white dot/black back

    SSD1306_WriteCommand(CMD_SET_MPX_RATIO);	// Set multiplex ratio(1 to 64)
    SSD1306_WriteCommand(VAL_MPX_RATIO_32L);

    SSD1306_WriteCommand(CMD_REFLECT_FBUF);

    SSD1306_WriteCommand(CMD_SET_VOFFSET);		// Set display offset
    SSD1306_WriteCommand(VAL_VOFFSET_NONE);		// No offset

    SSD1306_WriteCommand(CMD_SET_OSCDIV); 		// Set display clock divide ratio/oscillator frequency
    SSD1306_WriteCommand(VAL_OSC_FREQ_MAX);

    SSD1306_WriteCommand(CMD_SET_PRECHARGE);	// Set pre-charge period
    SSD1306_WriteCommand(VAL_PRECHG_DEFAULT);

    SSD1306_WriteCommand(CMD_SET_COMCONFIG);	// Set com pins hardware configuration
    SSD1306_WriteCommand(VAL_COM_CONFIG_32L);

    SSD1306_WriteCommand(CMD_SET_VCOMH);		// Set vcomh
    SSD1306_WriteCommand(VAL_VCOMH_DEFAULT);	// 0x20,0.77xVcc

    SSD1306_WriteCommand(CMD_SET_CHARGE_PUMP);	// Set DC-DC enable
    SSD1306_WriteCommand(VAL_CHG_PUMP_ENABLE);
    HAL_Delay(1);
    SSD1306_WriteCommand(CMD_DISPLAY_ON);		// Turn on SSD1306 panel

    // Clear frame buffer
    SSD1306_ClearBuffer();

    // Flush screen with frame buffer
    SSD1306_FlashScreen();
}

/**
 * @brief Clear all of frame buffer
 */
void SSD1306_ClearBuffer() {
    memset(Frame_Buffer,SCREEN_BLANK,sizeof(Frame_Buffer));
}

/**
 * @brief Update SSD1306 OLED screen with frame buffer
 */
bool SSD1306_FlashScreen(void) {
#if SSD1306_USE_DMA
	if (HAL_I2C_GetState(&SSD1306_I2C_PORT) != HAL_I2C_STATE_READY) {
		return false;
	}
	if ( HAL_I2C_Mem_Write_DMA(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, SSD1306_DATA, 1, Frame_Buffer, FB_SIZE) != HAL_OK){
		return false;
	}
	return true;
#else
    SSD1306_WriteData(Frame_Buffer, FB_SIZE);
    return true;
#endif
}

/**
 * @brief Set screen on/off
 * @param on	true = Set display ON, false = Set display off
 */
void SSD1306_SetScreen(bool on){
    SSD1306_WriteCommand( (on)? CMD_DISPLAY_ON : CMD_DISPLAY_OFF );
}
/**
 * @brief Render Msg_Buffer contents to frame buffer
 * @pre Sets up string contents to Msg_Buffer
 */
void SSD1306_Render2Buffer(void){
	for (uint8_t line = 0; line < MSG_LINES; line ++){
		bool isZerofill = false;
		for (uint8_t column = 0; column < MSG_WIDTH; column++){
			char ch = Msg_Buffer[line][column];
			if (ch == '\0') {
				isZerofill = true;	//indicates zero fill until end of line.
			}

			uint8_t cindex = ch - FONT_PRINTABLE_START;
			uint16_t fb_top = (column * FONT_WIDTH) + (line * SSD1306_WIDTH * 2);
			uint16_t font_top = (cindex * BYTES_PER_CHAR_DATA);

			for (uint8_t c = 0; c < FONT_WIDTH; c++){
				Frame_Buffer[fb_top + c ] = (isZerofill)? 0x00 : Font8x16[font_top + c];
				Frame_Buffer[fb_top + c + SSD1306_WIDTH] = (isZerofill)? 0x00 : Font8x16[font_top + c + FONT_WIDTH];
			}//Frame Buffer column Loop
		}//Msg_Buffer column Loop
	}//Msg_Buffer line Loop
}
#ifndef DEBUG
/**
 * @brief Rendar banner message to frame buffer
 * @param string	Message to screen
 * @param x		x coordinate to render
 * @param y		y coordinate to render
 * @param op	operator with frame buffer contents
 */
void SSD1306_RenderBanner(char *string, int x, int y ,uint8_t op){
	uint8_t	page = y / BITS_PER_PAGE;
	if (page >= MAX_PAGE) {
		page = MAX_PAGE;
	}
	int len = strlen(string);
	if ( ((len * FONT_WIDTH) + x) > (SSD1306_WIDTH-1) ){
		x = SSD1306_WIDTH - (FONT_WIDTH * len);
		if (x < 0) {
			x = 0;
		}
	}
	for (uint8_t i = 0; (string[i] != '\0' && i < MSG_WIDTH); i++){
		uint8_t ch_index = string[i] - FONT_PRINTABLE_START;
		uint16_t fb_top = (page * SSD1306_WIDTH) + x ;
		uint16_t font_top = (ch_index * BYTES_PER_CHAR_DATA);
		for (uint8_t column = 0; column < FONT_WIDTH; column++){
			uint8_t font_h = Font8x16[font_top + column];
			uint8_t font_l = Font8x16[font_top + column + FONT_WIDTH];
			uint16_t fb_index = fb_top + (i * FONT_WIDTH) + column;
#if 0
			if (op == INP){
#endif
				Frame_Buffer[fb_index] = font_h;
				Frame_Buffer[fb_index + SSD1306_WIDTH] = font_l;
#if 0
			} else if (op == XOR){
				Frame_Buffer[fb_index ] ^= font_h;
				Frame_Buffer[fb_index + SSD1306_WIDTH] ^= font_l;
			}
#endif
		}//Frame Buffer column Loop
	}//String Loop
}
/**
 * @brief Load bitmap image to frame buffer
 * @param bitmap SSD1306 style bitmap 8bit array.
 */
void SSD1306_LoadBitmap(){
	memcpy(Frame_Buffer,connect_bitmap,FB_SIZE);
}
#endif
