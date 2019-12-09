#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include "spm.h"
#include "spl.h"
#include "bootroader.h"
#include "mcu1.h"
#include "mcu1.h"
#include "mcu2.h"

void exec_app_code(void);

int main(void)
{
   uint8_t i;

   uart_init();
   uart_TX_byte(MCU_HELLO);
   
   for(i=0; i<10;i++){
      _delay_ms(100);
      if(!uart_RX_empty())
         break;
   }
   if(!uart_RX_empty()){
      if(uart_RX_byte() == MEGA_FINE){
         send_device_ID();
         load_flash();
      }
   }
   exec_app_code();
   return(0);
}

void exec_app_code(void)
{
   RAMPZ = 0;
   sbi(MCUCR, (1<<IVCE));
   cbi(MCUCR, (1<<IVSEL));
   asm("jmp 0x0000");
}
