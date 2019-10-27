// main.c
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "queue.h"

int main()
{
	char cmd[128], ch;
	int n = 0, i;

	uart_init();
	sei();
	printf("$ ");
	while(1){
		cli();
		ch = qi_delete();
		sei();
		if(ch){
			if(ch == '\r') continue;
			if(ch == '\n'){
				cmd[n] = 0;
				for ( i=0; i<n; i++) {
					printf("%c",cmd[i]);
				}
				n = 0;
				printf("\n$ ");
			}
			else
				cmd[n++] = ch;
		}
	}
	return 0;
}
