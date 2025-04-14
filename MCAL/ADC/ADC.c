#include "ADC.h"
#include "TM4C123.h"

void ADC1_Init()
{
    SYSCTL->RCGCADC |= (1 << 1);        // Enable ADC1 clock
    SYSCTL->RCGCGPIO |= (1 << 3);       // Enable clock for PORTD
    while ((SYSCTL->PRGPIO & (1 << 3)) == 0);
    //while ((SYSCTL->PRADC & (1 << 1)) == 0);
    
    for (volatile int i = 0; i < 1000; i++); // Delay for stabilization
    
    GPIOD->AFSEL |= (1 << 1);           // Enable alternate function on PD1
    GPIOD->DEN &= ~(1 << 1);            // Disable digital function
    GPIOD->AMSEL |= (1 << 1);           // Enable analog function
    
    ADC1->ACTSS &= ~(1 << 3);           // Disable SS3 during config
    ADC1->EMUX &= ~(0xF << 12);         // Software trigger for SS3
    
    ADC1->SSMUX3 = 6;                   // AIN6 (PD1)
    ADC1->SSCTL3 = (1 << 1) | (1 << 2); // IE0, END0
    
    ADC1->IM &= ~(1 << 3);              // Disable SS3 interrupt
    ADC1->ACTSS |= (1 << 3);            // Enable SS3
}

uint32_t ADC1_ReadValue(void)
{
    ADC1->PSSI |= (1 << 3);                 // Start conversion
    while ((ADC1->RIS & (1 << 3)) == 0);    // Wait for completion
    
    uint32_t adc_value = ADC1->SSFIFO3 & 0xFFF; // Mask to 12 bits
    ADC1->ISC = (1 << 3);                   // Clear completion flag
    
    return adc_value;
}
