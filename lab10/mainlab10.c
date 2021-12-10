/*
 * main.c
 *
 *  Created on: Oct 27, 2021
 *      Author: egodfrey
 */

#include "lcd.h"
#include "uart.h"
//#include "button.h"
//#include "lab5_scan_data.h"
#include "adc.h"
#include "timer.h"
#include "ping.h"
#include "servo.h"
#include <math.h>
#include <alarm.h>
#include "detection.h"
#define PI 3.14159265358979323846

//extern volatile int data;
//extern volatile int OF;
//volatile int distance;
//
//
//typedef struct values{
//    int angle;
//    double IR;
//    double sonar;
//}values;
//
// int init_angle[10];
// int final_angle[10];
// int widths[10];
// values aarray[90];
// double IR =0;

int main(void) {
    oi_t* sensor_data = oi_alloc();
    oi_init(sensor_data);

    servo_init();
    lcd_init();
    ping_init();
    adc_init();
    movement_init(sensor_data);
    uart_init(115200);

    char a;
//    scan_area();

    while(1){
        a = uart_receive();
        if (a == 'w'){
            move_forward(15);
        }
        else if (a == 's'){
            move_backward(15);
        }
        else if (a == 'a'){
            turn_left(22);
        }
        else if (a == 'd'){
            turn_right(22);
        }
        else if (a == 'q'){
            scan_area();
        }
    }









//    int i = 0;//Current Angle
//    int smallest = 100;//Smallest object
//    int items = 0;// Amount of items
//    int obj = 0;// Boolean used to detect if on an object or not
//    int oa = 1; //Used to count angles
//    int angle = 0;
//
//    for(i = 0; i <= 180; i += 2 ){
//        angle = i; // Current angle
//        servo_move(angle); // Spanning the sensors
//
//        ping_sendpulse();// Used for sonar
//        ping_read();
//
//        int ping = (adc_read());
//        IR = -1.745222 + (48.34164 + 1.745222) / pow((1 + pow((ping/743.249), 516.1554)), .002017931);// Shift IR-- BOT 10
//
//        aarray[angle].angle = angle;//Put everything inside struct
//        aarray[angle].IR = IR;
//        aarray[angle].sonar = distance;
//
//        if(IR < 45.0 && obj == 0){ //Currently on an object
//            obj = 1;
//            init_angle[oa] = i;
//        }
//        else if(IR> 45.0 && obj == 1){//Finished looking at object
//           final_angle[oa] = i;
//           widths[oa] = sqrt(pow(aarray[init_angle[oa]].sonar, 2) + pow(aarray[final_angle[oa]].sonar, 2) - (2 * aarray[init_angle[oa]].sonar * aarray[final_angle[oa]].sonar * cos(final_angle[oa] - init_angle[oa])));
//
//           if(widths[oa] < smallest && widths[oa] != 0){//Check if the width of the object is the smallest
//            smallest = oa;
//           }
//            oa++;
//            obj = 0;
//            items++;
//        }
//
//        timer_waitMillis(100);
//
//       lcd_printf("Angle: %d \n IR: %lf \n Objects: %d \n", aarray[angle].angle, aarray[angle].IR, items);
//
//    }

}
