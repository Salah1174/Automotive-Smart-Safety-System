/*
 * GPIO.c

 *
 *  Created on: Nov 20, 2019
 *      Author: Ahmed Magdy
 */
#include "util.h"
#include "stdtypes.h"
#include "GPIO_new.h"
unsigned long delay_A;
unsigned long delay_B;
unsigned long delay_C;
unsigned long delay_D;
unsigned long delay_E;
unsigned long delay_F;

void GPIO_Initialize_Port(PORT_ID port)
{
    if (port <= PF)
    {
        switch (port)
        {
        case PA:
            SET_BIT(RCGCGPIO, 0);    // Active Clock Of PORTA
            delay_A = RCGCGPIO;      // Delay
            GPIOLOCK_A = 0x4C4F434B; // UNLOCK PORTA
            SET_BIT(GPIOCR_A, 0);    ////Enable PORTA PIN
            SET_BIT(GPIOCR_A, 1);
            SET_BIT(GPIOCR_A, 2);
            SET_BIT(GPIOCR_A, 3);
            SET_BIT(GPIOCR_A, 4);
            SET_BIT(GPIOCR_A, 5);
            SET_BIT(GPIOCR_A, 6);
            SET_BIT(GPIOCR_A, 7);
            CLR_BIT(GPIOMSEL_A, 0);
            CLR_BIT(GPIOMSEL_A, 1);
            CLR_BIT(GPIOMSEL_A, 2);
            CLR_BIT(GPIOMSEL_A, 3);
            CLR_BIT(GPIOMSEL_A, 4);
            CLR_BIT(GPIOMSEL_A, 5);
            CLR_BIT(GPIOMSEL_A, 6);
            CLR_BIT(GPIOMSEL_A, 7);
            GPIOPCTL_A = 0x00000000;
            CLR_BIT(GPIOAFSEL_A, 0); // Disable Alternative Function Of PORTA
            CLR_BIT(GPIOAFSEL_A, 1);
            CLR_BIT(GPIOAFSEL_A, 2);
            CLR_BIT(GPIOAFSEL_A, 3);
            CLR_BIT(GPIOAFSEL_A, 4);
            CLR_BIT(GPIOAFSEL_A, 5);
            CLR_BIT(GPIOAFSEL_A, 6);
            CLR_BIT(GPIOAFSEL_A, 7);

            SET_BIT(GPIODEN_A, 0); // enable GPIO PORTA PEripheral
            SET_BIT(GPIODEN_A, 1);
            SET_BIT(GPIODEN_A, 2);
            SET_BIT(GPIODEN_A, 3);
            SET_BIT(GPIODEN_A, 4);
            SET_BIT(GPIODEN_A, 5);
            SET_BIT(GPIODEN_A, 6);
            SET_BIT(GPIODEN_A, 7);
            break;
        case PB:

            SET_BIT(RCGCGPIO, 1);    // Active Clock Of PORTB
            delay_B = RCGCGPIO;      // Delay
            GPIOLOCK_B = 0x4C4F434B; // UNLOCK PORTB
            SET_BIT(GPIOCR_B, 0);    ////Enable PORTB PIN
            SET_BIT(GPIOCR_B, 1);
            SET_BIT(GPIOCR_B, 2);
            SET_BIT(GPIOCR_B, 3);
            SET_BIT(GPIOCR_B, 4);
            SET_BIT(GPIOCR_B, 5);
            SET_BIT(GPIOCR_B, 6);
            SET_BIT(GPIOCR_B, 7);
            CLR_BIT(GPIOMSEL_B, 0);
            CLR_BIT(GPIOMSEL_B, 1);
            CLR_BIT(GPIOMSEL_B, 2);
            CLR_BIT(GPIOMSEL_B, 3);
            CLR_BIT(GPIOMSEL_B, 4);
            CLR_BIT(GPIOMSEL_B, 5);
            CLR_BIT(GPIOMSEL_B, 6);
            CLR_BIT(GPIOMSEL_B, 7);
            GPIOPCTL_B = 0x00000000;
            CLR_BIT(GPIOAFSEL_B, 0); // Disable Alternative Function Of PORTB
            CLR_BIT(GPIOAFSEL_B, 1);
            CLR_BIT(GPIOAFSEL_B, 2);
            CLR_BIT(GPIOAFSEL_B, 3);
            CLR_BIT(GPIOAFSEL_B, 4);
            CLR_BIT(GPIOAFSEL_B, 5);
            CLR_BIT(GPIOAFSEL_B, 6);
            CLR_BIT(GPIOAFSEL_B, 7);

            SET_BIT(GPIODEN_B, 0); // enable GPIO PEripheral
            SET_BIT(GPIODEN_B, 1);
            SET_BIT(GPIODEN_B, 2);
            SET_BIT(GPIODEN_B, 3);
            SET_BIT(GPIODEN_B, 4);
            SET_BIT(GPIODEN_B, 5);
            SET_BIT(GPIODEN_B, 6);
            SET_BIT(GPIODEN_B, 7);
            break;
        case PC:

            SET_BIT(RCGCGPIO, 2);    // Active Clock Of PORTC
            delay_C = RCGCGPIO;      // Delay
            GPIOLOCK_C = 0x4C4F434B; // UNLOCK PORTC
            SET_BIT(GPIOCR_C, 0);    ////Enable PORTC PIN
            SET_BIT(GPIOCR_C, 1);
            SET_BIT(GPIOCR_C, 2);
            SET_BIT(GPIOCR_C, 3);
            SET_BIT(GPIOCR_C, 4);
            SET_BIT(GPIOCR_C, 5);
            SET_BIT(GPIOCR_C, 6);
            SET_BIT(GPIOCR_C, 7);
            CLR_BIT(GPIOMSEL_C, 0);
            CLR_BIT(GPIOMSEL_C, 1);
            CLR_BIT(GPIOMSEL_C, 2);
            CLR_BIT(GPIOMSEL_C, 3);
            CLR_BIT(GPIOMSEL_C, 4);
            CLR_BIT(GPIOMSEL_C, 5);
            CLR_BIT(GPIOMSEL_C, 6);
            CLR_BIT(GPIOMSEL_C, 7);
            GPIOPCTL_C = 0x00000000;
            CLR_BIT(GPIOAFSEL_C, 0); // Disable Alternative Function Of PORTC
            CLR_BIT(GPIOAFSEL_C, 1);
            CLR_BIT(GPIOAFSEL_C, 2);
            CLR_BIT(GPIOAFSEL_C, 3);
            CLR_BIT(GPIOAFSEL_C, 4);
            CLR_BIT(GPIOAFSEL_C, 5);
            CLR_BIT(GPIOAFSEL_C, 6);
            CLR_BIT(GPIOAFSEL_C, 7);

            SET_BIT(GPIODEN_C, 0); // enable GPIO PEripheral
            SET_BIT(GPIODEN_C, 1);
            SET_BIT(GPIODEN_C, 2);
            SET_BIT(GPIODEN_C, 3);
            SET_BIT(GPIODEN_C, 4);
            SET_BIT(GPIODEN_C, 5);
            SET_BIT(GPIODEN_C, 6);
            SET_BIT(GPIODEN_C, 7);
            break;
        case PD:
            SET_BIT(RCGCGPIO, 3); // Active Clock Of PORTD
            delay_D = RCGCGPIO;
            GPIOLOCK_D = 0x4C4F434B;
            SET_BIT(GPIOCR_D, 0); ////Enable PORTD PIN
            SET_BIT(GPIOCR_D, 1);
            SET_BIT(GPIOCR_D, 2);
            SET_BIT(GPIOCR_D, 3);
            SET_BIT(GPIOCR_D, 4);
            SET_BIT(GPIOCR_D, 5);
            SET_BIT(GPIOCR_D, 6);
            SET_BIT(GPIOCR_D, 7);
            CLR_BIT(GPIOMSEL_D, 0);
            CLR_BIT(GPIOMSEL_D, 1);
            CLR_BIT(GPIOMSEL_D, 2);
            CLR_BIT(GPIOMSEL_D, 3);
            CLR_BIT(GPIOMSEL_D, 4);
            CLR_BIT(GPIOMSEL_D, 5);
            CLR_BIT(GPIOMSEL_D, 6);
            CLR_BIT(GPIOMSEL_D, 7);
            GPIOPCTL_D = 0x00000000;
            CLR_BIT(GPIOAFSEL_D, 0); // Disable Alternative Function Of PORTD
            CLR_BIT(GPIOAFSEL_D, 1);
            CLR_BIT(GPIOAFSEL_D, 2);
            CLR_BIT(GPIOAFSEL_D, 3);
            CLR_BIT(GPIOAFSEL_D, 4);
            CLR_BIT(GPIOAFSEL_D, 5);
            CLR_BIT(GPIOAFSEL_D, 6);
            CLR_BIT(GPIOAFSEL_D, 7);
            SET_BIT(GPIODEN_D, 0); // enable GPIO PEripheral
            SET_BIT(GPIODEN_D, 1);
            SET_BIT(GPIODEN_D, 2);
            SET_BIT(GPIODEN_D, 3);
            SET_BIT(GPIODEN_D, 4);
            SET_BIT(GPIODEN_D, 5);
            SET_BIT(GPIODEN_D, 6);
            SET_BIT(GPIODEN_D, 7);
            // Delay
            // UNLOCK PORTD

            break;
        case PE:

            SET_BIT(RCGCGPIO, 4);    // Active Clock Of PORTE
            delay_E = RCGCGPIO;      // Delay
            GPIOLOCK_E = 0x4C4F434B; // UNLOCK PORTE
            SET_BIT(GPIOCR_E, 0);    ////Enable PORTE PIN
            SET_BIT(GPIOCR_E, 1);
            SET_BIT(GPIOCR_E, 2);
            SET_BIT(GPIOCR_E, 3);
            SET_BIT(GPIOCR_E, 4);
            SET_BIT(GPIOCR_E, 5);
            CLR_BIT(GPIOMSEL_E, 0);
            CLR_BIT(GPIOMSEL_E, 1);
            CLR_BIT(GPIOMSEL_E, 2);
            CLR_BIT(GPIOMSEL_E, 3);
            CLR_BIT(GPIOMSEL_E, 4);
            CLR_BIT(GPIOMSEL_E, 5);
            GPIOPCTL_E = 0x00000000;
            CLR_BIT(GPIOAFSEL_E, 0); // Disable Alternative Function Of PORTE
            CLR_BIT(GPIOAFSEL_E, 1);
            CLR_BIT(GPIOAFSEL_E, 2);
            CLR_BIT(GPIOAFSEL_E, 3);
            CLR_BIT(GPIOAFSEL_E, 4);
            CLR_BIT(GPIOAFSEL_E, 5);
            SET_BIT(GPIODEN_E, 0); // enable GPIO PEripheral
            SET_BIT(GPIODEN_E, 1);
            SET_BIT(GPIODEN_E, 2);
            SET_BIT(GPIODEN_E, 3);
            SET_BIT(GPIODEN_E, 4);
            SET_BIT(GPIODEN_E, 5);
            CLR_BIT(GPIODEN_E, 6);
            CLR_BIT(GPIODEN_E, 7);
            break;
        case PF:
            SET_BIT(RCGCGPIO, 5);    // Active Clock Of PORTF
            delay_F = RCGCGPIO;      // Delay
            GPIOLOCK_F = 0x4C4F434B; // UNLOCK PORTF
            SET_BIT(GPIOCR_F, 0);    ////Enable PORTF PIN
            SET_BIT(GPIOCR_F, 1);
            SET_BIT(GPIOCR_F, 2);
            SET_BIT(GPIOCR_F, 3);
            SET_BIT(GPIOCR_F, 4);
            CLR_BIT(GPIOMSEL_F, 0);
            CLR_BIT(GPIOMSEL_F, 1);
            CLR_BIT(GPIOMSEL_F, 2);
            CLR_BIT(GPIOMSEL_F, 3);
            CLR_BIT(GPIOMSEL_F, 4);
            GPIOPCTL_F = 0x00000000;
            CLR_BIT(GPIOAFSEL_F, 0); // Disable Alternative Function Of PORTF
            CLR_BIT(GPIOAFSEL_F, 1);
            CLR_BIT(GPIOAFSEL_F, 2);
            CLR_BIT(GPIOAFSEL_F, 3);
            CLR_BIT(GPIOAFSEL_F, 4);
            SET_BIT(GPIODEN_F, 0); // enable GPIO PEripheral
            SET_BIT(GPIODEN_F, 1);
            SET_BIT(GPIODEN_F, 2);
            SET_BIT(GPIODEN_F, 3);
            SET_BIT(GPIODEN_F, 4);
            CLR_BIT(GPIODEN_F, 5);
            CLR_BIT(GPIODEN_F, 6);
            CLR_BIT(GPIODEN_F, 7);

            break;
        }
    }
}

