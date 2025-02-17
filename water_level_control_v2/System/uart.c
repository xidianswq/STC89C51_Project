#include "uart.h"
u8 UART_RX_BUF[UART_REC_LEN];     //接收缓冲,最大UART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 UART_RX_STA=0;       //接收状态标记

void UART_Init(void)
{
	SCON|=0X50;			//设置为工作方式1
	TMOD|=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=RELOAD_COUNT;	//计数器初始值设置
	TL1=TH1;
	ES=0;				//关闭接收中断
	EA=1;				//打开总中断
	TR1=1;				//打开计数器
	TI=1;          //发送中断标记位，如果使用printf函数的必须设置	
}

void UART_SendData(u8 dat)
{
	ES=0; //关闭串口中断
	TI=0; //清发送完毕中断请求标志位
	SBUF=dat; //发送
	while(TI==0); //等待发送完毕
	TI=0; //清发送完毕中断请求标志位
	ES=1; //允许串口中断
}

//ESP8266 WIFI发送AT指令
//pbuf：AT指令，字符串格式，如："AT"
void ESP8266_SendCmd(u8 *pbuf)
{
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	delay_10us(5);
	UART_SendData('\r');//回车
	delay_10us(5);
	UART_SendData('\n');//换行
	delay_ms(1000);
}

//ESP8266 WIFI发送数据到APP
//pbuf：数据
void ESP8266_SendData(u8 *pbuf)
{
	ESP8266_SendCmd("AT+CIPSEND=0,7");
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	UART_SendData('\n');//换行	
//	delay_ms(10);
}

//ESP8266-WIFI模块工作模式初始化
void ESP8266_ModeInit(void)
{
	ESP8266_SendCmd("AT+CWMODE=2");//设置路由器模式 1 staTIon模式 2 AP点 路由器模式 3 station+AP混合模式
	ESP8266_SendCmd("AT+CWSAP=\"PRECHIN\",\"prechin168\",11,0"); //设置WIFI热点名及密码
	ESP8266_SendCmd("AT+CIPAP=\"192.168.4.1\"");
//	ESP8266_SendCmd("AT+RST");//重新启动wifi模块
//	delay_ms(2000);
	ESP8266_SendCmd("AT+CIPMUX=1");	//开启多连接模式，允许多个各客户端接入
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");	//启动TCP/IP 端口为8080 实现基于网络控制	
} 

//WIFI控制初始化
void wifi_control_init(void)
{
	UART_Init();
	//ESP8266_ModeInit();
	ES=1;//允许串口中断
}

//串口中断服务函数
//接收手机APP发送的信号后控制板载资源
extern int setting_level;
#define VERIFY_NUM 3
void UART_IRQn() interrupt 4
{
	static u8 i=0;

	if(RI)
	{
		RI=0;
		UART_RX_BUF[i]=SBUF;//读取接收到的数据
		if(i==VERIFY_NUM)
		{
			i=0;
			//WIFI控制
			if(UART_RX_BUF[VERIFY_NUM]==WATER_LEVEL_ON)
				setting_level=setting_level>WATER_DISTANCE_MIN?WATER_DISTANCE_MIN:setting_level+1;//设定水位加1				
			else if(UART_RX_BUF[VERIFY_NUM]==WATER_LEVEL_DOWN)
				setting_level=setting_level<WATER_DISTANCE_MAX?WATER_DISTANCE_MAX:setting_level-1;//设定水位减1
		}
		else if(UART_RX_BUF[0]=='@')i++;
		else i=0;			
	}	
}

//printf重定向
char putchar(char ch)
{
	UART_SendData(ch);
	return ch;
}
