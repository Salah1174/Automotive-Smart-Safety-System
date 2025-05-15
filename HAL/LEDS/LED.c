#include <stdint.h>
#include <stdbool.h>
#include "TM4C123.h"
#include "FreeRTOS.h"
#include "task.h"

// Define LED pin
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_PORT GPIOF

void LEDs_Init(void)
{

	SYSCTL->RCGCGPIO |= (1U << 5);

	while ((SYSCTL->PRGPIO & (1U << 5)) == 0)
	{
	}

	// Set PF1 as output
	LED_PORT->DIR |= LED_RED;
	LED_PORT->DEN |= LED_RED;

	LED_PORT->DIR |= LED_BLUE;
	LED_PORT->DEN |= LED_BLUE;

	LED_PORT->DIR |= LED_GREEN;
	LED_PORT->DEN |= LED_GREEN;
}

// LED Blink Task
void RED(void)
{
	LED_PORT->DATA ^= LED_RED; // Toggle PF1
	LED_PORT->DATA = ~(LED_RED | LED_BLUE | LED_GREEN);
}
void YELLOW(void)
{
	LED_PORT->DATA ^= LED_RED | LED_GREEN; // Toggle PF2
	LED_PORT->DATA = ~(LED_BLUE);
}
void GREEN(void)
{
	LED_PORT->DATA ^= LED_GREEN; // Toggle PF3
	LED_PORT->DATA = ~(LED_BLUE | LED_RED);
}
void LED_off(void)
{
	LED_PORT->DATA = ~(LED_BLUE | LED_RED | LED_GREEN);
}
