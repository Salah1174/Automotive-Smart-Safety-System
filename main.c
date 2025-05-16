#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "LCD.h"
#include "PushButton.h"
#include "Potentiometer.h"
#include "Lock.h"
#include "Doors.h"

#include "ultrasonic.h"
#include "APP/Display/display.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "IginitionSwitch.h"
#include "Buzzer.h"
#include "LED.h"
#include "TM4C123.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_PORT GPIOF
#define BUZZER_PORT GPIO_PORTB_BASE
#define BUZZER_PIN GPIO_PIN_0

/* The interrupt number to use for the software interrupt generation.  This
could be any unused number.  In this case the first chip level (non system)
interrupt is used, which happens to be the watchdog on the LPC1768. */
#define mainSW_INTERRUPT_1 ((IRQn_Type)5)
#define mainSW_INTERRUPT_2 ((IRQn_Type)6)

/* Macro to force an interrupt. */
#define mainTRIGGER_INTERRUPT_1() NVIC_SetPendingIRQ(mainSW_INTERRUPT_1)
#define mainTRIGGER_INTERRUPT_2() NVIC_SetPendingIRQ(mainSW_INTERRUPT_2)

/* Macro to clear the same interrupt. */
#define mainCLEAR_INTERRUPT_1() NVIC_ClearPendingIRQ(mainSW_INTERRUPT_1)
#define mainCLEAR_INTERRUPT_2() NVIC_ClearPendingIRQ(mainSW_INTERRUPT_2)

/* The priority of the software interrupt.  The interrupt service routine uses
an (interrupt safe) FreeRTOS API function, so the priority of the interrupt must
be equal to or lower than the priority set by
configMAX_SYSCALL_INTERRUPT_PRIORITY - remembering that on the Cortex M3 high
numeric values represent low priority values, which can be confusing as it is
counter intuitive. */
#define mainSOFTWARE_INTERRUPT_PRIORITY_1 (5)
#define mainSOFTWARE_INTERRUPT_PRIORITY_2 (6)

/* Enable the software interrupt and set its priority. */
static void prvSetupSoftwareInterrupt(void);

/* The service routine for the interrupt.  This is the interrupt that the
task will be synchronized with. */
static void prvSetupSoftwareInterrupt(void);
void vSoftwareInterruptHandler_1(void);
void vSoftwareInterruptHandler_2(void);

void AlertLCD(void *pvParameter);
void GearLCD(void *pvParameter);
void ignition_task(void *pvParameters);

TaskHandle_t xDisplay = NULL;
TaskHandle_t xAlert = NULL;
TaskHandle_t xIgnition = NULL;
xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;
xSemaphoreHandle xLCDMutex;
xSemaphoreHandle xUltrasonicMutex;
SemaphoreHandle_t xIgnitionSemaphore;

LCD_I2C lcdDisplay;

void delay_ms(uint32_t ms)
{
	volatile uint32_t i;
	while (ms--)
	{
		for (i = 0; i < 4000; i++)
		{
		}
	}
}

volatile bool doorStatus = false;
volatile uint32_t speedValue = 0;
volatile uint32_t distanceValue = 0;
volatile bool carStatus = false;
volatile bool doorLock = false;
volatile bool ManualOverridden = false;

int main(void)
{
	prvSetupSoftwareInterrupt();
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
		;
	GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);

	LCDI2CInit(&lcdDisplay, 0x27, 16, 2);
	LEDs_Init();
	ultrasonic_Init();
	delay_ms(100);
	PushButton_Init();
	potentiometer_Init();
	DOOR_Init();
	Lock_Init();
	IgnitionSwitch_Init();

	/* Enable interrupt in NVIC and set priority */
	NVIC_SetPriority(GPIOC_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY + 1);
	vSemaphoreCreateBinary(xBinarySemaphore1);
	vSemaphoreCreateBinary(xBinarySemaphore2);
	xIgnitionSemaphore = xSemaphoreCreateBinary();

	xLCDMutex = xSemaphoreCreateMutex();
	xUltrasonicMutex = xSemaphoreCreateMutex();
	//		if(xLCDMutex != NULL)
	//		{
	//		}

	bool lastPressed = false;
	distanceValue = ultrasonic_ReadValue();
	xTaskCreate(ignition_task, "Ignition", 244, NULL, 6, &xIgnition);
	xTaskCreate(GearLCD, "Gear LCD", 244, NULL, 2, &xDisplay);
	xTaskCreate(AlertLCD, "Alert LCD", 150, NULL, 3, &xAlert);
	vTaskStartScheduler();

	for (;;)
	{
		// This point should never be reached.
	}
}

