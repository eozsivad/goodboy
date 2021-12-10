/*
 * adc.c
 *
 *  Created on: Oct 20, 2021
 *      Author: egodfrey
 */


#include <adc.h>
#include <inc/tm4c123gh6pm.h>
#include <math.h>

void adc_init(){

    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0b00000010;
    timer_waitMillis(5);
    GPIO_PORTB_AFSEL_R  |= 0b00010000;
    GPIO_PORTB_DIR_R    &= ~0b00010000;
    GPIO_PORTB_DEN_R    &= ~0b00010000;
    GPIO_PORTB_AMSEL_R  |= 0b00010000;
    //GPIO_PORTB_ADCCTL_R &= 0x00;

    ADC0_ACTSS_R    &= ~0b00000010;
    ADC0_EMUX_R     &= ~0xF0;
    ADC0_SSCTL1_R   &= ~0x0F;
    ADC0_SSCTL1_R     |= 0x06;
    ADC0_SAC_R       |= 0x04;
    ADC0_SSMUX1_R     &= ~0xF0;
    ADC0_SSMUX1_R     |= 0x0A;
    ADC0_ACTSS_R    |= 0b00000010;

}

int adc_read(void){
    unsigned int value;

    ADC0_PSSI_R  |= 0b00000010;
    while((ADC0_RIS_R & 0x02) == 0);
    value = (unsigned int)ADC0_SSFIFO1_R & 0x00000FFF;
    ADC0_ISC_R      |= 0b00000010;
    return value;
}

float adc_conversionIR(int IRrawvalue){
    int a = 144600;
    float b = -1.198;
    return a * pow(IRrawvalue, b);
}
