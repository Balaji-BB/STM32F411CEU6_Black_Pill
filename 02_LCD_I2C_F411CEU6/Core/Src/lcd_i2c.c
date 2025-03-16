/*
 * lcd_i2c.c
 *
 *  Created on: Feb 18, 2025
 *      Author: Balaji
 */



/* I2C LCD MODULE PIN CONNECTIONS
 * RS - P0
 * RW - P1
 * E - P2
 * D0 - P3
 * D1 -
 * D2 -
 * D3 -
 * D4 - P4
 * D5 - P5
 * D6 - P6
 * D7 - P7
 *
 * P7 P6 P5.....P0 DATA FRAME STRUCTURE
 */


/* 16X2 LCD NOTES
 *  RS = 0 -> COMMAND
 *  RS = 1 -> DATA
 *  RW = 0 -> WRITE MODE
 *  RW = 1 -> READ MODE // MOSTLY NOT USED READ MODE
 *  E - HIGH TO LOW FOR DATA TRANSMISSION
 */

#include "main.h"
#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;


#define LCD_CLEAR_DISP 						0x1

//SHIFT register
#define DISP_SHIFT_RIGHT					0X1C
#define DISP_SHIFT_LEFT						0X18
#define CURSOR_SHIFT_LEFT					0X10
#define CURSOR_SHIFT_RIGHT					0X14

#define BL_ENABLE 1<<3
#define COMMAND_MODE 0
#define DATA_MODE 1
#define EN_HIGH		1<<2
#define EN_LOW		0
uint8_t _LCD_SLAVE_ID = 0;

uint8_t _I2C_SLAVE_ADDR_SCANNER(I2C_HandleTypeDef hi2c)
{
	uint8_t slave_id = 1;
	while(slave_id!=0)
	{
		if(HAL_I2C_IsDeviceReady(&hi2c1, slave_id, 1, 100)== 0)
		{
			_LCD_SLAVE_ID = slave_id;
			break;
		}
		slave_id++;
	}
	return slave_id;
}



void LCD_Init(void)
{

//	_I2C_SLAVE_ADDR_CHECK(LCD_SLAVE_ADDR);
	HAL_Delay(50); //50ms Delay waiting after powering up
	LCD_SEND_COMMAND(0x30); // Function set - 8 Bit Length Interface mode
	HAL_Delay(5);
	LCD_SEND_COMMAND(0x30);
	HAL_Delay(5);
	LCD_SEND_COMMAND(0x30);
	HAL_Delay(1);
	LCD_SEND_COMMAND(0x20); // Function set - 4 Bit Length Interface mode
	HAL_Delay(1);

	LCD_SEND_COMMAND(0x28);
	// Function set - 4 Bit Length, No. of Display lines/rows - 2, Font - 5x7 mode
	HAL_Delay(1);
	LCD_SEND_COMMAND(0x08); // Display OFF
	HAL_Delay(1);
	LCD_SEND_COMMAND(0x01); // Display clear
	HAL_Delay(2);
	LCD_SEND_COMMAND(0x06);
	// Entry mode set, Increment cursor - ON, Shift Cursor - OFF
	HAL_Delay(2);
	LCD_SEND_COMMAND(0x0F); // Display ON, Cursor ON, Blink ON
	HAL_Delay(2);
}

void LCD_SEND_COMMAND(uint8_t cmd)
{
	uint8_t upper_nibble = cmd & 0xF0;
	uint8_t lower_nibble = (cmd<<4)&0xF0;
	uint8_t data[4] = {0};
	data[0] = (upper_nibble | BL_ENABLE | COMMAND_MODE | EN_HIGH);
	data[1] = (upper_nibble | BL_ENABLE | COMMAND_MODE | EN_LOW);
	data[2] = (lower_nibble | BL_ENABLE | COMMAND_MODE | EN_HIGH);
	data[3] = (lower_nibble | BL_ENABLE | COMMAND_MODE | EN_LOW);
	uint8_t err = HAL_I2C_Master_Transmit(&hi2c1, LCD_SLAVE_ADDR, (uint8_t *)&data, 4, 100);

	if(err)
	{
		__NOP();
	}
	else
	{
		__NOP();
	}
}

