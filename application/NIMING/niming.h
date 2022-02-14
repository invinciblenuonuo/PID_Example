#ifndef _NIMING
#define _NIMING
#include "main.h"

////传送数据给匿名四轴上位机软件(V2.6版本)
////fun:功能字. 0XA0~0XAF
////data:数据缓存区,最多28字节!!
////len:data区有效数据个数
void usart1_niming_report(uint8_t fun,uint8_t *data,uint8_t len);
void usart1_report_imu(long num1,long num2,long num3,long num4,long num5);

#endif

