/*
 * servo.h
 *
 *  Created on: May 4, 2024
 *      Author: choua
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32h5xx_hal.h"
#include <stdbool.h>


typedef struct
{
	uint16_t numera;
	uint32_t channel;

}Servo;

void SERVO_INIT(TIM_HandleTypeDef *_htim, uint16_t cycle);
void SERVO_SET_TIM(TIM_HandleTypeDef *_htim);
void SERVO_SET_DUTY_CYCLE(uint16_t cycle);

void Servo_Start(Servo *motor, uint32_t _channel);
void Servo_Stop(Servo *motor);
bool Servo_Write(Servo *motor, uint16_t val);

TIM_HandleTypeDef* SERVO_GET_TIMER();

#endif /* INC_SERVO_H_ */
