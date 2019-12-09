#include <avr/io.h>
#include "berify.h"
/*
uint8_t flash_page_berify(uint16_t pg_num, uint8_t pg_buf[],uint16_t pg_bytesz)
{
	uint16_t pg_addr, wd_off, wd, *wbp;

	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) << 8;

	for(wd_off = 0, wbp = (uint16_t *)pg_buf; wd_off < pg_bytesz; wd_off += 2, wbp++)
	{
		wd = flash_word_read(pg_addr + wd_off);
			if(wd != *wbp)
				return 0;
 	}

	return 1;
}
*/
