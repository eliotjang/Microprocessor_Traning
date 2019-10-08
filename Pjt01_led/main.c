// coded by eliotjang
// 2019.10.07
// main.c
#include <util/delay.h>
#include "led.h"
int main(void)
{
	int i; // uint8_t will not work.
	// because it don't have minus..
	// but also not work with int.. because of casting. maybe?
	led_init();
	_delay_ms(1500);
	led_on_all();
	_delay_ms(1500);
	led_off_all();
	_delay_ms(1500);
	for ( i=0 ; i<7; i++) {
		led_on(i);
		_delay_ms(500);
	}
	led_off(0), _delay_ms(500);
	led_off(2), _delay_ms(500);
	led_off(4), _delay_ms(500);
	led_off(6), _delay_ms(500);

	_delay_ms(1000);
	led_mask(0), led_mask(1);
	_delay_ms(500);
	led_mask(2), led_mask(3);
	_delay_ms(500);
	led_mask(4), led_mask(5);
	_delay_ms(500);
	led_mask(6), led_mask(7);
	_delay_ms(500);
	// it's not work what I expect...
	
	while(1)
		;	// for readability
	return 0;
}
