// uart.h
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE *stream);
void uart_init(void);
void uart_echo(char ch);
