/*
 * pca9955.c
 *
 *  Created on: Apr 20, 2024
 *      Author: jacki
 */


#include "pca9955.h"
int address = 0x20;     // first 7 bits addr 0100000
int address_write = 0x40;   // 01000000 full byte 
int timeout = 25;
int delaytime = 120;

//All addresses needed for the commands to control the leds page 14-16 Datasheet table 7
int MODE1 = 0x00;
int LEDOUT0 = 0x2;
int LEDOUT1 = 0x03;
int GRPPWM = 0x06;        // group duty cycle control
int GRPFREQ = 0x07;       // group frequency

/*-----------led control setup-------------*/
//RGB => LED0, LED1, LED2
int LEDOFF = 0x00;
int LEDON = 0x05;

char COLOR[3] = {'r', 'g', 'b'};
//2*i is the address of ith register, follow by 2*i + 1 data
uint8_t RED[10] = {0x08, 0x00, 0x0B, 0x00, 0x0E, 0x00, 0x11, 0x00, 0x14, 0x00};
uint8_t GRE[10] = {0x09, 0x00, 0x0C, 0x00, 0x0F, 0x00, 0x12, 0x00, 0x15, 0x00};
uint8_t BLUE[10] = {0x0A, 0x00, 0x0D, 0x00, 0x10, 0x00, 0x13, 0x00, 0x16, 0x00};

int ALLCALLADR = 0x43;    // all call I2C bus address
int PWMALL = 0x44;        // brightness control for all LED
int IREF0 = 0x18;         // output current value registers
int IREF1 = 0x19;         // output current value registers
int IREF2 = 0x20;         // output current value registers

uint8_t IREFALL[2] = {0x45, 0xFF};

/*-----------other registers-------------*/
// The values of the registers are defined at the page of each register
int MODE1val = 0x89;       // 10001001 // default mod
int MODE1valcolour = 0xA9; // colour change

int MODE2val = 0x01;       // 00000001
int LEDOUT0OFF = 0x00;     // 00000000
int LEDOUT0ON = 0x01;      // 00000001
int PWM_val = 0x80;
int IREF_val = 0x14;
int ALLCALL_val = 0x70;
int rawR =0,rawG=0,rawB=0;


/*-------------function definiton------------------*/
void PCA9955_InitALL(I2C_HandleTypeDef *hi2c){
    HAL_I2C_Master_Transmit(hi2c, address_write, IREFALL, 2, timeout);
}
void WriteCommand(I2C_HandleTypeDef *hi2c, char color, int num, int brightness){
    if (color == 'r'){
        RED[2*num + 1] = brightness;
        HAL_I2C_Master_Transmit(hi2c, address_write, &RED[2*num], 2, timeout);     
    }
    else if (color == 'g'){
        GRE[2*num + 1] = brightness;
        HAL_I2C_Master_Transmit(hi2c, address_write, &GRE[2*num], 2, timeout);
    }
    else if (color == 'b'){
        BLUE[2*num + 1] = brightness;
        HAL_I2C_Master_Transmit(hi2c, address_write, &BLUE[2*num], 2, timeout);   
    }
}
void PCA9955_ClearAll(I2C_HandleTypeDef *hi2c){
    for (int i = 0; i < 5; i++){
        WriteCommand(hi2c, 'r', i, 0);
        WriteCommand(hi2c, 'g', i, 0);
        WriteCommand(hi2c, 'b', i, 0);
    }
}
void RGB_Blink(I2C_HandleTypeDef *hi2c, int delay){
    for (int color = 0; color < 3; color++){
        for (int i = 0; i < 5; i ++){
            WriteCommand(hi2c, COLOR[color], i, LEDON);
        }
        HAL_Delay(delay);
        for (int i = 0; i < 5; i ++){
            WriteCommand(hi2c, COLOR[color], i, LEDOFF);
        }
        HAL_Delay(delay);
    }
}

void Rapid_Blink(I2C_HandleTypeDef *hi2c){
    for (int color = 0; color < 3; color++){
        WriteCommand(hi2c, COLOR[color], 0, LEDON);
        HAL_Delay(100);
        for (int i = 1; i < 5; i ++){
            WriteCommand(hi2c, COLOR[color], i - 1, LEDOFF);
            WriteCommand(hi2c, COLOR[color], i, LEDON);
            HAL_Delay(100);
        }
        WriteCommand(hi2c, COLOR[color], 4, LEDOFF);
        HAL_Delay(100);
    }
}

void BreathRBG(I2C_HandleTypeDef *hi2c, int r, int g, int b){
    int temp_color[3] = {0};
    for (int i = 0;i<6; i++){
        temp_color[0] = (r/6)*i; temp_color[1] = (g/6)*i; temp_color[2] = (b/6)*i;
        for (int color = 0; color < 3; color++){
            for (int j = 0; j < 5; j++){
                WriteCommand(hi2c, COLOR[color], j, temp_color[color]);
            }
        }
        HAL_Delay(delaytime);
    }
    HAL_Delay(delaytime/30);
    for (int i = 6;i > 0;i--){
        temp_color[0] = (r/6)*i; temp_color[1] = (g/6)*i; temp_color[2] = (b/6)*i;
        for (int color = 0; color < 3; color++){
            for (int j = 0; j < 5; j++){
                WriteCommand(hi2c, COLOR[color], j, temp_color[color]);
            }
        }
        HAL_Delay(delaytime);
    }
    PCA9955_ClearAll(hi2c);
}
void BreathRGB_Show(I2C_HandleTypeDef *hi2c){
    BreathRBG(hi2c, 50, 0, 0);
    BreathRBG(hi2c, 0, 50, 0);
    BreathRBG(hi2c, 0, 0, 50);
    BreathRBG(hi2c, 50, 50, 0);
    BreathRBG(hi2c, 50, 0, 50);
    BreathRBG(hi2c, 0, 50, 50);
}
