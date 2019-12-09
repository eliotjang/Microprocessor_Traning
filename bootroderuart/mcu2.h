void flash_page_buffer_write(uint8_t pg_buf[], uint16_t pg_bytesz);
void flash_page_erase(uint16_t pg_num);
void flash_page_write(uint16_t pg_num);
void flash_RWW_clearSB(void);

//uint8_t flash_page_verify(uint16_t pg_num, uint8_t pg_buf[], uint16_t pg_bytesz);

void uart_TX_BYTE(uint8_t by);
uint8_t uart_RX_byte(void);
uint16_t get_flash_page_number(void);
//uint8_t get_flash_page(uint8_t pgbuf, uint16_t pg_bytesz);
