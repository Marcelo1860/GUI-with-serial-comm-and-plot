#ifndef UART_H
#define	UART_H


#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#include <xc.h>

void uart_init(void);
char uart_receive(void);
char uart_receive_1(void);
void uart_send(char data);
void uart_text_receive(char *buffer);
void uart_send_text(char *buffer);
void reinicia_uart(void);

#endif	/* UART_H */

