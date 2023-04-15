/*
 * File:   newmain.c
 * Author: Baders
 *
 * Created on 12 de abril de 2023, 20:47
 */


#include "main.h"

int main()
{
    unsigned long int temperatura = 0;
    int contador = 0;
    
    OSCCONbits.IRCF = 0b111;        //SETEA EL CLOCK EN 8MHz
    
    config_HAL();
    init_ADC();
    HIGH_TEMP = 0x00;
    TEMP = 0x00;
    uart_init();
    
    while(1)
    {
        strcpy(buffer,"   ");
        temperatura = leer_ADC();
        temperatura = temperatura*100;
        temperatura = temperatura/1023;
        temperatura = temperatura/10;
        contador ++;
        if (contador == 1000)
        {
            sprintf(buffer, "%ld", temperatura);// utiliza sprintf para convertir el número a una cadena de caracteres
            buffer[19] = ';';
            uart_send_text(buffer);
            contador = 0;
        }

//        __delay_ms(100);        //Espera entre lecturas para estabilizar módulo y señal
        HIGH_TEMP = 0x00;
        TEMP = 0x00;
        switch(temperatura)
        {
            case 10:
                HIGH_TEMP |= 0x03;
            case 9:
                HIGH_TEMP |= 0x01;
            case 8:
                if(temperatura<9)
                    {
                    HIGH_TEMP = 0x00;
                    }
                TEMP |= 0xFF;
            case 7:
                TEMP |= 0xFF>>1;
            case 6:
                TEMP |= 0xFF>>2;
            case 5:
                TEMP |= 0xFF>>3;
            case 4:
                TEMP |= 0xFF>>4;
            case 3:
                TEMP |= 0xFF>>5;
            case 2:
                TEMP |= 0xFF>>6;
            case 1:
                TEMP |= 0xFF>>7;
                break;      
        }
        
    } 

    return (0);
}

void config_HAL(void)
{
    TRISD = 0x00;
    TRISE = 0x00;
    ANSEL = 0x00;
    ANSELH = 0x00;
}
