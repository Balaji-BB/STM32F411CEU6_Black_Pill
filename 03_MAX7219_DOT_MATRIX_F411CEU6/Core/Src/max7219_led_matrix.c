/*
 * max7219_led_matrix.c
 *
 *  Created on: Mar 13, 2025
 *      Author: Balaji
 */

#include "main.h"
#include "max7219_led_matrix.h"
#include "stdlib.h"
#include "string.h"

#define MAX7219_DEVICES_CNT					(uint8_t)0x4
/*
 * INITIALISATION REGISTER ADDRESS MACROS
 */
#define DECODE_MODE_REG						(uint8_t)0x9
#define INTENSITY_REG						(uint8_t)0xA
#define SCAN_LIMIT_REG						(uint8_t)0xB
#define SHUTDOWN_REG						(uint8_t)0xC
#define DISPLAY_TEST_REG					(uint8_t)0xF


#define INTENSITY_1_IN_32					(uint8_t)0X0 //Minimum possible intensity
#define INTENSITY_3_IN_32					(uint8_t)0X1
#define INTENSITY_5_IN_32					(uint8_t)0X2
#define INTENSITY_7_IN_32					(uint8_t)0X3
#define INTENSITY_9_IN_32					(uint8_t)0X4
#define INTENSITY_11_IN_32					(uint8_t)0X5
#define INTENSITY_13_IN_32					(uint8_t)0X6
#define INTENSITY_15_IN_32					(uint8_t)0X7
#define INTENSITY_17_IN_32					(uint8_t)0X8
#define INTENSITY_19_IN_32					(uint8_t)0X9
#define INTENSITY_21_IN_32					(uint8_t)0XA
#define INTENSITY_23_IN_32					(uint8_t)0XB
#define INTENSITY_25_IN_32					(uint8_t)0XC
#define INTENSITY_27_IN_32					(uint8_t)0XD
#define INTENSITY_29_IN_32					(uint8_t)0XE
#define INTENSITY_31_IN_32					(uint8_t)0XF // Maximum possible intensity

#define SCAN_LIMIT_ALL_DIGITS				(uint8_t)0x7

#define SHUTDOWN_ENABLE						0
#define SHUTDOWN_DISABLE					1 //Normal Operation

