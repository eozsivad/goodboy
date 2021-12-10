/*
 * ping.h
 *
 *  Created on: Oct 27, 2021
 *      Author: egodfrey
 */

#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include "Timer.h"

enum {RISING, FALLING, DONE} ping_state;
int tr,tf,t_total;

void ping_init();

void TIMER3B_Handler(void);
void ping_sendpulse(void);
int ping_read();
#endif /* PING_H_ */
