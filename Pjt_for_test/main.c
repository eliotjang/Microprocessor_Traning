// main.c

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "app.h"
#include "queue.h"

int main()
{
	char cmd[128], ch;
	int n = 0;

	printf("$ ");
	uart_init();
	sei();
	//printf("$ ");
	while(1){
		cli();
		ch = qi_delete();
		sei();
		if(ch){
			if(ch == '\r') continue;
			if(ch == '\n'){
				cmd[n] = 0;
				if(!strcmp(cmd, "app")) app_prime(2000);
				else if(!strcmp(cmd, "name")) printf("My name is 엄수현입니다\n");
				else					printf("Merong...\n");
				n = 0;
				printf("$ ");
			}
			else
				cmd[n++] = ch;
		}
	}
	return 0;
}
