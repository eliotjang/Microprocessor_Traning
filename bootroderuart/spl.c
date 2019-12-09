#include <avr/io.h>
#include "spl.h"
#include "spm.h"

void flash_page_buffer_write(uint8_t pg_buf[], uint16_t pg_bytesz)
{
	uint16_t wd_off, *wbp;

	for( wd_off = 0,wbp = (uint16_t *)pg_buf; wd_off < pg_bytesz; wd_off += 2, wbp++)
		flash_page_buffer_word_write(wd_off, *wbp);
}

void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd)
{
	R00 = R01;

	PGBUF = wd;
	ZPNTR = wd_off;

	wait_for_SPM();

	SPMCSR = (1<<SPMEN);
	asm("SPM");

	R01=R00;
}
void flash_page_write(uint16_t pg_num)
{
	uint16_t pg_addr;

	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) <<8;

	do_SPM(pg_addr, (1<<PGWRT) | (1<<SPMEN));
}

