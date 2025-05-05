#define PART_TM4C123GH6PM

#include "IginitionSwitch.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SWITCH_PORT_BASE GPIO_PORTC_BASE
#define SWITCH_PERIPH SYSCTL_PERIPH_GPIOC
#define SWITCH_PIN GPIO_PIN_5

extern volatile bool carStatus;

void IgnitionSwitch_Init(void)
{
    // 1. Enable clock for GPIOC
    SysCtlPeripheralEnable(SWITCH_PERIPH);
    while (!SysCtlPeripheralReady(SWITCH_PERIPH))
        ;

    // 2. Configure PC5 as input with pull-up
    GPIOPinTypeGPIOInput(SWITCH_PORT_BASE, SWITCH_PIN);
    GPIOPadConfigSet(SWITCH_PORT_BASE, SWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // 3. Configure interrupt on falling edge
    GPIOIntDisable(SWITCH_PORT_BASE, SWITCH_PIN);                    // Disable before configuring
    GPIOIntClear(SWITCH_PORT_BASE, SWITCH_PIN);                      // Clear interrupt flag
    GPIOIntTypeSet(SWITCH_PORT_BASE, SWITCH_PIN, GPIO_FALLING_EDGE); // Set falling edge trigger
    GPIOIntEnable(SWITCH_PORT_BASE, SWITCH_PIN);                     // Enable GPIO interrupt

    // 4. Enable in NVIC
    IntEnable(INT_GPIOC); // Defined in hw_ints.h
}

// void IgnitionSwitch_Init(void)
//{
////    // Enable GPIOF peripheral
////    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
////    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
////        ;

////    // Configure PF4 as input with pull-up
////    GPIOPinTypeGPIOInput(SWITCH_PORT, SWITCH_PIN);
////    GPIOPadConfigSet(SWITCH_PORT, SWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//
//

//    SYSCTL->RCGCGPIO |= (1 << 2); 						// Clock to PortC
//    while ((SYSCTL->PRGPIO & (1 << 2)) == 0);	// Ensure Clock worked

//    GPIOC->DIR &= ~(1 << 5);      						// PC5 input
//    GPIOC->DEN |= (1 << 5);       						// Digital enable
//    GPIOC->PUR |= (1 << 5);       						// Pull-up

//    GPIOC->IS &= ~(1 << 5);       						// Edge sensitive
//    GPIOC->IEV &= ~(1 << 5);      						// Falling edge
//    GPIOC->ICR |= (1 << 5);       						// Clear flag
//    GPIOC->IM |= (1 << 5);        						// Unmask interrupt
//
//    NVIC->ISER[0] |= (1 << 2);      /* Enable IRQ2 (GPIOC) */
//}

bool IgnitionSwitch_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(SWITCH_PORT_BASE, SWITCH_PIN) == 0);
}