void GPIO_Set_Pin_Direction(PORT_ID port, PIN_ID pin, DIRECTION_ID direction)
{
    if ((port <= PF) && (pin <= PIN7))
    {
        switch (direction)
        {
        case OUT:
            switch (port)
            {
            case PA:
                SET_BIT(GPIODIR_A, pin);

                break;
            case PB:
                SET_BIT(GPIODIR_B, pin);
                break;
            case PC:
                SET_BIT(GPIODIR_C, pin);
                break;
            case PD:
                SET_BIT(GPIODIR_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    SET_BIT(GPIODIR_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    SET_BIT(GPIODIR_F, pin);
                }
                break;
            }
            break;
        case INFREE:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, pin);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, pin);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, pin);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    CLR_BIT(GPIODIR_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    CLR_BIT(GPIODIR_F, pin);
                }
                break;
            }
            break;
        case INPULLUP:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, pin);
                SET_BIT(GPIOPUR_A, pin);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, pin);
                SET_BIT(GPIOPUR_B, pin);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, pin);
                SET_BIT(GPIOPUR_C, pin);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, pin);
                SET_BIT(GPIOPUR_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    CLR_BIT(GPIODIR_E, pin);
                    SET_BIT(GPIOPUR_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    CLR_BIT(GPIODIR_F, pin);
                    SET_BIT(GPIOPUR_F, pin);
                }
                break;
            }
            break;
        case INPULLDOWN:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, pin);
                SET_BIT(GPIOPDR_A, pin);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, pin);
                SET_BIT(GPIOPDR_B, pin);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, pin);
                SET_BIT(GPIOPDR_C, pin);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, pin);
                SET_BIT(GPIOPDR_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    CLR_BIT(GPIODIR_E, pin);
                    SET_BIT(GPIOPDR_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    CLR_BIT(GPIODIR_F, pin);
                    SET_BIT(GPIOPDR_F, pin);
                }
                break;
            }
            break;
        }
    }
}

