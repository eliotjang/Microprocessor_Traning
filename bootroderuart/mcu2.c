#include <avr/io.h>
#include "mcu1.h"
#include "mcu2.h"
#include "spl.h"
#include "spm.h"
#include "bootroader.h"
#include "berify.h"

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
void load_flash(void)
{
   uint8_t page_buf[PageByteSize];
   uint16_t page_num;

   uart_TX_byte(MCU_FLASH_GET);

   while(1){
      page_num = get_flash_page_number();
      if(page_num == 0xffff)
         return;
      if(get_flash_page(page_buf, sizeof(page_buf))){
         flash_page_buffer_write(page_buf, sizeof(page_buf));
         flash_page_erase(page_num);
         flash_page_write(page_num);
         flash_RWW_clearSB();
         if(flash_page_verify(page_num, page_buf, sizeof(page_buf)))
            uart_TX_byte(MCU_FLASH_PAGE_OK);
         else
            uart_TX_byte(MCU_FLASH_VRIFY_ERR);
      }
      else{
         uart_TX_byte(MCU_FLASH_CKSUM_ERR);
      }
   }
}
