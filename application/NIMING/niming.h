#ifndef _NIMING
#define _NIMING
#include "main.h"

////�������ݸ�����������λ�����(V2.6�汾)
////fun:������. 0XA0~0XAF
////data:���ݻ�����,���28�ֽ�!!
////len:data����Ч���ݸ���
void usart1_niming_report(uint8_t fun,uint8_t *data,uint8_t len);
void usart1_report_imu(long num1,long num2,long num3,long num4,long num5);

#endif

