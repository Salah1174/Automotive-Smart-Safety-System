/*
 * NVIC.c
 *
 */

#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"


/*********************************************************************
* Service Name: blink
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to alert user about incorrect data entry in the main program (This is development code for debugging, not production code)
**********************************************************************/

void blink(void){
    GPIO_PORTF_AMSEL_REG &= ~(1<<1);      /* Disable Analog on PF1 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= (1<<1);       /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<1);      /* Disable alternative function on PF1 */
    GPIO_PORTF_DEN_REG   |= (1<<1);       /* Enable Digital I/O on PF1 */
    while(1){
        GPIO_PORTF_DATA_REG  = 0x1;
        volatile int i;
        for (i = 0; i < 9999; i++);
        GPIO_PORTF_DATA_REG  = 0x0;
        for (i =0; i<9999; i++);
    }
}

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    Enable_Exceptions();
    if(IRQ_Num>138){
        blink(); //Alert user about error in entry
        return;
    }
    volatile uint32 * ptrEnableReg = (volatile uint32 *) 0xE000E100; //put address of first enable register in ptr

    volatile uint8 offset = IRQ_Num/32; //calculate offset to determine which register we use and help determine which bit
    ptrEnableReg[offset] |= (1<< (IRQ_Num - (32*offset)));  //determine which bit in the identified register
    GPIO_PORTF_DATA_REG  = 0x0;

//
//    if(IRQ_Num<=31){
//        NVIC_EN0_REG = NVIC_EN0_REG | (1 << IRQ_Num);
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=32 && IRQ_Num<=63){
//        NVIC_EN1_REG = NVIC_EN1_REG | (1 << (IRQ_Num-32));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=64 && IRQ_Num<=95){
//        NVIC_EN2_REG = NVIC_EN2_REG | (1 << (IRQ_Num-64));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=96 && IRQ_Num<=127){
//        NVIC_EN3_REG = NVIC_EN3_REG | (1 << (IRQ_Num-96));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=128){
//        NVIC_EN4_REG = NVIC_EN4_REG | (1 << (IRQ_Num-128));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    Disable_Exceptions();
    if(IRQ_Num>138){
        blink(); //Alert user about error in entry
        return;
    }

    volatile uint32 * ptrEnableReg = (volatile uint32 *) 0xE000E180;

    volatile uint8 offset = IRQ_Num/32;
    ptrEnableReg[offset] |= (1<< (IRQ_Num - (32*offset)));
    GPIO_PORTF_DATA_REG  = 0x0;

//    if(IRQ_Num<=31){
//        NVIC_DIS0_REG = NVIC_DIS0_REG | (1 << IRQ_Num);
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=32 && IRQ_Num<=63){
//        NVIC_DIS1_REG = NVIC_DIS1_REG | (1 << (IRQ_Num-32));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=64 && IRQ_Num<=95){
//        NVIC_DIS2_REG = NVIC_DIS2_REG | (1 << (IRQ_Num-64));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=96 && IRQ_Num<=127){
//        NVIC_DIS3_REG = NVIC_DIS3_REG | (1 << (IRQ_Num-96));
//        GPIO_PORTF_DATA_REG  = 0x0;
//    }
//    else if(IRQ_Num>=128){
//        NVIC_DIS4_REG = NVIC_DIS4_REG | (1 << (IRQ_Num-128));
//        GPIO_PORTF_DATA_REG  = 0x0;
//
//    }

}


/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in) #1: IRQ_Num - Number of the IRQ from the target vector table
* Parameters (in) #2: IRQ_Priority - Priority user wishes to set for specific IRQ
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority of Interrupt request for specific IRQ
**********************************************************************/

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
    if(IRQ_Num>138 ){
         blink(); //Alert user about error in entry
         return;
    }

    //need to also check PRIMASK using assembly (that its set to enable interrupts)

    volatile uint32 *nvic_pri = (volatile uint32 *)0xE000E400; //point to first priority register

    volatile uint8 offset = (IRQ_Num/4); //offset determines which register we want to modify its bits
    volatile uint8 shift = ((IRQ_Num % 4)*8 + 5); //determine which section in the register
    nvic_pri[offset] &= ~(0x7 << shift);
    nvic_pri[offset] |= IRQ_Priority<<shift;

}


