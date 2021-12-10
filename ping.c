/*
 * ping.c
 *
 *  Created on: Oct 27, 2021
 *      Author: egodfrey
 */
#include <ping.h>
#include <inc/tm4c123gh6pm.h>
#include <math.h>
#include <Timer.h>
#include <driverlib/interrupt.h>

void ping_init(){

    SYSCTL_RCGCGPIO_R |= 0b00000010;
    SYSCTL_RCGCTIMER_R |= 0b00001000;
    timer_waitMillis(5);
    GPIO_PORTB_AFSEL_R  &= ~0b00001000;
    GPIO_PORTB_DIR_R    &= ~0b00001000;
    GPIO_PORTB_DEN_R    |= 0b00001000;
    //GPIO_PORTB_AMSEL_R  |= 0b00001000;

//    TIMER3_CTL_R |= 0x0D08;
//    TIMER3_CFG_R |= 0x4;
//    TIMER3_TBMR_R |= 0x3;
//    TIMER3_TBILR_R |= 0xFFFF;
//    TIMER3_TBPR_R |= 0xFF00;
//    TIMER3_IMR_R |= 0x0400;
    NVIC_EN1_R |= 0x00000010;
    GPIO_PORTB_AFSEL_R |= 0b00001000;
        GPIO_PORTB_PCTL_R &= 0xFFFF0FFF;
        GPIO_PORTB_PCTL_R |= 0x00007000;


        TIMER3_CTL_R &= ~0x0100;
        //TIMER3_CTL_R |= 0x0D08;
        TIMER3_CFG_R = 0x4;
        TIMER3_TBMR_R = 0x7;
        TIMER3_CTL_R |= 0x0C00;
        TIMER3_TBILR_R |= 0xFFFF;
        TIMER3_TBPR_R |= 0xFF;
        TIMER3_IMR_R |= 0x0400;
        TIMER3_CTL_R |= 0x0100;

        IntRegister(INT_TIMER3B, TIMER3B_Handler);
        IntMasterEnable();
}

void ping_sendpulse(void){
    TIMER3_CTL_R &= ~0x0100;
    TIMER3_IMR_R &= ~0x0400;
    GPIO_PORTB_AFSEL_R &= ~0b00001000;

    GPIO_PORTB_DATA_R &= ~0b00001000;// Set PB3 to low
    GPIO_PORTB_DIR_R |= 0b00001000;// Set PB3 as output
    GPIO_PORTB_DATA_R |= 0b00001000;// Set PB3 to high
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= ~0b00001000;// Set PB3 to low
    GPIO_PORTB_DIR_R &= ~0b00001000;// Set PB3 as input

    TIMER3_ICR_R |= 0x0400;
    TIMER3_CTL_R |= 0x0100;
    TIMER3_IMR_R |= 0x0400;
    GPIO_PORTB_AFSEL_R |= 0b00001000;


}


void TIMER3B_Handler(void) {
    //if rising and mask

    if (ping_state == RISING){

        ping_state = FALLING;
        tf = TIMER3_TBR_R;
    }
        //save value

    else if (ping_state == FALLING ){
        ping_state = DONE;
        tr = TIMER3_TBR_R;
    }


        // save value

    // clear interrupts
    TIMER3_ICR_R |= 0x0400;
}

int ping_read() {
    ping_state = RISING;
    ping_sendpulse();
    while(ping_state != DONE){

    }
    t_total = (tf-tr);

    return t_total;
}

//void scanobjects(){
//    extern volatile int data;
//    extern volatile int OF;
//    volatile int distance;
//    char sendstr[100];
//
//    typedef struct values{
//        int angle;
//        double IR;
//        double sonar;
//    }values;
//
//     int init_angle[10];
//     int final_angle[10];
//     int widths[10];
//     values aarray[90];
//     double IR =0;
//
//    servo_init();
//    lcd_init();
//    ping_init();
//    adc_init();
//
//    int i = 0;//Current Angle
//    int smallest = 0;//Smallest object
//    int items = 0;// Amount of items
//    int obj = 0;// Boolean used to detect if on an object or not
//    int oa = 1; //Used to count angles
//    int angle = 0;
//
//    for(i = 0; i <= 180; i += 2 ){
//            angle = i; // Current angle
//            servo_move(angle); // Spanning the sensors
//
//            ping_sendpulse();// Used for sonar
//            ping_read();
//
//            int ping = (adc_read());
//            IR = -1.745222 + (48.34164 + 1.745222) / pow((1 + pow((ping/743.249), 516.1554)), .002017931);// Shift IR-- BOT 10
//
//            aarray[angle].angle = angle;//Put everything inside struct
//            aarray[angle].IR = IR;
//            aarray[angle].sonar = distance;
//
//            if(IR < 60.0 && obj == 0){ //Currently on an object
//                obj = 1;
//                init_angle[oa] = i;
//            }
//            else if(IR> 60.0 && obj == 1){//Finished looking at object
//               final_angle[oa] = i;
//               widths[oa] = sqrt(pow(aarray[init_angle[oa]].sonar, 2) + pow(aarray[final_angle[oa]].sonar, 2) - (2 * aarray[init_angle[oa]].sonar * aarray[final_angle[oa]].sonar * cos(final_angle[oa] - init_angle[oa])));
//
//               if(widths[oa] < smallest && widths[oa] != 0){//Check if the width of the object is the smallest
//                smallest = oa;
//               }
//                oa++;
//                obj = 0;
//                items++;
//            }
//
//            timer_waitMillis(100);
//
//           lcd_printf("Angle: %d \n IR: %lf \n Objects: %d \n", aarray[angle].angle, aarray[angle].IR, items);
//
//        }
//}
