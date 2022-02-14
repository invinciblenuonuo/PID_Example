#include "niming.h"
#include "usart.h"

////�������ݸ�����������λ�����(v6�汾)
////fun:������. 0XA0~0XAF
////data:���ݻ�����,���28�ֽ�!!
////len:data����Ч���ݸ���

void usart1_niming_report(uint8_t fun,uint8_t *data,uint8_t len)
{
	uint8_t send_buf[32];
	uint8_t i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+5]=0;	//У��������
	send_buf[0]=0xAA;	//֡ͷ
	send_buf[1]=0x05;	//
	send_buf[2]=0xAF;	//
	send_buf[3]=fun;	//������
	send_buf[4]=len;	//���ݳ���
	for(i=0;i<len;i++)
	{
		send_buf[5+i]=data[i];			//��������
	}
	
	for(i=0;i<len+5;i++)
	{
		send_buf[len+5]+=send_buf[i];	//����У���	
	}
	send_buf[len+5]=(uint8_t)send_buf[len+5]&0xff;
		
	HAL_UART_Transmit( &huart1 ,send_buf , 32 , 100);
}

//0xAA\0x05\0xaf\0xf1\len\....\sum
////ͨ������3�ϱ����������ݸ�����
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


