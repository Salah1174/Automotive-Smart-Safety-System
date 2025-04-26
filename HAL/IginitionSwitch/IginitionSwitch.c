#include "IginitionSwitch.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


#define SWITCH_PORT GPIO_PORTC_BASE
#define SWITCH_PIN GPIO_PIN_5

void IgnitionSwitch_Init(void)
{
//    // Enable GPIOF peripheral
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
//    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
//        ;

//    // Configure PF4 as input with pull-up
//    GPIOPinTypeGPIOInput(SWITCH_PORT, SWITCH_PIN);
//    GPIOPadConfigSet(SWITCH_PORT, SWITCH_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
		
		


    SYSCTL->RCGCGPIO |= (1 << 2); 						// Clock to PortC
    while ((SYSCTL->PRGPIO & (1 << 2)) == 0);	// Ensure Clock worked

    GPIOC->DIR &= ~(1 << 5);      						// PC5 input
    GPIOC->DEN |= (1 << 5);       						// Digital enable
    GPIOC->PUR |= (1 << 5);       						// Pull-up

    GPIOC->IS &= ~(1 << 5);       						// Edge sensitive
    GPIOC->IEV &= ~(1 << 5);      						// Falling edge
    GPIOC->ICR |= (1 << 5);       						// Clear flag
    GPIOC->IM |= (1 << 5);        						// Unmask interrupt
     
    NVIC->ISER[0] |= (1 << 2);      /* Enable IRQ2 (GPIOC) */
}
bool IgnitionSwitch_Read(void)
{
    // Return true if pressed (logic low)
    return (GPIOPinRead(SWITCH_PORT, SWITCH_PIN) == 0);
}
