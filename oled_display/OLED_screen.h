/*
 * OLED_screen.h
 *
 *  Created on: May 4, 2024
 *      Author: jacki
 */

#ifndef INC_OLED_SCREEN_H_
#define INC_OLED_SCREEN_H_
#include <stdbool.h>
#include <stdlib.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"

#define LENGTH_LIMIT 6

#define EnterChar 'F'
#define CancelChar 'C'
#define YESChar '1'
#define NOChar '0'

typedef struct OLED_Screen{
    char lentemp[LENGTH_LIMIT];
    char qtytemp[LENGTH_LIMIT];
    bool isTrim; bool isCrimp;
    uint8_t state;
    uint8_t count;
}OLED_Screen;

bool Screen_CheckState(OLED_Screen *oled, uint8_t *keypressed);
void Screen_Init(OLED_Screen* oled);
void Screen_UpdateAll(uint8_t qsize);


//low level procedures
bool IsDigit(char c);
void DisplayState(uint8_t state);
void Screen_DefaultDisplay(void);
void Screen_Cancel(void);
void Screen_UpdateLength(OLED_Screen* oled, uint8_t *keypressed);
void Screen_UpdateQty(OLED_Screen *oled, uint8_t *keypressed);
void Screen_UpdateTrim(OLED_Screen *oled, uint8_t *keypressed);
void Screen_UpdateCrimp(OLED_Screen *oled, uint8_t *keypressed);
void Screen_UpdateTitle(uint8_t qsize);
uint16_t ConvertStringToInt(char *str); 


#endif /* INC_OLED_SCREEN_H_ */
