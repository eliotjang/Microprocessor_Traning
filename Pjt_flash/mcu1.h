#include <avr/io.h>

#define MCU_TYPE 0x88
#define MCU_FLASHSZ 'q'
#define MCU_PAGESZ 'T'
#define MCU_EEPROMSZ '4'
#define PageByteSize 256
#define MCU_BOOTSZ 'e'
#define MCU_HELLO '>'
#define MEGA_FINE '<'
#define MCU_FLASH_GET '!'
#define MCU_FLASH_PAGE_OK'!'
#define MCU_FLASH_CKSUM_ERR '@'
#define MCU_FLASH_VRIFY_ERR '@'

void send_device_ID(void);
uint16_t get_flash_page_number(void)
uint8_t get_flash_page(uint8_t pg_buf[], uint16_t pg_bytesz)
