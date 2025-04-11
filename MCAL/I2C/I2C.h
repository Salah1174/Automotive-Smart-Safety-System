#ifndef I2C_H
#define I2C_H
#include <stdint.h>

void I2C_Init(void);
uint8_t I2C_Write(uint32_t slave_address, uint8_t slave_memory_address, uint32_t bytes_count, uint8_t* data);
// uint8_t I2C_Read();
#endif