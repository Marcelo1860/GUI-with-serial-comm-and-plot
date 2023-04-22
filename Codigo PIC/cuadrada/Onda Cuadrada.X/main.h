#ifndef MAIN_H
#define	MAIN_H

#define _XTAL_FREQ 8000000
#include <xc.h>
#include "adc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "uart.h"
#include <string.h>
#include "inttimer.h"

#define HIGH_TEMP PORTE
#define TEMP PORTD

char buffer[20] = " ";
void config_HAL(void);


#endif	/* MAIN_H */
