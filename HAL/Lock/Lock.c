#include "PushButton.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define LOCK_PORT GPIO_PORTC_BASE
#define LOCK_PIN GPIO_PIN_6

void Lock_Init(void)
{
    // Enable GPIOF peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
        ;

    // Configure PF4 as input with pull-up
    GPIOPinTypeGPIOInput(LOCK_PORT, LOCK_PIN);
    GPIOPadConfigSet(LOCK_PORT, LOCK_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
bool Lock_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(LOCK_PORT, LOCK_PIN) == 0);
}