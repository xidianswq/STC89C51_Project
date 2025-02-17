#include "motor.h"

void Water_In(void)
{
	in_motor=1;
	out_motor=0;
}

void Water_Out(void)
{
	in_motor=0;
	out_motor=1;
}