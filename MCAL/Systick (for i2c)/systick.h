#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>

#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable

#define SYSCTL_RCC_R            (*((volatile uint32_t *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile uint32_t *)0x400FE070))
#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2	
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000  // System Clock Divisor 2
#define SYSCTL_RCC2_SYSDIV2LSB  0x00400000  // Additional LSB for SYSDIV2
#define SYSCTL_RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define SYSCTL_RCC_XTAL_M       0x000007C0  // Crystal Value
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  // 16 MHz
#define SYSCTL_RIS_R            (*((volatile uint32_t *)0x400FE050))
	#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status

typedef struct {
    uint32_t NumTicksPer10ms;
    uint32_t NumTicksPer10us;
    uint32_t NumTicksPer_us;
    uint32_t busClockFreq;
} systick_config_t;

int SysTick_Init(systick_config_t* config);
void SysTick_Wait(systick_config_t* config, uint32_t delay);
void SysTick_Wait10ms(systick_config_t* config, uint32_t delay);
void SysTick_Wait10us(systick_config_t* config, uint32_t delay);
void SysTick_Wait_us(systick_config_t* config, uint32_t delay);

void PLL_Init80MHz(void);
uint32_t PLL_GetBusClockFreq(void);
#endif