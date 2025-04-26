#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "Buzzer.h"

#define BUZZER_PORT GPIO_PORTE_BASE
#define BUZZER_PIN GPIO_PIN_3
void delay_(uint32_t ms)
{
    volatile uint32_t i;
    while (ms--)
    {
        for (i = 0; i < 4000; i++)
        {
        }
    }
}
void Buzzer_Init()
{
    // Enable the peripheral for GPIO Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;

    // Configure Pin 2 on Port F as output
    GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);
}

void Buzzer_On()
{
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, BUZZER_PIN); // Set PF2 high
}

void Buzzer_Off()
{
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0x00); // Set PF2 low
}

 void Buzzer_Buzz(uint32_t frequency) {
    uint32_t periodMs = 1000 / frequency;
    uint32_t halfPeriodMs = periodMs / 2;

    // uint32_t cycles = durationMs / periodMs; //gam3t eno runs 3alatol mesh b duration mo3yna

    while (1){
        Buzzer_On();
        delay_(frequency);
        Buzzer_Off();
        delay_(frequency);
    }
}