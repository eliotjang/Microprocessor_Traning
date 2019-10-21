
#include <avr/interrupt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <avr/io.h>
#include<util/delay.h>
#include"uart.h"
#include"queue.h"
int main()
{
	char cmd[128],*cp;
	int n;
	uart_init();
	sei();
	while(1){
		printf("$  ");
		if(scanf("%s %d",cmd,&n)<0)
			break;
		if((cp=strtok(cmd,"\n\r\t "))==NULL) continue;
		if(!strcmp(cmd,"prime")) app_prime(n);
		else printf("Unknown command...\n");
	}
	printf("logout,good bye!!\n");
	while(1);
}
