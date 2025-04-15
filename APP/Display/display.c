
#include "display.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/ULTRASONIC/ultrasonic.h"
#include "../HAL/Doors/Doors.h"
#include "../HAL/Potentiometer/Potentiometer.h"
#include "../MCAL/Timer0/timer0.h"
#include "inc/tm4c123gh6pm.h"

// #include "TM4C123GH6PM.h"
// #include "driverlib/i2c.h"
// #include "driverlib/i2c.h"
 #include "driverlib/sysctl.h"
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
//	clear(lcdDisplay);
		home(lcdDisplay);

    // Print a message on the LCD
	  print(lcdDisplay, "Speed:");
	
	
	
		setCursor(lcdDisplay,12,0);
		print(lcdDisplay,"km/h");

    // Move the cursor to the second line and print another message
//    command(lcdDisplay, LCD_SETDDRAMADDR|LCD_SETCGRAMADDR); // Move cursor to the second line
		setCursor(lcdDisplay,0,1);
		print(lcdDisplay, "Door:");
	

	

}

void R_Display(LCD_I2C *lcdDisplay){
//		clear(lcdDisplay);
		home(lcdDisplay);
	   // Print a message on the LCD
	  print(lcdDisplay, "Speed:");
	
		setCursor(lcdDisplay,12,0);
		print(lcdDisplay,"km/h");

    // Move the cursor to the second line and print another message
    setCursor(lcdDisplay,0,1); // Move cursor to the second line
		print(lcdDisplay, "Distance:");
	
		setCursor(lcdDisplay,15,1);
		print(lcdDisplay, "m");

	
}
void Alert_Display(LCD_I2C *lcdDisplay){
	home(lcdDisplay);
	setCursor(lcdDisplay,3,0);
	print(lcdDisplay, "Attention!");

	
//	setCursor(lcdDisplay,2,1); // Move cursor to the second line
		
	while(1){
//	scrollDisplayRight(lcdDisplay);
	  setCursor(lcdDisplay,2,1);
		print(lcdDisplay, "Door is open!");
//    timer0B_delayMs(10000);
		SysCtlDelay(1000000);
		setCursor(lcdDisplay,2,1);
		print(lcdDisplay, "            !");
//		timer0B_delayMs(1000000);
			SysCtlDelay(1000000);
	}
	
}
