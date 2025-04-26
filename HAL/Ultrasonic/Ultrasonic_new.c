#include "Ultrasonic_new.h"
#include "Timer0_new.h"    // for Timer0_Delay
   // for Timer3_Count_Init, Timer3_Count_Ret
#include "GPIO_new.h"
#include "util.h"
#include <stdint.h>
#define ULTRASONIC_TIMEOUT_TICKS 0x00FFFFFFU
// If bus = 16 MHz, tick = 1/16 µs, speed = 0.034 cm/µs:
// cm per tick = (1/16)*0.034 = 0.002125 cm
#define CM_PER_TICK (0.002125f)

void Ultrasonic_init(void)
{
    // 1) GPIO: PA2 output for Trigger
    GPIO_Initialize_Port(PA);
    GPIO_Set_Pin_Direction(PA, PIN2, OUT);
    GPIO_Write_Pin(PA, PIN2, LOWV);

    // 2) Timer3A capture on PB2
    Timer3_Count_Init();
}

void Ultrasonic_Trigger(void)
{
    GPIO_Write_Pin(PA, PIN2, HIGHV);
    Timer0_Delay(10);  // 10 µs
    GPIO_Write_Pin(PA, PIN2, LOWV);
}

static u32 Timer3_CapturePulseTicks(void)
{
    u32 t0, t1;
    u32 timeout = 0;

    // Clear and wait rising
    GPTMICR3 = 1 << 0;
    while ((GPTMRIS3 & 1) == 0) {
        if (++timeout >= ULTRASONIC_TIMEOUT_TICKS) return UINT32_MAX;
    }
    t0 = GPTMTAR3;

    // Clear and wait falling
    GPTMICR3 = 1 << 0;
    timeout = 0;
    while ((GPTMRIS3 & 1) == 0) {
        if (++timeout >= ULTRASONIC_TIMEOUT_TICKS) return UINT32_MAX;
    }
    t1 = GPTMTAR3;

    return (t1 - t0) & 0x00FFFFFFU;
}

u32 Ultrasonic_readDistance(void)
{
    Ultrasonic_Trigger();

    u32 ticks = Timer3_CapturePulseTicks();
    if (ticks == UINT32_MAX) {
        return UINT32_MAX;  // timeout/no echo
    }

    // Distance = (ticks * cm_per_tick) / 2
    float cm = (ticks * CM_PER_TICK) * 0.5f;
    return (u32)(cm + 0.5f);
}
