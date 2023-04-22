#include "uart.h"

void uart_init(void)
{

    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    TXSTAbits.BRGH = 0;             //SETEO EL BAUDRATE EN MODO 8bits
    BAUDCTLbits.BRG16 = 1;          //SETEO EL BAUDRATE EN MODO 8bits


    /*con esto la formula del baudrate es:
     * BaudRate = Fosc/(64*([SPBRGHx:SPBRGx]+1))
     * [SPBRGHx:SPBRGx] =  (Fosc/(16*BaudRate))-1
     * Fosc = 8000000                           20MHz
     * BaudRate = 9600                          9600
     * [SPBRGH:SPBRG] = 51.083333 ~= 51         129.2 ~= 130
     */

    SPBRG = 51;                   //SETEO EL BAUDRATE EN 9600
    TXSTAbits.SYNC = 0;           //SETEO LA UART COMO ASICRONA
    RCSTAbits.SPEN = 1;           //HABILITO EL PUERTO SERIE
    RCSTA = 0b10010000;           //SPEN=1, CREN=1, addr-det disabled.

}


char uart_receive_1(void)       //SE UTILIZA PARA EL CASO DE LAS INTERRUPCIONES
{
    unsigned int conta = 0;
    char salida = 0;
    if(RCSTAbits.OERR)          //SI SE PRODUJO UN ERROR DE OVERRUN
        {
        RCSTAbits.CREN = 0;     //RESETEANDO LA HABILITACION PARA RECEPCCION SE BORRA EL ERROR
        RCSTAbits.CREN = 1;
        }
    while(!RCIF && (conta != 1000))
        {
        conta++;
        __delay_us(100);
        }
    if(conta != 1000)
        {
        RCIF = 0;
        salida = RCREG;
        }else
            {
            salida = 255;            
            }
    return salida;
}

char uart_receive(void)
{
    do{
    if(RCSTAbits.OERR)          //SI SE PRODUJO UN ERROR DE OVERRUN
        {
        RCSTAbits.CREN = 0;     //RESETEANDO LA HABILITACION PARA RECEPCCION SE BORRA EL ERROR
        RCSTAbits.CREN = 1;
        }
    }while(!RCIF);
    RCIF = 0;
    return RCREG;
}

void uart_send(char data)
{
    TXEN = 1;
    while (TXIF == 0);   // wait until TXREG is not busy
    TXREG = data;        // send character
}

void uart_text_receive(char *buffer)
{
        while(1)
        {
        *buffer = uart_receive();
        if(*buffer == ';')              //EL TERMINAL VIRTUAL NO ENVIA CORRECTAMENTE EL '\0'
            {
            break;
            }
            else{
                buffer++;
                }
        }

}

void uart_send_text(char *buffer)
{
    char aux;
    do{
        aux = *buffer;
        uart_send(aux);
        buffer++;
    }while(*buffer != ';');//EL TERMINAL VIRTUAL NO ENVIA CORRECTAMENTE EL '\0'
    uart_send('\r');
    uart_send('\n');
}


void reinicia_uart(void)        //SIRVE PARA FORZAR EL REINICIO DE LA UART EN EL CASO QUE HAGA FALTA
{
RCSTAbits.SPEN = 0;           //DESHABILITO EL PUERTO SERIE
RCSTAbits.CREN = 0;
RCSTAbits.SPEN = 1;           //HABILITO EL PUERTO SERIE
RCSTAbits.CREN = 1;
}
