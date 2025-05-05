#define PART_TM4C123GH6PM
#include "PushButton.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#define LOCK_PORT GPIO_PORTE_BASE
#define LOCK_PIN GPIO_PIN_5

extern volatile bool doorLock;

void Lock_Init(void)
{
    // 1. Enable clock for GPIOE
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
        ;

    // 2. Configure PE5 as input with pull-up
    GPIOPinTypeGPIOInput(LOCK_PORT, LOCK_PIN);
    GPIOPadConfigSet(LOCK_PORT, LOCK_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // 3. Configure interrupt on falling edge
    GPIOIntDisable(LOCK_PORT, LOCK_PIN);                    // Disable interrupt before configuring
    GPIOIntClear(LOCK_PORT, LOCK_PIN);                      // Clear any prior interrupt
    GPIOIntTypeSet(LOCK_PORT, LOCK_PIN, GPIO_FALLING_EDGE); // Trigger on falling edge
    GPIOIntEnable(LOCK_PORT, LOCK_PIN);                     // Enable GPIO interrupt

    // 4. Enable NVIC interrupt for GPIOE
    IntEnable(INT_GPIOE); // Enable interrupt in NVIC
    IntMasterEnable();    // Enable global interrupts (optional if already done)
}

bool Lock_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(LOCK_PORT, LOCK_PIN) == 0);
}
