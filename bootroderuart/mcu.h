#if defined __AVR_ATMEGA2560__

#define MCU_TYPE			0x88
#define MCU_FLASHSZ			'q'
#define MCU_PAGESZ			'T'
#define MCU_EEPROMSZ		'4'
#define PageByteSize		256

#endif

#define MCU_BOOTSZ			'e'

#define MCU_HELLO			'>'
#define MEGA_FINE			'<'
#define MCU_FLASH_GET		'!'
#define MCU_FLASH_PAGE_OK	'!'
#define MCU_FLASH_CKSUM_ERR	'@'
#define MCU_FLASH_VRIFY_ERR	'@'
