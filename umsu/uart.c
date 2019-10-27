// uart.c
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "uart.h"
#include "queue.h"

int volatile txbusy;

void uart_init()
{
	UBRR0H = 0x00; UBRR0L = 0x07; // 115.2K
	//sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	//sbi(UCSR0B, RXCIE0);
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

ISR(USART0_TX_vect)
{
	char ch;
	if((ch = qo_delete()) == 0){
		txbusy = 0;
	}
	else
		UDR0 = ch;
}

ISR(USART0_RX_vect)
{
	char ch;
	ch = UDR0;
	qi_insert(ch);
}
