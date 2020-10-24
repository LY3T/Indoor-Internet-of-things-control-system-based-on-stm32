#include "delay.h"
#include "usart2.h"	 	 
#include "stdio.h"	 	  
#include "usart.h"	
//ʵ��printf()
#include "string.h"
#include "stdarg.h"

#include "dma.h"

#include "WM.h"

//#define ID_ICONVIEW_SW        	(GUI_ID_USER + 0x03)


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
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 			//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�

//��־
u8 USART2_RX_FLAG=0;					//USART2���ձ�־����������ʱ��1
u8 USART2_TX_FLAG=0;					//USART2���ͱ�־����������ʱ��1

//JDY-24M ��������֡
u8 JDY_RX_BUFF[JDY_MAX_RX_NUM][JDY_MAX_RX_LEN];



extern OS_Q DATA_Msg;			//����һ����Ϣ���У����ڷ�������
extern OS_ERR err;


extern u8 led_state[2];


extern WM_HWIN dropdown;

extern bool dropdown_item_flag[3];

extern bool sys_init_finish_flag;


//����2�����ж�
void USART2_IRQHandler(void)
{
	//���������������ջ����йأ�char�����255����int��65535,����ȡ���ϴ����
    unsigned int num=0;
	
		u8 *p=NULL;

	WM_MESSAGE Message;	

	
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
    if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)
    {
       num = USART2->SR;
       num = USART2->DR; //��USART_IT_IDLE��־
		
//	   USART_ReceiveData(USART2);//��USART_IT_IDLE��־
	   USART_ClearFlag(USART2,USART_FLAG_TC);
		
       DMA_Cmd(DMA1_Channel6,DISABLE);    //�ر�DMA
       num = USART2_MAX_RECV_LEN -  DMA_GetCurrDataCounter(DMA1_Channel6);      //�ܸ���-ʣ�����=�õ������������ݸ���  
       USART2_RX_BUF[num] = '\0';			//�ӽ�����
		
		
		
	   
		
		printf("���ݳ���Ϊ:%d\r\n",USART2_RX_BUF[2]-2);
		
		
		p = &USART2_RX_BUF[7];
		
		printf("%s\r\n",p);
		
		//�ж��Ƿ�������֡
		if(strstr(p,"offline"))
		{

			if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==2)
			{
				mesh_dev[USART2_RX_BUF[4]-2].STAT = false;
			}
			else if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==3)
			{
				mesh_dev[USART2_RX_BUF[4]-2].STAT = false;
			}
			else if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==4)
			{
				mesh_dev[USART2_RX_BUF[4]-2].STAT = false;
			}
			
		}
		else{
			
		
		
		
		
		
		//ѡ��JDY����֡
		if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==2)
		{
			mesh_dev[USART2_RX_BUF[4]-2].MADDR = USART2_RX_BUF[4];
			mesh_dev[USART2_RX_BUF[4]-2].NETID = 1122;
			
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_num = USART2_RX_BUF[7] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[0] = (USART2_RX_BUF[8] - 0x30) * 10 + (USART2_RX_BUF[9] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[1] = (USART2_RX_BUF[10] - 0x30) * 10 + (USART2_RX_BUF[11] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_num = USART2_RX_BUF[12] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[0] = USART2_RX_BUF[13] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[1] = USART2_RX_BUF[14] - 0x30;
			
			mesh_dev[USART2_RX_BUF[4]-2].STAT = true;
			
			printf("MADDR:%d\r\n",mesh_dev[USART2_RX_BUF[4]-2].MADDR);
		}
		else if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==3)
		{
			
//			if(dropdown_item_flag[1]==false)
//			{
//				dropdown_item_flag[1] = true;
//				DROPDOWN_AddString(dropdown,"0003");
//				
//			}
			
			
			mesh_dev[USART2_RX_BUF[4]-2].MADDR = USART2_RX_BUF[4];
			mesh_dev[USART2_RX_BUF[4]-2].NETID = 1122;
			
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_num = USART2_RX_BUF[7] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[0] = (USART2_RX_BUF[8] - 0x30) * 10 + (USART2_RX_BUF[9] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[1] = (USART2_RX_BUF[10] - 0x30) * 10 + (USART2_RX_BUF[11] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_num = USART2_RX_BUF[12] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[0] = USART2_RX_BUF[13] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[1] = USART2_RX_BUF[14] - 0x30;
			
			mesh_dev[USART2_RX_BUF[4]-2].STAT = true;
			
			printf("MADDR:%d\r\n",mesh_dev[USART2_RX_BUF[4]-2].MADDR);
		}
		else if(USART2_RX_BUF[3]==0&&USART2_RX_BUF[4]==4)
		{
			mesh_dev[USART2_RX_BUF[4]-2].MADDR = USART2_RX_BUF[4];
			mesh_dev[USART2_RX_BUF[4]-2].NETID = 1122;
			
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_num = USART2_RX_BUF[7] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[0] = (USART2_RX_BUF[8] - 0x30) * 10 + (USART2_RX_BUF[9] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_only_value[1] = (USART2_RX_BUF[10] - 0x30) * 10 + (USART2_RX_BUF[11] - 0x30);
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_num = USART2_RX_BUF[12] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[0] = USART2_RX_BUF[13] - 0x30;
			mesh_dev[USART2_RX_BUF[4]-2].Read_write_value[1] = USART2_RX_BUF[14] - 0x30;
			
			mesh_dev[USART2_RX_BUF[4]-2].STAT = true;
			
			printf("MADDR:%d\r\n",mesh_dev[USART2_RX_BUF[4]-2].MADDR);
			
		}
//		else if(strstr(p,"SW_C"))
//		{
//			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_SW);
//			Message.MsgId = WM_NOTIFY_PARENT;
//			Message.Data.v = WM_NOTIFICATION_USER + 1;
//			WM_SendMessage(pMsg->hWin, &Message);				
//		}
		else 
		{
			printf("%s\r\n",USART2_RX_BUF);
			printf("unknown msg\r\n");
		}
		
		
//			Message.hWinSrc = WM_GetDialogItem(WM_HBKWIN, ID_ICONVIEW_SW);
//			Message.MsgId = WM_NOTIFY_PARENT;
//			Message.Data.v = WM_NOTIFICATION_USER + 1;
//			WM_SendMessage(WM_HBKWIN, &Message);			
		
		
		if(sys_init_finish_flag)
			OSQPost((OS_Q*		)&DATA_Msg,		
					(void*		)&"c",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);		
		
			
	}
		
		
		//������Ļ��Ϣ
		//�������£��ô��ڶ�ʱ���ص��������� ���ﲻ��
		//�Զ����£�����Ӧ���ڷ���Ϣ ����������� ����ʹ����Ч������
		//WM_SendMessageNoPara(WM_HBKWIN,WM_PAINT);
		WM_Invalidate(WM_HBKWIN);
		
		
		

		
		
		
	   //�ַ������� ����������buffer
	   //strcpy(receive_data_buffer,receive_data);
	   //memset(&receive_data[num],'\0',128-num);
       DMA1_Channel6->CNDTR=USART2_MAX_RECV_LEN;       //�������ý������ݸ���        
	   DMA_Cmd(DMA1_Channel6,ENABLE);  //����DMA
       USART2_RX_FLAG = 1;           //�������ݱ�־λ��1
    }
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}   


//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart2_DMA_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //����2ʱ��ʹ��
	//��λ����2
 	USART_DeInit(USART2);  
	//USART2_TX   PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART2_RX	  PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB11
	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART2, &USART_InitStructure); //��ʼ������	2

	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//ʹ�ܿ����ж�
	//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�   
	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

	DMA1_USART2_init();
}


