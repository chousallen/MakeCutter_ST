/*
 * stepmotor.h
 *
 *  Created on: Apr 25, 2024
 *      Author: jacki
 */

#ifndef SRC_STEPMOTOR_H_
#define SRC_STEPMOTOR_H_

#include "main.h"
void microDelay (uint16_t delay, TIM_HandleTypeDef *htim2);
void stepCCV (int steps, uint16_t delay, TIM_HandleTypeDef *htim2);
void stepCV (int steps, uint16_t delay, TIM_HandleTypeDef *htim2);
#endif /* SRC_STEPMOTOR_H_ */
