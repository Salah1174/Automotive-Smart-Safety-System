#include "ultrasonic.h""
#include "ADC0.h"
void ultrasonic_Init()
{
ADC0_Init();
}
uint32_t ultrasonic_ReadValue()
{
uint32_t distanceValue = ADC0_ReadValue();
return distanceValue;
}
	