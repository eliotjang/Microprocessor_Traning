#include <stdio.h>
#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "queue.h"

#define ETX 0x04 // ^D : End of Text

int uart_putchar(char ch, FILE *stream);
int uart_putchar_1(char ch, FILE *stream);
int uart_putchar_2(char ch, FILE *stream);
void uart_echo(char ch);
int uart_getchar(FILE *stream);
char buf[64];
int volatile bufi, txend=1;

FILE Mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL,_FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM (NULL,uart_getchar, _FDEV_SETUP_READ);
char uart_busy;

void uart_init() {
	stdin = &Mystdin;
	stdout = &Mystdout;
	q_init();
	uart_busy=0;
	UBRR0H=0x00; UBRR0L=0x07;
	sbi(UCSR0A,U2X0);
	sbi(UCSR0B,TXEN0);
	sbi(UCSR0B,TXCIE0);
	sbi(UCSR0B,RXEN0);
	sbi(UCSR0B,RXCIE0);
}

/*void uart_putstart(char str[]) {
	char ch; int n= strlen(str);
	while(sizeof(buf)-strlen(buf+bufi)-1<n);
	strcpy(buf,buf+bufi); strcat(buf,str);
	bufi=0;
	if(txend) {
		txend=0;
		ch=buf[bufi++];
		UDR0=ch;
	}
}*/
// this
int uart_getchar(FILE *stream) {
	char ch;

	do {
		cli();
		ch=qi_delete();
		sei();
	} while(ch==0);

	if(ch==ETX) return(-1);
	else return(ch);
}
int uart_putchar(char ch, FILE *stream) {
	if(ch=='\n')
		uart_putchar('\r',stream);
	cli();
	if(!uart_busy) {
		UDR0 = ch;
		uart_busy=1;
	}
	else {
		while(qo_insert(ch)==0) {
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();
	return(1);
}
ISR(USART0_TX_vect) {
	char ch;

	if((ch=qo_delete())==0)
		uart_busy=0;
	else
		UDR0=ch;
}
//
ISR(USART0_RX_vect) {
	char ch;

	ch=UDR0;
	if(ch!=ETX) {
		if(ch=='\r')
			ch='\n';
		uart_echo(ch);
	}
	qi_insert(ch);
}
void uart_echo(char ch) {
	if(ch=='\n') uart_echo('\r');

	if(!uart_busy) {
		UDR0=ch;
		uart_busy=1;
	}
	else
		qo_insert(ch);
}
	
int uart_putchar_1(char ch, FILE *stream) {
	if(ch=='\n')
		uart_putchar_1('\r',stream);
	_delay_ms(1);
	UDR0=ch;
	return(1);
}

int uart_putchar_2(char ch, FILE *stream) {
	if(ch=='\n')
		uart_putchar_2('\r',stdout);
	while(!(UCSR0A & (1<<UDRE0)))
		;
	UDR0=ch;
	return(1);
}





