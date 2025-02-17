//定时器模块定义
#ifndef TIMER_H
#define TIMER_H

#include "water_level_control.h"
#define CLK_FRE 12000000 	//时钟频率
#define CLK_DIV 12			//机器周期分频

extern unsigned long int system_tick;	//系统节拍

void delay_s(u16 s);
void delay_10us(u16 ten_us);
void delay_ms(u16 ms);

void Timer_Init();

#endif