#include "menu.h"
#include "lcd1602.h"
#include "stdio.h"
//当前页
int page=0;
int last_page=0;
//系统运行时间
int working_hour=0;
int working_minute=0;
int working_second=0;
//当日时间
int current_hour=12;
int current_minute=30;
int current_second=30;

//浇水间隔（h）
int watering_gap=120;			
//浇水持续时长（s）
int watering_last=20;			
//浇水使能位
int water_sign=0;

int *num=NULL;
int num_max=24;

void running_time(void)
{
	//时间计算
	working_second++;
	
	//判断是否浇水
	if(water_sign==1 && working_second>=watering_last)water_sign=0;
	
	if(working_second==60)
	{
		working_second=0;
		working_minute++;
		current_second=0;
		current_minute++;
		
		if(working_minute==60)
		{
			working_minute=0;
			working_hour++;
			
			//判断是否浇水
			if(working_hour%watering_gap==0)water_sign=1;
		
		}
		if(current_minute==60)
		{
			current_minute=0;
			current_hour++;
			if(current_hour==24)
			{
				current_hour=0;
			}
		}
	}
}

//菜单显示函数
void show_page(void)
{
	void page_1(void);
	void page_2(void);
	void page_3(void);
	void page_4(void);
	void page_5(void);
	void page_6(void);

	if(page!=last_page){
		lcd1602_clear();
		last_page=page;
	}
	switch(page){
		case 0:page_1();break;
		case 1:page_2();break;
		case 2:page_3();break;
		case 3:page_4();break;
		case 4:page_5();break;
		case 5:page_6();break;
	}		
}

void page_1(void)
{
	char str1[]="current time:";
	char str2[16];
	sprintf(str2,"%02d:%02d:%02d",current_hour,current_minute,working_second);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

void page_2(void)
{
	char str1[]="working time:";
	char str2[16];
	sprintf(str2,"%04d:%02d:%02d",working_hour,working_minute,working_second);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

void page_3(void)
{
	char str1[]="set time:";
	char str2[16];
	num=&current_hour;
	num_max=24;
	sprintf(str2,"%02d",current_hour);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

void page_4(void)
{
	char str1[]="set minute:";
	char str2[16];
	num=&current_minute;
	num_max=60;
	sprintf(str2,"%02d",current_minute);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

void page_5(void)
{
	char str1[]="watering gap:";
	char str2[16];
	num=&watering_gap;
	num_max=240;
	sprintf(str2,"%03d hours",watering_gap);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

void page_6(void)
{
	char str1[]="watering last:";
	char str2[16];
	num=&watering_last;
	num_max=60;
	sprintf(str2,"%02d seconds",watering_last);
	lcd1602_show_string(0,0,str1);
	lcd1602_show_string(0,1,str2);	
}

//****************************************
//**************按键控制部分**************
//****************************************
//开启外部中断（按键）
void Exti_Init(void)
{
	IT0=1;//跳变沿触发方式（下降沿）
	EX0=1;//打开INT1的中断允许
	IT1=1;//跳变沿触发方式（下降沿）
	EX1=1;//打开INT1的中断允许
	EA=1;//打开总中断
}

//按键中断函数（外部中断0,1）
void exti0() interrupt 0 //外部中断0中断函数
{
	void show_page(void);

	int ten_us=1000;
	EX0=0;
	while(ten_us--);//消抖
	if(key1==0)
	{	
		//中断处理函数
		page=(page+1)%MAX_PAGE;
	}
	EX0=1;					
}

void exti1() interrupt 2 //外部中断1中断函数
{
	void show_page(void);
	
	int ten_us=1000;
	EX1=0;
	while(ten_us--);//消抖
	if(key2==0)
	{
		//中断处理函数
		*num=(*num+1)%num_max;	
	}
	EX1=1;
}