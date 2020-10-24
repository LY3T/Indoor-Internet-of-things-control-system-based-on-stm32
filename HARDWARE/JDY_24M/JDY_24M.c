#include "delay.h" 			 
#include "usart.h" 			 
#include "usart2.h" 			 
#include "JDY_24M.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"

#include "stdarg.h"	


//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif


////��־
//u8 jdy_send = 0;




//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-HC05����ģ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/3/29
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20140329
//�޸�LED�����ӣ�ԭ����PC5����ΪPA4���Լ���MiniSTM32������V3.0									  
////////////////////////////////////////////////////////////////////////////////// 	   

/**********************************

//��ʼ��ATK-HC05ģ��
//����ֵ:0,�ɹ�;1,ʧ��.
u8 JDY_24M_Init(void)
{
	u8 retry=10,t;	  		 
	u8 temp=1;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ��PORTA
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��A15
	 
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	JDY_24M_STAT=1; 
	
	usart3_init(115200);	//��ʼ������2Ϊ:9600,������.
	
	while(retry--)
	{
		delay_ms(10);
		u3_printf("AT\r\n");		//����AT����ָ��
		for(t=0;t<10;t++) 			//��ȴ�50ms,������HC05ģ��Ļ�Ӧ
		{
			if(USART3_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART3_RX_STA&0X8000)	//���յ�һ��������
		{
			temp=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			USART3_RX_STA=0;			 
			if(temp==5&&USART3_RX_BUF[0]=='+'&&USART3_RX_BUF[1]=='O'&&USART3_RX_BUF[2]=='K')
			{
				temp=0;//���յ�OK��Ӧ
				break;
			}
		}			    		
	}		    
	if(retry==0)temp=1;	//���ʧ��
	return temp;	  
}	 
//��ȡATK-HC05ģ��Ľ�ɫ
//����ֵ:0,�ӻ�;1,����;0XFF,��ȡʧ��.							  
u8 JDY_24M_Get_Role(void)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		delay_ms(10);
		u3_printf("AT+ROLE?\r\n");	//��ѯ��ɫ
		for(t=0;t<20;t++) 			//��ȴ�200ms,������HC05ģ��Ļ�Ӧ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)break;
		}		
		if(USART3_RX_STA&0X8000)	//���յ�һ��������
		{
			temp=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			USART3_RX_STA=0;			 
			if(temp==13&&USART3_RX_BUF[0]=='+')//���յ���ȷ��Ӧ����
			{
				temp=USART3_RX_BUF[6]-'0';//�õ�����ģʽֵ
				break;
			}
		}		
	}
	if(retry==0)temp=0XFF;//��ѯʧ��.
	return temp;
} 							   
//ATK-HC05��������
//�˺�����������ATK-HC05,�����ڽ�����OKӦ���ATָ��
//atstr:ATָ�.����:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"���ַ���
//����ֵ:0,���óɹ�;����,����ʧ��.							  
u8 JDY_24M_Set_Cmd(u8* atstr)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		delay_ms(10);
		u3_printf("%s\r\n",atstr);	//����AT�ַ���
		for(t=0;t<20;t++) 			//��ȴ�100ms,������HC05ģ��Ļ�Ӧ
		{
			if(USART3_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART3_RX_STA&0X8000)	//���յ�һ��������
		{
			temp=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			USART3_RX_STA=0;			 
			if(temp==4&&USART3_RX_BUF[0]=='O')//���յ���ȷ��Ӧ����
			{			
				temp=0;
				break;			 
			}
		}		
	}
	if(retry==0)temp=0XFF;//����ʧ��.
	return temp;
} 
///////////////////////////////////////////////////////////////////////////////////////////////////
//ͨ���ú���,��������USMART,���Խ��ڴ���3�ϵ�ATK-HC05ģ��
//str:���.(����ע�ⲻ����Ҫ������س���)
void JDY_24M_CFG_CMD(u8 *str)
{					  
	u8 temp;
	u8 t;		  
	delay_ms(10);
	u3_printf("%s\r\n",(char*)str); //����ָ��
	for(t=0;t<50;t++) 				//��ȴ�500ms,������HC05ģ��Ļ�Ӧ
	{
		if(USART3_RX_STA&0X8000)break;
		delay_ms(10);
	}									    
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{
		temp=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
		USART3_RX_STA=0;
		USART3_RX_BUF[temp]=0;		//�ӽ�����		 
		printf("\r\n%s",USART3_RX_BUF);//���ͻ�Ӧ���ݵ�����1
	} 				 
}


*************************/