void GPIO_Set_Port_Direction(PORT_ID port, DIRECTION_ID direction)
{
    if (port <= PF)
    {
        switch (direction)
        {
        case OUT:
            switch (port)
            {
            case PA:
                SET_BIT(GPIODIR_A, 0);
                SET_BIT(GPIODIR_A, 1);
                SET_BIT(GPIODIR_A, 2);
                SET_BIT(GPIODIR_A, 3);
                SET_BIT(GPIODIR_A, 4);
                SET_BIT(GPIODIR_A, 5);
                SET_BIT(GPIODIR_A, 6);
                SET_BIT(GPIODIR_A, 7);
                break;
            case PB:
                SET_BIT(GPIODIR_B, 0);
                SET_BIT(GPIODIR_B, 1);
                SET_BIT(GPIODIR_B, 2);
                SET_BIT(GPIODIR_B, 3);
                SET_BIT(GPIODIR_B, 4);
                SET_BIT(GPIODIR_B, 5);
                SET_BIT(GPIODIR_B, 6);
                SET_BIT(GPIODIR_B, 7);
                break;
            case PC:
                SET_BIT(GPIODIR_C, 0);
                SET_BIT(GPIODIR_C, 1);
                SET_BIT(GPIODIR_C, 2);
                SET_BIT(GPIODIR_C, 3);
                SET_BIT(GPIODIR_C, 4);
                SET_BIT(GPIODIR_C, 5);
                SET_BIT(GPIODIR_C, 6);
                SET_BIT(GPIODIR_C, 7);
                break;
            case PD:
                SET_BIT(GPIODIR_D, 0);
                SET_BIT(GPIODIR_D, 1);
                SET_BIT(GPIODIR_D, 2);
                SET_BIT(GPIODIR_D, 3);
                SET_BIT(GPIODIR_D, 4);
                SET_BIT(GPIODIR_D, 5);
                SET_BIT(GPIODIR_D, 6);
                SET_BIT(GPIODIR_D, 7);
                break;
            case PE:
                SET_BIT(GPIODIR_E, 0);
                SET_BIT(GPIODIR_E, 1);
                SET_BIT(GPIODIR_E, 2);
                SET_BIT(GPIODIR_E, 3);
                SET_BIT(GPIODIR_E, 4);
                SET_BIT(GPIODIR_E, 5);
                break;
            case PF:
                SET_BIT(GPIODIR_F, 0);
                SET_BIT(GPIODIR_F, 1);
                SET_BIT(GPIODIR_F, 2);
                SET_BIT(GPIODIR_F, 3);
                SET_BIT(GPIODIR_F, 4);
                break;
            }
            break;
        case INFREE:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, 0);
                CLR_BIT(GPIODIR_A, 1);
                CLR_BIT(GPIODIR_A, 2);
                CLR_BIT(GPIODIR_A, 3);
                CLR_BIT(GPIODIR_A, 4);
                CLR_BIT(GPIODIR_A, 5);
                CLR_BIT(GPIODIR_A, 6);
                CLR_BIT(GPIODIR_A, 7);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, 0);
                CLR_BIT(GPIODIR_B, 1);
                CLR_BIT(GPIODIR_B, 2);
                CLR_BIT(GPIODIR_B, 3);
                CLR_BIT(GPIODIR_B, 4);
                CLR_BIT(GPIODIR_B, 5);
                CLR_BIT(GPIODIR_B, 6);
                CLR_BIT(GPIODIR_B, 7);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, 0);
                CLR_BIT(GPIODIR_C, 1);
                CLR_BIT(GPIODIR_C, 2);
                CLR_BIT(GPIODIR_C, 3);
                CLR_BIT(GPIODIR_C, 4);
                CLR_BIT(GPIODIR_C, 5);
                CLR_BIT(GPIODIR_C, 6);
                CLR_BIT(GPIODIR_C, 7);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, 0);
                CLR_BIT(GPIODIR_D, 1);
                CLR_BIT(GPIODIR_D, 2);
                CLR_BIT(GPIODIR_D, 3);
                CLR_BIT(GPIODIR_D, 4);
                CLR_BIT(GPIODIR_D, 5);
                CLR_BIT(GPIODIR_D, 6);
                CLR_BIT(GPIODIR_D, 7);
                break;
            case PE:
                CLR_BIT(GPIODIR_E, 0);
                CLR_BIT(GPIODIR_E, 1);
                CLR_BIT(GPIODIR_E, 2);
                CLR_BIT(GPIODIR_E, 3);
                CLR_BIT(GPIODIR_E, 4);
                CLR_BIT(GPIODIR_E, 5);
                break;
            case PF:
                CLR_BIT(GPIODIR_F, 0);
                CLR_BIT(GPIODIR_F, 1);
                CLR_BIT(GPIODIR_F, 2);
                CLR_BIT(GPIODIR_F, 3);
                CLR_BIT(GPIODIR_F, 4);
                break;
            }
            break;
        case INPULLDOWN:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, 0);
                CLR_BIT(GPIODIR_A, 1);
                CLR_BIT(GPIODIR_A, 2);
                CLR_BIT(GPIODIR_A, 3);
                CLR_BIT(GPIODIR_A, 4);
                CLR_BIT(GPIODIR_A, 5);
                CLR_BIT(GPIODIR_A, 6);
                CLR_BIT(GPIODIR_A, 7);
                SET_BIT(GPIOPDR_A, 0);
                SET_BIT(GPIOPDR_A, 1);
                SET_BIT(GPIOPDR_A, 2);
                SET_BIT(GPIOPDR_A, 3);
                SET_BIT(GPIOPDR_A, 4);
                SET_BIT(GPIOPDR_A, 5);
                SET_BIT(GPIOPDR_A, 6);
                SET_BIT(GPIOPDR_A, 7);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, 0);
                CLR_BIT(GPIODIR_B, 1);
                CLR_BIT(GPIODIR_B, 2);
                CLR_BIT(GPIODIR_B, 3);
                CLR_BIT(GPIODIR_B, 4);
                CLR_BIT(GPIODIR_B, 5);
                CLR_BIT(GPIODIR_B, 6);
                CLR_BIT(GPIODIR_B, 7);
                SET_BIT(GPIOPDR_B, 0);
                SET_BIT(GPIOPDR_B, 1);
                SET_BIT(GPIOPDR_B, 2);
                SET_BIT(GPIOPDR_B, 3);
                SET_BIT(GPIOPDR_B, 4);
                SET_BIT(GPIOPDR_B, 5);
                SET_BIT(GPIOPDR_B, 6);
                SET_BIT(GPIOPDR_B, 7);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, 0);
                CLR_BIT(GPIODIR_C, 1);
                CLR_BIT(GPIODIR_C, 2);
                CLR_BIT(GPIODIR_C, 3);
                CLR_BIT(GPIODIR_C, 4);
                CLR_BIT(GPIODIR_C, 5);
                CLR_BIT(GPIODIR_C, 6);
                CLR_BIT(GPIODIR_C, 7);
                SET_BIT(GPIOPDR_C, 0);
                SET_BIT(GPIOPDR_C, 1);
                SET_BIT(GPIOPDR_C, 2);
                SET_BIT(GPIOPDR_C, 3);
                SET_BIT(GPIOPDR_C, 4);
                SET_BIT(GPIOPDR_C, 5);
                SET_BIT(GPIOPDR_C, 6);
                SET_BIT(GPIOPDR_C, 7);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, 0);
                CLR_BIT(GPIODIR_D, 1);
                CLR_BIT(GPIODIR_D, 2);
                CLR_BIT(GPIODIR_D, 3);
                CLR_BIT(GPIODIR_D, 4);
                CLR_BIT(GPIODIR_D, 5);
                CLR_BIT(GPIODIR_D, 6);
                CLR_BIT(GPIODIR_D, 7);
                SET_BIT(GPIOPDR_D, 0);
                SET_BIT(GPIOPDR_D, 1);
                SET_BIT(GPIOPDR_D, 2);
                SET_BIT(GPIOPDR_D, 3);
                SET_BIT(GPIOPDR_D, 4);
                SET_BIT(GPIOPDR_D, 5);
                SET_BIT(GPIOPDR_D, 6);
                SET_BIT(GPIOPDR_D, 7);
                break;
            case PE:
                CLR_BIT(GPIODIR_E, 0);
                CLR_BIT(GPIODIR_E, 1);
                CLR_BIT(GPIODIR_E, 2);
                CLR_BIT(GPIODIR_E, 3);
                CLR_BIT(GPIODIR_E, 4);
                CLR_BIT(GPIODIR_E, 5);
                SET_BIT(GPIOPDR_E, 0);
                SET_BIT(GPIOPDR_E, 1);
                SET_BIT(GPIOPDR_E, 2);
                SET_BIT(GPIOPDR_E, 3);
                SET_BIT(GPIOPDR_E, 4);
                SET_BIT(GPIOPDR_E, 5);
                break;
            case PF:
                CLR_BIT(GPIODIR_F, 0);
                CLR_BIT(GPIODIR_F, 1);
                CLR_BIT(GPIODIR_F, 2);
                CLR_BIT(GPIODIR_F, 3);
                CLR_BIT(GPIODIR_F, 4);
                SET_BIT(GPIOPDR_F, 0);
                SET_BIT(GPIOPDR_F, 1);
                SET_BIT(GPIOPDR_F, 2);
                SET_BIT(GPIOPDR_F, 3);
                SET_BIT(GPIOPDR_F, 4);
                break;
            }
            break;
        case INPULLUP:
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODIR_A, 0);
                CLR_BIT(GPIODIR_A, 1);
                CLR_BIT(GPIODIR_A, 2);
                CLR_BIT(GPIODIR_A, 3);
                CLR_BIT(GPIODIR_A, 4);
                CLR_BIT(GPIODIR_A, 5);
                CLR_BIT(GPIODIR_A, 6);
                CLR_BIT(GPIODIR_A, 7);
                SET_BIT(GPIOPUR_A, 0);
                SET_BIT(GPIOPUR_A, 1);
                SET_BIT(GPIOPUR_A, 2);
                SET_BIT(GPIOPUR_A, 3);
                SET_BIT(GPIOPUR_A, 4);
                SET_BIT(GPIOPUR_A, 5);
                SET_BIT(GPIOPUR_A, 6);
                SET_BIT(GPIOPUR_A, 7);
                break;
            case PB:
                CLR_BIT(GPIODIR_B, 0);
                CLR_BIT(GPIODIR_B, 1);
                CLR_BIT(GPIODIR_B, 2);
                CLR_BIT(GPIODIR_B, 3);
                CLR_BIT(GPIODIR_B, 4);
                CLR_BIT(GPIODIR_B, 5);
                CLR_BIT(GPIODIR_B, 6);
                CLR_BIT(GPIODIR_B, 7);
                SET_BIT(GPIOPUR_B, 0);
                SET_BIT(GPIOPUR_B, 1);
                SET_BIT(GPIOPUR_B, 2);
                SET_BIT(GPIOPUR_B, 3);
                SET_BIT(GPIOPUR_B, 4);
                SET_BIT(GPIOPUR_B, 5);
                SET_BIT(GPIOPUR_B, 6);
                SET_BIT(GPIOPUR_B, 7);
                break;
            case PC:
                CLR_BIT(GPIODIR_C, 0);
                CLR_BIT(GPIODIR_C, 1);
                CLR_BIT(GPIODIR_C, 2);
                CLR_BIT(GPIODIR_C, 3);
                CLR_BIT(GPIODIR_C, 4);
                CLR_BIT(GPIODIR_C, 5);
                CLR_BIT(GPIODIR_C, 6);
                CLR_BIT(GPIODIR_C, 7);
                SET_BIT(GPIOPUR_C, 0);
                SET_BIT(GPIOPUR_C, 1);
                SET_BIT(GPIOPUR_C, 2);
                SET_BIT(GPIOPUR_C, 3);
                SET_BIT(GPIOPUR_C, 4);
                SET_BIT(GPIOPUR_C, 5);
                SET_BIT(GPIOPUR_C, 6);
                SET_BIT(GPIOPUR_C, 7);
                break;
            case PD:
                CLR_BIT(GPIODIR_D, 0);
                CLR_BIT(GPIODIR_D, 1);
                CLR_BIT(GPIODIR_D, 2);
                CLR_BIT(GPIODIR_D, 3);
                CLR_BIT(GPIODIR_D, 4);
                CLR_BIT(GPIODIR_D, 5);
                CLR_BIT(GPIODIR_D, 6);
                CLR_BIT(GPIODIR_D, 7);
                SET_BIT(GPIOPUR_D, 0);
                SET_BIT(GPIOPUR_D, 1);
                SET_BIT(GPIOPUR_D, 2);
                SET_BIT(GPIOPUR_D, 3);
                SET_BIT(GPIOPUR_D, 4);
                SET_BIT(GPIOPUR_D, 5);
                SET_BIT(GPIOPUR_D, 6);
                SET_BIT(GPIOPUR_D, 7);
                break;
            case PE:
                CLR_BIT(GPIODIR_E, 0);
                CLR_BIT(GPIODIR_E, 1);
                CLR_BIT(GPIODIR_E, 2);
                CLR_BIT(GPIODIR_E, 3);
                CLR_BIT(GPIODIR_E, 4);
                CLR_BIT(GPIODIR_E, 5);
                SET_BIT(GPIOPUR_E, 0);
                SET_BIT(GPIOPUR_E, 1);
                SET_BIT(GPIOPUR_E, 2);
                SET_BIT(GPIOPUR_E, 3);
                SET_BIT(GPIOPUR_E, 4);
                SET_BIT(GPIOPUR_E, 5);
                break;
            case PF:
                CLR_BIT(GPIODIR_F, 0);
                CLR_BIT(GPIODIR_F, 1);
                CLR_BIT(GPIODIR_F, 2);
                CLR_BIT(GPIODIR_F, 3);
                CLR_BIT(GPIODIR_F, 4);
                SET_BIT(GPIOPUR_F, 0);
                SET_BIT(GPIOPUR_F, 1);
                SET_BIT(GPIOPUR_F, 2);
                SET_BIT(GPIOPUR_F, 3);
                SET_BIT(GPIOPUR_F, 4);
                break;
            }
            break;
        }
    }
}

