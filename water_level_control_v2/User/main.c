#include "water_level_control.h"	//按键设定水位，水位控制
#include "menu.h"		//菜单界面
#include "timer.h"		//定时器
#include "motor.h"		//水阀开关控制
#include "lcd1602.h"	//lcd显示屏

//资源使用说明
/*
timer.h		定时器0			 	
motor.h		P1^0,P1^1	 	
lcd1602.h	P0--DATA,P2^5--RW,P2^6--RS,P2^7--EN
*/

//系统运行时间
extern int working_hour;
extern int working_minute;
extern int working_second;
extern int water_sign;
void System_Init(){
	char str1[]="AUTO-WATERING   ";
	char str2[]="     WELCOME-SWQ";
	Null_Action();
	Timer_Init();	  		//系统滴答定时器初始化
	Exti_Init();			//按键中断初始化
	lcd1602_init();	   		//lcd屏初始化
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);
	delay_s(3);
	lcd1602_clear();
}

int main()
{
	System_Init();
	while(1)
	{
		delay_ms(799);
		running_time();
		show_page();	 	
	 	if(water_sign)Water_In();
		else Null_Action();
	}
}
