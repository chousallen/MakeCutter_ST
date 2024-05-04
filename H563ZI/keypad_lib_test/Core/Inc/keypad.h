/*
 * keypad.h
 *
 *  Created on: May 5, 2024
 *      Author: choua
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stm32h5xx.h"
#include <stdbool.h>

extern uint8_t Last_Key_Down;

typedef struct
{
	GPIO_TypeDef* RowPorts[4];
	GPIO_TypeDef* ColPorts[4];
	uint16_t RowPins[4];
	uint16_t ColPins[4];
	uint8_t rising_pin; //should be column pins
	uint8_t let_falling_pin; //should be row pins
	uint8_t keys[4][4]; //keys[col][row]
	bool key_down;
}Keypad;

void Keypad_Start(Keypad *kb, GPIO_TypeDef* *RowPorts, GPIO_TypeDef* *ColPorts, uint16_t *RowPins, uint16_t *ColPins, uint8_t **keys);
//write high

void Keypad_Rising_EXTI(Keypad *kb, uint16_t GPIO_Pin);
//column is known, assign to rising pin, pull row low

void Keypad_Falling_EXTI(Keypad *kb,uint16_t GPIO_Pin);
//check if same as last rising exti pin


#endif /* INC_KEYPAD_H_ */