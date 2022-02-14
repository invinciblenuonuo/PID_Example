#include "niming.h"
#include "usart.h"

////传送数据给匿名四轴上位机软件(v6版本)
////fun:功能字. 0XA0~0XAF
////data:数据缓存区,最多28字节!!
////len:data区有效数据个数

void usart1_niming_report(uint8_t fun,uint8_t *data,uint8_t len)
{
	uint8_t send_buf[32];
	uint8_t i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+5]=0;	//校验数置零
	send_buf[0]=0xAA;	//帧头
	send_buf[1]=0x05;	//
	send_buf[2]=0xAF;	//
	send_buf[3]=fun;	//功能字
	send_buf[4]=len;	//数据长度
	for(i=0;i<len;i++)
	{
		send_buf[5+i]=data[i];			//复制数据
	}
	
	for(i=0;i<len+5;i++)
	{
		send_buf[len+5]+=send_buf[i];	//计算校验和	
	}
	send_buf[len+5]=(uint8_t)send_buf[len+5]&0xff;
		
	HAL_UART_Transmit( &huart1 ,send_buf , 32 , 100);
}

//0xAA\0x05\0xaf\0xf1\len\....\sum
////通过串口3上报结算后的数据给电脑
void usart1_report_imu(long num1,long num2,long num3,long num4,long num5)
{
	uint8_t tbuf[10]; 
	
	tbuf[0]=(num1>>8)&0XFF;
	tbuf[1]=num1&0XFF;
	
	tbuf[2]=(num2>>8)&0XFF;
	tbuf[3]=num2&0XFF;
	
	tbuf[4]=(num3>>8)&0XFF;
	tbuf[5]=num3&0XFF; 
	
	tbuf[6]=(num4>>8)&0XFF;
	tbuf[7]=num4&0XFF; 
	
	tbuf[8]=(num5>>8)&0XFF;
	tbuf[9]=num5&0XFF; 
	
	usart1_niming_report(0XF1,tbuf,10);
}   


