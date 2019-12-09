#define ZPNTR		(*(uint16_t *) 0x1E)

uint16_t flash_word_read(uint16_t pb_addr);
uint8_t flash_page_berify(uint16_t pg_num, uint8_t pg_buf[],uint16_t pg_bytesz);
