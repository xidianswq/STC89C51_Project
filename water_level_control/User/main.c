#include "water_level_control.h"	//按键设定水位，水位控制
#include "timer.h"		//定时器
#include "cs100a.h"		//超声波测距
#include "lcd1602.h"	//lcd屏显示
#include "uart.h"		//uart通信
#include "motor.h"		//水阀开关控制
//资源使用说明
/*
timer.h		定时器0			 	
cs100a.h	P2^0--TRIG,P2^1--ECHO
motor.h		P1^0,P1^1	 	
lcd1602.h	P0--DATA,P2^5--RW,P2^6--RS,P2^7--EN
uart.h		定时器1,P3^0--TXD,P3^1--RXD
*/
void System_Init(){
	char str1[]="current:";
	char str2[]="setting:";
	Timer_Init();	  		//系统滴答定时器初始化
	Exti_Init();
	Cs100a_Init();	  		//超声波模块初始化
	wifi_control_init(); 	//esp8266初始化
	printf("WELLCOME!\n\r");
	lcd1602_init();	   		//lcd屏初始化
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);
}
int main(){
	System_Init();
	//测距+显示
	while(1)
	{
		Cs100a_Start();										//测距
		Show_Distance();									//显示当前水位
		Show_Setting_Water_Level();							//显示当前设定水位	
		printf("D:%d|",WATER_LEVEL_INT((int)distance));
		printf("L:%d|",WATER_LEVEL_PERCENT((int)distance));	
		Water_Level_Control();								//控制水位
		delay_ms(100);
	}
	return 0;		
}
