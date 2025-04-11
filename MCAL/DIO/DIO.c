//#include "DIO.h"
//
//#define PORTA_BASE 0x40004000
//#define PORTB_BASE 0x40005000
//#define PORTC_BASE 0x40006000
//#define PORTD_BASE 0x40007000
//#define PORTE_BASE 0x40024000
//#define PORTF_BASE 0x40025000
//
//#define PORT_BASE_ADDR(port) ( \
//    (port == 'A') ? PORTA_BASE : \
//    (port == 'B') ? PORTB_BASE : \
//    (port == 'C') ? PORTC_BASE : \
//    (port == 'D') ? PORTD_BASE : \
//    (port == 'E') ? PORTE_BASE : \
//    PORTF_BASE)
//
//void DIO_Init(uint8_t port, uint8_t pin, DIO_PinDirection direction) {
//    volatile uint32_t *dirReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x400);
//    volatile uint32_t *denReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x51C);
//
//    // Enable clock for the port (RCGCGPIO)
//    SYSCTL_RCGCGPIO_R |= (1 << (port - 'A'));
//
//    // Small delay to ensure clock is stable
//    for (volatile int i = 0; i < 5; i++) {}
//
//    // Special unlock sequence for Port F if necessary
//    if (port == 'F') {
//        GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock Port F
//        GPIO_PORTF_CR_R |= (1 << pin);   // Allow changes to the specified pin
//    }
//
//    // Wait for the port to be ready
//    //while ((SYSCTL_PRGPIO_R & (1 << (port - 'A'))) == 0) {}
//
//    // Set pin direction
//    if (direction == DIO_PIN_OUTPUT) {
//        *dirReg |= (1 << pin);  // Set as output
//    } else {
//        *dirReg &= ~(1 << pin); // Set as input
//    }
//
//    // Enable digital function
//    *denReg |= (1 << pin);
//}
//
//
//void DIO_WritePin(uint8_t port, uint8_t pin, uint8_t value) {
//    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + (1 << (pin + 2)));
//    *dataReg = value ? 0xFF : 0x00;
//}
//
//void DIO_WritePort(uint8_t port, uint8_t value) {
//    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x3FC);
//    *dataReg = value;
//}
//
//uint8_t DIO_ReadPin(uint8_t port, uint8_t pin) {
//    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + (1 << (pin + 2)));
//    return (*dataReg) ? 1 : 0;
//}
//
//uint8_t DIO_ReadPort(uint8_t port) {
//    volatile uint32_t *dataReg = (volatile uint32_t *)(PORT_BASE_ADDR(port) + 0x3FC);
//    return (uint8_t)(*dataReg);
//}
