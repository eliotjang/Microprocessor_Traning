#include <avr/io.h>
#include "read.h"


void flash_byte_read(uint16_t pb_addr)
{
	do_LPM_word(pb_addr);
	return;
}
void flash_word_read(uint16_t pw_addr)
{
	do_LPM_word(pw_addr);
	return;
}

void do_LPM_byte(uint16_t pb_addr)
{
	ZPNTR = pb_addr;
	asm("ELPM R24,Z");
}

void do_LPM_word(uint16_t pw_addr)
{
	ZPNTR = pw_addr;
	
	asm("ELPM R24,Z+ ");
	asm("ELPM R25,Z");
}


