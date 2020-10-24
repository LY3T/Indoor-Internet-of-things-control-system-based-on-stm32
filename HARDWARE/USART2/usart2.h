#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

#include <stdbool.h>


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口3驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/3/29
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define USART2_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		600					//最大发送缓存字节数

#define JDY_MAX_RX_NUM		2					//最大JDY-24M接收数据帧个数
#define JDY_MAX_RX_LEN		30					//最大JDY-24M接收数据帧长度

#define READ_ONLY_NUM_MAX  10
#define READ_WRITE_NUM_MAX 10

//设备结构体
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




extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节


extern u8 USART2_RX_FLAG;					//USART2接收标志，启动接收时置1
extern u8 USART2_TX_FLAG;					//USART2发送标志，启动发送时置1

//JDY-24M 接收数据帧
extern u8 JDY_RX_BUFF[JDY_MAX_RX_NUM][JDY_MAX_RX_LEN];


void usart2_DMA_init(u32 bound);				//串口2初始化 
void u2_printf(char* fmt,...);
void u2_DMA_printf(char *format,...);

void DMA_USART2_Tx_Data(u8 *buffer,u32 size);



#endif













