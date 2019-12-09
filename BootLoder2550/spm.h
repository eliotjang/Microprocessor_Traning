#define ZPNTR	(*(uint16_t *)0x1E)

void do_SPM(uint16_t pg_num, uint8_t spm_cmd);
void flash_page_erase(uint16_t pg_num);
void wait_for_SPM();
void do_SPM(uint16_t pg_addr, uint8_t spm_cmd);
void do_SPM(uint16_t pg_num, uint8_t spm_cmd);
