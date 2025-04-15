#include "ADC1.h"
#include "LCD.h"
#include "APP/Display/display.h"
#include "TM4C123.h"

#include "FreeRTOS.h"
#include <stdint.h>
#include <stdbool.h>

void delay_ms(uint32_t ms) {
    volatile uint32_t i;
    while (ms--) {
        for (i = 0; i < 4000; i++) {}
    }
}

int main() {

 
    // Initialize the LCD
    LCD_I2C lcdDisplay;
    LCDI2CInit(&lcdDisplay, 0x27, 16, 2); // Address: 0x27, 16 columns, 2 rows

    // call app?
	
		//gear
//    D_Display(&lcdDisplay);
//		R_Display(&lcdDisplay);
	
		//alert
	Alert_Display(&lcdDisplay);

    ADC1_Init();
    uint32_t adcvalue = 0;

    //dio test?
//    DIO_Init('F', 1, DIO_PIN_OUTPUT);  
//    DIO_Init('F', 0, DIO_PIN_INPUT);   

//    bool buttonPressed = false;
while (true) {
    //        uint8_t input = DIO_ReadPin('F', 0);
    
    //        if (input == 1 && !buttonPressed) {
    //            delay_ms(20); 
    //            if (DIO_ReadPin('F', 0) == 1) {
    //                uint8_t current = DIO_ReadPin('F', 1);
    //                DIO_WritePin('F', 1, !current); 
    //                buttonPressed = true;
    //            }
    //        }
    
    //        if (input == 0) {
    //            buttonPressed = false;
    //        }
    //    }
    
    while (1) {
        adcvalue = ADC1_ReadValue();
        delay_ms(1000);
    }

//    return 0;
}
}
