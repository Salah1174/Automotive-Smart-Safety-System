#ifndef IGNITION_SWITCH_H
#define IGNITION_SWITCH_H
#include <stdbool.h>
#include <stdint.h>

void IgnitionSwitch_Init(void);
bool IgnitionSwitch_Read(void);

#endif