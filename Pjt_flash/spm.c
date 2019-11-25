// store program memory
// spm.c
#include <avr/io.h>
#define INLPM
#include "spm.h"

#define R01 (*(uint8_t *)0x01)
#define PGBUF (*(uint16_t *)0x00)
#define ZPNTR (*(uint16_t *)0x1E)

void flash_page_erase(uint16_t pg_num)
{
	uint16_t pg_addr;

	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) << 8;
	do_SPM(pg_addr, (1 << PGERS) | (1 << SPMEN) );
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
	while(SPMCSR & ( 1 << SPMEN))
		;
}

/* 플래시 페이지 버퍼 쓰기 함수 */

void flash_page_buffer_write(uint8_t pg_buf[], uint16_t pg_bytesz)
{
	uint16_t wd_off, *wbp;

	for (wd_off=0, wbp=(uint16_t *)pg_buf; wd_off < pg_bytesz; wd_off+=2, wbp++)
		flash_page_buffer_word_write(wd_off, *wbp);
}

void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd)
{
	uint8_t r1 = R01;
	PGBUF = wd;
	ZPNTR = wd_off;

	wait_for_SPM();

	SPMCSR = (1<<SPMEN);
	asm("SPM");

	R01 = r1;
}

/* 플래시 페이지 쓰기 함수 */
void flash_page_write(uint16_t pg_num)
{
	uint16_t pg_addr;
	RAMPZ = pg_num >> 8;
	pg_addr = (pg_num & 0xff) << 8;

	do_SPM(pg_addr, (1<<PGWRT) | (1<<SPMEN));
}

/* RWW 특성 재생 함수 */
void flash_RWW_clearSB()
{
	do_SPM(0, (1<<RWWSRE) | (1<<SPMEN));
}

void flash_byte_read(uint16_t pb_addr)
{
	do_LPM_byte(pb_addr);
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
	asm("ELPM R24,Z+");
	asm("ELPM R25,Z");
}
