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
#include "IginitionSwitch.h"
#include "ultrasonic.h"

#include "APP/Display/display.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 


#include "core_cm4.h"



#define LED_PORT GPIO_PORTF_BASE
#define LED_PIN GPIO_PIN_1

/* The interrupt number to use for the software interrupt generation.  This
could be any unused number.  In this case the first chip level (non system)
interrupt is used, which happens to be the watchdog on the LPC1768. */
#define mainSW_INTERRUPT_ID		( ( IRQn_Type ) 5 )

/* Macro to force an interrupt. */
#define mainTRIGGER_INTERRUPT()	NVIC_SetPendingIRQ( mainSW_INTERRUPT_ID )

/* Macro to clear the same interrupt. */
#define mainCLEAR_INTERRUPT()	NVIC_ClearPendingIRQ( mainSW_INTERRUPT_ID )

/* The priority of the software interrupt.  The interrupt service routine uses
an (interrupt safe) FreeRTOS API function, so the priority of the interrupt must
be equal to or lower than the priority set by
configMAX_SYSCALL_INTERRUPT_PRIORITY - remembering that on the Cortex M3 high
numeric values represent low priority values, which can be confusing as it is
counter intuitive. */
#define mainSOFTWARE_INTERRUPT_PRIORITY 		( 5 )

/* Enable the software interrupt and set its priority. */
static void prvSetupSoftwareInterrupt( void );

/* The service routine for the interrupt.  This is the interrupt that the
task will be synchronized with. */
void vSoftwareInterruptHandler( void );



TaskHandle_t 	xDisplay= NULL;	
TaskHandle_t xAlert = NULL; 
xSemaphoreHandle xBinarySemaphore; 





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





static void prvSetupSoftwareInterrupt(void){
/* The interrupt service routine uses an (interrupt safe) FreeRTOS API
		function so the interrupt priority must be at or below the priority defined
	by configSYSCALL_INTERRUPT_PRIORITY. */
	NVIC_SetPriority( mainSW_INTERRUPT_ID, mainSOFTWARE_INTERRUPT_PRIORITY );

	/* Enable the interrupt. */
	NVIC_EnableIRQ( mainSW_INTERRUPT_ID );
}

void vSoftwareInterruptHandler( void )
{
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* 'Give' the semaphore to unblock the task. */
    xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );

    /* Clear the software interrupt bit using the interrupt controllers
    Clear Pending register. */
    mainCLEAR_INTERRUPT();

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

void AlertLCD(void *pvParameter){
	  xSemaphoreTake(xBinarySemaphore, 0); 
		while(1){
			xSemaphoreTake(xBinarySemaphore, 100000); 
//		//vPrintString("hEllo");
			Alert_Display(&lcdDisplay);
			delay_ms(2500);
			//vTaskDelay( 250 / portTICK_RATE_MS );
		}
}

//void AlertozLCD(void *pvParameter){
	//mainTRIGGER_INTERRUPT();
//}//

void GearLCD(void *pvParameter){
	
	while(1){
		bool currentPress = PushButton_Read();
		if (currentPress ==false){
			D_Display(&lcdDisplay,100,1,1);
			delay_ms(2500);
		}
		
		if (currentPress ==true){
			R_Display(&lcdDisplay,100,1);	
			delay_ms(2500);
		}
		vTaskDelay( 250 / portTICK_RATE_MS );
		mainTRIGGER_INTERRUPT();
	}
}


int main(void)
{
	
//		xSemaphoreTake(xBinarySemaphore,0);
		__ASM(" CPSIE I ");
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
	
		vSemaphoreCreateBinary(xBinarySemaphore);
    //Alert_Display(&lcdDisplay);
		
		
		
		bool carStatus = false;
		bool doorLocked = false;
		bool doorStatus = false;
    bool lastPressed = false;
    uint32_t speed = 0;
    uint32_t distance = 0;
		xTaskCreate(GearLCD, "Gear LCD"	, 150, NULL, 2, &xDisplay);
		xTaskCreate(AlertLCD, "Alert LCD", 150, NULL, 3, &xAlert); 
		//xTaskCreate(AlertozLCD, "Alertoz LCD", 150, NULL, 2, NULL); 
		vTaskStartScheduler();
		
		
		
		
    while (1)
    {
		
//        bool currentPressed = PushButton_Read();
//        uint8_t state = GPIOPinRead(LED_PORT, LED_PIN);
//        speed = potentiometer_ReadValue();
//        distance = ultrasonic_ReadValue();
//				doorStatus = DOOR_Status();
//				doorLocked = Lock_Read(); 
//				carStatus = IgnitionSwitch_Read();
//			
//        if (currentPressed && !lastPressed)
//        {
//            // Debounce delay
//            SysCtlDelay(SysCtlClockGet() / 100); // ~10 ms

//            // Confirm again
//            if (PushButton_Read())
//            {

//                // Toggle LED
//                state = GPIOPinRead(LED_PORT, LED_PIN);
//                GPIOPinWrite(LED_PORT, LED_PIN, state ^ LED_PIN);
//            }
//        }
//        if (state)
//        {
//            D_Display(&lcdDisplay, speed, doorStatus,doorLocked);
//            delay_ms(1000);
//        }
//        else
//        {
//            R_Display(&lcdDisplay, distance,carStatus);
//            delay_ms(1000);
//        }
//        lastPressed = currentPressed;
    }
}