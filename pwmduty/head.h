#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4//key1-4为功能键
#define key_matrix P1
#define	led P0
#define control P2
sbit k1=P3^1;sbit k2=P3^0;sbit k3=P3^2;sbit k4=P3^3;
sbit PWM=P3^4;
unsigned char word[16]={0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char letter[46] = {   
0x77,0x7c,0x39,0x5e,0x79,0x71,0x3d,0x76,0x0f,0x0e,
0x75,0x38,0x37,0x54,0x5c,0x73,0x67,0x31,0x49,0x78,
0x3e,0x1c,0x7e,0x64,0x6e,0x59,1,15,0x10,8,
0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int con[8]={0,4,8,12,16,20,24,28};
int duty[2];
idata int print_set[8]={29,29,29,18,4,19,29,29};
idata int print_enter[8]={29,29,4,13,19,4,17,29};
idata int print_num[8]={29,29,29,29,29,29,29,29};
//对照表：
//0A 1B 2C 3D 4E 5F 6G 7H 8I 9J 10K 11L 12M 13N 14O 15P 16Q 17R 18S 19T 20U 21V 22W 23X 24Y 25Z
//26- 27 | 28|  29_
idata int key,i,j,k,symbol;//全局变量定义太多，系统默认寻址data区，满了，定义要前加idata
idata int duty_num;


void delay(int a)
{
	while(a--);
}


int key_scan(int mode)
{
	int judge=1;
	if(mode==1)judge=1;
	if(judge==1&&(k1==0||k2==0||k3==0||k4==0))
	   { judge=0;
		 delay(10000);
		 if(k1==0)return KEY1;
		 else if(k2==0)return KEY2;
		 else if(k3==0)return KEY3;
		 else return KEY4;
	   }
	else {
	judge=1;
	return 0;
	}//不同按下返回值需不同，才能区分哪个按下
}
int key_line_scan(void)
{
	static int key=0;

	key_matrix=0x0f;
	if(key_matrix!=0x0f)
	{
		delay(1000);
		if(key_matrix!=0x0f)
		{
			key_matrix=0x0f;
			switch(key_matrix)	
			{
				case 0x07: key=1;break;
				case 0x0b: key=2;break;
				case 0x0d: key=3;break;
				case 0x0e: key=4;break;
			}
			
			key_matrix=0xf0;
			switch(key_matrix)	
			{
				case 0x70: key=key;break;
				case 0xb0: key=key+4;break;
				case 0xd0: key=key+8;break;
				case 0xe0: key=key+12;break;
			}
			while(key_matrix!=0xf0);	
		}
	}
	else
		key=0;		
	
	return key;		
}


void print_words(int a[8])
{	
	while(1)
	{	
		
	    
		key=0,j=0;
		for(j=0;j<8;j++)
		{
			control=con[7-j];
			led=letter[a[j]];
			delay(100);
			led=0;
		}
		key=key_scan(0);
	  if(key!=0)
	  { delay(10000);
		if(key==4)break;//确认
	  }
		
	}
}


void get_pass_words(int b[2])
{
	while(1)
	{   
		key=key_line_scan();
		if(key!=0)
		{
			b[i]=key-1;
			i++;
		}
		if(i==2)break;
		key=0;
	}	
}

void get_the_word_loop(int word_enter[2])
{
	while(symbol)
	{
		key=0,i=0,j=0;
		//set your password
		get_pass_words(word_enter);

		//print real words and judge if reset or not	
		while(1)
		{
			  key=key_scan(0);
			  if(key!=0)
			  {
				if(key==1)break;//实现修改输出！
				if(key==2);
				if(key==3);
				if(key==4)
					{
					symbol=0;
					delay(1000);
					break;
					}//确认
			  }
				for(j=0;j<2;j++)
				{
					control=con[7-j];
					led=word[word_enter[j]];
					delay(10);
					led=0;
				}
		  	  
		}
	}
}