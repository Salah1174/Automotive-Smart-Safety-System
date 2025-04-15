#ifndef DISPLAY_H
#define DISPLAY_H

#include "../HAL/LCD/LCD.h"

void Display_Test(LCD_I2C *lcdDisplay);


void D_Display(LCD_I2C *lcdDisplay);
void R_Display(LCD_I2C *lcdDisplay);
void Alert_Display(LCD_I2C *lcdDisplay);


#endif