void LCD_SEND_DATA(uint8_t data)
{
	uint8_t upper_nibble = data & 0xF0;
	uint8_t lower_nibble = (data<<4)&0xF0;
	uint8_t data_d[4] = {0};
	data_d[0] = (upper_nibble | BL_ENABLE | DATA_MODE | EN_HIGH);
	data_d[1] = (upper_nibble | BL_ENABLE | DATA_MODE | EN_LOW);
	data_d[2] = (lower_nibble | BL_ENABLE | DATA_MODE | EN_HIGH);
	data_d[3] = (lower_nibble | BL_ENABLE | DATA_MODE | EN_LOW);
	uint8_t err = HAL_I2C_Master_Transmit(&hi2c1, LCD_SLAVE_ADDR, (uint8_t *)&data_d, 4, 100);

	if(err)
	{
		__NOP();
	}
	else
	{
		__NOP();
	}
}


void LCD_SEND_STRING(const char *str)
{
	while(*str != '\0')
	{
		LCD_SEND_DATA(*str);
		HAL_Delay(100);
		str++;
	}

}
void LCD_SET_HOME_POSITION(void)
{
	LCD_SET_CURSOR(1, 1);
}
void LCD_SET_CURSOR(uint8_t row, uint8_t col)
{
	uint8_t pos = 0;
	col = col-1;
	switch(row)
	{
	case 1:
		pos = 0x80 | col;
		break;
	case 2:
		pos = 0xC0 | col;
		break;
	default:
		__NOP();
		break;
	}
	LCD_SEND_COMMAND(pos);
}
void LCD_CLEAR_DISPLAY(void)
{
	LCD_SEND_COMMAND(LCD_CLEAR_DISP);
	HAL_Delay(2);
}

void LCD_DECREMENT_CURSOR_MODE(void)
{
	LCD_SEND_COMMAND(CURSOR_MODE_DEC);
}
void LCD_INCREMENT_CURSOR_MODE(void)
{
	LCD_SEND_COMMAND(CURSOR_MODE_INC);
}


void LCD_CURSOR_ON(void)
{
	LCD_SEND_COMMAND(0xE);
}
void LCD_CURSOR_OFF(void)
{
	LCD_SEND_COMMAND(0xC);  // Display ON, Cursor OFF
}
void LCD_CURSOR_BLINK_ON(void)
{
	LCD_SEND_COMMAND(0xF);
}
void LCD_CURSOR_BLINK_OFF(void)
{
	LCD_SEND_COMMAND(0xE);
}
void LCD_INCREMENT_CURSOR(void)
{
	LCD_SEND_COMMAND(CURSOR_SHIFT_RIGHT); // Move Cursor to Right
}
void LCD_DECREMENT_CURSOR(void)
{
	LCD_SEND_COMMAND(CURSOR_SHIFT_LEFT); // Move Cursor to Left
}
void LCD_SHIFT_DISP_RIGHT(void)
{
	LCD_SEND_COMMAND(DISP_SHIFT_RIGHT); // Shift Entire Display to Right
}
void LCD_SHIFT_DISP_LEFT(void)
{
	LCD_SEND_COMMAND(DISP_SHIFT_LEFT); // Shift Entire Display to LEFT
}
void LCD_SCROLL_RIGHT(void)
{
	LCD_SEND_COMMAND(DISP_SHIFT_RIGHT);
}
void LCD_SCROLL_LEFT(void)
{
	LCD_SEND_COMMAND(DISP_SHIFT_LEFT);
}
void LCD_AUTO_SCROLL(void)
{
	uint8_t col = 1;
	while(col<16)
	{
		LCD_SEND_COMMAND(DISP_SHIFT_RIGHT);
		col++;
		HAL_Delay(1000);
	}
	while(col!=1)
	{
		LCD_SEND_COMMAND(DISP_SHIFT_LEFT);
		HAL_Delay(1000);
		col--;
	}
}

void LCD_CLEAR_ROW(uint8_t row)
{
	LCD_SET_CURSOR(row, 1);
//	LCD_SEND_STRING("                ");
	uint8_t ind = 1;
	while(ind <= 16)
	{
		LCD_SEND_DATA(' ');
		ind++;
	}
}

