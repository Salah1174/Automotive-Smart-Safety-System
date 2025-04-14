#include "TM4C123GH6PM.h"

#include "I2C.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"


void I2C_Init(void){
 SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
 
    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
     

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
 
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
     
    // Select the I2C function for I2C0 functions on B2 and B3
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
 
    /* Enable and initialize the I2C0 master module.  Use the system clock for
     * the I2C0 module.  The last parameter sets the I2C data transfer rate.
     * If false the data rate is set to 100kbps and if true the data rate will
     * be set to 400kbps.  For this example we will use a data rate of 100kbps.
     */
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);
     
    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

void I2CSendByte(uint8_t slave_addr, uint8_t value){
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false); // set address of slave for master to communicate with
	//put data to be sent into FIFO
  I2CMasterDataPut(I2C0_BASE, value);
	//Initiate send of data from the MCU
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
         
  // Wait until MCU is done transferring.
  while(I2CMasterBusy(I2C0_BASE));
}
//uint8_t I2C_Write(uint32_t slave_address, uint8_t slave_memory_address, uint32_t bytes_count, uint8_t* data){}