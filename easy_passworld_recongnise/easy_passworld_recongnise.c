#include<reg52.h>
#include"passwordrelated.h"

void main ()
{	
	//print some words
	print_words(print_set);

	//get the real password
	symbol=1; 
	get_the_word_loop(real_word);
	
	//print some words
	key=0,i=0,j=0;
	print_words(print_enter);	
	
	//get the pass password
	symbol=1; 
	get_the_word_loop(pass_word);

	//judge the result and do something
	judge_word(real_word,pass_word);
	if(k==8)
	{
	beep_judge(1);
	;//other actions		
	}

	else beep_judge(0);	
	
}

