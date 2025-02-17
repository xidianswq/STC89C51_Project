//通用头文件定义
#ifndef WATER_LEVEL_CONTROL_H
#define WATER_LEVEL_CONTROL_H
#include<reg52.h>
#include "stdio.h"

//定义最高，最低水位时超声波测距的距离（cm）
#define WATER_DISTANCE_MAX		 0
#define WATER_DISTANCE_MIN 		15
//允许波动幅度
#define LEVEL_WAVE				1	
#define WATER_LEVEL_INT(dis)		(dis<WATER_DISTANCE_MAX||dis>WATER_DISTANCE_MIN)?(dis<WATER_DISTANCE_MAX?WATER_DISTANCE_MAX:WATER_DISTANCE_MIN):dis
#define WATER_LEVEL_PERCENT(dis) 	(dis<WATER_DISTANCE_MAX||dis>WATER_DISTANCE_MIN)?(dis<WATER_DISTANCE_MAX?100:0):(WATER_DISTANCE_MIN-dis)*100/(WATER_DISTANCE_MIN-WATER_DISTANCE_MAX) 
typedef unsigned int u16;		//对系统默认数据类型进行重定义
typedef unsigned char u8;

sbit key1=P3^2;
sbit key2=P3^3;

extern unsigned long int system_tick;	//系统节拍
extern int setting_level;

void delay_10us(u16 ten_us);
void delay_ms(u16 ms);
void Exti_Init(void);
void Show_Setting_Water_Level(void);
void Water_Level_Control(void);
#endif