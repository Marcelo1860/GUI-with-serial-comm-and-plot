#ifndef ADC_H
#define	ADC_H
#define _XTAL_FREQ 8000000
#include <xc.h>

void init_ADC(void);
void set_CHANNEL(char channel);
int leer_ADC(void);



#endif	/* ADC_H */


