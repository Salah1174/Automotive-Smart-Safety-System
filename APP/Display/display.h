#ifndef DISPLAY_H
#define DISPLAY_H

#include "../HAL/LCD/LCD.h"

void Display_Test(LCD_I2C *lcdDisplay);

void D_Display(LCD_I2C *lcdDisplay, uint32_t speedValue, uint8_t doorStatus,uint8_t lockStatus);
void R_Display(LCD_I2C *lcdDisplay, uint32_t distanceValue,uint32_t speed,uint8_t doorStatus,uint8_t lockStatus);
void Alert_Display(LCD_I2C *lcdDisplay);
void carOn_Display(LCD_I2C *lcdDisplay);
void carOff_Display(LCD_I2C *lcdDisplay);

#endif