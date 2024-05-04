/*
 * keypad.c
 *
 *  Created on: May 5, 2024
 *      Author: choua
 */

#include "stm32h5xx.h"
#include "keypad.h"
#include <stdbool.h>

uint8_t Last_Key_Down;

void Keypad_Start(Keypad *kb, GPIO_TypeDef* *_RowPorts, GPIO_TypeDef* *_ColPorts, uint16_t *_RowPins, uint16_t *_ColPins, uint8_t **keys)
{
	for(int i=0; i<4; i++)
	{
		kb->RowPorts[i] = _RowPorts[i];
		kb->ColPorts[i] = _ColPorts[i];
		kb->RowPins[i] = _RowPins[i];
		kb->ColPins[i] = _ColPins[i];
	}
	kb->rising_pin = 255;
	kb->let_falling_pin = 255;

	Last_Key_Down = 0;

	//return;

	HAL_GPIO_WritePin(kb->RowPorts[0], kb->RowPins[0], SET);
	HAL_GPIO_WritePin(kb->RowPorts[1], kb->RowPins[1], SET);
	HAL_GPIO_WritePin(kb->RowPorts[2], kb->RowPins[2], SET);
	HAL_GPIO_WritePin(kb->RowPorts[3], kb->RowPins[3], SET);

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			kb->keys[i][j] = keys[i][j];
		}
	}
}

void Keypad_Rising_EXTI(Keypad *kb, uint16_t GPIO_Pin)
{
	if (GPIO_Pin == kb->ColPins[0])
		kb->rising_pin = 0;
	else if (GPIO_Pin == kb->ColPins[1])
		kb->rising_pin = 1;
	else if(GPIO_Pin == kb->ColPins[2])
		kb->rising_pin = 2;
	else if(GPIO_Pin == kb->ColPins[3])
		kb->rising_pin = 3;
	else
		return;

	kb->key_down = true;
	kb->let_falling_pin = 0;
	HAL_GPIO_WritePin(kb->RowPorts[0], kb->RowPins[0], RESET);
	HAL_GPIO_WritePin(kb->RowPorts[0], kb->RowPins[0], SET);
	kb->let_falling_pin = 1;
	HAL_GPIO_WritePin(kb->RowPorts[1], kb->RowPins[1], RESET);
	HAL_GPIO_WritePin(kb->RowPorts[1], kb->RowPins[1], SET);
	kb->let_falling_pin = 2;
	HAL_GPIO_WritePin(kb->RowPorts[2], kb->RowPins[2], RESET);
	HAL_GPIO_WritePin(kb->RowPorts[2], kb->RowPins[2], SET);
	kb->let_falling_pin = 3;
	HAL_GPIO_WritePin(kb->RowPorts[3], kb->RowPins[3], RESET);
	HAL_GPIO_WritePin(kb->RowPorts[3], kb->RowPins[3], SET);
	kb->let_falling_pin = 4;
	kb->rising_pin = 4;
}

void Keypad_Falling_EXTI(Keypad *kb, uint16_t GPIO_Pin)
{
	if(!kb->key_down || GPIO_Pin != kb->rising_pin)
		return ;
	if(kb->let_falling_pin > 3)
		return ;
	Last_Key_Down = kb->keys[kb->rising_pin][kb->let_falling_pin];

	kb->key_down = false;
}