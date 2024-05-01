/*
 * pca9955.h
 *
 *  Created on: Apr 20, 2024
 *      Author: jacki
 */

#ifndef INC_PCA9955_H_
#define INC_PCA9955_H_

#include "main.h"

void PCA9955_InitALL(I2C_HandleTypeDef *hi2c);
void WriteCommand(I2C_HandleTypeDef *hi2c, char color, int num, int LEDstate);
void PCA9955_ClearAll(I2C_HandleTypeDef *hi2c);
void RGB_Blink(I2C_HandleTypeDef *hi2c, int delay);
void Rapid_Blink(I2C_HandleTypeDef *hi2c);
void BreathRBG(I2C_HandleTypeDef *hi2c, int r, int g, int b);
void BreathRGB_Show(I2C_HandleTypeDef *hi2c);
#endif /* INC_PCA9955_H_ */
