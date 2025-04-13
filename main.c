#include "DIO.h"
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

void delay_ms(uint32_t ms) {
    volatile uint32_t i;
    while (ms--) {
        for (i = 0; i < 4000; i++) {} 
    }
}

int main() {
    DIO_Init('F', 1, DIO_PIN_OUTPUT);  
    DIO_Init('F', 0, DIO_PIN_INPUT);   

    bool buttonPressed = false;

    while (true) {
        uint8_t input = DIO_ReadPin('F', 0);

        if (input == 1 && !buttonPressed) {
            delay_ms(20); 
            if (DIO_ReadPin('F', 0) == 1) {
                uint8_t current = DIO_ReadPin('F', 1);
                DIO_WritePin('F', 1, !current); 
                buttonPressed = true;
            }
        }

        if (input == 0) {
            buttonPressed = false;
        }
    }

    return 0;
}