void ignition_task(void *pvParameters)
{

	bool currentPressed;
	bool lastPressed = true;
	carStatus = 0;
	doorLock = 0;

	while (1)
	{
		currentPressed = IgnitionSwitch_Read();
		if (currentPressed)
		{
			xSemaphoreTake(xIgnitionSemaphore, portMAX_DELAY);
			// state =0 ----> carOff
			// state =1 ----> carOn
			carStatus ^= 1;
		}
		delay_ms(200);
		if (carStatus && (currentPressed != lastPressed))
		{
			xSemaphoreTake(xLCDMutex, portMAX_DELAY);
			backlight(&lcdDisplay);
			carOn_Display(&lcdDisplay);
			distanceValue = ultrasonic_ReadValue();
			xSemaphoreGive(xLCDMutex);
			delay_ms(250);
			vTaskDelete(NULL);
		}
		if (!carStatus && (currentPressed != lastPressed))
		{
			xSemaphoreTake(xLCDMutex, portMAX_DELAY);
			// carOff_Display(&lcdDisplay);
			LED_PORT->DATA = ~(LED_RED | LED_BLUE | LED_GREEN);
			clear(&lcdDisplay);
			noBacklight(&lcdDisplay);
			xSemaphoreGive(xLCDMutex);
			__asm(" WFI"); // Enter sleep mode
		}

		lastPressed = currentPressed;
	}
}

void GearLCD(void *pvParameter)
{
	while (1)
	{

		bool currentPress = PushButton_Read();
		speedValue = potentiometer_ReadValue();
		doorStatus = DOOR_Status();
		carStatus = IgnitionSwitch_Read();
		// distanceValue = ultrasonic_ReadValue();

		if (speedValue > 50 && !ManualOverridden)
		{
			// LOCK THE DOOR AUTOMATICALLY
			doorLock = 1;
		}
		if (speedValue <= 50)
		{
			ManualOverridden = false;
		}

		if (speedValue > 150 && doorStatus == true)
		{
			mainTRIGGER_INTERRUPT_1();
		}

		if (currentPress == false)
		{
			xSemaphoreTake(xLCDMutex, portMAX_DELAY);
			D_Display(&lcdDisplay, speedValue, doorStatus, doorLock);
			xSemaphoreGive(xLCDMutex);
			delay_ms(500);
		}

		if (currentPress == true)
		{
			xSemaphoreTake(xLCDMutex, portMAX_DELAY);
			xSemaphoreTake(xUltrasonicMutex, portMAX_DELAY);
			distanceValue = ultrasonic_ReadValue();
			xSemaphoreGive(xUltrasonicMutex);
			R_Display(&lcdDisplay, distanceValue, speedValue, doorStatus, doorLock);
			xSemaphoreGive(xLCDMutex);
			if (distanceValue > 1000)
			{
				GREEN();
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 1); // Set PF1 high
				delay_ms(500);
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0x00); // Set PF1 low
				delay_ms(500);
			}
			if (distanceValue > 600 && distanceValue < 1000)
			{
				YELLOW();
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 1); // Set PF1 high
				delay_ms(250);
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0x00); // Set PF1 low
				delay_ms(250);
			}
			if (distanceValue > 200 && distanceValue < 600)
			{
				YELLOW();
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 1); // Set PF1 high
				delay_ms(50);
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0x00); // Set PF1 low
				delay_ms(50);
			}
			if (distanceValue < 200)
			{
				LED_PORT->DATA = ~(LED_RED | LED_BLUE | LED_GREEN);

			//	GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 1); // Set PF1 high
			//	delay_ms(50);
				GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0x00); // Set PF1 low
				delay_ms(50);
			}
		}

		if (carStatus)
		{
			xSemaphoreTake(xIgnitionSemaphore, portMAX_DELAY);
			xTaskCreate(ignition_task, "Ignition", 244, NULL, 6, &xIgnition);
			delay_ms(500);
			//		mainTRIGGER_INTERRUPT_2();
		}
		vTaskDelay(250 / portTICK_RATE_MS);
	}
}

