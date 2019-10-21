#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <avr/interrupt.h>
#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>

#define ETX 0x04

//int uart_putchar_2(char ch, FILE *stream);
int uart_putchar_3(char ch, FILE *stream);
int uart_getchar_3(FILE *stream);



FILE Mystdout = FDEV_SETUP_STREAM (uart_putchar_3, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM (NULL, uart_getchar_3, _FDEV_SETUP_READ);
char uart_busy;

void uart_init()
{
	stdout = &Mystdout;
	stdin = &Mystdin;
	uart_busy = 0;
	q_init();
	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}


int uart_getchar_3(FILE *stream)
{
	char ch;

	do{
		cli();
		ch = qi_delete();
		sei();
	}while(ch==0);

	if(ch==ETX)
		return(-1);
	else
		return(ch);
}
int uart_putchar_3(char ch, FILE *stream)
{


	if (ch == '\n')
		uart_putchar_3('\r', stream);
	cli();
	if(!uart_busy){
		UDR0 = ch;
		uart_busy = 1;
	}else{
		while(qo_insert(ch)==0){
			sei();
			_delay_us(100);
			cli();
		}
	}

	sei();
	return(1);
}


int is_prime(int n)
{
	int i;
	for(i=2;i<=n/2;i++)
		if((n%i)==0)
			return(0);
	return(1);
}
app_prime(int t)
{
	int n, count =0;
	for(n = 2; n<=t;n++){
		if(is_prime(n)){
			count++;
			printf("%d is a prime number!!\n",n);
		}			
	}
	printf("count = %d\n",count);
}

ISR(USART0_TX_vect)
{

	char ch;
	if((ch = qo_delete())==0) 
		uart_busy = 0;
	else
		UDR0 = ch;
}
ISR(USART0_RX_vect)
{

	char ch;

	ch = UDR0;
	if(ch!=ETX){
		if(ch=='\r')
			ch='\n';
		uart_echo(ch);
	}
	qi_insert(ch);
}
void uart_echo(char ch)
{
	if(ch=='\n')
		uart_echo('\r');
	if(!uart_busy){
		UDR0 = ch;
		uart_busy = 1;
	}
	else
		qo_insert(ch);
}
