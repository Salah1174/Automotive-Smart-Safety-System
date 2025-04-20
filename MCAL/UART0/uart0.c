#include "uart0.h"
#include "TM4C123.h"

static void GPIO_SetupUART0Pins(void)
{
    SYSCTL->RCGCGPIO |= 0x01; /* Enable clock for GPIO PORTA */
    while (!(SYSCTL->PRGPIO & 0x01))
        ;                 /* Wait until GPIO PORTA clock is activated and it is ready for access*/
    GPIOA->AMSEL &= 0xFC; /* Disable Analog on PA0 & PA1 */
    ;
    GPIOA->DIR &= 0xFE; /* Configure PA0 as input pin */
    ;
    GPIOA->DIR |= 0x02; /* Configure PA1 as output pin */
    ;
    GPIOA->AFSEL |= 0x03; /* Enable alternative function on PA0 & PA1 */
    ;
    /* Set PMCx bits for PA0 & PA1 with value 1 to use PA0 as UART0 RX pin and PA1 as UART0 Tx pin */
    GPIOA->PCTL = (GPIOA->PCTL & 0xFFFFFF00) | 0x00000011;
    GPIOA->DEN |= 0x03; /* Enable Digital I/O on PA0 & PA1 */
}
void UART0_Init(void) /* UART0 configuration: 1 start, 8 bits data, No Parity, 1 stop bit and 9600BPS */
{
    /* Setup UART0 pins PA0 --> U0RX & PA1 --> U0TX */
    GPIO_SetupUART0Pins();
    SYSCTL->RCGCUART |= 0x01; /* Enable clock for UART0 */
    while (!(SYSCTL->PRUART & 0x01))
        ;           /* Wait until UART0 clock is activated and it is ready for access*/
    UART0->CTL = 0; /* Disable UART0 at the beginning */
    UART0->CC = 0;  /* Use System Clock*/
                    /* To Configure UART0 with Baud Rate 9600 */
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    /* UART Line Control Register Settings
     * BRK = 0 Normal Use
     * PEN = 0 Disable Parity
     * EPS = 0 No affect as the parity is disabled
     * STP2 = 0 1-stop bit at end of the frame
     * FEN = 0 FIFOs are disabled
     * WLEN = 0x3 8-bits data frame
     * SPS = 0 no stick parity*/
    UART0->LCRH = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);
    /* UART Control Register Settings
     * RXE = 1 Enable UART Receive
     * TXE = 1 Enable UART Transmit
     * HSE = 0 The UART is clocked using the system clock divided by 16
     * UARTEN = 1 Enable UART*/
    UART0->CTL = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
}

void UART0_SendByte(uint8_t data)
{
    while (!(UART0->FR & UART_FR_TXFE_MASK))
        ; /* Wait until the transmit FIFO is empty */
    UART0->DR = data;
}

uint8_t UART0_ReceiveByte(void)
{
    while (UART0->FR & UART_FR_RXFE_MASK)
        ;             /* Wait until the receive FIFO is not empty */
    return UART0->DR; /* Read the byte */
}

void UART0_SendString(const uint8_t *pData)
{
    uint32_t uCounter = 0;
    /* Transmit the whole string */
    while (pData[uCounter] != '\0')
    {
        UART0_SendByte(pData[uCounter]); /* Send the byte */
        uCounter++;                      /* increment the counter to the next byte */
    }
}

void UART0_SendInteger(int64_t sNumber)
{
    uint8_t uDigits[20];
    int8_t uCounter = 0;
    /* Send the negative sign in case of negative numbers */
    if (sNumber < 0)
    {
        UART0_SendByte('-');
        sNumber *= -1;
    }
    /* Convert the number to an array of characters */
    do
    {
        uDigits[uCounter++] = sNumber % 10 + '0'; /* Convert each digit to its corresponding ASCI character */
        sNumber /= 10;                            /* Remove the already converted digit */
    } while (sNumber != 0);
    /* Send the array of characters in a reverse order as the digits were converted from right to left */
    for (uCounter--; uCounter >= 0; uCounter--)
    {
        UART0_SendByte(uDigits[uCounter]);
    }
}