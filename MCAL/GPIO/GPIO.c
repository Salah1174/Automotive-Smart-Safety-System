#include "gpio.h"
#include "inc/tm4c123gh6pm.h"

#define GPIO_DIR_MODE_OUT 1
#define GPIO_DIR_MODE_IN 0

    void DIO_Init(char port, uint8_t pins, uint32_t direction)
{
    volatile uint32_t delay;
    switch (port)
    {
    case 'A':
        SYSCTL_RCGCGPIO_R |= 0x01;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
        GPIO_PORTA_CR_R |= pins;
        GPIO_PORTA_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTA_DIR_R | pins) : (GPIO_PORTA_DIR_R & ~pins);
        GPIO_PORTA_DEN_R |= pins;
        GPIO_PORTA_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;

    case 'B':
        SYSCTL_RCGCGPIO_R |= 0x02;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
        GPIO_PORTB_CR_R |= pins;
        GPIO_PORTB_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTB_DIR_R | pins) : (GPIO_PORTB_DIR_R & ~pins);
        GPIO_PORTB_DEN_R |= pins;
        GPIO_PORTB_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;

    case 'C':
        SYSCTL_RCGCGPIO_R |= 0x04;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        GPIO_PORTC_CR_R |= pins;
        GPIO_PORTC_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTC_DIR_R | pins) : (GPIO_PORTC_DIR_R & ~pins);
        GPIO_PORTC_DEN_R |= pins;
        GPIO_PORTC_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;

    case 'D':
        SYSCTL_RCGCGPIO_R |= 0x08;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTD_LOCK_R = 0x4C4F434B;
        GPIO_PORTD_CR_R |= pins;
        GPIO_PORTD_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTD_DIR_R | pins) : (GPIO_PORTD_DIR_R & ~pins);
        GPIO_PORTD_DEN_R |= pins;
        GPIO_PORTD_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;

    case 'E':
        SYSCTL_RCGCGPIO_R |= 0x10;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTE_LOCK_R = 0x4C4F434B;
        GPIO_PORTE_CR_R |= pins;
        GPIO_PORTE_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTE_DIR_R | pins) : (GPIO_PORTE_DIR_R & ~pins);
        GPIO_PORTE_DEN_R |= pins;
        GPIO_PORTE_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;

    case 'F':
        SYSCTL_RCGCGPIO_R |= 0x20;
        delay = SYSCTL_RCGCGPIO_R;
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_CR_R |= 0x1F;
        GPIO_PORTF_DIR_R = (direction == GPIO_DIR_MODE_OUT) ? (GPIO_PORTF_DIR_R | pins) : (GPIO_PORTF_DIR_R & ~pins);
        GPIO_PORTF_DEN_R |= pins;
        GPIO_PORTF_PUR_R |= (direction == GPIO_DIR_MODE_IN) ? pins : 0;
        break;
    }
}

uint8_t GPIO_PinRead(char port, uint8_t pin)
{
    switch (port)
    {
    case 'A':
        return (GPIO_PORTA_DATA_R & pin) ? 1 : 0;
    case 'B':
        return (GPIO_PORTB_DATA_R & pin) ? 1 : 0;
    case 'C':
        return (GPIO_PORTC_DATA_R & pin) ? 1 : 0;
    case 'D':
        return (GPIO_PORTD_DATA_R & pin) ? 1 : 0;
    case 'E':
        return (GPIO_PORTE_DATA_R & pin) ? 1 : 0;
    case 'F':
        return (GPIO_PORTF_DATA_R & pin) ? 1 : 0;
    default:
        return 0;
    }
}

void DIO_Write(char port, uint8_t pin, uint8_t value)
{
    switch (port)
    {
    case 'A':
        if (value)
            GPIO_PORTA_DATA_R |= pin;
        else
            GPIO_PORTA_DATA_R &= ~pin;
        break;
    case 'B':
        if (value)
            GPIO_PORTB_DATA_R |= pin;
        else
            GPIO_PORTB_DATA_R &= ~pin;
        break;
    case 'C':
        if (value)
            GPIO_PORTC_DATA_R |= pin;
        else
            GPIO_PORTC_DATA_R &= ~pin;
        break;
    case 'D':
        if (value)
            GPIO_PORTD_DATA_R |= pin;
        else
            GPIO_PORTD_DATA_R &= ~pin;
        break;
    case 'E':
        if (value)
            GPIO_PORTE_DATA_R |= pin;
        else
            GPIO_PORTE_DATA_R &= ~pin;
        break;
    case 'F':
        if (value)
            GPIO_PORTF_DATA_R |= pin;
        else
            GPIO_PORTF_DATA_R &= ~pin;
        break;
    }
}

uint8_t GPIO_ReadPort(char port)
{
    switch (port)
    {
    case 'A':
        return GPIO_PORTA_DATA_R;
    case 'B':
        return GPIO_PORTB_DATA_R;
    case 'C':
        return GPIO_PORTC_DATA_R;
    case 'D':
        return GPIO_PORTD_DATA_R;
    case 'E':
        return GPIO_PORTE_DATA_R;
    case 'F':
        return GPIO_PORTF_DATA_R;
    default:
        return 0;
    }
}

void GPIO_WritePort(char port, uint8_t value)
{
    switch (port)
    {
    case 'A':
        GPIO_PORTA_DATA_R = value;
        break;
    case 'B':
        GPIO_PORTB_DATA_R = value;
        break;
    case 'C':
        GPIO_PORTC_DATA_R = value;
        break;
    case 'D':
        GPIO_PORTD_DATA_R = value;
        break;
    case 'E':
        GPIO_PORTE_DATA_R = value;
        break;
    case 'F':
        GPIO_PORTF_DATA_R = value;
        break;
    }
}
