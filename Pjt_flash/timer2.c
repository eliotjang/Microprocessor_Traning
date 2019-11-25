// timer2.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include "timer2.h"
void timer2_init(void) {
	TCNT2=0;
	sbi(ASSR,AS2);
	sbi(TIMSK2, TOIE2);
	TCCR2B |= (1<<CS22) | (1<<CS20);
}
ISR(TIMER2_OVF_vect) {
	static  int count = 0;
	TCNT2=0;
	if((++count%4)==0)
		time_flag = 1;
	//time_flag=1;
}
