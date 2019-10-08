// coded by eliotjang
// 2019.10.07
// led.c
#include <avr/io.h>
#include "led.h" // declare of struct things..

uint8_t Leds;

void led_init(){
	Leds = DDRL = PORTL = 0xff;
}
void led_on_all(){
	Leds = PORTL = 0x00;
}
void led_off_all(){
	Leds = PORTL = 0xff;
}
void led_on(uint8_t led_no){
	Leds &= ~(1 << led_no);
	PORTL = Leds;
}
void led_off(uint8_t led_no){
	Leds |= (1 << led_no);
	PORTL = Leds;
}
void led_mask(uint8_t led_mask){
	Leds = ~led_mask;
	PORTL = Leds;
}
