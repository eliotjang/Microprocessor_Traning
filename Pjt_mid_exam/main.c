//main.c
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "timer2.h"

void pr_time(int sec);

int main()
{
	int sec = 0;
	//uint8_t h,m,s;
	uart_init();
	timer2_init(); sei();
	//h=m=s=0;
	while(1) {
		while(!time_flag);
		time_flag = 0;
		sec++;
		pr_time(sec);
	}
}
void pr_time(int sec)
{
	int ss, mm, hh;
	ss = sec % 60; sec = sec / 60;
	mm = sec % 60; sec = sec / 60;
	hh = sec;
	printf("%.2d:%.2d:%.2d\n",hh,mm,ss);
	/*for(h=0,m=0,s=0; ;s++) {
		time_flag=0;
		while(time_flag ==0);
		if(s==60) {
			m++;
			s=0;
		}
		else if(m==60) {
			h++;
			m=0;
		}
		printf("%2d:%2d:%2d\n",h,m,s);
	}*/
}
