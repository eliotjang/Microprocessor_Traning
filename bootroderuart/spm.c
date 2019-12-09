#include <avr/io.h>
#include "spm.h"


void flash_page_erase(uint16_t pg_num)
{
	uint16_t pg_addr;

	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) << 8;
	do_SPM(pg_addr, (1 << PGERS) | (1 << SPMEN));
}

void do_SPM(uint16_t pg_addr, uint8_t spm_cmd)
{
	wait_for_SPM();

	ZPNTR = pg_addr;
	SPMCSR = spm_cmd;
	asm("SPM");
}

void wait_for_SPM()
{
	while(SPMCSR & (1 << SPMEN))
				;
}

void flash_RWW_clearSB()
{
	do_SPM(0, (1<<RWWSRE) | (1<<SPMEN));
}

