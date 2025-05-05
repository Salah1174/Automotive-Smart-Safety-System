#ifndef TM4C_ULTRASONIC_H
#define TM4C_ULTRASONIC_H

#include "stdtypes.h"

// Initialize GPIO & Timer for ultrasonic
void Ultrasonic_init(void);

// Send a 10��s trigger pulse
void Ultrasonic_Trigger(void);

// Measure and return distance in centimeters
// Returns UINT32_MAX on timeout/no-echo
u32 Ultrasonic_readDistance(void);

#endif // TM4C_ULTRASONIC_H
