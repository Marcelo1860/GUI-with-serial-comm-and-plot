#include "adc1.h"

void init_ADC(void)
{
//CONFIGURACION DEL PUERTO POR DEFAULT
    //(SI SE DESEA UTILIZAR OTRO PUERTO CABIAR LAS LINEAS CORRESPONDIENTES DE DICHO PUERTO)
    TRISAbits.TRISA0 = 1;       //SETEA AN0 COMO ENTRADA
    ANSELbits.ANS0 = 1;         //SETEA AN0 COMO FUNCION ANALOGICA
    set_CHANNEL(0);
    ADCON0bits.ADCS = 0b001;     //SETEA Tad CON FOSC/8 1uS
    ADCON1bits.ADFM = 1;        //JUSTIFICADO A LA DERECHA
    ADCON1bits.VCFG1 = 1;       //REFERENCIA NEGATIVA A VSS
    ADCON1bits.VCFG0 = 1;       //REFERENCIA POSITIVA A VDD
    ADCON0bits.ADON = 1;        // ENCIENDE EL MODULO

    __delay_ms(100);        
}

void set_CHANNEL(unsigned char channel)
{
    if(channel < 14,channel >= 0)                //VERIFICA QUE SEA UN CANAL VALIDO
    {
    ADCON0bits.CHS = channel;       //SETEA EL CANAL DESEADO
    }else
        {
        ADCON0bits.CHS = 0b0000;    //CANAL POR DEFAULT AN0
        }
}

int leer_ADC(void)
{
    int lectura, i = 0;
    ADCON0bits.GO_DONE = 1;
    do{
        if(ADCON1bits.ADFM == 1)
        {
        lectura = ((ADRESH << 8) & 0b1100000000) | ADRESL;
        }
        if(ADCON1bits.ADFM == 0)
        {
        lectura = ((ADRESH << 2) & 0b1111111100) | ((ADRESL>>6) & 0b0000000011);
        }
        i++;
    }while((i != 1000 ) && (ADCON0bits.GO_DONE) == 1);
    return lectura;
}

