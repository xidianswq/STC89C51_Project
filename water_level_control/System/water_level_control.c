#include "water_level_control.h"
#include "lcd1602.h"
#include "motor.h"
#include "cs100a.h"

unsigned long int system_tick=0;

int setting_level=(WATER_DISTANCE_MAX+WATER_DISTANCE_MIN)/2;

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

//精确延时ms
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

//开启外部中断（按键）
void Exti_Init(void)
{
	IT0=1;//跳变沿触发方式（下降沿）
	EX0=1;//打开INT1的中断允许
	IT1=1;//跳变沿触发方式（下降沿）
	EX1=1;//打开INT1的中断允许
	EA=1;//打开总中断
}

//水位显示函数
void Show_Setting_Water_Level(void)
{
	//显示
	int i;
	u8 temp_buf[6];
	u16 temp_value=setting_level*10;
	temp_buf[0]=temp_value/1000+0x30;
	temp_buf[1]=temp_value%1000/100+0x30;
	temp_buf[2]=temp_value%100/10+0x30;
	temp_buf[3]='.';
	temp_buf[4]=temp_value%10+0x30;
	temp_buf[5]='\0';
	for(i=0;temp_buf[i]<'0'||temp_buf[i]>'9';i++);
	lcd1602_show_string(8,1,&temp_buf[i]);
}

//设定水位函数（外部中断0,1）
void exti0() interrupt 0 //外部中断0中断函数
{
	int ten_us=1000;
	EX0=0;
	while(ten_us--);//消抖
	if(key1==0)setting_level=setting_level<WATER_DISTANCE_MAX?WATER_DISTANCE_MAX:setting_level-1;//设定水位减1
	EX0=1;					
}

void exti1() interrupt 2 //外部中断1中断函数
{
	int ten_us=1000;
	EX1=0;
	while(ten_us--);//消抖
	if(key2==0)setting_level=setting_level>WATER_DISTANCE_MIN?WATER_DISTANCE_MIN:setting_level+1;//设定水位加1
	EX1=1;					
}

//水位控制函数
void Water_Level_Control()
{
	if(distance<setting_level+LEVEL_WAVE)Water_Out();
	else if(distance>setting_level-LEVEL_WAVE)Water_In();
}