#include "inttimer1.h"


void init_inttimer(void){
    // Configurar el temporizador 1 para generar interrupciones cada 25 us
    T1CONbits.TMR1CS = 0; // Fosc/4 como fuente de reloj
    T1CONbits.T1CKPS = 0b00; // Sin divisor de reloj
    T1CONbits.T1SYNC = 0; // No sincronizar con reloj externo
    TMR1H = 0xFF; // Cargar el valor de cuenta inicial para generar interrupciones cada 25 us
    TMR1L = 0xE7;
    PIR1bits.RCIF = 0; // Limpiar la bandera de interrupci�n
    PIE1bits.RCIE = 1; // Habilitar las interrupciones de RX
    PIR1bits.ADIF = 0; // Limpiar la bandera de interrupci�n
    PIE1bits.ADIE = 1; // Habilitar las interrupciones del ADC
    INTCONbits.PEIE = 1; // Habilitar las interrupciones perif�ricas
    INTCONbits.GIE = 1; // Habilitar las interrupciones globales
    //T1CONbits.TMR1ON = 1; // Encender el temporizador 1
}