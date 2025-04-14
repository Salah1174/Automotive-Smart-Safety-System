
#include "systick.h"

#include "TM4C123GH6PM.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"

int SysTick_Init(systick_config_t* config)
{
	uint32_t busClockFreq = PLL_GetBusClockFreq();
	
	// Return failure if the PLL hasn't been initialized.
	if (busClockFreq == 0) {
		return -1;
	}
	
	config->busClockFreq = busClockFreq;

    // Establish the number of ticks in 10ms for later use...
    config->NumTicksPer10ms = busClockFreq * 0.01;

    // Establish the number of ticks in 10us for later use...
    config->NumTicksPer10us = busClockFreq * 0.00001;
    
    // Establish the number of ticks in 1us for later use...
    config->NumTicksPer_us = busClockFreq * 0.000001;

	// 1) Disable SysTick during initialization.
	NVIC_ST_CTRL_R = 0;
	
	// 2) Set the RELOAD register to establish a modulo RELOAD + 1 decrement counter
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	
	// 3) Clear the accumulator
	NVIC_ST_CURRENT_R = 0;
	
	// 4) Set clock source to core clock and enable 
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
	
	// Success
	return 0;
}

void SysTick_Wait(systick_config_t* config, uint32_t delay)
{
    // Delay in number of bus cycle period units
    NVIC_ST_RELOAD_R = delay - 1;
    
    // Clear CURRENT
    NVIC_ST_CURRENT_R = 0; 
    
    // Wait for COUNT flag to be set upon rollover.
    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0) {
    }
}

void SysTick_Wait10ms(systick_config_t* config, uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(config, config->NumTicksPer10ms);
    }
}

void SysTick_Wait10us(systick_config_t* config, uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(config, config->NumTicksPer10us);
    }
}

void SysTick_Wait_us(systick_config_t* config, uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(config, config->NumTicksPer_us);
    }
}

void PLL_Init80MHz(void)
{
	SYSCTL_Type sysctl;
	// 0) Set USERCC2 bit in order to use RCC2
	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
	
	// 1) Set the BYPASS bit to bypass PLL while initializing.
	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

	// 2) Clear and set the XTAL bits to 16MHz
	SYSCTL_RCC_R = ((SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) | SYSCTL_RCC_XTAL_16MHZ);
	
	// 3)	Clear the OSCSRC2 bits to configure for Main OSC
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
	
	// 4) Activate PLL by clearing PWRDN.
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
	
	// 5) Use 400 MHz PLL
	SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400 ;
	
	// 6) Clear the SYSDIV2 bits and set to 0x4 = 80MHz
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~(SYSCTL_RCC2_SYSDIV2_M | SYSCTL_RCC2_SYSDIV2LSB)) | (0x4 << 22);  
	
	// 7) Wait for the PLL to lock
	while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0)
	{
	}
	
	// 8) Clear BYPASS to enable PLL.
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
	
//	busClockFreq_ = 80000000;
	
}

uint32_t PLL_GetBusClockFreq(void)
{
	return 80000000;
}