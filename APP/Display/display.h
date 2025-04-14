#ifndef DISPLAY_H
#define DISPLAY_H

#include "../HAL/LCD/LCD.h"


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void noCursor(LCD_I2C *display  );
void cursor(LCD_I2C *display  );
void backlight(LCD_I2C *display);
void noBacklight(LCD_I2C *display);
void noBlink(LCD_I2C *display  );
void blink(LCD_I2C *display  );
void scrollDisplayRight(LCD_I2C *display  );
void scrollDisplayLeft(LCD_I2C *display  );
void noDisplay(LCD_I2C *display  );
void display(LCD_I2C *display  );
void leftToRight(LCD_I2C *display  );
void rightToLeft(LCD_I2C *display  );
void autoscroll(LCD_I2C *display  );
void noAutoscroll(LCD_I2C *display  );
size_t printChar(LCD_I2C *display, const char c  );
size_t print(LCD_I2C *display, const char* str  );

#endif