#include "delay.h"
#include "usart3.h"	 	 
#include "stdio.h"	 	  
#include "usart.h"	
//实现printf()
#include "string.h"
#include "stdarg.h"

#include "dma.h"

#include "JDY_24M.h"

//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif

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

//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 			//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节

//标志
u8 USART3_RX_FLAG=0;					//USART3接收标志，启动接收时置1
u8 USART3_TX_FLAG=0;					//USART3发送标志，启动发送时置1





extern OS_Q AT_JDY_Msg;			//定义一个消息队列，用于发送数据

extern OS_Q DATA_Msg;			//定义一个消息队列，用于发送数据
extern OS_ERR err;


void USART3_IRQHandler(void)
{
	//数据类型与最大接收缓存有关，char最大是255个，int是65535,这里取个较大的数
    unsigned int num=0;
	
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
    if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)
    {
       num = USART3->SR;
       num = USART3->DR; //清USART_IT_IDLE标志
		
//	   USART_ReceiveData(USART3);//清USART_IT_IDLE标志
	   USART_ClearFlag(USART3,USART_FLAG_TC);
		
       DMA_Cmd(DMA1_Channel3,DISABLE);    //关闭DMA
       num = USART3_MAX_RECV_LEN -  DMA_GetCurrDataCounter(DMA1_Channel3);      //总个数-剩余个数=得到真正接收数据个数  
       USART3_RX_BUF[num] = '\0';			//加结束符
		
	   printf("%s",USART3_RX_BUF);
		
		
		//接收到APP发来的开灯消息
		//strstr(s1,s2);检测s2是否为s1的一部分，是返回该位置，否则返回false，它强制转换为bool类型了
		if(strstr(USART3_RX_BUF,"0002SW1ON"))
		{
			printf("rev :0002SW1ON\r\n");
			

			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"D",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);			
				
		}
		else if(strstr(USART3_RX_BUF,"0002SW1OFF"))
		{
			printf("rev :0002SW1OFF\r\n");
			

			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"C",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);				
		}
		else if(strstr(USART3_RX_BUF,"0003SW1ON"))
		{
			printf("rev :0003SW1ON\r\n");
			

			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"H",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);				
		}
		else if(strstr(USART3_RX_BUF,"0003SW1OFF"))
		{
			printf("rev :0003SW1OFF\r\n");
			

			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"G",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);				
		}
		else if(strstr(USART3_RX_BUF,"0004SW1ON"))
		{
			printf("rev :0004SW1ON");
			

			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"L",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);				
		}
		else if(strstr(USART3_RX_BUF,"0004SW1OFF"))
		{
			printf("rev :0004SW1OFF\r\n");
			
			OSQPost((OS_Q*		)&AT_JDY_Msg,		
					(void*		)&"K",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);				
		}

		
		
		
		
		
	   //字符串拷贝 拷贝到备份buffer
	   //strcpy(receive_data_buffer,receive_data);
	   //memset(&receive_data[num],'\0',128-num);
       DMA1_Channel3->CNDTR=USART3_MAX_RECV_LEN;       //重新设置接收数据个数        
	   DMA_Cmd(DMA1_Channel3,ENABLE);  //开启DMA
       USART3_RX_FLAG = 1;           //接收数据标志位置1
    }
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}   


//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart3_DMA_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能
	//复位串口3
 	USART_DeInit(USART3);  
	//USART3_TX   PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口	3

	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//使能空闲中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启中断   
	USART_ClearFlag(USART3,USART_FLAG_TC);
	USART_Cmd(USART3, ENABLE);                    //使能串口 

	DMA1_USART3_init();
}


//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}


//DMA 发送应用源码 TX
void DMA_USART3_Tx_Data(u8 *buffer,u32 size)
{
	//等待上一次发送完成（USART2_TX_FLAG为1即还在发送数据）
	while(USART3_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	USART3_TX_FLAG = 1;					//USART3发送标志（启动发送）
	DMA1_Channel2->CMAR = (u32)buffer;	//设置要发送的数据地址
	DMA1_Channel2->CNDTR = size;		//设置要发送的字节数目
	DMA_Cmd(DMA1_Channel2,ENABLE);		//开始DMA发送
}

//DMA1通道2中断
void DMA1_Channel2_IRQHandler(void)
{
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
	if(DMA_GetITStatus(DMA1_IT_TC2)!=RESET)		//DMA接收完成标志
	{
		DMA_ClearITPendingBit(DMA1_IT_TC2);		//清除中断标志 
		USART_ClearFlag(USART3,USART_FLAG_TC);	//清除串口3的标志位
		DMA_Cmd(DMA1_Channel2,DISABLE);			//关闭USART3 TX DMA1 所指示的通道
		USART3_TX_FLAG = 0;						//USART3发送标志(关闭)
	}
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}

void u3_DMA_printf(char *format,...)
{
	//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>，用于获取不确定个数的参数。
	va_list arg_ptr;//实例化可变长参数列表
	
	//等待上一次发送完成（USART3_TX_FLAG为1即还在发送数据）
	while(USART3_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	
	va_start(arg_ptr,format);				//初始化可变参数列表，设置format为可变长列表的起始点（第一个元素）
	
	//USART3_MAX_TX_LEN+1可接受的最大字符数(非字节数，UNICODE一个字符两个字节), 防止产生数组越界
	vsnprintf((char*)USART3_TX_BUF,USART3_MAX_SEND_LEN+1,format,arg_ptr);//从USART3_TX_BUF的首地址开始拼合，拼合format内容；USART3_MAX_TX_LEN+1限制长度，防止产生数组越界
	
	va_end(arg_ptr);						//注意必须关闭
	
	DMA_USART3_Tx_Data(USART3_TX_BUF,strlen((const char*)USART3_TX_BUF));//发送USART3_TX_BUF内容
	
}











