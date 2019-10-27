// main.c
#include <stdio.h> // for printf(), fputs
#include <avr/interrupt.h> // for sei(), cli()
#include <util/delay.h> // for _delay_ms()
#include "uart.h" // for uart_init()
#include "queue.h" // for qi_delete()

int main()
{
	char cmd[128], ch;
	int n = 0;

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
				// for문을 사용하거나 fputs사용하면 됨.
				/*for( i=0; i<n; i++) {
					printf("%c",cmd[i]);
				}*/
				fputs(cmd, stdout);
				_delay_ms(3000);
				n = 0;
				printf("\n$ ");
			}
			else
				cmd[n++] = ch;
		}
	}
}
