
#include "display.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/ULTRASONIC/ultrasonic.h"
#include "../HAL/Doors/Doors.h"
#include "../HAL/Potentiometer/Potentiometer.h"
#include "../MCAL/Timer0/timer0.h""

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
//void Display_Test(LCD_I2C *lcdDisplay) {
//    // Clear the display
//    clear(lcdDisplay);
////	  command(lcdDisplay, 0x0f);

//    // Print a message on the LCD
//    print(lcdDisplay, "Hello, World!");

//    // Move the cursor to the second line and print another message
//    command(lcdDisplay, 0xC0); // Move cursor to the second line
//    print(lcdDisplay, "Welcome!");

//}

void D_Display(LCD_I2C *lcdDisplay){
	clear(lcdDisplay);


    // Print a message on the LCD
	  print(lcdDisplay, "Speed:");
		print(lcdDisplay,"km/h");

    // Move the cursor to the second line and print another message
//    command(lcdDisplay, LCD_SETDDRAMADDR|LCD_SETCGRAMADDR); // Move cursor to the second line
		setCursor(lcdDisplay,0,1);
		print(lcdDisplay, "hmm:");
		
	

}

void R_Display(LCD_I2C *lcdDisplay){
		command(lcdDisplay, LCD_CLEARDISPLAY);
	
	   // Print a message on the LCD
	  print(lcdDisplay, "Speed:");
		print(lcdDisplay,"km/h");

    // Move the cursor to the second line and print another message
    command(lcdDisplay, 0xC0); // Move cursor to the second line
		print(lcdDisplay, "Distance:");
		print(lcdDisplay,"m");
	
}
void Alert_Display(LCD_I2C *lcdDisplay){
	print(lcdDisplay, "     Attention!");
	
	command(lcdDisplay, 0xC0); // Move cursor to the second line
		
//	while(1){
////		blink(lcdDisplay);

//		print(lcdDisplay, "Door is open!");
//    timer0A_delayMs(100000000);
////		blink(lcdDisplay);

//		print(lcdDisplay, "            !");
//		timer0A_delayMs(1000000000);
//	}
	
}
