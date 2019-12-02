#include<avr/io.h>
#include"uart.h"
#include"spm.h"
#include"mcu.h"


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
