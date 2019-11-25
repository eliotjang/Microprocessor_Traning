// spm.h
#include <avr/io.h> //for uint8_t

#ifdef INLPM
	void flash_byte_read(uint16_t pb_addr);
#else
	uint8_t flash_byte_read(uint16_t pb_addr);
#endif

void do_SPM(uint16_t pg_addr, uint8_t spm_cmd);
void wait_for_SPM(void);
void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd);
void flash_page_erase(uint16_t pg_num);
void wait_for_SPM();
void flash_page_buffer_write(uint8_t pg_buf[], uint16_t pg_bytesz);
void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd);
void flash_page_write(uint16_t pg_num);
void flash_RWW_clearSB();
void do_LPM_byte(uint16_t pb_addr);
void do_LPM_word(uint16_t pw_addr);
void flash_byte_read(uint16_t pb_addr);
void flash_word_read(uint16_t pw_addr);
uint8_t flash_page_verify(uint16_t pg_num, uint8_t pg_buf[], uint16_t pg_bytesz);
