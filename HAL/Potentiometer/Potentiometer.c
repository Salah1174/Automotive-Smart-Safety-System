#include "Potentiometer.h"
#include "ADC1.h"
void potentiometer_Init()
{
ADC1_Init();
}
uint32_t potentiometer_ReadValue()
{
uint32_t speedValue = ADC1_ReadValue();
return speedValue;
}
