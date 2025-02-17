#ifndef MENU_H
#define MENU_H
#include "lcd1602.h"

#define MAX_PAGE 6	//总界面数

sbit key1=P3^2;
sbit key2=P3^3;

//系统运行时间
extern int working_hour;
extern int working_minute;
extern int working_second;
extern int water_sign;

void running_time(void);
void show_page(void);
void Exti_Init(void);

#endif
