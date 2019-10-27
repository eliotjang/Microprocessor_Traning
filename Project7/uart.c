// uart.c
#include <stdio.h> // for FILE
#include <avr/io.h> // FOR UBRR0H, UBRR0L.. I guess
#include <avr/interrupt.h> // for sei(), cli(), ISR()
#include <compat/deprecated.h>
#include <util/delay.h> // for sbi(), _delay_ms()
#include "uart.h"
#include "queue.h"
//int uart_putchar(char ch, FILE *stream);

//FILE Mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL, _FDEV_SETUP_WRITE);
char volatile txbusy; // for always access memory
// uart_busy가 int이던 char이던 상관없음.
void uart_init()
{
	//stdout = &Mystdout;
	txbusy = 0;
	q_init();
	UBRR0H = 0x00; UBRR0L = 0x07; // 115.2K
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
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

void uart_putchar(char ch)
{
	if (ch == '\n')
		uart_putchar('\r');
	cli();
	if (!txbusy) {
		UDR0 = ch, txbusy = 1;
		//sei();
		//return;
	}
	//sei();
	else {
		while(qo_insert(ch) == 0) {
			sei();
			_delay_ms(100);
			cli();
		}
	}
	sei();	
}
	

/*int uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n') uart_putchar('\r', stream);

	cli();
	if(!uart_busy){
		UDR0 = ch;
		uart_busy = 1;
	}
	else{
		while(qo_insert(ch) == 0){
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();
	
	return(1);
}*/
