#include<reg52.h>
#include"head.h"
void PwmInit(){
	 TMOD|=0X01;
	 TH0=h_num[1];
	 TL0=l_num[1];
	 ET0=1;
	 EA=1;
	 TR0=1;
}
void main ()
{	int duty_num;
	//print some words
	print_words(print_set);
	//get the real password
	symbol=1; 
	get_the_word_loop(duty);
	duty_num=duty[1]+10*duty[0];
	prog=103;		//固有时间（us）（等价占空比为除9）
	h_num[1]=(65535-461*duty_num/100-461*duty_num/100+prog)/256;
	l_num[1]=(65535-461*duty_num/100-461*duty_num/100+prog)%256;
	h_num[0]=(64613+461*duty_num/100+461*duty_num/100+prog)/256;
	l_num[0]=(64613+461*duty_num/100+461*duty_num/100+prog)%256;

	PwmInit();
	print_num[6]=30+duty[0];
	print_num[7]=30+duty[1];
	print_words(print_num);

}
void Pwm()interrupt 1
{	 
	PWM=~PWM;
	TH0=h_num[PWM];
	TL0=l_num[PWM];
}