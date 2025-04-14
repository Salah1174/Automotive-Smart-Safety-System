#ifndef UART0_H_
#define UART0_H_
#include <stdint.h>
#define UART_DATA_5BITS 0x0
#define UART_DATA_6BITS 0x1
#define UART_DATA_7BITS 0x2
#define UART_DATA_8BITS 0x3
#define UART_LCRH_WLEN_BITS_POS 5
#define UART_CTL_UARTEN_MASK 0x00000001
#define UART_CTL_TXE_MASK 0x00000100
#define UART_CTL_RXE_MASK 0x00000200
#define UART_FR_TXFE_MASK 0x00000080
#define UART_FR_RXFE_MASK 0x00000010
/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern void UART0_Init(void);

extern void UART0_SendByte(uint8_t data);

extern uint8_t UART0_ReceiveByte(void);

extern void UART0_SendString(const uint8_t *pData);

extern void UART0_SendInteger(int64_t sNumber);

#endif
