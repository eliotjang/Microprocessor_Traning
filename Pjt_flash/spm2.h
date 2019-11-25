// spm2.h
#include <avr/io.h> //for uint8_t

uint16_t flash_word_read(uint16_t pw_addr);
uint8_t flash_page_verify(uint16_t pg_num, uint8_t pg_buf[], uint16_t pg_bytesz);
