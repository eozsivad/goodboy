#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "open_interface.h"
#include "uart.h"

void movement_init(oi_t* s);

void move_forward(int centimeters);

void move_backward(int centimeters);

void move_backward_unsafe(int centimeters);

void turn_right(int degrees);

void turn_left(int degrees);

int checkInterrupts();

void move();

void push_w();
void push_a();
void push_s();
void push_d();

volatile int botX;
volatile int botY;
volatile int botAngle;
volatile struct position {
    char appCommand;
    int objectX;
    int objectY;
} currentPosition;
//
//// Moves the robot forward in cm
//void move_forward(oi_t *sensor, int centimeters);
//
////turns the robot given degrees
//void turn_clockwise(oi_t *sensor, int degrees);
//
////bump right if right bumper is hit
//void bump_right(oi_t *sensor);
//
////bump left if left bumper is hit
//void bump_left(oi_t *sensor);
//
//void turn_counter(oi_t *sensor, int degrees);
//
//void move_backward(oi_t *sensor, int centimeters);
//
//bool hole(oi_t* sensor_data);
//
//bool cliff(oi_t* sensor_data);
#endif /* MOVEMENT_H_ */