/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in) #1: Exception_Num - Number of the exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to enable specific ARM system or fault exceptions.
**********************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
    Enable_Exceptions();
    Enable_Faults();
    if(Exception_Num>15 || Exception_Num<=2){ //cant modify NMIn Reset, or stack pointer
        blink(); //Alert user about error in entry
        return;
    }
    switch(Exception_Num){
    case 0: return;
    case 1: return;
    case 2: return;
    case 3: NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK; //memory
            break;
    case 4: NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK; //bus
            break;
    case 5: NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK; //usage
            break;
    case 6: //NVIC_SYSTEM_SYSHNDCTRL |= (1<<15); //SVC
            //break;
            return;
    case 7: //NVIC_SYSTEM_SYSHNDCTRL |= (1<<8); //Debug Monitor
            //break;
            return;
    case 8: //NVIC_SYSTEM_SYSHNDCTRL |= (1<<10); //PendSV
            //break;
            return;
    case 9: SYSTICK_CTRL_REG |= (1<<1); //Systick
            break;
    default: return;
    }

}


/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in) #1: Exception_Num - Number of the exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to disable specific ARM system or fault exceptions.
**********************************************************************/

void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
    Disable_Exceptions();
    Disable_Faults();
    if(Exception_Num>15 || Exception_Num<=2){ //cant modify NMI, Reset, or stack pointer
        blink(); //Alert user about error in entry
        return;
    }
    switch(Exception_Num){
    case 0: return;
    case 1: return;
    case 2: return;
    case 3: NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<16); //memory
        break;
    case 4: NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<17); //bus
            break;
    case 5: NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<18); //usage
            break;
    case 6: //NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<15); //SVC
            //break;
            return;
    case 7: //NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<8); //Debug Monitor
            //break;
            return;
    case 8: //NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<10); //PendSV
            //break;
            return;
    case 9: SYSTICK_CTRL_REG &= ~(1<<1); //Systick
            break;
    default: return;
    }

}


/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in) #1: Exception_Num - Number of the Exception from the target vector table
* Parameters (in) #2: Exception_Priority - Priority user wishes to set for specific Exception
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority of Exception for specific IRQ
**********************************************************************/

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
    if(Exception_Num>15 || Exception_Num<=2){ //cant modify NMI, Reset, or stack pointer
            blink(); //Alert user about error in entry
            return;
    }

    //need to also check PRIMASK using assembly (that its set to enable the specific exceptions and faults)

    switch(Exception_Num){
      case 3: NVIC_SYSTEM_PRI1_REG &= ~(MEM_FAULT_PRIORITY_MASK);
          NVIC_SYSTEM_PRI1_REG |= (Exception_Priority<<MEM_FAULT_PRIORITY_BITS_POS); //memory
          break;
      case 4: NVIC_SYSTEM_PRI1_REG &= ~(BUS_FAULT_PRIORITY_MASK);
              NVIC_SYSTEM_PRI1_REG |= (Exception_Priority<<BUS_FAULT_PRIORITY_BITS_POS); //bus
              break;
      case 5: NVIC_SYSTEM_PRI1_REG &= ~(USAGE_FAULT_PRIORITY_MASK);
              NVIC_SYSTEM_PRI1_REG |= (Exception_Priority<<USAGE_FAULT_PRIORITY_BITS_POS); //usage
              break;
      case 6: NVIC_SYSTEM_PRI2_REG &= ~(SVC_PRIORITY_MASK);
              NVIC_SYSTEM_PRI2_REG |= (Exception_Priority<<SVC_PRIORITY_BITS_POS); //SVC
              break;
      case 7: NVIC_SYSTEM_PRI3_REG &= ~(DEBUG_MONITOR_PRIORITY_MASK);
              NVIC_SYSTEM_PRI3_REG |= (Exception_Priority<<DEBUG_MONITOR_PRIORITY_BITS_POS); //Debug Monitor
              break;
      case 8: NVIC_SYSTEM_PRI3_REG &= ~(PENDSV_PRIORITY_MASK);
              NVIC_SYSTEM_PRI3_REG |= (Exception_Priority<<PENDSV_PRIORITY_BITS_POS); //PendSV
              break;
      case 9: NVIC_SYSTEM_PRI3_REG &= ~(SYSTICK_PRIORITY_MASK);
              NVIC_SYSTEM_PRI3_REG |= (Exception_Priority<<SYSTICK_PRIORITY_BITS_POS); //Systick
              break;
      default: return;
      }

}



