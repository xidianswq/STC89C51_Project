//超声波测距模块定义
#ifndef CS100A_H
#define CS100A_H
#include "water_level_control.h"

sbit cs100a_trig=P2^0;	//开启信号发送引脚
sbit cs100a_echo=P2^1;	//上下边沿信号接收引脚

#define RECORD_NUM 10	//记录水位存储数
#define FLOAT_RANGE 3	//允许水位波动误差

extern float distance;	 	//测量距离

void Cs100a_Init(void);
void Cs100a_Start(void);

#endif
