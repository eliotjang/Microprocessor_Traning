// uart.c
#include <avr/io.h>
#include <compat/deprecated.h>	//for sbi()
#include <avr/interrupt.h>
#include "uart.h"
#include "queue.h"

int volatile txbusy;

void uart_init()
{
	UBRR0H = 0; UBRR0L = 0x07;
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, TXCIE0);
}

void uart_putchar(char ch)
{
	cli();
	if (!txbusy) {
		UDR0 = ch, txbusy = 1;
		sei();
		return;
	}
	sei();
	while(qo_insert(ch) == 0)
		;
}
ISR(USART0_RX_vect)
{
	char ch;
	ch = UDR0;
	qi_insert(ch);
}

ISR(USART0_TX_vect)
{
	char ch;
	if ( !(ch = qo_delete()) )
		txbusy = 0;
	else
		UDR0 = ch;
}

