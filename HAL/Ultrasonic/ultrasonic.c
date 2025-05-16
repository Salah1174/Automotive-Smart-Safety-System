#include "ultrasonic.h"
#include "Timer1.h"
#include "TM4C123.h"
#include <stdint.h>

#define TRIGGER_PIN (1 << 6) // PA6

extern volatile uint32_t distanceValue;

void PortA_Init(void)
{
    SYSCTL->RCGCGPIO |= (1 << 0); // Enable clock to GPIOA
    while ((SYSCTL->PRGPIO & (1 << 0)) == 0)
        ; // Wait until ready

    GPIOA->DIR |= TRIGGER_PIN;    // Set PA6 as output
    GPIOA->DEN |= TRIGGER_PIN;    // Enable digital on PA6
    GPIOA->AFSEL &= ~TRIGGER_PIN; // Disable alternate function
    GPIOA->PCTL &= ~(0x0F << 24); // Clear PCTL for PA6
    GPIOA->AMSEL &= ~TRIGGER_PIN; // Disable analog on PA6
}

void ultrasonic_Init()
{
    PortA_Init();  // Trigger pin (PA6)
    Timer1_Init(); // Echo pin (PB4 with edge-time capture)
}

uint32_t ultrasonic_ReadValue()
{
    uint32_t risingEdge, fallingEdge, pulseWidth;
    float distance;
    int timeout = 100000;

    // Send trigger pulse: 10us HIGH
    GPIOA->DATA &= ~TRIGGER_PIN; // Clear trigger
    for (volatile int i = 0; i < 100; i++)
        ;                       // Small delay
    GPIOA->DATA |= TRIGGER_PIN; // Set trigger high
    for (volatile int i = 0; i < 160; i++)
        ;                        // Approx 10us delay
    GPIOA->DATA &= ~TRIGGER_PIN; // Set trigger low

    // Wait for rising edge
    while ((TIMER1->RIS & (1 << 2)) == 0 && timeout--)
        ;
    if (timeout <= 0)
        return 0; // Or some default/error value
    risingEdge = TIMER1->TAR;
    TIMER1->ICR |= (1 << 2); // Clear capture flag

    // Wait for falling edge
    while ((TIMER1->RIS & (1 << 2)) == 0)
        ;
    fallingEdge = TIMER1->TAR;
    TIMER1->ICR |= (1 << 2); // Clear capture flag

    // Handle overflow
    if (fallingEdge > risingEdge)
        pulseWidth = fallingEdge - risingEdge;
    else
        pulseWidth = (0xFFFF - risingEdge) + fallingEdge;

    // Calculate distance in cm (Time in clock ticks at 16 MHz ? 1 tick = 62.5ns)
    distance = (pulseWidth * 0.0343) / 2; // Speed of sound is ~343 m/s
    distanceValue = (uint32_t)distance;
    return distanceValue;
}