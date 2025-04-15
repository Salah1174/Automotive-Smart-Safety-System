#include "Doors.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "driverlib\gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

extern volatile bool doorStatus;

void DOOR_Init(void)
{
    DIO_Init('B', GPIO_PIN_3, GPIO_DIR_MODE_IN);
}

bool DOOR_Status(void)
{
    bool doorCurrentStatus = DIO_ReadPin('B', GPIO_PIN_3);
    return doorCurrentStatus;
}
