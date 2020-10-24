#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

#include <stdbool.h>


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����3��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define USART2_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		600					//����ͻ����ֽ���

#define JDY_MAX_RX_NUM		2					//���JDY-24M��������֡����
#define JDY_MAX_RX_LEN		30					//���JDY-24M��������֡����

#define READ_ONLY_NUM_MAX  10
#define READ_WRITE_NUM_MAX 10

//�豸�ṹ��
extern struct dev_info
{
	u16 NETID;
	u16 MADDR;
	u8 Read_only_num;
	u8 Read_only_value[READ_ONLY_NUM_MAX];
	u8 Read_write_num;
	bool Read_write_value[READ_WRITE_NUM_MAX];
	bool STAT;
	u32 HB_NUM;
};	

extern struct dev_info mesh_dev[5];




extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�


extern u8 USART2_RX_FLAG;					//USART2���ձ�־����������ʱ��1
extern u8 USART2_TX_FLAG;					//USART2���ͱ�־����������ʱ��1

//JDY-24M ��������֡
extern u8 JDY_RX_BUFF[JDY_MAX_RX_NUM][JDY_MAX_RX_LEN];


void usart2_DMA_init(u32 bound);				//����2��ʼ�� 
void u2_printf(char* fmt,...);
void u2_DMA_printf(char *format,...);

void DMA_USART2_Tx_Data(u8 *buffer,u32 size);



#endif













