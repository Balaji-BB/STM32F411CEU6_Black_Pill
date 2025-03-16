/*
 * tm1637_seg_display.c
 *
 *  Created on: Feb 19, 2025
 *      Author: Balaji
 */


#include "tm1637_seg_display.h"

uint8_t TM1637_DIGIT_DATA[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X7, 0X7F, 0X67};
uint8_t TM1637_SEGMENT_DATA[4];

void TM1637_START(void)
{
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, SET);
	HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, RESET);
	Delay_us(2);// delay in 2uS
	HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, SET);
}
void TM1637_STOP(void)
{
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, RESET);
	Delay_us(2);// delay in 2uS
	HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, RESET);
	Delay_us(2);// delay in 2uS
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, SET);
	Delay_us(2);// delay in 2uS
	HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, SET);
}
void TM1637_CHECKACK(void)
{
	//CLK pin LOW before getting ACK
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, RESET);
	Delay_us(2);// delay in 5uS (larger delay than usual)
	// check dio pin is reset - Left out
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, SET);
	Delay_us(2);// delay in 2uS
	HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, RESET);
}
void Delay_us (int time)
{
	for (int i=0; i<time; i++)
	{
		for (int j=0; j<7; j++)
		{
			__asm__("nop");
		}
	}
}
void TM1637_WRITEBYTE(uint8_t byte)
{
	// Only when clock is low, data has to be sent over DIO pin
	for(int i=0; i<8; i++)
	{
		//CLK pin LOW before sending data
		HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, RESET);
		if((byte>>i) & (0x1)) //Check whether bit is set or reset
		{
			HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, SET);
		}
		else
		{
			HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, RESET);
		}
		Delay_us(3);// delay in 3uS
		//CLK pin HIGH after sending data
		HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, SET);
		Delay_us(3);// delay in 3uS
	}
}
void TM1637_WRITEDATA(uint8_t *data, uint8_t addr, uint8_t size)
{
	TM1637_START();
//	TM1637_WRITEBYTE(AUTO_INC_ADDR_NORMAL_WRITE_MODE); //COMMAND1 - SET DATA
	TM1637_WRITEBYTE(FIX_ADDR_NORMAL_WRITE_MODE); //COMMAND1 - SET DATA
	TM1637_CHECKACK();
	TM1637_STOP();
	TM1637_START();
	TM1637_WRITEBYTE(addr); //COMMAND2 - SET ADDRESS
	TM1637_CHECKACK();
	for(int i=0; i<size; i++)
	{
		TM1637_WRITEBYTE(data[i]); //DATA1...DATAn - DISPLAY DATA TRANSMISSION
		TM1637_CHECKACK();
	}
	TM1637_STOP();
	TM1637_START();
	TM1637_WRITEBYTE(DISP_ON_PULSE_WIDTH_MAX); //COMMAND2 - CONTROL DISPLAY
	TM1637_CHECKACK();
	TM1637_STOP();
}

void TM1637_CLK_DISP(uint8_t hours, uint8_t minutes)
{
	  TM1637_SEGMENT_DATA[0] = TM1637_DIGIT_DATA[hours/10];
	  TM1637_SEGMENT_DATA[1] = TM1637_DIGIT_DATA[hours%10] | 0x80; // For enabling colon in display
	  TM1637_SEGMENT_DATA[2] = TM1637_DIGIT_DATA[minutes/10];
	  TM1637_SEGMENT_DATA[3] = TM1637_DIGIT_DATA[minutes%10];
	  TM1637_WRITEDATA((uint8_t *)&TM1637_SEGMENT_DATA[0], SRAM_ADDR_DIGIT0, 1);
	  TM1637_WRITEDATA((uint8_t *)&TM1637_SEGMENT_DATA[1], SRAM_ADDR_DIGIT1, 1);
	  TM1637_WRITEDATA((uint8_t *)&TM1637_SEGMENT_DATA[2], SRAM_ADDR_DIGIT2, 1);
	  TM1637_WRITEDATA((uint8_t *)&TM1637_SEGMENT_DATA[3], SRAM_ADDR_DIGIT3, 1);
}