//����2,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}


//DMA ����Ӧ��Դ�� TX
void DMA_USART2_Tx_Data(u8 *buffer,u32 size)
{
	//�ȴ���һ�η�����ɣ�USART2_TX_FLAGΪ1�����ڷ������ݣ�
	while(USART2_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	USART2_TX_FLAG = 1;					//USART2���ͱ�־���������ͣ�
	DMA1_Channel7->CMAR = (u32)buffer;	//����Ҫ���͵����ݵ�ַ
	DMA1_Channel7->CNDTR = size;		//����Ҫ���͵��ֽ���Ŀ
	DMA_Cmd(DMA1_Channel7,ENABLE);		//��ʼDMA����
}

//DMA1ͨ��2�ж�
void DMA1_Channel7_IRQHandler(void)
{
#ifdef SYSTEM_SUPPORT_OS	 	
	OSIntEnter();    
#endif	
	if(DMA_GetITStatus(DMA1_IT_TC7)!=RESET)		//DMA������ɱ�־
	{
		DMA_ClearITPendingBit(DMA1_IT_TC7);		//����жϱ�־ 
		USART_ClearFlag(USART2,USART_FLAG_TC);	//�������2�ı�־λ
		DMA_Cmd(DMA1_Channel7,DISABLE);			//�ر�USART2 TX DMA1 ��ָʾ��ͨ��
		USART2_TX_FLAG = 0;						//USART2���ͱ�־(�ر�)
		
		
	}
#ifdef SYSTEM_SUPPORT_OS	 
	OSIntExit();  											 
#endif	
}

void u2_DMA_printf(char *format,...)
{
	//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>�����ڻ�ȡ��ȷ�������Ĳ�����
	va_list arg_ptr;//ʵ�����ɱ䳤�����б�
	
	//�ȴ���һ�η�����ɣ�USART3_TX_FLAGΪ1�����ڷ������ݣ�
	while(USART2_TX_FLAG)
	{
	#ifdef SYSTEM_SUPPORT_OS	 	
		delay_ms(10);    
	#endif		
	}		
	
	
	
	
	
	va_start(arg_ptr,format);				//��ʼ���ɱ�����б�����formatΪ�ɱ䳤�б����ʼ�㣨��һ��Ԫ�أ�
	
	//USART2_MAX_TX_LEN+1�ɽ��ܵ�����ַ���(���ֽ�����UNICODEһ���ַ������ֽ�), ��ֹ��������Խ��
	vsnprintf((char*)USART2_TX_BUF,USART2_MAX_SEND_LEN+1,format,arg_ptr);//��USART2_TX_BUF���׵�ַ��ʼƴ�ϣ�ƴ��format���ݣ�USART2_MAX_TX_LEN+1���Ƴ��ȣ���ֹ��������Խ��
	
	va_end(arg_ptr);						//ע�����ر�
	
	DMA_USART2_Tx_Data(USART2_TX_BUF,strlen((const char*)USART2_TX_BUF));//����USART3_TX_BUF����
	
	
	
	
}











