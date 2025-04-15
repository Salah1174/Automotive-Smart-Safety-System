#ifndef LCD_H
#define LCD_H


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../MCAL/Timer0/timer0.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
//#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define LCD_CURSOROFF 0x0c

#define En 4  // Enable bit
#define Rw 2  // Read/Write bit
#define Rs 1  // Register select bit

typedef struct {
	uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;
}LCD_I2C;


//functions 

void LCDI2CInit(LCD_I2C *display, uint8_t address, uint8_t lcd_cols,uint8_t lcd_rows);
void begin(LCD_I2C *display);
void configDisplay(LCD_I2C *display  );
void clear(LCD_I2C *display );
void home(LCD_I2C *display );
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


void setCursor(LCD_I2C *display,uint8_t col, uint8_t row);
//*********** Low-level LCD functions **************
void command(LCD_I2C *display, uint8_t value );
void send(LCD_I2C *display, uint8_t value, uint8_t mode );
void write4bits(LCD_I2C *display, uint8_t value);
void expanderWrite(LCD_I2C *display, uint8_t _data);
void pulseEnable(LCD_I2C *display, uint8_t _data );

#endif