//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void JDY_MESH_printf(u8 CMD,u16 Target_MADDR, char* fmt,...)  
{ 

//	OS_ERR err;
	u16 i=0,ulen=0; 
	va_list ap; 
	u8 sendbuf[50];
	u8 tmpbuf[50];
	
	//OSSchedLock(&err);
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//�����ٽ���

	
	//OSSchedLock(&err);
	
	//��ʽ���ַ���
	va_start(ap,fmt);
	ulen=vsprintf((char*)tmpbuf,fmt,ap);
	va_end(ap);
	//��ʼ��sendbuf
	for(i=0;i<50;i++) sendbuf[i]=0x00;
	
	//��ʼ��sendbuf
	//memset(sendbuf,'\0',sizeof(sendbuf));
	//֡ͷ��
	sendbuf[0]=0x41;
	sendbuf[1]=0x54;
	sendbuf[2]=0x2b;
	sendbuf[3]=0x4d;	
	sendbuf[4]=0x45;
	sendbuf[5]=0x53;
	sendbuf[6]=0x48;
	sendbuf[7]=CMD&0xff;		
	sendbuf[8]=Target_MADDR>>8;	
	sendbuf[9]=Target_MADDR&0x00ff;
	
	
	
//	sendbuf[10]=0x11;
//	sendbuf[11]=0x22;
	
//	sendbuf[12]=0x0D;
//	sendbuf[13]=0x0A;	
	
	//ƴ��
	for(i=0;i<ulen;i++)
	{
		sendbuf[10+i]=tmpbuf[i];
	}
	
//	sendbuf[10+ulen]=0x0d;
//	sendbuf[10+ulen+1]=0x0a;
//	
	//OSSchedUnlock(&err);
	
//	for(i=0;i<ulen+10;i++)
//	{
//		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART2,sendbuf[i]); 
//	}
	//OSSchedUnlock(&err);
	//OSSchedUnlock();
//	OS_CRITICAL_EXIT();	//�˳��ٽ���
	
	
	
	//u2_DMA_printf("%s",sendbuf);
	
	printf("JDY TX :%d\r\n",ulen);
	
	
	DMA_USART2_Tx_Data(sendbuf,10+ulen);
	
	
	
//	for(i=0;i<14;i++)
//	{
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART3,sendbuf[i]); 
//	}	
	
	
	/*
	strlen��������һ���������Ĺ����������ڴ��ĳ��λ�ã��������ַ�����ͷ���м�ĳ��λ�ã�
	������ĳ����ȷ�����ڴ����򣩿�ʼɨ�裬ֱ��������һ���ַ���������'\0'Ϊֹ��
	Ȼ�󷵻ؼ�����ֵ(���Ȳ�����'\0')
	*/
	
	
//	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	
//	i = sizeof(USART3_TX_BUF)/sizeof(USART3_TX_BUF[0]);
	
//	printf("%d\r\n",sizeof(USART3_TX_BUF));
	
//	printf("%d\r\n",i);
	
//	for(j=0;j<i;j++)							//ѭ����������
//	{
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART3,USART3_TX_BUF[j]); 
//	} 
}




//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void JDY_AT_printf(char* fmt,...)  
{  
	u16 i=0,ulen=0; 
	va_list ap; 
	u8 sendbuf[128];
	
	//��ʼ��sendbuf
	//for(i=0;i<128;i++) sendbuf[i]=0x00;	
	
	//��ʼ��sendbuf
	memset(sendbuf,'\0',sizeof(sendbuf));
	
	//��ʽ���ַ���
	va_start(ap,fmt);
	ulen=vsprintf((char*)sendbuf,fmt,ap);
	va_end(ap);
	
//	//�����ַ���
//	for(i=0;i<ulen;i++)
//	{
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART3,sendbuf[i]); 
//	} 

//	u2_DMA_printf("%s\r\n",sendbuf);
	u2_DMA_printf("%s",sendbuf);
}





