/*
 * OLED_screen.c
 *
 *  Created on: May 4, 2024
 *      Author: jacki
 */

#include "OLED_screen.h"


void Screen_Init(OLED_Screen* oled){
    for (int i = 0; i < LENGTH_LIMIT;i++){
        oled->lentemp[i] = ' ';
        oled->qtytemp[i] = ' ';
    }
    oled->count = 0;
    oled->state = 0;
    oled->isCrimp = false; oled->isTrim = false;
}

bool IsDigit(char c) {
  return c >= '0' && c <= '9';
}

uint16_t ConvertStringToInt(char *str) {
    uint16_t i = 0;
    uint16_t num = 0;
    while (str[i] != ' ' && i < LENGTH_LIMIT){
        if (IsDigit(str[i]) == true){
            uint16_t digit = str[i] - '0';
            num = num * 10 + digit;
        }
        i++;
    }
    return num;
}

void DisplayState(uint8_t state){
    ssd1306_FillRectangle(0, 20, 6, 49, Black);
    ssd1306_SetCursor(63, 40); ssd1306_WriteChar(' ', Font_7x10, White);
    if (state == 0){
        ssd1306_SetCursor(0, 20);
        ssd1306_WriteChar('>', Font_7x10, White);        
    }
    else if (state == 1){
        ssd1306_SetCursor(0, 30);
        ssd1306_WriteChar('>', Font_7x10, White);  
    }
    else if (state == 2){
        ssd1306_SetCursor(0, 40);
        ssd1306_WriteChar('>', Font_7x10, White);  
    }
    else if (state == 3){
        ssd1306_SetCursor(63, 40);
        ssd1306_WriteChar('>', Font_7x10, White);  
    }
    ssd1306_UpdateScreen();
}

bool Screen_CheckState(OLED_Screen *oled, uint8_t *keypressed){
    if (oled->state == 0){
        if (*keypressed == EnterChar){
            oled->count = 0;
            oled->state++;
            DisplayState(oled->state);
        }
        else if (*keypressed == CancelChar){
            Screen_Init(oled);
            Screen_Cancel();
        }
        else {
            Screen_UpdateLength(oled, keypressed);
        }
    }
    else if (oled->state == 1){
        if (*keypressed == EnterChar){
            oled->count = 0;
            oled->state++;
            DisplayState(oled->state);
        }
        else if (*keypressed == CancelChar){
            Screen_Init(oled);
            Screen_Cancel();
        }
        else {
            Screen_UpdateQty(oled, keypressed);
        }
    }
    else if (oled->state == 2){
        if (*keypressed == EnterChar){
            oled->count = 0;
            oled->state++;
            DisplayState(oled->state);
        }
        else if (*keypressed == CancelChar){
            Screen_Init(oled);
            Screen_Cancel();
        }
        else {
            Screen_UpdateTrim(oled, keypressed);
        }
    }
    else if (oled->state == 3){
        if (*keypressed == EnterChar){
            oled->count = 0;
            oled->state = 0;
            //store in tasklist
            DisplayState(oled->state);
            Screen_Cancel();
            return true;
        }
        else if (*keypressed == CancelChar){
            Screen_Init(oled);
            Screen_Cancel();
        }
        else {
            Screen_UpdateCrimp(oled, keypressed);
        }
    }
    return false;
}


void Screen_DefaultDisplay(void){
    char taskq[] = "Task in Queue: 0  ";
    char title[] = "**Add New Tasks**";
    char subsec1[] = "len: 0         ";
    char subsec2[] = "qty: 0         ";
    char unit[] = "mm";
    char subsec3[] = "trim:N "; //8
    char subsec4[] = "crimp:N "; //9
    char guide1[] = "F:enter";
    char guide2[] = "C:cancel";
    ssd1306_SetCursor(0, 0); ssd1306_WriteString(taskq, Font_7x10, White);
    //add new tasks
    ssd1306_FillRectangle(0, 9, 127, 19, White);
    ssd1306_SetCursor(0, 10); 
    ssd1306_WriteString(title, Font_7x10, Black);
    //length:
    ssd1306_SetCursor(0, 20); ssd1306_WriteChar('>', Font_7x10, White);
    ssd1306_SetCursor(8, 20); ssd1306_WriteString(subsec1, Font_7x10, White); 
    ssd1306_SetCursor(114, 20); ssd1306_WriteString(unit, Font_7x10, White);
    //qty:
    ssd1306_SetCursor(8, 30); ssd1306_WriteString(subsec2, Font_7x10, White);
    //trim:
    ssd1306_SetCursor(8, 40); ssd1306_WriteString(subsec3, Font_7x10, White);
    //crimp:
    ssd1306_SetCursor(70, 40); ssd1306_WriteString(subsec4, Font_7x10, White);
    //guide prompt
    ssd1306_FillRectangle(0, 50, 127, 63, White);
    ssd1306_SetCursor(8, 52); ssd1306_WriteString(guide1, Font_7x10, Black);
    ssd1306_SetCursor(63,52); ssd1306_WriteString(guide2, Font_7x10, Black);
    ssd1306_UpdateScreen();
}

