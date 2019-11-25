// store program memory
// spm2.c
#include <avr/io.h>
#include "spm2.h"

#define R01 (*(uint8_t *)0x01)
#define PGBUF (*(uint16_t *)0x00)
#define ZPNTR (*(uint16_t *)0x1E)

uint8_t flash_page_verify(uint16_t pg_num, uint8_t pg_buf[], uint16_t pg_bytesz)
{
	uint16_t pg_addr, wd_off, wd, *wbp;

	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) << 8;
	for (wd_off=0, wbp=(uint16_t *)pg_buf; wd_off<pg_bytesz; wd_off+=2, wbp++) {
		wd = flash_word_read(pg_addr + wd_off);
		if (wd != *wbp)
			return 0;
	}
	return 1;
}
