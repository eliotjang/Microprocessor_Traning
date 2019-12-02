#include "uart.h"
void uart_init()
{
	uint16_t baudrate;
	baudrate = F_CPU/16/9600 -1 ;
	UBRR0H = baudrate >> 8;
	UBRR0L = baudrate;
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

uint8_t uart_RX_empty(void)
{
	return(!(UCSR0A & (1<<RXC0)));
}
uint8_t uart_RX_clear(void)
{
	return(UDR0);

}
uint8_t uart_RX_byte(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return(UDR0);
}
void uart_TX_byte(uint8_t by)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = by;
}
