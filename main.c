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
#define LED_PORT GPIO_PORTF_BASE
#define LED_PIN GPIO_PIN_1

/* The interrupt number to use for the software interrupt generation.  This
could be any unused number.  In this case the first chip level (non system)
interrupt is used, which happens to be the watchdog on the LPC1768. */
#define mainSW_INTERRUPT_1	( ( IRQn_Type ) 5 )
#define mainSW_INTERRUPT_2	( ( IRQn_Type ) 6 )

/* Macro to force an interrupt. */
#define mainTRIGGER_INTERRUPT_1()	NVIC_SetPendingIRQ( mainSW_INTERRUPT_1 )
#define mainTRIGGER_INTERRUPT_2()	NVIC_SetPendingIRQ( mainSW_INTERRUPT_2 )

/* Macro to clear the same interrupt. */
#define mainCLEAR_INTERRUPT_1()	NVIC_ClearPendingIRQ( mainSW_INTERRUPT_1 )
#define mainCLEAR_INTERRUPT_2()	NVIC_ClearPendingIRQ( mainSW_INTERRUPT_2 )

/* The priority of the software interrupt.  The interrupt service routine uses
an (interrupt safe) FreeRTOS API function, so the priority of the interrupt must
be equal to or lower than the priority set by
configMAX_SYSCALL_INTERRUPT_PRIORITY - remembering that on the Cortex M3 high
numeric values represent low priority values, which can be confusing as it is
counter intuitive. */
#define mainSOFTWARE_INTERRUPT_PRIORITY_1 		( 5 )
#define mainSOFTWARE_INTERRUPT_PRIORITY_2 		( 6 )

/* Enable the software interrupt and set its priority. */
static void prvSetupSoftwareInterrupt( void );

/* The service routine for the interrupt.  This is the interrupt that the
task will be synchronized with. */
void vSoftwareInterruptHandler_1( void );
void vSoftwareInterruptHandler_2( void );


void AlertLCD(void *pvParameter);

void GearLCD(void *pvParameter);

void ignition_task (void * pvParameters);


TaskHandle_t 	xDisplay= NULL;	
TaskHandle_t xAlert = NULL; 
TaskHandle_t xIgnition =NULL;
xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;
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
static void prvSetupSoftwareInterrupt(void);

void vSoftwareInterruptHandler_1( void );





int main(void)
{

		prvSetupSoftwareInterrupt();
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) ;
    GPIOPinTypeGPIOOutput(LED_PORT, LED_PIN);

		
    LCDI2CInit(&lcdDisplay, 0x27, 16, 2);
	  ultrasonic_Init();
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

		
		
		
		bool carStatus = false;
		bool doorLocked = false;
		bool doorStatus = false;
    bool lastPressed = false;
    uint32_t speed = 0;
    uint32_t distance = 0;

		xTaskCreate(ignition_task,"Ignition" ,244,NULL , 6,&xIgnition);
		xTaskCreate(GearLCD, "Gear LCD"	, 244 , NULL, 2, &xDisplay);
		xTaskCreate(AlertLCD, "Alert LCD", 150, NULL, 3, &xAlert);
		vTaskStartScheduler();
		
		
		
		
    while (1)
    {
		

    }
}
void ignition_task (void * pvParameters){
	static uint32_t Carstate =0;
	bool currentPressed ;
	bool lastPressed=true ; 
	bool state = 0;
	
	while(1)
	{
		currentPressed = IgnitionSwitch_Read();
		if(currentPressed)
			{		
				xSemaphoreTake(xIgnitionSemaphore, portMAX_DELAY);
			//state =0 ----> carOff
			//state =1 ----> carOn
       state ^= 1;		
//			Carstate++;
    }
		delay_ms(200);
		if(state && (currentPressed != lastPressed) )//&&(Carstate%2!=0)
		{

								carOn_Display(&lcdDisplay);
								delay_ms(250);
								vTaskDelete(NULL);
			
		}
		if(!state && (currentPressed != lastPressed) )//&& (Carstate%2==0)
		{
			
			carOff_Display(&lcdDisplay);
			__asm(" WFI"); // Enter sleep mode 
			
		}			
	
		lastPressed= currentPressed;
}
}

