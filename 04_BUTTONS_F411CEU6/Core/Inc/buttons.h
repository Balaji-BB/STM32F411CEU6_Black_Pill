/*
 * buttons.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Balaji
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "main.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void Buttons_Init(void);
void Button_Debouncing(void);

#endif /* INC_BUTTONS_H_ */