extern SPI_HandleTypeDef hspi1;
const uint8_t font[27][8] = {
		{0x18, 0x24, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00}, // A
		{0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00}, // B
		{0x3C, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00}, // C
		{0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00}, // D
		{0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00}, // E
		{0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00}, // F
		{0x3C, 0x42, 0x40, 0x4E, 0x42, 0x42, 0x3C, 0x00}, // G
		{0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00}, // H
		{0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // I
		{0x0E, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00}, // J
		{0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0x00}, // K
		{0x40, 0x40, 0x40, 0x40, 0x40, 0x42, 0x7E, 0x00}, // L
		{0x42, 0x66, 0x5A, 0x5A, 0x42, 0x42, 0x42, 0x00}, // M
		{0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x00}, // N
		{0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00}, // O
		{0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0x00}, // P
		{0x3C, 0x42, 0x42, 0x42, 0x46, 0x42, 0x3D, 0x00}, // Q
		{0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00}, // R
		{0x3C, 0x42, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00}, // S
		{0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // T
		{0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00}, // U
		{0x42, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18, 0x00}, // V
		{0x42, 0x42, 0x42, 0x5A, 0x5A, 0x24, 0x24, 0x00}, // W
		{0x42, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00}, // X
		{0x42, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, 0x00}, // Y
		{0x7E, 0x04, 0x08, 0x18, 0x30, 0x40, 0x7E, 0x00},  // Z
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // space
};

void MAX7219_Init(void)
{
	MAX7219_Write(DECODE_MODE_REG, 0); //No BCD Decoding
//	MAX7219_Write(INTENSITY_REG, INTENSITY_15_IN_32);
	MAX7219_Write(INTENSITY_REG, INTENSITY_3_IN_32);
	MAX7219_Write(SCAN_LIMIT_REG, SCAN_LIMIT_ALL_DIGITS); //Display all digits
	MAX7219_Write(SHUTDOWN_REG, SHUTDOWN_DISABLE); //Noraml Operation
	MAX7219_Write(DISPLAY_TEST_REG, 0); //Noraml Operation - No test mode
	for(int i=1; i<=8; i++)
	{
		MAX7219_Write(i,i);
	}
}
void MAX7219_Multi_Init(void)
{
	MAX7219_Write(DECODE_MODE_REG, 0); //No BCD Decoding
	MAX7219_Write(INTENSITY_REG, INTENSITY_15_IN_32);
	MAX7219_Write(SCAN_LIMIT_REG, SCAN_LIMIT_ALL_DIGITS); //Display all digits
	MAX7219_Write(SHUTDOWN_REG, SHUTDOWN_DISABLE); //Noraml Operation
	MAX7219_Write(DISPLAY_TEST_REG, 0); //Noraml Operation - No test mode
	for(int i=1; i<=8; i++)
	{
		MAX7219_Write(i,i);
	}
}

void MAX7219_Write(uint8_t reg_addr, uint8_t reg_data)
{
	uint16_t SPI_DATA = (reg_addr<<8) | reg_data;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&SPI_DATA, 1, 100);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);
}
void MAX7219_Multi_Write(uint8_t reg_addr, uint8_t* reg_data)
{
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, RESET);
	for(int i=0; i<MAX7219_DEVICES_CNT; i++)
	{
		uint16_t SPI_DATA = (reg_addr<<8) | reg_data[i];
		HAL_SPI_Transmit(&hspi1, (uint8_t*)&SPI_DATA, 1, 100);
	}
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);
}
void MAX7219_Multi_Display(char *text)
{
	uint8_t MAX7219_data[MAX7219_DEVICES_CNT][8] = {0};
	for(uint8_t i = 0; (i<MAX7219_DEVICES_CNT) && (text[i] != '\0'); i++)
	{
		uint8_t ind = 0;
		if(text[i] == 32)
		{
			ind = 26;
		}
		else
		{
			ind = text[i] - 'A';
		}
		for(uint8_t j = 0; j<7; j++)
		{
			MAX7219_data[i][j] = font[ind][j];
		}
	}

	for(uint8_t row=0; row<8; row++)
	{
		uint8_t MAX7219_Rowdata[MAX7219_DEVICES_CNT];
		{
			for(uint8_t module = 0; module<MAX7219_DEVICES_CNT; module++)
			{
				MAX7219_Rowdata[module]=MAX7219_data[module][row];
			}
		}
		MAX7219_Multi_Write(row+1,(uint8_t *) &MAX7219_Rowdata);
	}
}
void MAX7219_Scroll_Text(char *text, uint32_t speed)
{
	uint32_t length = strlen(text);
	//	uint8_t MAX7219_data[19+4][8] = {0}; // static size allocation
	uint8_t **MAX7219_data;
	MAX7219_data = (uint8_t**)malloc(sizeof(uint8_t*)*(length+4));
	for(int i =0;i<(length+4); i++)
	{
		MAX7219_data[i] = (uint8_t*)malloc(sizeof(uint8_t)*8);
	}
	for(uint8_t i = 0; (i<length) && (text[i] != '\0'); i++)
	{
		uint8_t ind = 0;
		if(text[i] == 32)
		{
			ind = 26;
		}
		else
		{
			ind = text[i] - 'A';
		}
		for(uint8_t j = 0; j<=7; j++)
		{
			MAX7219_data[i][j] = font[ind][j];
		}
	}
	for(uint8_t i = length; (i<length+4) ; i++)
	{
		uint8_t ind = 26;
		for(uint8_t j = 0; j<=7; j++)
		{
			MAX7219_data[i][j] = font[ind][j];
		}
	}
	//	for(uint8_t shift = 0, shift_sub = 0; shift<(8*(MAX7219_DEVICES_CNT+1));shift++,shift_sub++)
	for(uint32_t shift = 0, shift_sub = 0; shift<(8*(length));shift++,shift_sub++)
	{
		uint8_t module_sub = 0;
		uint8_t quot = shift/8;
		uint8_t rem = shift%8;
		if((quot==0) &&(rem==shift))
		{
			module_sub = 0;
			shift_sub = shift;
		}
		else if(rem==0)
		{
			module_sub = quot-1;
			shift_sub = 8;
		}
		else
		{
			module_sub = quot;
			shift_sub = rem;
		}

		uint8_t MAX7219_Rowdata[MAX7219_DEVICES_CNT];
		for(uint8_t row=0; row<8; row++)
		{
			for(uint8_t module = 0; module<(MAX7219_DEVICES_CNT); module++)
			{
				MAX7219_Rowdata[module]=(MAX7219_data[module_sub+module][row]<<shift_sub) | (MAX7219_data[module_sub+module+1][row]>>(8-shift_sub));
			}
			MAX7219_Multi_Write(row+1,(uint8_t *) &MAX7219_Rowdata);
		}
		HAL_Delay(speed);
	}
	for(int i =0;i<length; i++)
	{
		free(MAX7219_data[i]);
	}
	free(MAX7219_data);
}
