#include "TM4C123GH6PM.h"
 #include "inc/tm4c123gh6pm.h"
#include <stdint.h>

#include "driverlib/timer.h"
 //used in lcd operations taht need delay
 void Timer0A_Init(void){
     SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;
     while (!(SYSCTL_PRTIMER_R & SYSCTL_PRTIMER_R0)); /* wait for Timer0 to be ready */
     TIMER0_CTL_R &= ~TIMER_CTL_TAEN;            /* disable Timer before initialization */
     TIMER0_CFG_R = 0x04;         /* 32-bit individual Timer only works with prescaler*/
     TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;        /* Periodic down-counter only works in simulation */
     TIMER0_CTL_R |= TIMER_CTL_TAEN;         /* enable Timer A after initialization*/  
 }
 void timer0A_delayMs(int ttime){
     TIMER0_CTL_R &= ~TIMER_CTL_TAEN;            /* disable Timer before initialization */
     TIMER0_TAILR_R = SystemCoreClock * ttime - 1;  /* Timer A interval load value register*/
 //    TIMER0_TAILR_R =0xfF;
     // TIMER0_TAPR_R = 0x00;     /* TimerA Prescaler 16MHz/250=64000Hz */
     TIMER0_ICR_R |= TIMER_ICR_TATOCINT;          /* clear the TimerA timeout flag*/
     TIMER0_CTL_R |= TIMER_CTL_TAEN;         /* enable Timer A after initialization*/
     while ((TIMER0_RIS_R & 0x1) == 0){
		 uint32_t timerValue = TimerValueGet(TIMER0_BASE, TIMER_A);
		 }  /* wait for TimerA timeout flag to set*/	

 }


 //used exclusively for alert blinking delay :)
 void Timer0B_Init(void){
     SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;
     while (!(SYSCTL_PRTIMER_R & SYSCTL_PRTIMER_R0)); /* wait for Timer0 to be ready */
     TIMER0_CTL_R &= ~TIMER_CTL_TBEN;            /* disable Timer before initialization */
     TIMER0_CFG_R = 0x04;         /* 32-bit individual Timer only works with prescaler*/
     TIMER0_TBMR_R = TIMER_TBMR_TBMR_PERIOD;        /* Periodic down-counter only works in simulation */
     TIMER0_CTL_R |= TIMER_CTL_TBEN;         /* enable Timer A after initialization*/  
 }
 void timer0B_delayMs(int ttime){
     TIMER0_CTL_R &= ~TIMER_CTL_TBEN;            /* disable Timer before initialization */
     TIMER0_TBILR_R = SystemCoreClock * ttime - 1;  /* Timer A interval load value register*/
 //    TIMER0_TAILR_R =0xfF;
     // TIMER0_TAPR_R = 0x00;     /* TimerA Prescaler 16MHz/250=64000Hz */
     TIMER0_ICR_R |= TIMER_ICR_TBTOCINT;          /* clear the TimerA timeout flag*/
     TIMER0_CTL_R |= TIMER_CTL_TBEN;         /* enable Timer A after initialization*/
     while ((TIMER0_RIS_R & 0x100) == 0){
		 uint32_t timerValue = TimerValueGet(TIMER0_BASE, TIMER_B);
		 }  /* wait for TimerA timeout flag to set*/	

 }

//#include "driverlib/timer.h"
//#include "driverlib/sysctl.h"
//#include "inc/hw_memmap.h"
//#include <stdbool.h>
//#include <stdint.h>

//void Timer0A_Init(void) {
//    // Enable the clock for Timer0
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)); // Wait for Timer0 to be ready

//    // Configure Timer0A as a 16-bit periodic timer
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);

//    // Set the load value for 1ms delay (assuming 16 MHz clock)
//    TimerLoadSet(TIMER0_BASE, TIMER_A, SystemCoreClock - 1);

//    // Enable Timer0A
//    TimerEnable(TIMER0_BASE, TIMER_A);
//}

//void timer0A_delayMs(int ttime) {
//    // Disable Timer0A before setting the load value
//    TimerDisable(TIMER0_BASE, TIMER_A);

//    // Set the load value for the desired delay in milliseconds
//    TimerLoadSet(TIMER0_BASE, TIMER_A, (SystemCoreClock * ttime) - 1); // 16 MHz / 1000 = 16000

//    // Clear the timer interrupt flag
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

//    // Enable Timer0A
//    TimerEnable(TIMER0_BASE, TIMER_A);

//    // Wait for the timer to time out
//    while (!(TimerIntStatus(TIMER0_BASE, false) & TIMER_TIMA_TIMEOUT)) {
//        // Do nothing, just wait
//        uint32_t timerValue = TimerValueGet(TIMER0_BASE, TIMER_A);
//    }

//    // Clear the timer interrupt flag after timeout
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//}

//void Timer0B_Init(void) {
//    // Enable the clock for Timer0
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)); // Wait for Timer0 to be ready

//    // Configure Timer0B as a 16-bit periodic timer
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

//    // Set the load value for 1ms delay (assuming 16 MHz clock)
//    TimerLoadSet(TIMER0_BASE, TIMER_B, SystemCoreClock - 1);

//    // Enable Timer0B
//    TimerEnable(TIMER0_BASE, TIMER_B);
//}

//void timer0B_delayMs(int ttime) {
//    // Disable Timer0B before setting the load value
//    TimerDisable(TIMER0_BASE, TIMER_B);

//    // Set the load value for the desired delay in milliseconds
//    TimerLoadSet(TIMER0_BASE, TIMER_B, (SystemCoreClock * ttime) - 1); // 16 MHz / 1000 = 16000

//    // Clear the timer interrupt flag
//    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

//    // Enable Timer0B
//    TimerEnable(TIMER0_BASE, TIMER_B);


//    // Wait for the timer to time out
//    while (!(TimerIntStatus(TIMER0_BASE, false) & TIMER_TIMB_TIMEOUT)) {
//        // Do nothing, just wait

//    }

//    // Clear the timer interrupt flag after timeout
//    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
//}

