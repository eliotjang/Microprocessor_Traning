#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "app_list.h"
#include "queue.h"
#include "uart.h"

int main()
{
	char cmd[128], *cp, *ap;
	int n = 0;

	uart_init();
	sei();
	while(1) {
		printf( "$ " );
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if ((cp = strtok(cmd, "\n\r\t  ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t  ");
		if (!strcmp(cmd, "prime")) app_prime(ap);
		else if (!strcmp(cmd, "list" )) app_list(ap);
		else printf( "Unknown command...\n" );
		printf("logout, good bye !!!\n" );
		while(1);
	}
}
