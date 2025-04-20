#include "Doors.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include <stdbool.h>

#define LIMITSWITCH_PORT GPIO_PORTC_BASE
#define LIMITSWITCH_PIN GPIO_PIN_4

volatile bool doorStatus = false;

void DOOR_Init(void)
{
    // Enable Port C peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
        ;

    // Configure PC4 as input with pull-up
    GPIOPinTypeGPIOInput(LIMITSWITCH_PORT, LIMITSWITCH_PIN);
    GPIOPadConfigSet(LIMITSWITCH_PORT, LIMITSWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //    // Configure interrupt for falling edge (button press)
    //    GPIOIntDisable(LIMITSWITCH_PORT, LIMITSWITCH_PIN);                    // Disable interrupt during setup
    //    GPIOIntClear(LIMITSWITCH_PORT, LIMITSWITCH_PIN);                      // Clear any pending interrupt
    //    GPIOIntTypeSet(LIMITSWITCH_PORT, LIMITSWITCH_PIN, GPIO_FALLING_EDGE); // Falling edge trigger
    //    GPIOIntEnable(LIMITSWITCH_PORT, LIMITSWITCH_PIN);                     // Enable interrupt

    //    // Enable GPIO Port C interrupt in NVIC
    //    IntEnable(INT_GPIOC_TM4C123);  // Replace INT_GPIOC with INT_GPIOC_TM4C123
    //    IntMasterEnable(); // Enable processor-level interrupts
}

bool DOOR_Status(void)
{
    return !GPIOPinRead(LIMITSWITCH_PORT, LIMITSWITCH_PIN); // Return true if pressed
}

// Interrupt Service Routine for Port C
// void GPIOC_Handler(void)
//{
//    // Clear the interrupt flag
//    GPIOIntClear(LIMITSWITCH_PORT, LIMITSWITCH_PIN);

//    // Toggle door status or perform your logic here
//    doorStatus = true; // or any other action
//}
