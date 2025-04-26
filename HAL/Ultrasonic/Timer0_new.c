/*
 * Timer0.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Ahmed Magdy
 */
#include "stdtypes.h"
#include "util.h"
#include "GPIO_new.h"
#include "Timer0_new.h"
#define ULTRASONIC_TIMEOUT_TICKS 0x00FFFFFF
#define UINT32_MAX		100
int i;
void Timer0_Delay(u32 ttime)
{
    SET_BIT(RCGCTIMER,0);    //Enable clock for timer0

    CLR_BIT(GPTMCTL,0);      //Disable timer0 during configuration


    GPTMCFG=0x04;

    GPTMTAMR = 0x02;     //Select one shot timer& Down count selection

    GPTMTAILR = 16-1;  //Set clock to 16MHZ
    SET_BIT(GPTMICR,0);       //Clear flag

    SET_BIT(GPTMCTL,0);        //Enable timer0
    for(i=0;i<(ttime/2);i++)
    {
        while((GET_BIT(GPTMRIS,0))==0); //wait for TimerA timeout flag to set*/
        SET_BIT(GPTMICR,0);       //Clear flag
    }
}

void Timer3_Count_Init(void){


    SET_BIT(RCGCTIMER,3);    //Enable clock for timer3
    SET_BIT(RCGCGPIO,1);        //enable GPIO clock

    CLR_BIT(GPIODIR_B,2);        //enable GPIO clock
    SET_BIT(GPIODEN_B,2);        //enable GPIO clock
    SET_BIT(GPIOAFSEL_B,2);        //enable GPIO clock

    GPIOPCTL_B  &=~0x00000F00;
    GPIOPCTL_B  |=0x00000700;

    CLR_BIT(GPTMCTL3,0);      //Disable timer0 during configuration


    GPTMCFG3=0x04;

    GPTMTAMR3 = 0x17;     //Select one shot timer& Down count selection
//    GPTAMATCHR3 = 0xFFFF;
  //  GPTMTAPMR3 = 0xFF;
    SET_BIT(GPTMCTL3, 2);
    SET_BIT(GPTMCTL3, 3);
    //clear 3
    SET_BIT(GPTMCTL3,0);        //Enable timer3 to start counting
}

u32 Timer3_Count_Ret(void)
{
    u32 start, stop, timer = 0;

    // First edge (rising)
    GPTMICR3 = 1;  // clear
    while ((GPTMRIS3 & 1) == 0) {
        if (++timer >= ULTRASONIC_TIMEOUT_TICKS) return UINT32_MAX;
    }
    start = GPTMTAR3;

    // Second edge (falling)
    GPTMICR3 = 1;  // clear
    timer = 0;
    while ((GPTMRIS3 & 1) == 0) {
        if (++timer >= ULTRASONIC_TIMEOUT_TICKS) return UINT32_MAX;
    }
    stop = GPTMTAR3;

    return (stop - start) & 0x00FFFFFF;
}

void Timer2_Count_Init(void){

    SET_BIT(RCGCTIMER,2);    //Enable clock for timer2
    SET_BIT(RCGCGPIO,1);        //enable GPIO clock
    SET_BIT(RCGCGPIO,5);        //enable GPIO clock
    CLR_BIT(GPIODIR_B,0);        //enable GPIO clock
    CLR_BIT(GPIODIR_F,4);
    SET_BIT(GPIODEN_B,0);        //enable GPIO clock
    SET_BIT(GPIODEN_F,4);
    SET_BIT(GPIOAFSEL_B,0);        //enable GPIO clock
    SET_BIT(GPIOAFSEL_F,4);
    GPIOPCTL_B  &=~0x0000000F;
    GPIOPCTL_B  |=0x00000007;
    GPIOPCTL_B  &=~0x000F0000;
       GPIOPCTL_B  |=0x00070000;

    CLR_BIT(GPTMCTL2,0);      //Disable timer0 during configuration


    GPTMCFG2=0x04;

    GPTMTAMR2 = 0x17;     //Select one shot timer& Down count selection
//    GPTAMATCHR3 = 0xFFFF;
  //  GPTMTAPMR3 = 0xFF;
    SET_BIT(GPTMCTL2, 2);
    SET_BIT(GPTMCTL2, 3);
    //clear 3
    SET_BIT(GPTMCTL2,0);        //Enable timer3 to start counting
}

u32 Timer2_Count_Ret(void){

    SET_BIT(GPTMICR2,2);
    while(GET_BIT(GPTMRIS2, 2)==0){}
    u32 duration1 =  GPTMTAR2;


    SET_BIT(GPTMICR2,2);
    while(GET_BIT(GPTMRIS2, 2)==0){}
    u32 duration2 =   GPTMTAR2;


    return (duration2 - duration1) &0x00FFFFFF;

}