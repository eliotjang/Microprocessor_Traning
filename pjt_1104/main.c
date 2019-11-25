// main.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>

#define LED_DDR (*(uint8 *)0x10a)
#define LED_PORT (*(uint8 *)0x10b)

uint8_t time_flag;
void timer_init();
main()
{
	uint8_t i;
	timer_init(); sei();
	LED_DDR = 0xff;
	LED_PORT = 0xff;
