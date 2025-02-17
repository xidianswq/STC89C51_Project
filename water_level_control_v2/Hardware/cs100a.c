#include "cs100a.h"
#include "timer.h"				  	

float distance=0;
float distance_record[RECORD_NUM]={0};

void Cs100a_Init(void)
{
	cs100a_trig=0;	
}

void record_distance(float distance)
{
	int i;
	for(i=RECORD_NUM-1;i>0;i--)
	{
		distance_record[i]=distance_record[i-1];							   	
	}
	distance_record[0]=distance; 
}

float average_distance()
{
	int i;
	float average_distance,sum_distance;
	for(sum_distance=0,i=0;i<RECORD_NUM;i++)sum_distance+=distance_record[i];
	average_distance=sum_distance/RECORD_NUM;
	return average_distance;
}

int judge_distance_correct(float distance)
{
	float average;
	average=average_distance();
	if(average-FLOAT_RANGE<distance<average+FLOAT_RANGE)return 1;
	else return 0;
}

void Cs100a_Start(void)
{	
	int i,temp_count,count,time;
	long int temp_tick,tick;
	float distance_temp;
	cs100a_trig=0;
	for(i=0;i<600;i++);	//50us
	cs100a_trig=1;

	while(!cs100a_echo);	//等待上升沿
	temp_tick=system_tick;
	temp_count=(0xff-TH0)*256+(0xff-TL0);
	while(cs100a_echo);		//等待下降沿
	tick=system_tick;
	count=(TH0-0xfc)*256+(TL0-0x18); 	
 
	if(tick>temp_tick)
	{
		time=count+temp_count+1000*(tick-temp_tick-1);
	}
	else if(tick==temp_tick)
	{
		time=temp_count-count;//+count-1000;		
	}
	distance_temp=17000.0*time*CLK_DIV/CLK_FRE;
	record_distance(distance_temp);
	//if(judge_distance_correct(distance_temp))distance=distance_record[0];
	distance=average_distance();
}
