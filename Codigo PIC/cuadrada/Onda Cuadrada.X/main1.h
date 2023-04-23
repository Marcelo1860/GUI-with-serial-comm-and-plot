#ifndef MAIN_H
#define	MAIN_H

#define _XTAL_FREQ 8000000
#include <xc.h>
#include "adc1.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "uart1.h"
#include <string.h>
#include "inttimer1.h"

#define HIGH_TEMP PORTE
#define TEMP PORTD

char buffer[20] = " ";
void config_HAL(void);


#endif	/* MAIN_H */
