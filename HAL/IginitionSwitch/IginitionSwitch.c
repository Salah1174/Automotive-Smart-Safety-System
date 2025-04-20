#include "IginitionSwitch.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define SWITCH_PORT GPIO_PORTC_BASE
#define SWITCH_PIN GPIO_PIN_5

void IgnitionSwitch_Init(void)
{
    // Enable GPIOF peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
        ;

    // Configure PF4 as input with pull-up
    GPIOPinTypeGPIOInput(SWITCH_PORT, SWITCH_PIN);
    GPIOPadConfigSet(SWITCH_PORT, SWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
bool IgnitionSwitch_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(SWITCH_PORT, SWITCH_PIN) == 0);
}
