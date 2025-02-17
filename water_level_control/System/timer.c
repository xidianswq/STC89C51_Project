#include"timer.h"
void Timer_Init(){
	TMOD|=0x01;	//timer0工作方式1，16位计数器
	TH0=0xfc;
	TL0=0x18;	//计时1us		
	ET0=1;		//timer0中断开关
	EA=1;		//全局中断开关
	TR0=1;		//timer0开始工作(系统节拍定时器)
}
