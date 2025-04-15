#include <stdbool.h>
#include <stdint.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "..\MCAL\DIO\DIO.h"
#include "..\MCAL\Timer0\timer0.h"

void Buzzer_Init()
{
  DIO_Init('F', GPIO_PIN_3, GPIO_DIR_MODE_OUT);
}
void Buzzer_On()
{
    DIO_WritePin('F', GPIO_PIN_3, 1);
}

void Buzzer_Off()
{
    DIO_WritePin('F', GPIO_PIN_3, 0);
}


void Buzzer_Buzz(uint32_t frequency) {
    uint32_t periodMs = 1000 / frequency; 
    uint32_t halfPeriodMs = periodMs / 2; 

    // uint32_t cycles = durationMs / periodMs; //gam3t eno runs 3alatol mesh b duration mo3yna

    while (1){
        Buzzer_On(); 
        timer0B_delayMs(halfPeriodMs);
        Buzzer_Off(); 
        timer0B_delayMs(halfPeriodMs); 
    }
}