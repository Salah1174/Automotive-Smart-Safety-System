#include "Timer1.h"
#include "TM4C123.h"
#include <stdint.h>

void Timer1_Init(void)
{
    // 1. Enable clock for Timer1 and GPIOB
    SYSCTL->RCGCTIMER |= (1 << 1); // Enable Timer1 clock
    SYSCTL->RCGCGPIO |= (1 << 1);  // Enable GPIOB clock
    while ((SYSCTL->PRTIMER & (1 << 1)) == 0)
        ; // Wait for Timer1 ready
    while ((SYSCTL->PRGPIO & (1 << 1)) == 0)
        ; // Wait for GPIOB ready

    // 2. Configure PB4 (T1CCP0) for timer input capture
    GPIOB->DIR &= ~(1 << 4);    // PB4 as input
    GPIOB->AFSEL |= (1 << 4);   // Enable alternate function on PB4
    GPIOB->PCTL &= ~0x000F0000; // Clear PCTL bits for PB4
    GPIOB->PCTL |= 0x00070000;  // Configure PB4 as T1CCP0
    GPIOB->DEN |= (1 << 4);     // Enable digital function on PB4

    // 3. Disable Timer1A before configuration
    TIMER1->CTL &= ~(1 << 0); // Disable Timer1A

    // 4. Configure Timer1A for 16-bit, capture mode
    TIMER1->CFG = 0x00000004; // 16-bit timer configuration
    TIMER1->TAMR = 0x17;      // Timer A Mode: Capture | Edge-Time | Count-Up

    // 5. Capture on both edges (rising and falling)
    TIMER1->CTL &= ~(0x3 << 2); // Clear TAEVENT bits
    TIMER1->CTL |= (0x3 << 2);  // Both edges

    // 6. Set timer interval (not required in edge-time mode, but good practice)
    TIMER1->TAILR = 0xFFFF; // Max count for 16-bit

    // 7. Clear any pending interrupts and optionally enable capture interrupt
    TIMER1->ICR = (1 << 2); // Clear capture event interrupt

    // Optional: Enable interrupt (commented out if polling is used)
    // TIMER1->IMR |= (1 << 2);             // Unmask capture match interrupt
    // NVIC_EnableIRQ(TIMER1A_IRQn);       // Enable IRQ in NVIC

    // 8. Enable Timer1A
    TIMER1->CTL |= (1 << 0); // Enable Timer1A
}
