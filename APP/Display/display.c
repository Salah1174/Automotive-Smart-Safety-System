
#include "display.h"
#include "../HAL/LCD/LCD.h"

// #include "TM4C123GH6PM.h"
// #include "driverlib/i2c.h"
// #include "driverlib/i2c.h"
// #include "driverlib/sysctl.h"
// #include "driverlib/gpio.h"
// #include "driverlib/pin_map.h"
// #include "inc/hw_memmap.h"
// #include "inc/hw_types.h"
// #include "inc/hw_i2c.h"

//test
void Display_Task(LCD_I2C *lcdDisplay) {
    // Clear the display
    clear(lcdDisplay);
//	  command(lcdDisplay, 0x0f);

    // Print a message on the LCD
    print(lcdDisplay, "Hello, World!");

    // Move the cursor to the second line and print another message
    command(lcdDisplay, 0xC0); // Move cursor to the second line
    print(lcdDisplay, "Welcome!");
		noCursor(lcdDisplay);
		command(lcdDisplay, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
