/*
 * Timer0.h
 *
 *  Created on: Nov 27, 2019
 *      Author: Ahmed Magdy
 */

#ifndef TIMER0_NEW_H_
#define TIMER0_NEW_H_
#include "stdtypes.h"
#include "util.h"

#define RCGCTIMER (*((volatile unsigned long *)0x400FE604))
#define GPTMCTL (*((volatile unsigned long *)0x4003000C))
#define GPTMCFG (*((volatile unsigned long *)0x40030000))
#define GPTMTAMR (*((volatile unsigned long *)0x40030004))
#define GPTMTAILR (*((volatile unsigned long *)0x40030028))
#define GPTMRIS (*((volatile unsigned long *)0x4003001C))
#define GPTMICR (*((volatile unsigned long *)0x40030024))
#define GPTMIMR (*((volatile unsigned long *)0x40030018))
#define GPTMMIS (*((volatile unsigned long *)0x40030020))
#define EN0 (*((volatile unsigned long *)0xE000E100))
//********************************************************************

#define GPTMCTL3 (*((volatile unsigned long *)0x4003300C))
#define GPTMCFG3 (*((volatile unsigned long *)0x40033000))
#define GPTMTAMR3 (*((volatile unsigned long *)0x40033004))
#define GPTMTAILR3 (*((volatile unsigned long *)0x40033028))
#define GPTMRIS3 (*((volatile unsigned long *)0x4003301C))
#define GPTMICR3 (*((volatile unsigned long *)0x40033024))
#define GPTMIMR3 (*((volatile unsigned long *)0x40033018))
#define GPTMMIS3 (*((volatile unsigned long *)0x40033020))
#define GPTAMATCHR3 (*((volatile unsigned long *)0x40033030))
#define GPTMTAPMR3 (*((volatile unsigned long *)0x40033040))
#define GPTMTAR3 (*((volatile unsigned long *)0x40033048))
//*********************************************************************
#define GPTMCTL2 (*((volatile unsigned long *)0x4003200C))
#define GPTMCFG2 (*((volatile unsigned long *)0x40032000))
#define GPTMTAMR2 (*((volatile unsigned long *)0x40032004))
#define GPTMTAILR2 (*((volatile unsigned long *)0x40032028))
#define GPTMRIS2 (*((volatile unsigned long *)0x4003201C))
#define GPTMICR2 (*((volatile unsigned long *)0x40032024))
#define GPTMIMR2 (*((volatile unsigned long *)0x40032018))
#define GPTMMIS2 (*((volatile unsigned long *)0x40032020))
#define GPTAMATCHR2 (*((volatile unsigned long *)0x40032030))
#define GPTMTAPMR2 (*((volatile unsigned long *)0x40032040))
#define GPTMTAR2 (*((volatile unsigned long *)0x40032048))

/**/
// void PLL_Initialize(void);
void Timer0_Delay(u32 ttime);
void Timer3_Count_Init(void);
u32 Timer3_Count_Ret(void);

u32 Timer2_Count_Ret(void);
void Timer2_Count_Init(void);

#endif /* TIMER0_H_ */