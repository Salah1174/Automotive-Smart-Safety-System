#include "TM4C123.h"
#include "DIO.h"

#define PORT_BASE_ADDR(port) ( \
    (port == 'A') ? GPIOA_BASE : \
    (port == 'B') ? GPIOB_BASE : \
    (port == 'C') ? GPIOC_BASE : \
    (port == 'D') ? GPIOD_BASE : \
    (port == 'E') ? GPIOE_BASE : \
    GPIOF_BASE)

void DIO_Init(uint8_t port, uint8_t pin, DIO_PinDirection direction) {
    volatile uint32_t *baseAddr = (volatile uint32_t *)PORT_BASE_ADDR(port);
    volatile uint32_t *dirReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x400);
    volatile uint32_t *denReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x51C);
    volatile uint32_t *pdrReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x514);

    // Enable clock for the port (RCGCGPIO)
    SYSCTL->RCGCGPIO |= (1 << (port - 'A'));

    // Wait until the port is ready
    while ((SYSCTL->PRGPIO & (1 << (port - 'A'))) == 0);

    // Special unlock sequence for Port F if necessary
    if (port == 'F' && direction == DIO_PIN_INPUT) {
        GPIOF->LOCK = 0x4C4F434B;
        GPIOF->CR |= (1 << pin);
    }

    if (direction == DIO_PIN_OUTPUT) {
        *dirReg |= (1 << pin);     
    } else {
        *dirReg &= ~(1 << pin);    
        *pdrReg |= (1 << pin);     
    }

    *denReg |= (1 << pin);         
}



void DIO_WritePin(uint8_t port, uint8_t pin, uint8_t value) {
    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + (1 << (pin + 2)));
    *dataReg = value ? (1 << pin) : 0;
}

void DIO_WritePort(uint8_t port, uint8_t value) {
    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x3FC);
    *dataReg = value;
}


uint8_t DIO_ReadPin(uint8_t port, uint8_t pin) {
    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + (1 << (pin + 2)));
    return (*dataReg) ? 1 : 0;
}



uint8_t DIO_ReadPort(uint8_t port) {
    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x3FC);
    return (uint8_t)(*dataReg);
}
