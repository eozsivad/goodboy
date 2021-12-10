/*
 * adc.h
 *
 *  Created on: Oct 20, 2021
 *      Author: egodfrey
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "Timer.h"

void adc_init();

int adc_read(void);

float adc_conversionIR(int IRrawvalue);
#endif /* ADC_H_ */
