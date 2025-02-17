//定时器模块定义
#ifndef TIMER_H
#define TIMER_H

#include "water_level_control.h"
#define CLK_FRE 12000000 	//时钟频率
#define CLK_DIV 12			//机器周期分频

void Timer_Init();

#endif