void AlertLCD(void *pvParameter)
{
	xSemaphoreTake(xBinarySemaphore1, 0);
	while (1)
	{
		xSemaphoreTake(xBinarySemaphore1, 100000);
		speedValue = potentiometer_ReadValue();
		doorStatus = DOOR_Status();
		// distanceValue = ultrasonic_ReadValue();
		xSemaphoreTake(xLCDMutex, portMAX_DELAY);
		Alert_Display(&lcdDisplay);
		xSemaphoreGive(xLCDMutex);

		while (speedValue > 150 && doorStatus == true)
		{
			speedValue = potentiometer_ReadValue();
			xSemaphoreTake(xUltrasonicMutex, portMAX_DELAY);
			distanceValue = ultrasonic_ReadValue();
			xSemaphoreGive(xUltrasonicMutex);
			doorStatus = DOOR_Status();
			GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 1);
			RED();
			//delay_ms(20);
		}
		GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0);
		LED_off();
	}
}

static void prvSetupSoftwareInterrupt(void)
{
	/* The interrupt service routine uses an (interrupt safe) FreeRTOS API
			function so the interrupt priority must be at or below the priority defined
		by configSYSCALL_INTERRUPT_PRIORITY. */
	NVIC_SetPriority(mainSW_INTERRUPT_1, mainSOFTWARE_INTERRUPT_PRIORITY_1);
	NVIC_SetPriority(mainSW_INTERRUPT_2, mainSOFTWARE_INTERRUPT_PRIORITY_2);

	/* Enable the interrupt. */
	NVIC_EnableIRQ(mainSW_INTERRUPT_1);
	NVIC_EnableIRQ(mainSW_INTERRUPT_2);
}

void vSoftwareInterruptHandler_1(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	/* 'Give' the semaphore to unblock the task. */
	xSemaphoreGiveFromISR(xBinarySemaphore1, &xHigherPriorityTaskWoken);

	/* Clear the software interrupt bit using the interrupt controllers
	Clear Pending register. */
	mainCLEAR_INTERRUPT_1();

	/* Giving the semaphore may have unblocked a task - if it did and the
	unblocked task has a priority equal to or above the currently executing
	task then xHigherPriorityTaskWoken will have been set to pdTRUE and
	portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
	higher priority task.

	NOTE: The syntax for forcing a context switch within an ISR varies between
	FreeRTOS ports.  The portEND_SWITCHING_ISR() macro is provided as part of
	the Cortex M3 port layer for this purpose.  taskYIELD() must never be called
	from an ISR! */
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void GPIOC_Handler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (GPIOC->MIS & (1 << 5)) /* Check if interrupt caused by PC5 */
	{
		GPIOC->ICR |= (1 << 5); /* Clear the interrupt flag */

		/* Give the semaphore to unblock the ignition task */
		xSemaphoreGiveFromISR(xIgnitionSemaphore, &xHigherPriorityTaskWoken);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void GPIOE_Handler(void) // Lock -> PE5
{
	uint32_t status = GPIOIntStatus(GPIO_PORTE_BASE, true);
	if (status & GPIO_PIN_5)
	{
		GPIOIntClear(GPIO_PORTE_BASE, GPIO_PIN_5);
		doorLock ^= 1;
		ManualOverridden = true; // mark that user manually toggled
	}
}