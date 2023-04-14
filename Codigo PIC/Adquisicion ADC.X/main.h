#ifndef MAIN_H
#define	MAIN_H

#define _XTAL_FREQ 8000000
#include <xc.h>
#include "adc.h"

#define HIGH_TEMP PORTE
#define TEMP PORTD

void config_HAL(void);


#endif	/* MAIN_H */