void GPIO_Write_Pin(PORT_ID port, PIN_ID pin, VOLTAGE_ID value)
{
    if ((port <= PF) && (pin <= PIN7))
    {
        if (value == LOWV)
        {
            switch (port)
            {
            case PA:
                CLR_BIT(GPIODATA_A, pin);
                break;
            case PB:
                CLR_BIT(GPIODATA_B, pin);
                break;
            case PC:
                CLR_BIT(GPIODATA_C, pin);
                break;
            case PD:
                CLR_BIT(GPIODATA_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    CLR_BIT(GPIODATA_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    CLR_BIT(GPIODATA_F, pin);
                }
                break;
            }
        }
        else if (value == HIGHV)
        {
            switch (port)
            {
            case PA:
                SET_BIT(GPIODATA_A, pin);
                break;
            case PB:
                SET_BIT(GPIODATA_B, pin);
                break;
            case PC:
                SET_BIT(GPIODATA_C, pin);
                break;
            case PD:
                SET_BIT(GPIODATA_D, pin);
                break;
            case PE:
                if (pin <= PIN5)
                {
                    SET_BIT(GPIODATA_E, pin);
                }
                break;
            case PF:
                if (pin <= PIN4)
                {
                    SET_BIT(GPIODATA_F, pin);
                }
                break;
            }
        }
    }
}

void GPIO_Write_Port(PORT_ID port, u8 value)
{
    if (port <= PF)
    {
        switch (port)
        {
        case PA:
            GPIODATA_A = value;
            break;
        case PB:
            GPIODATA_B = value;
            break;
        case PC:
            GPIODATA_C = value;
            break;
        case PD:
            GPIODATA_D = value;
            break;
        case PE:
            GPIODATA_E = value;
            break;
        case PF:
            GPIODATA_F = value;
            break;
        }
    }
}

u8 GPIO_Read_Pin(PORT_ID port, PIN_ID pin, u8 value)
{
    u8 data;
    if ((port <= PF) && (pin <= PIN7))
    {
        switch (port)
        {
        case PA:
            value = GET_BIT(GPIODATA_A, pin);
            data = value;
            break;
        case PB:
            value = GET_BIT(GPIODATA_B, pin);
            data = value;
            break;
        case PC:
            value = GET_BIT(GPIODATA_C, pin);
            data = value;
            break;
        case PD:
            value = GET_BIT(GPIODATA_D, pin);
            data = value;
            break;
        case PE:
            if (pin <= PIN5)
            {
                value = GET_BIT(GPIODATA_E, pin);
                data = value;
            }
            break;
        case PF:
            if (pin <= PIN4)
            {
                value = GET_BIT(GPIODATA_F, pin);
                data = value;
            }
            break;
        }
    }
    return data;
}

u8 GPIO_Read_Port(PORT_ID port, u8 value)
{
    u8 data;
    if (port <= PF)
    {
        switch (port)
        {
        case PA:
            value = GPIODATA_A;
            data = value;
            break;
        case PB:
            value = GPIODATA_B;
            data = value;
            break;
        case PC:
            value = GPIODATA_C;
            data = value;
            break;
        case PD:
            value = GPIODATA_D;
            data = value;
            break;
        case PE:
            value = GPIODATA_E;
            data = value;
            break;
        case PF:
            value = GPIODATA_F;
            data = value;
            break;
        }
    }
    return data;
}
void delay(unsigned long count)
{
    unsigned long i = 0;
    for (i = 0; i < count; i++)
        ;
}
