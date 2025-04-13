#ifndef I2C_H
#define I2C_H
#include <stdint.h>


#define GPIO_PB2_I2C0SCL        0x00010803
#define GPIO_PB3_I2C0SDA        0x00010C03

void I2C_Init(void);
void I2CSendByte(uint8_t slave_addr, uint8_t value);
//uint8_t I2C_Write(uint32_t slave_address, uint8_t slave_memory_address, uint32_t bytes_count, uint8_t* data);
// uint8_t I2C_Read();
#endif