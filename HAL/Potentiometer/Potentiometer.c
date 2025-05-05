#include "Potentiometer.h"
#include "ADC1.h"

extern volatile uint32_t speedValue;

void potentiometer_Init()
{
    ADC1_Init();
}
uint32_t potentiometer_ReadValue()
{
    speedValue = (ADC1_ReadValue() * 200) / 4095;
    return speedValue;
}
