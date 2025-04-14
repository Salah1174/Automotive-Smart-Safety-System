#ifndef UART5_H_
#define UART5_H_
#include <stdint.h>

/*******************************************************************************
 *                             Preprocessor Macros                             *
 *******************************************************************************/

#define UART_DATA_5BITS 0x0
#define UART_DATA_6BITS 0x1
#define UART_DATA_7BITS 0x2
#define UART_DATA_8BITS 0x3
#define UART_LCRH_WLEN_BITS_POS 5

/* UART5 Control Register Masks */
#define UART_CTL_UARTEN_MASK 0x00000001 // UART Enable
#define UART_CTL_TXE_MASK 0x00000100    // UART Transmit Enable
#define UART_CTL_RXE_MASK 0x00000200    // UART Receive Enable

/* UART5 Flag Register Masks */
#define UART_FR_TXFE_MASK 0x00000080 // UART Transmit FIFO Empty
#define UART_FR_RXFE_MASK 0x00000010 // UART Receive FIFO Empty

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern volatile uint8_t UART5_ReceivedByte; // Variable to store received byte

extern void UART5_Init(void);

extern void UART5_SendByte(uint8_t data);

extern uint8_t UART5_ReceiveByte(void);

extern void UART5_SendString(const uint8_t *pData);

extern void UART5_SendInteger(int64_t sNumber);

#endif /* UART5_H_ */
