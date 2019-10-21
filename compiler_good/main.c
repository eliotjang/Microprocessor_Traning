#include <util/delay.h>
#define LED_DDR (*(uint8_t *)0x10a)
#define LED_PORT (*(uint8_t volatile *)0x10b)

int main() {
	LED_DDR = 0xff;
	while(1) {
		_delay_ms(1000);
		LED_PORT = 0xff;
		_delay_ms(1000);
		LED_PORT = 0X00;
	}
		return 0;
}
