
#include "display.h"
#include "../HAL/LCD/LCD.h"

#include "TM4C123GH6PM.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"

// Turns the underline cursor on/off
void noCursor(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_CURSORON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}
void cursor(LCD_I2C *display  ) {
	display->_displaycontrol |= LCD_CURSORON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

void backlight(LCD_I2C *display) {
	display->_backlightval=LCD_BACKLIGHT;
	expanderWrite(display, 0);
}

void noBacklight(LCD_I2C *display) {
	display->_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(display, 0);
}

void noBlink(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_BLINKON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

void blink(LCD_I2C *display  ) {
	display->_displaycontrol |= LCD_BLINKON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(LCD_I2C *display) {
	command(display, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT );
}
void scrollDisplayRight(LCD_I2C *display ) {
	command(display, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT );
}

// Turn the display on/off (quickly)
void noDisplay(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}
void display(LCD_I2C *display) {
	display->_displaycontrol |= LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

// This is for text that flows Left to Right
void leftToRight(LCD_I2C *display  ) {
	display->_displaymode |= LCD_ENTRYLEFT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This is for text that flows Right to Left
void rightToLeft(LCD_I2C *display  ) {
	display->_displaymode &= ~LCD_ENTRYLEFT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This will 'right justify' text from the cursor
void autoscroll(LCD_I2C *display  ) {
	display->_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This will 'left justify' text from the cursor
void noAutoscroll(LCD_I2C *display ) {
	display->_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

size_t printChar(LCD_I2C *display, const char c ){
	return write(display, c );
}

size_t print(LCD_I2C *display, const char* str  ){
	return write_string(display, (const uint8_t *)str, strlen(str) ); // beware of casting!!! Type safe in this case :)
}
