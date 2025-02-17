#include"timer.h"
unsigned long int system_tick=0;

void Timer_Init(){
	TMOD|=0x01;	//timer0工作方式1，16位计数器
	TH0=0xfc;
	TL0=0x18;	//计时1us		
	ET0=1;		//timer0中断开关
	EA=1;		//全局中断开关
	TR0=1;		//timer0开始工作(系统节拍定时器)
}

//精确延时秒s
void delay_s(u16 s)
{
	void delay_ms(u16 ms);
	int temp=0;
	for(temp=0;temp<s;temp++)delay_ms(1000);		
}

//精确延时毫秒ms
void delay_ms(u16 ms)
{
	unsigned long int temp=system_tick;
	while(temp+ms>=system_tick);	
}

//定时器中断，系统节拍
void timer0_intp()interrupt 1 
{
	TH0=0xfc;
	TL0=0x18;	//计时1ms
	system_tick++;
}