
#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
//#include "uart.h" // 이걸해주니까 계속 컴파일만 한다.!!;;;

#define Q_size 8

static char buf[64];
static int volatile bufi,txend;


void uart_init();

int uart_putchar_3(char ch, FILE *stream);


int is_prime(int n);

int uart_getchar_3(FILE *stream);

void uart_echo(char ch);
