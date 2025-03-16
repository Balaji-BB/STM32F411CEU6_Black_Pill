/*
 * buttons.c
 *
 *  Created on: Feb 18, 2025
 *      Author: Balaji
 */


#include "main.h"
#include "buttons.h"
#include"stdbool.h"

#define DEBUG_BUTTONS			1
#define DEBOUNCE_DELAY		(uint32_t)250U

#ifdef	DEBUG_BUTTONS
			uint8_t BUTTONS[5];
#endif

typedef enum
{
	LEFT,RIGHT,CENTER,UP,DOWN
}ButtonsTypedef_enum;
typedef struct
{
	bool pressed;
	uint32_t current_time;
	uint32_t last_interrupt_time;
	uint32_t count;
}ButtonTypedef_struct;

volatile ButtonTypedef_struct Button_Struct[5];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == CENTER_BTN_Pin)
	{
		Button_Struct[CENTER].pressed = true;
	}
	if(GPIO_Pin == RIGHT_BTN_Pin)
	{
		Button_Struct[RIGHT].pressed = true;
	}
	if(GPIO_Pin == LEFT_BTN_Pin)
	{
		Button_Struct[LEFT].pressed = true;
	}
	if(GPIO_Pin == UP_BTN_Pin)
	{
		Button_Struct[UP].pressed = true;
	}
	if(GPIO_Pin == DOWN_BTN_Pin)
	{
		Button_Struct[DOWN].pressed = true;
	}
}
void Buttons_Init(void)
{
	for(int ind = LEFT; ind<=DOWN; ind++)
	{
		Button_Struct[ind].pressed = false;
		Button_Struct[ind].current_time = 0;
		Button_Struct[ind].last_interrupt_time = 0;
		Button_Struct[ind].count = 0;
	}
}
void Button_Debouncing(void)
{
	for(int ind = LEFT; ind<=DOWN; ind++)
	{
	if(Button_Struct[ind].pressed == true)
	{
		Button_Struct[ind].pressed = false;
		Button_Struct[ind].current_time = HAL_GetTick();
		if((Button_Struct[ind].current_time - Button_Struct[ind].last_interrupt_time) > DEBOUNCE_DELAY)
		{
			Button_Struct[ind].count +=1;
#ifdef	DEBUG_BUTTONS
			BUTTONS[ind] = Button_Struct[ind].count;
#endif
		}
		Button_Struct[ind].last_interrupt_time = Button_Struct[ind].current_time;
	}
	}
}
