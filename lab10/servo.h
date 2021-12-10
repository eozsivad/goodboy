/*
 * servo.h
 *
 *  Created on: Nov 9, 2021
 *      Author: egodfrey
 */

#ifndef SERVO_H_
#define SERVO_H_

volatile signed pulse_width;
void servo_init();
int servo_move(double degrees);

#endif /* SERVO_H_ */
