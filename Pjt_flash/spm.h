#include <avr/io.h>
#ifdef INLPM
	void flash_byte_read(uint16_t pb_addr);
	void flash_word_read(uint16_t pw_addr);
#else
	uint8_t flash_byte_read(uint16_t pb_addr);
	uint16_t flash_word_read(uint16_t pw_addr);
#endif
void flash_RWW_clearSB();

#define ZPNTR (*(uint16_t*)0x1E)
#define PGBUF (*(uint16_t *)0x00)

#define R01 (*(uint8_t *)0x01)
#define R00 (*(uint8_t *)0x00)
void do_SPM(uint16_t pg_num , uint8_t spm_cmd);
void wait_for_SPM(void);
void do_LPM_byte(uint16_t pb_addr);
void do_LPM_word(uint16_t pw_addr);
void flash_page_buffer_word_write(uint16_t wd_off,uint16_t wd);
void flash_page_erase(uint16_t pg_num);
void flash_page_buffer_write(uint8_t pg_buf[],uint16_t pg_bytesz);
void flash_page_buffer_word_write(uint16_t wd_off,uint16_t wd);
void flash_page_write(uint16_t pg_num);
void flash_page_buffer_word_write(uint16_t wd_off,uint16_t wd);

uint8_t flash_page_verify(uint16_t pg_num , uint8_t pg_buf[] , uint16_t pg_bytesz);
