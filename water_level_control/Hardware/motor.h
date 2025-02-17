#ifndef MOTOR_H
#define	MOTOR_H
#include "water_level_control.h"

sbit in_motor=P1^0;
sbit out_motor=P1^1;

void Water_In(void);
void Water_Out(void);	

#endif