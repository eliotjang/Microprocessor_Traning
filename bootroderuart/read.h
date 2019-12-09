#define ZPNTR		(*(uint16_t *) 0x1E)
#define inread
void do_LPM_byte(uint16_t pb_addr);
void do_LPM_word(uint16_t pw_addr);


#ifdef inread
	void flash_byte_read(uint16_t pb_addr);
#else
	uint8_t flash_byte_read(uint16_t pb_addr);
#endif

#ifdef inread
	void flash_word_read(uint16_t pb_addr);
#else
	uint8_t flash_word_read(uint16_t pb_addr);
#endif
