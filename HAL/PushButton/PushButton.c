/*
GEAR
GEAR
GEAR
GEAR
GEAR
GEAR
*/

#include "PushButton.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

extern volatile bool gearStatus;

#define BUTTON_PORT GPIO_PORTF_BASE
#define BUTTON_PIN GPIO_PIN_4

void PushButton_Init(void)
{
    // Enable GPIOF peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;

    // Configure PF4 as input with pull-up
    GPIOPinTypeGPIOInput(BUTTON_PORT, BUTTON_PIN);
    GPIOPadConfigSet(BUTTON_PORT, BUTTON_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

bool PushButton_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(BUTTON_PORT, BUTTON_PIN) == 0);
}
