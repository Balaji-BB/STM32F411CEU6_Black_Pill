/*
 * max7219_led_matrix.h
 *
 *  Created on: Mar 13, 2025
 *      Author: Balaji
 */

#ifndef INC_MAX7219_LED_MATRIX_H_
#define INC_MAX7219_LED_MATRIX_H_


void MAX7219_Init(void);
void MAX7219_Multi_Init(void);
void MAX7219_Write(uint8_t reg_addr, uint8_t reg_data);
void MAX7219_Multi_Write(uint8_t reg_addr, uint8_t* reg_data);
void MAX7219_Multi_Display(char *text);
void MAX7219_Scroll_Text(char *text, uint32_t speed);


#endif /* INC_MAX7219_LED_MATRIX_H_ */
