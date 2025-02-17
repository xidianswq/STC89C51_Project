#include<reg52.h>
#include"head.h"
void PwmInit(){
	 TMOD|=0X01;
	 TH0=0xFF;
	 TL0=0xF6;
	 ET0=1;
	 EA=1;
	 TR0=1;
}
void main ()
{
	int count=0;
	//print some words
//	print_words(print_set);
	//get the real password
	symbol=1; 
//	get_the_word_loop(duty);
	duty[0]=0;
	duty[1]=1;
	duty_num=30*(10*duty[0]+duty[1])/100;
	while(1){
		count++;
		if(count>=100)
			count=0;
		if(count<=duty_num)	
			PWM=1;
		else
			PWM=0;	
	}
}

