/*
 * GPIO.h
 *
 *  Created on: Nov 20, 2019
 *      Author: Ahmed Magdy
 */

#ifndef GPIO_H_
#define GPIO_H_

#define RCGCGPIO (*((volatile unsigned long *)0x400FE608))
//*******************************************************************************************************
#define GPIOLOCK_A (*((volatile unsigned long *)0x40004520))
#define GPIOLOCK_B (*((volatile unsigned long *)0x40005520))
#define GPIOLOCK_C (*((volatile unsigned long *)0x40006520))
#define GPIOLOCK_D (*((volatile unsigned long *)0x40007520))
#define GPIOLOCK_E (*((volatile unsigned long *)0x40024520))
#define GPIOLOCK_F (*((volatile unsigned long *)0x40025520))
//*****************************************************************************************************************
#define GPIOCR_A (*((volatile unsigned long *)0x40004524))
#define GPIOCR_B (*((volatile unsigned long *)0x40005524))
#define GPIOCR_C (*((volatile unsigned long *)0x40006524))
#define GPIOCR_D (*((volatile unsigned long *)0x40007524))
#define GPIOCR_E (*((volatile unsigned long *)0x40024524))
#define GPIOCR_F (*((volatile unsigned long *)0x40025524))
//*******************************************************************************************************************
#define GPIOAFSEL_A (*((volatile unsigned long *)0x40004420))
#define GPIOAFSEL_B (*((volatile unsigned long *)0x40005420))
#define GPIOAFSEL_C (*((volatile unsigned long *)0x40006420))
#define GPIOAFSEL_D (*((volatile unsigned long *)0x40007420))
#define GPIOAFSEL_E (*((volatile unsigned long *)0x40024420))
#define GPIOAFSEL_F (*((volatile unsigned long *)0x40025420))
//******************************************************************************************************************
#define GPIOPCTL_A (*((volatile unsigned long *)0x4000452C))
#define GPIOPCTL_B (*((volatile unsigned long *)0x4000552C))
#define GPIOPCTL_C (*((volatile unsigned long *)0x4000652C))
#define GPIOPCTL_D (*((volatile unsigned long *)0x4000752C))
#define GPIOPCTL_E (*((volatile unsigned long *)0x4002452C))
#define GPIOPCTL_F (*((volatile unsigned long *)0x4002552C))
//********************************************************************************************************************
#define GPIOMSEL_A (*((volatile unsigned long *)0x40004528))
#define GPIOMSEL_B (*((volatile unsigned long *)0x40005528))
#define GPIOMSEL_C (*((volatile unsigned long *)0x40006528))
#define GPIOMSEL_D (*((volatile unsigned long *)0x40007528))
#define GPIOMSEL_E (*((volatile unsigned long *)0x40024528))
#define GPIOMSEL_F (*((volatile unsigned long *)0x40025528))
//*******************************************************************************************************************
#define GPIODIR_A (*((volatile unsigned long *)0x40004400))
#define GPIODIR_B (*((volatile unsigned long *)0x40005400))
#define GPIODIR_C (*((volatile unsigned long *)0x40006400))
#define GPIODIR_D (*((volatile unsigned long *)0x40007400))
#define GPIODIR_E (*((volatile unsigned long *)0x40024400))
#define GPIODIR_F (*((volatile unsigned long *)0x40025400))
//************************************************************************************************
#define GPIOPUR_A (*((volatile unsigned long *)0x40004510))
#define GPIOPUR_B (*((volatile unsigned long *)0x40005510))
#define GPIOPUR_C (*((volatile unsigned long *)0x40006510))
#define GPIOPUR_D (*((volatile unsigned long *)0x40007510))
#define GPIOPUR_E (*((volatile unsigned long *)0x40024510))
#define GPIOPUR_F (*((volatile unsigned long *)0x40025510))
//********************************************************************************************
#define GPIOPDR_A (*((volatile unsigned long *)0x40004514))
#define GPIOPDR_B (*((volatile unsigned long *)0x40005514))
#define GPIOPDR_C (*((volatile unsigned long *)0x40006514))
#define GPIOPDR_D (*((volatile unsigned long *)0x40007514))
#define GPIOPDR_E (*((volatile unsigned long *)0x40024514))
#define GPIOPDR_F (*((volatile unsigned long *)0x40025514))
//**************************************************************************************************
#define GPIODATA_A (*((volatile unsigned long *)0x400043FC)) // BASE + OFSSET + MASK=0x3FC
#define GPIODATA_B (*((volatile unsigned long *)0x400053FC)) // BASE + OFSSET + MASK
#define GPIODATA_C (*((volatile unsigned long *)0x400063FC)) // BASE + OFSSET + MASK
#define GPIODATA_D (*((volatile unsigned long *)0x400073FC)) // BASE + OFSSET + MASK
#define GPIODATA_E (*((volatile unsigned long *)0x400243FC)) // BASE + OFSSET + MASK
#define GPIODATA_F (*((volatile unsigned long *)0x400253FC)) // BASE + OFSSET + MASK
//*******************************************************************************************
#define GPIODEN_A (*((volatile unsigned long *)0x4000451C))
#define GPIODEN_B (*((volatile unsigned long *)0x4000551C))
#define GPIODEN_C (*((volatile unsigned long *)0x4000651C))
#define GPIODEN_D (*((volatile unsigned long *)0x4000751C))
#define GPIODEN_E (*((volatile unsigned long *)0x4002451C))
#define GPIODEN_F (*((volatile unsigned long *)0x4002551C))
//*******************************************************************

#include "stdtypes.h"
#include "util.h"
typedef enum
{
	PA = 0,
	PB,
	PC,
	PD,
	PE,
	PF
} PORT_ID;

typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7

} PIN_ID;

typedef enum
{
	OUT = 0,
	INPULLUP,
	INPULLDOWN,
	INFREE
} DIRECTION_ID;

typedef enum
{
	LOWV = 0,
	HIGHV
} VOLTAGE_ID;

void GPIO_Initialize_Port(PORT_ID port);
void GPIO_Set_Pin_Direction(PORT_ID port, PIN_ID pin, DIRECTION_ID direction);
void GPIO_Set_Port_Direction(PORT_ID port, DIRECTION_ID direction);
void GPIO_Write_Pin(PORT_ID port, PIN_ID pin, VOLTAGE_ID value);
void GPIO_Write_Port(PORT_ID port, u8 value);
u8 GPIO_Read_Pin(PORT_ID port, PIN_ID pin, u8 value);
void delay(unsigned long count);
u8 GPIO_Read_Port(PORT_ID port, u8 value);
#endif /* GPIO_H_ */
