/*
 * tm1637_seg_display.h
 *
 *  Created on: Feb 19, 2025
 *      Author: Balaji
 */

#ifndef INC_TM1637_SEG_DISPLAY_H_
#define INC_TM1637_SEG_DISPLAY_H_

#include "main.h"

#define AUTO_INC_ADDR_NORMAL_WRITE_MODE			(uint8_t)0X40
#define FIX_ADDR_NORMAL_WRITE_MODE				(uint8_t)0x44
#define SRAM_ADDR_DIGIT0						(uint8_t)0XC0
#define SRAM_ADDR_DIGIT1						(uint8_t)0XC1
#define SRAM_ADDR_DIGIT2						(uint8_t)0XC2
#define SRAM_ADDR_DIGIT3						(uint8_t)0XC3
#define DISP_ON_PULSE_WIDTH_1					(uint8_t)0x88 //MINIMUM BRIGHTNNESS
#define DISP_ON_PULSE_WIDTH_2					(uint8_t)0x89
#define DISP_ON_PULSE_WIDTH_4					(uint8_t)0x8A
#define DISP_ON_PULSE_WIDTH_10					(uint8_t)0x8B
#define DISP_ON_PULSE_WIDTH_11					(uint8_t)0x8C
#define DISP_ON_PULSE_WIDTH_12					(uint8_t)0x8D
#define DISP_ON_PULSE_WIDTH_13					(uint8_t)0x8E
#define DISP_ON_PULSE_WIDTH_14					(uint8_t)0x8F //MAXIMUM BRIGHTNNESS

#define DISP_ON_PULSE_WIDTH_MIN					DISP_ON_PULSE_WIDTH_1
#define DISP_ON_PULSE_WIDTH_MAX					DISP_ON_PULSE_WIDTH_14


void TM1637_START(void);
void TM1637_STOP(void);
void TM1637_CHECKACK(void);
void Delay_us (int time);
void TM1637_WRITEBYTE(uint8_t byte);
void TM1637_WRITEDATA(uint8_t *data, uint8_t addr, uint8_t size);
void TM1637_CLK_DISP(uint8_t hours, uint8_t minutes);


#endif /* INC_TM1637_SEG_DISPLAY_H_ */
