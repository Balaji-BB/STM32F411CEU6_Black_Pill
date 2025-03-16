/*
 * lcd_i2c.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Balaji
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_
#define LCD_SLAVE_ADDR						78U// DECIMAL - 39
/*
 * LCD Commands set
 * 01 - Clear Display
 * 02 - Return Home
 * 04 - Decrement Cursor mode
 * 06 - Increment Cursor mode
 * 05 - Shift Display Right
 * 07 - Shift Display Left
 * 10 - Shift Cursor Left
 * 14 - Shift Cursor Right
 * 08 - Display OFF, Cursor OFF
 * 0A - Display ON, Cursor OFF
 * OC - Display ON, Cursor OFF
 * OE - Display ON, Cursor Blink OFF
 * OF - Display ON, Cursor Blink ON
 */

/*
 * Set of LCD Commands as Macros
 */
#define LCD_CLEAR_DISP 						0x1
#define RETURN_HOME							0x2
#define CURSOR_MODE_DEC						0x4
#define CURSOR_MODE_INC						0x6
//SHIFT register
#define DISP_SHIFT_RIGHT					0X1C
#define DISP_SHIFT_LEFT						0X18
#define CURSOR_SHIFT_LEFT					0X10
#define CURSOR_SHIFT_RIGHT					0X14

/*
 * Macros for utilizing in data transmission to LCD
 */
#define BL_ENABLE							1<<3
#define COMMAND_MODE 						0
#define DATA_MODE 							1
#define EN_HIGH								1<<2
#define EN_LOW								0

uint8_t _I2C_SLAVE_ADDR_SCANNER(I2C_HandleTypeDef hi2c);
/*
 * LCD basic functions
 */
void LCD_Init(void);
void LCD_SEND_COMMAND(uint8_t cmd);
void LCD_SEND_DATA(uint8_t data);
void LCD_SEND_STRING(const char *str);
/*
 * LCD cursor positioning
 */
void LCD_SET_HOME_POSITION(void);
void LCD_SET_CURSOR(uint8_t row, uint8_t col);
/*
 * LCD cursor modes control
 */
void LCD_INCREMENT_CURSOR_MODE(void);
void LCD_DECREMENT_CURSOR_MODE(void);
void LCD_CURSOR_ON(void);
void LCD_CURSOR_OFF(void);
void LCD_CURSOR_BLINK_ON(void);
void LCD_CURSOR_BLINK_OFF(void);
/*
 * LCD cursor control - increment / decrement
 */
void LCD_INCREMENT_CURSOR(void);
void LCD_DECREMENT_CURSOR(void);
/*
 * LCD display control - Shift display to right / left
 */
void LCD_SHIFT_DISP_RIGHT(void);
void LCD_SHIFT_DISP_LEFT(void);
/*
 * LCD Scroll functions
 */
void LCD_SCROLL_RIGHT(void);
void LCD_SCROLL_LEFT(void);
void LCD_AUTO_SCROLL(void);
/*
 * LCD display clear functions
 */
void LCD_CLEAR_DISPLAY(void);
void LCD_CLEAR_ROW(uint8_t row);


#endif /* INC_LCD_I2C_H_ */
