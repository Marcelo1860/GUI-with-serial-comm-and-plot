/*
 * File:   newmain.c
 * Author: Baders
 *
 * Created on 12 de abril de 2023, 20:47
 */


#include "main1.h"

// Variables globales
volatile unsigned int muestras[40]; // Array para almacenar las muestras
volatile unsigned char contador = 0; // Contador de muestras
volatile float stop = 1;
volatile float datoenv = 0;
int main()
{

    //OSCCONbits.IRCF = 0b111;        //SETEA EL CLOCK EN 8MHz
    OSCCONbits.OSTS = 1;
    OSCCONbits.HTS = 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.SCS = 0;
    config_HAL();
    init_ADC();
    uart_init();
    init_inttimer();
    ADCON0bits.GO = 1;
    
    while(1)
    {
        
        // Esperar a que se adquieran las 40 muestras
        while (contador < 40);
        //PIE1bits.TMR1IE = 0;//se desactiva interrupcon del timer1
        PIE1bits.ADIE = 0; // deshabilitar las interrupciones del ADC
        // Hacer algo con las muestras
        for(int i=0; i<=40; i++){
            strcpy(buffer,"   ");
            datoenv = muestras[i]*(5.0/1023.0);
            sprintf(buffer, "%f", datoenv);// utiliza sprintf para convertir el n�mero a una cadena de caracteres
            buffer[19] = ';';
            uart_send_text(buffer);    
        }
        strcpy(buffer,"   ");
        sprintf(buffer, "%f",stop );// utiliza sprintf para convertir el n�mero a una cadena de caracteres
        buffer[19] = ';';
        uart_send_text(buffer); 

        
        // Reiniciar el contador y el proceso de adquisici�n de muestras
        contador = 0;
        ADCON0bits.GO = 1;
        //PIE1bits.TMR1IE = 1;//se activa interrupcon del timer1
        PIE1bits.ADIE = 1; // Habilitar las interrupciones del ADC
    } 

    return (0);
}

void interrupt TMR1_ISR() {
        PIR1bits.ADIF = 0; // Limpiar la bandera de interrupción del ADC
        muestras[contador] = ((ADRESH << 8) & 0b1100000000) | ADRESL; // Almacenar el valor de ADRESH y ADRESL en el array de muestras
        //muestras[contador] = ADRESH;
        contador++; // Incrementar el contador de muestras
        if (contador < 40) {
            ADCON0bits.GO = 1; // Iniciar la siguiente conversi�n
        }

    //PIR1bits.TMR1IF = 0; // Limpiar la bandera de interrupci�n del temporizador 1
}

void config_HAL(void)
{
    TRISD = 0x00;
    TRISE = 0x00;
    ANSEL = 0x00;
    ANSELH = 0x00;
}
