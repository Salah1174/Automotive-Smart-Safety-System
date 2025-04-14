#include "ADC.h"
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>

void delay_ms(uint32_t ms) {
    volatile uint32_t i;
    while (ms--) {
        for (i = 0; i < 4000; i++) {}
    }
}

int main(void) {
    ADC1_Init();
    uint32_t adcvalue = 0;

    while (1) {
        adcvalue = ADC1_ReadValue();
        // Place a breakpoint here and watch `adcvalue`
        delay_ms(1000);
    }

    return 0;
}
