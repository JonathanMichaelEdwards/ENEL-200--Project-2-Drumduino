// ****************************************************************************
// File:     uart.c                                                           *
// Authors:  Jonathan Edwards                                                 *
// Date:     08/26/2019                                                       *
// Descr:    Transmitting and Recieving bytes to/from the monitor             *
// ****************************************************************************

#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

#define BIT(X)               (1 << (X)) 
#define BUAD                 9600
#define UART_BAUD_REGISTERS  (((16000000 / (BUAD * 16UL))) - 1)

int getChar(FILE*);
int putChar(char, FILE*);

FILE IO = FDEV_SETUP_STREAM(putChar, getChar, _FDEV_SETUP_RW);


int getChar(FILE *stream)
{
    putChar(0, stream);

    //Wait untill a data is available
    while(!(UCSR0A & BIT(RXC0)));

    // Now USART has got data from host
    return UDR0;
}


int putChar(char data, FILE *stream)
{
    if (data == '\n') putChar('\r', stream);

    // Wait until the transmitter is ready
    while (!(UCSR0A & BIT(UDRE0)));

    // Now write the data to USART buffer
    UDR0 = data;

    return 0;
}

void uartInit(void)
{
    UCSR0B |= BIT(RXEN0) | BIT(TXEN0) | BIT(RXCIE0) | BIT(TXCIE0);
	UCSR0C |= BIT(UCSZ00) | BIT(UCSZ01);
	UBRR0L = UART_BAUD_REGISTERS;

    stdin = stdout = &IO;
}
