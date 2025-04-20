#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void DIO_Init(char port, uint8_t pins, uint32_t direction);
uint8_t GPIO_PinRead(char port, uint8_t pin);
void DIO_Write(char port, uint8_t pin, uint8_t value);
uint8_t GPIO_ReadPort(char port);
void GPIO_WritePort(char port, uint8_t value);

#endif
