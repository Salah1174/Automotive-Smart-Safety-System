#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>

void delay(void) {
    volatile uint32_t i;
    for (i = 0; i < 200000; i++) {
    }
}

int main()
{
    SYSCTL->RCGCGPIO |= 0x20; 
    while ((SYSCTL->PRGPIO & 0x20) == 0)
		{
    }
    GPIOF->DIR |= 0x02;
    GPIOF->DEN |= 0x02;
    while (true)
    {
        GPIOF->DATA ^= 0x02;  
        delay();
    }
    return 0;
}
