#include "uart5.h"
#include "TM4C123.h"
#include <stdbool.h>

#define UART_IM_RXIM            0x00000010  // UART Receive Interrupt Mask
#define INT_UART5               77          // UART5
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_MIS_RXMIS          0x00000010  // UART Receive Masked Interrupt Status
#define UART_ICR_RXIC           0x00000010  // Receive Interrupt Clear


volatile uint8_t UART5_ReceivedByte = 0; // Variable to store received byte
volatile uint8_t UART5_ReceivedFlag = 0; // Flag to indicate a new byte was received


void UART5_Init(void)
{
    // Step 1: Enable clock for UART5 and GPIO Port E
		SYSCTL->RCGCUART |= 0x20; // Enable clock for UART5 (bit 5 = 0x20);
		SYSCTL->RCGCGPIO |= 0x10; // Enable clock for GPIO Port E (bit 4 = 0x10);
		
    // Wait until UART5 and GPIO Port E are ready
    while (!(SYSCTL->PRUART & 0x20)); // Wait until UART5 is ready
    while (!(SYSCTL->PRGPIO & 0x10)); // Wait until GPIO Port E is ready
	
	
    // Step 2: Configure GPIO pins PE4 (RX) and PE5 (TX) for UART5
		GPIOE->AMSEL &= ~0x30;                                       // Disable analog functionality on PE4 (RX) and PE5 (TX)
		GPIOE->DIR |= 0x20;                                          // Set PE5 (TX) as output
		GPIOE->DIR &= ~0x10;                                         // Set PE4 (RX) as input
		GPIOE->AFSEL |= 0x30;                                        // Enable alternate function on PE4 and PE5
		GPIOE->PCTL = (GPIOE->PCTL & 0xFF00FFFF) | 0x00110000; // Set PE4 as RX and PE5 as TX
		GPIOE->DEN |= 0x30;                                          // Enable digital I/O on PE4 and PE5
	
    // Step 3: Disable UART5 for configuration
		UART5->CTL &= ~UART_CTL_UARTEN_MASK; // Disable UART5
    
	// Step 4: Configure the baud rate for UART5 (9600 bps)
		UART5->IBRD = 104; // Integer part of the divisor (for 9600 bps, with 16 MHz system clock)
		UART5->FBRD = 11;  // Fractional part of the divisor
    // Step 5: Configure UART5 line control settings

		UART5->LCRH = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS); // 8 bits data // Enable FIFOs
		
    // Step 6: Enable RX interrupt
		UART5->IM |= UART_IM_RXIM;            // Enable RX interrupt;
		NVIC->ISER[1] |= (1 << (INT_UART5 % 32));  // UART5 = Interrupt #61, so ISER[1], bit 29
		
    // Step 7: Enable UART5, TX, and RX
		UART5->CTL = UART_CTL_UARTEN_MASK | UART_CTL_RXE_MASK | UART_CTL_TXE_MASK;
}
void UART5_SendByte(uint8_t data)
{
    while (UART5->FR & UART_FR_TXFF);  // Wait until the TX FIFO is not full
		UART5->DR = data; // Write the byte to the UART Data Rister
}
uint8_t UART5_ReceiveByte(void)
{
    UART5_ReceivedFlag = 0; // Clear the flag
    return UART5_ReceivedByte;
}
void UART5_SendString(const uint8_t *pData)
{
    while (*pData != '\0')
    {
        UART5_SendByte(*pData); // Send each byte of the string
        pData++;
    }
}
void UART5_SendInteger(int64_t sNumber)
{
    uint8_t uDigits[20];
    int8_t uCounter = 0;

    // Send the negative sign in case of negative numbers
    if (sNumber < 0)
    {
        UART5_SendByte('-');
        sNumber *= -1;
    }

    // Convert the number to an array of characters
    do
    {
        uDigits[uCounter++] = sNumber % 10 + '0'; // Convert each digit to its corresponding ASCII character
        sNumber /= 10;                            // Remove the already converted digit
    } while (sNumber != 0);

    // Send the array of characters in reverse order
    for (uCounter--; uCounter >= 0; uCounter--)
    {
        UART5_SendByte(uDigits[uCounter]);
    }
}

void UART5_Handler(void)
{
    if (UART5->MIS & UART_MIS_RXMIS) // Check if RX interrupt occurred
    {
        UART5_ReceivedByte = (uint8_t)UART5->DR; // Read the received byte
        switch (UART5_ReceivedByte)
        {
        }
        UART5->ICR |= UART_ICR_RXIC; // Clear the RX interrupt flag
    }
}
