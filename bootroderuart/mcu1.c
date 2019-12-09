#include <avr/io.h>
#include "bootroader.h"
#include "mcu1.h"



void send_device_ID(void)
{
   uart_TX_byte(MCU_TYPE);
   uart_TX_byte(MCU_FLASHSZ);
   uart_TX_byte(MCU_BOOTSZ);
   uart_TX_byte(MCU_PAGESZ);
   uart_TX_byte(MCU_EEPROMSZ);
}

uint16_t get_flash_page_number(void)
{
   uint8_t pg_num_hi, pg_num_lo;

   pg_num_hi = uart_RX_byte();
   pg_num_lo = uart_RX_byte();

   return((uint16_t)((pg_num_hi <<8) + + pg_num_lo));
}

uint8_t get_flash_page(uint8_t pg_buf[],uint16_t pg_bytesz)
{
   uint16_t i;
   uint8_t checksum =0 , received_checksum;
   for ( i=0; i< pg_bytesz; i++){
      pg_buf[i] = uart_RX_byte();
      checksum += pg_buf[i];
      }

      received_checksum = uart_RX_byte();
      if (checksum == received_checksum)
         return 1;
      else
         return 0;
}
