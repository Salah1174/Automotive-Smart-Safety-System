#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>
#include <stdint.h>

void Buzzer_Init();
void Buzzer_On();
void Buzzer_Off();
void Buzzer_Buzz(uint32_t frequency);

#endif