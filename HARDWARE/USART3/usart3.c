#include "delay.h"
#include "usart3.h"	 	 
#include "stdio.h"	 	  
#include "usart.h"	
//ʵ��printf()
#include "string.h"
#include "stdarg.h"

#include "dma.h"

#include "JDY_24M.h"

//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif

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

//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 			//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

//��־
u8 USART3_RX_FLAG=0;					//USART3���ձ�־����������ʱ��1
u8 USART3_TX_FLAG=0;					//USART3���ͱ�־����������ʱ��1





extern OS_Q AT_JDY_Msg;			//����һ����Ϣ���У����ڷ�������

extern OS_Q DATA_Msg;			//����һ����Ϣ���У����ڷ�������
extern OS_ERR err;


void USART3_IRQHandler(void)
{
	//���������������ջ����йأ�char�����255����int��65535,����ȡ���ϴ����
    unsigned int num=0;
	
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
    if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)
    {
       num = USART3->SR;
       num = USART3->DR; //��USART_IT_IDLE��־
		
//	   USART_ReceiveData(USART3);//��USART_IT_IDLE��־
	   USART_ClearFlag(USART3,USART_FLAG_TC);
		
       DMA_Cmd(DMA1_Channel3,DISABLE);    //�ر�DMA
       num = USART3_MAX_RECV_LEN -  DMA_GetCurrDataCounter(DMA1_Channel3);      //�ܸ���-ʣ�����=�õ������������ݸ���  
       USART3_RX_BUF[num] = '\0';			//�ӽ�����
		
	   printf("%s",USART3_RX_BUF);
		
		
		//���յ�APP�����Ŀ�����Ϣ
		//strstr(s1,s2);���s2�Ƿ�Ϊs1��һ���֣��Ƿ��ظ�λ�ã����򷵻�false����ǿ��ת��Ϊbool������
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

		
		
		
		
		
	   //�ַ������� ����������buffer
	   //strcpy(receive_data_buffer,receive_data);
	   //memset(&receive_data[num],'\0',128-num);
       DMA1_Channel3->CNDTR=USART3_MAX_RECV_LEN;       //�������ý������ݸ���        
	   DMA_Cmd(DMA1_Channel3,ENABLE);  //����DMA
       USART3_RX_FLAG = 1;           //�������ݱ�־λ��1
    }
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}   


//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart3_DMA_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����3ʱ��ʹ��
	//��λ����3
 	USART_DeInit(USART3);  
	//USART3_TX   PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART3_RX	  PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3

	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//ʹ�ܿ����ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�   
	USART_ClearFlag(USART3,USART_FLAG_TC);
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

	DMA1_USART3_init();
}


//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}


//DMA ����Ӧ��Դ�� TX
void DMA_USART3_Tx_Data(u8 *buffer,u32 size)
{
	//�ȴ���һ�η�����ɣ�USART2_TX_FLAGΪ1�����ڷ������ݣ�
	while(USART3_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	USART3_TX_FLAG = 1;					//USART3���ͱ�־���������ͣ�
	DMA1_Channel2->CMAR = (u32)buffer;	//����Ҫ���͵����ݵ�ַ
	DMA1_Channel2->CNDTR = size;		//����Ҫ���͵��ֽ���Ŀ
	DMA_Cmd(DMA1_Channel2,ENABLE);		//��ʼDMA����
}

//DMA1ͨ��2�ж�
void DMA1_Channel2_IRQHandler(void)
{
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
	if(DMA_GetITStatus(DMA1_IT_TC2)!=RESET)		//DMA������ɱ�־
	{
		DMA_ClearITPendingBit(DMA1_IT_TC2);		//����жϱ�־ 
		USART_ClearFlag(USART3,USART_FLAG_TC);	//�������3�ı�־λ
		DMA_Cmd(DMA1_Channel2,DISABLE);			//�ر�USART3 TX DMA1 ��ָʾ��ͨ��
		USART3_TX_FLAG = 0;						//USART3���ͱ�־(�ر�)
	}
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}

void u3_DMA_printf(char *format,...)
{
	//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>�����ڻ�ȡ��ȷ�������Ĳ�����
	va_list arg_ptr;//ʵ�����ɱ䳤�����б�
	
	//�ȴ���һ�η�����ɣ�USART3_TX_FLAGΪ1�����ڷ������ݣ�
	while(USART3_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	
	va_start(arg_ptr,format);				//��ʼ���ɱ�����б�����formatΪ�ɱ䳤�б����ʼ�㣨��һ��Ԫ�أ�
	
	//USART3_MAX_TX_LEN+1�ɽ��ܵ�����ַ���(���ֽ�����UNICODEһ���ַ������ֽ�), ��ֹ��������Խ��
	vsnprintf((char*)USART3_TX_BUF,USART3_MAX_SEND_LEN+1,format,arg_ptr);//��USART3_TX_BUF���׵�ַ��ʼƴ�ϣ�ƴ��format���ݣ�USART3_MAX_TX_LEN+1���Ƴ��ȣ���ֹ��������Խ��
	
	va_end(arg_ptr);						//ע�����ر�
	
	DMA_USART3_Tx_Data(USART3_TX_BUF,strlen((const char*)USART3_TX_BUF));//����USART3_TX_BUF����
	
}











