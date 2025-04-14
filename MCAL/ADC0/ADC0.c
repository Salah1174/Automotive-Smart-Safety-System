#include "ADC0.h"
#include "TM4C123.h"

void ADC0_Init()
{
    SYSCTL->RCGCADC |= (1 << 0);  // Enable ADC0 clock
    SYSCTL->RCGCGPIO |= (1 << 4); // Enable clock for PORTE
    while ((SYSCTL->PRGPIO & (1 << 4)) == 0)
        ;

    for (volatile int i = 0; i < 1000; i++)
        ; // Delay for stabilization

    GPIOE->AFSEL |= (1 << 2); // Enable alternate function on PE2
    GPIOE->DEN &= ~(1 << 2);  // Disable digital function
    GPIOE->AMSEL |= (1 << 2); // Enable analog function

    ADC0->ACTSS &= ~(1 << 3);   // Disable SS3 during config
    ADC0->EMUX &= ~(0xF << 12); // Software trigger for SS3

    ADC0->SSMUX3 = 1;                   // AIN1 (PE2)
    ADC0->SSCTL3 = (1 << 1) | (1 << 2); // IE0, END0

    ADC0->IM &= ~(1 << 3);   // Disable SS3 interrupt
    ADC0->ACTSS |= (1 << 3); // Enable SS3
}

uint32_t ADC0_ReadValue(void)
{
    ADC0->PSSI |= (1 << 3); // Start conversion
    while ((ADC0->RIS & (1 << 3)) == 0)
        ; // Wait for completion

    uint32_t adc_value = ADC0->SSFIFO3 & 0xFFF; // Mask to 12 bits
    ADC0->ISC = (1 << 3);                       // Clear completion flag

    return adc_value;
}
