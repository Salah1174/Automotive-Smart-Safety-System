#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#include "LCD.h"
#include "PushButton.h"
#include "Potentiometer.h"
#include "Lock.h"
#include "Doors.h"
#include "IginitionSwitch.h"
#include "ultrasonic.h"

#include "APP/Display/display.h"

#define LED_PORT GPIO_PORTF_BASE
#define LED_PIN GPIO_PIN_1


void delay_ms(uint32_t ms)
{
    volatile uint32_t i;
    while (ms--)
    {
        for (i = 0; i < 4000; i++)
        {
        }
    }
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) ;
    GPIOPinTypeGPIOOutput(LED_PORT, LED_PIN);

		LCD_I2C lcdDisplay;
    LCDI2CInit(&lcdDisplay, 0x27, 16, 2);
	  ultrasonic_Init();
    PushButton_Init();
    potentiometer_Init();
		DOOR_Init();
		Lock_Init();
		IgnitionSwitch_Init();
    Alert_Display(&lcdDisplay);
		
		bool carStatus = false;
		bool doorLocked = false;
		bool doorStatus = false;
    bool lastPressed = false;
    uint32_t speed = 0;
    uint32_t distance = 0;
	
    while (1)
    {
        bool currentPressed = PushButton_Read();
        uint8_t state = GPIOPinRead(LED_PORT, LED_PIN);
        speed = potentiometer_ReadValue();
        distance = ultrasonic_ReadValue();
				doorStatus = DOOR_Status();
				doorLocked = Lock_Read(); 
				carStatus = IgnitionSwitch_Read();
			
        if (currentPressed && !lastPressed)
        {
            // Debounce delay
            SysCtlDelay(SysCtlClockGet() / 100); // ~10 ms

            // Confirm again
            if (PushButton_Read())
            {

                // Toggle LED
                state = GPIOPinRead(LED_PORT, LED_PIN);
                GPIOPinWrite(LED_PORT, LED_PIN, state ^ LED_PIN);
            }
        }
        if (state)
        {
            D_Display(&lcdDisplay, speed, doorStatus,doorLocked);
            delay_ms(1000);
        }
        else
        {
            R_Display(&lcdDisplay, distance,carStatus);
            delay_ms(1000);
        }
        lastPressed = currentPressed;
    }
}