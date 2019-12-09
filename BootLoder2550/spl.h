#define PGBUF	(*(uint16_t *)0x00)
#define ZPNTR	(*(uint16_t *)0x1E)
#define R00		(*(uint8_t *)0x00)
#define R01		(*(uint8_t *)0x01)

void wait_for_SPM(void);
void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd);
void flash_page_buffer_word_write(uint16_t wd_off, uint16_t wd);
void flash_page_buffer_write(uint8_t pg_buf[], uint16_t pg_bytesz);
void flash_page_write(uint16_t pg_num);