void GearLCD(void *pvParameter){
	uint32_t speed;
	bool door;
	bool lock;
	bool ignition;
	uint32_t distance;
	
	while(1){
		bool currentPress = PushButton_Read();
		speed = potentiometer_ReadValue();
		door = DOOR_Status();
		lock = Lock_Read();
		ignition = IgnitionSwitch_Read();
//		distance = ultrasonic_ReadValue();
		distance=0;
		
		if(speed>10){
			//LOCK THE DOOR AUTOMATICALLY
		lock = 0;
		}
		if(lock){
		//IMPLEMENT HARDWARE INTERRUPT ?
		}
		if(speed >150 && door == true ){
					mainTRIGGER_INTERRUPT_1();
				}
		
		if (currentPress ==false){
			
			D_Display(&lcdDisplay,speed,door,lock);
			delay_ms(500);
		}
		
		if (currentPress ==true){
			
			R_Display(&lcdDisplay,distance,speed,door,lock);
				if(distance >100){
					//GREEN: SAFE		    BUZZER:SMALL FRQ
					
				}else if(distance<30){
					//RED: DANGER ZONE	BUZZER:LARGE FRQ
				}else{
					//YELLOW: CAUTION ZONE	BUZZER:MEDIUM FRQ
				}
			delay_ms(500);
				
		}
		if(ignition)
		{
		xSemaphoreTake(xIgnitionSemaphore, portMAX_DELAY);
		xTaskCreate(ignition_task,"Ignition" ,244,NULL , 6,&xIgnition);
		delay_ms(500);
//		mainTRIGGER_INTERRUPT_2();
		}
		
		vTaskDelay( 250 / portTICK_RATE_MS );
				
	}
}
void AlertLCD(void *pvParameter){
	  xSemaphoreTake(xBinarySemaphore1, 0); 
		while(1){
			xSemaphoreTake(xBinarySemaphore1, 100000); 
			uint32_t speed = potentiometer_ReadValue();
			bool door = DOOR_Status();
			Alert_Display(&lcdDisplay);
			while (speed >150 && door == true ){
				speed = potentiometer_ReadValue();
				door = DOOR_Status();
				
				delay_ms(500);
			}
			
			//vTaskDelay( 250 / portTICK_RATE_MS );
		}
}







static void prvSetupSoftwareInterrupt(void){
/* The interrupt service routine uses an (interrupt safe) FreeRTOS API
		function so the interrupt priority must be at or below the priority defined
	by configSYSCALL_INTERRUPT_PRIORITY. */
	NVIC_SetPriority( mainSW_INTERRUPT_1, mainSOFTWARE_INTERRUPT_PRIORITY_1 );
	NVIC_SetPriority( mainSW_INTERRUPT_2, mainSOFTWARE_INTERRUPT_PRIORITY_2 );

	/* Enable the interrupt. */
	NVIC_EnableIRQ( mainSW_INTERRUPT_1 );
	NVIC_EnableIRQ( mainSW_INTERRUPT_2 );
}
void vSoftwareInterruptHandler_1( void ){
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* 'Give' the semaphore to unblock the task. */
    xSemaphoreGiveFromISR( xBinarySemaphore1, &xHigherPriorityTaskWoken );

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
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
void GPIOC_Handler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if (GPIOC->MIS & (1 << 5)) /* Check if interrupt caused by PC5 */
			{
					GPIOC->ICR |= (1 << 5); /* Clear the interrupt flag */

					/* Give the semaphore to unblock the ignition task */
					xSemaphoreGiveFromISR(xIgnitionSemaphore, &xHigherPriorityTaskWoken);
			}
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

