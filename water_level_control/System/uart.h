#ifndef UART_H
#define UART_H
#include "water_level_control.h"

//定义WIFI控制命令
#define WATER_LEVEL_ON			'+'
#define WATER_LEVEL_DOWN		'-'
#define RELOAD_COUNT 0xF3 //宏定义波特率发生器的载入值 4800(考虑倍频) 误差为0.16%
#define UART_REC_LEN  			10  	//定义最大接收字节数 50

extern u8  UART_RX_BUF[UART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART_RX_STA;         		//接收状态标记	

void wifi_control_init();
char putchar (char);
#endif