void Screen_Cancel(void){
    char subsec1[] = "len: 0         ";
    char subsec2[] = "qty: 0         ";
    char unit[] = "mm";
    char subsec3[] = "trim:N ";
    char subsec4[] = "crimp:N ";
    char guide1[] = "F:enter";
    char guide2[] = "C:cancel";
    //length:
    ssd1306_SetCursor(0, 20); ssd1306_WriteChar('>', Font_7x10, White);
    ssd1306_SetCursor(8, 20); ssd1306_WriteString(subsec1, Font_7x10, White); 
    ssd1306_SetCursor(114, 20); ssd1306_WriteString(unit, Font_7x10, White);
    //qty:
    ssd1306_SetCursor(8, 30); ssd1306_WriteString(subsec2, Font_7x10, White);
    //trim:
    ssd1306_SetCursor(8, 40); ssd1306_WriteString(subsec3, Font_7x10, White);
    //crimp:
    ssd1306_SetCursor(70, 40); ssd1306_WriteString(subsec4, Font_7x10, White);
    //guide prompt
    ssd1306_FillRectangle(0, 50, 127, 63, White);
    ssd1306_SetCursor(8, 52); ssd1306_WriteString(guide1, Font_7x10, Black);
    ssd1306_SetCursor(63,52); ssd1306_WriteString(guide2, Font_7x10, Black);
    ssd1306_UpdateScreen();
}

void Screen_UpdateLength(OLED_Screen* oled, uint8_t *keypressed){
    char unit[] = "mm";
    if (IsDigit(*keypressed)){
        oled->lentemp[oled->count] = *keypressed;
        oled->count = (oled->count + 1) % LENGTH_LIMIT;
        ssd1306_SetCursor(42, 20);
        ssd1306_WriteString(oled->lentemp, Font_7x10, White);
        ssd1306_SetCursor(114, 20); ssd1306_WriteString(unit, Font_7x10, White);
    }
    ssd1306_UpdateScreen();
}

void Screen_UpdateQty(OLED_Screen *oled, uint8_t *keypressed){
    if (IsDigit(*keypressed)){
        oled->qtytemp[oled->count] = *keypressed;
        oled->count = (oled->count + 1) % LENGTH_LIMIT;
        ssd1306_SetCursor(42, 30);
        ssd1306_WriteString(oled->qtytemp, Font_7x10, White);
    }
    ssd1306_UpdateScreen();
}

void Screen_UpdateTrim(OLED_Screen *oled, uint8_t *keypressed){
    char str1[] = "Y";
    char str2[] = "N";
    ssd1306_SetCursor(42, 40);
    if (IsDigit(*keypressed)){
        if (*keypressed == YESChar){
            oled->isTrim = true;
            ssd1306_WriteString(str1, Font_7x10, White);
        }
        else {
            oled->isTrim = false;
            ssd1306_WriteString(str2, Font_7x10, White);
    }
    }
    ssd1306_UpdateScreen();
}

void Screen_UpdateCrimp(OLED_Screen *oled, uint8_t *keypressed){
    char str1[] = "Y";
    char str2[] = "N";
    ssd1306_SetCursor(112, 40);
    if (IsDigit(*keypressed)){
        if (*keypressed == YESChar){
            oled->isCrimp = true;
            ssd1306_WriteString(str1, Font_7x10, White);
        }
        else {
            oled->isCrimp = false;
            ssd1306_WriteString(str2, Font_7x10, White);
    }
    }
    ssd1306_UpdateScreen();
}

void Screen_UpdateAll(uint8_t qsize){ //input current queue size
    char temp[4];
    char title[] = "**Add New Tasks**";
    itoa(qsize, temp, 10);
    ssd1306_SetCursor(105, 0); ssd1306_WriteString(temp, Font_7x10, White);
    ssd1306_FillRectangle(0, 9, 127, 19, White);
    ssd1306_SetCursor(0, 10); 
    ssd1306_WriteString(title, Font_7x10, Black);
    Screen_Cancel();
}

void Screen_UpdateTitle(uint8_t qsize){
    char temp[4];
    char title[] = "**Add New Tasks**";
    itoa(qsize, temp, 10);
    ssd1306_SetCursor(105, 0); ssd1306_WriteString(temp, Font_7x10, White);
    ssd1306_FillRectangle(0, 9, 127, 19, White);
    ssd1306_SetCursor(0, 10); 
    ssd1306_WriteString(title, Font_7x10, Black);
    ssd1306_UpdateScreen();
}