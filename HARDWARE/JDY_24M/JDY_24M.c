#include "delay.h" 			 
#include "usart.h" 			 
#include "usart2.h" 			 
#include "JDY_24M.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"

#include "stdarg.h"	


//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif


////标志
//u8 jdy_send = 0;




//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//ATK-HC05蓝牙模块驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/3/29
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20140329
//修改LED的连接，原来接PC5，改为PA4，以兼容MiniSTM32开发板V3.0									  
////////////////////////////////////////////////////////////////////////////////// 	   

/**********************************

//初始化ATK-HC05模块
//返回值:0,成功;1,失败.
u8 JDY_24M_Init(void)
{
	u8 retry=10,t;	  		 
	u8 temp=1;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能PORTA
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化A15
	 
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	JDY_24M_STAT=1; 
	
	usart3_init(115200);	//初始化串口2为:9600,波特率.
	
	while(retry--)
	{
		delay_ms(10);
		u3_printf("AT\r\n");		//发送AT测试指令
		for(t=0;t<10;t++) 			//最长等待50ms,来接收HC05模块的回应
		{
			if(USART3_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART3_RX_STA&0X8000)	//接收到一次数据了
		{
			temp=USART3_RX_STA&0X7FFF;	//得到数据长度
			USART3_RX_STA=0;			 
			if(temp==5&&USART3_RX_BUF[0]=='+'&&USART3_RX_BUF[1]=='O'&&USART3_RX_BUF[2]=='K')
			{
				temp=0;//接收到OK响应
				break;
			}
		}			    		
	}		    
	if(retry==0)temp=1;	//检测失败
	return temp;	  
}	 
//获取ATK-HC05模块的角色
//返回值:0,从机;1,主机;0XFF,获取失败.							  
u8 JDY_24M_Get_Role(void)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		delay_ms(10);
		u3_printf("AT+ROLE?\r\n");	//查询角色
		for(t=0;t<20;t++) 			//最长等待200ms,来接收HC05模块的回应
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)break;
		}		
		if(USART3_RX_STA&0X8000)	//接收到一次数据了
		{
			temp=USART3_RX_STA&0X7FFF;	//得到数据长度
			USART3_RX_STA=0;			 
			if(temp==13&&USART3_RX_BUF[0]=='+')//接收到正确的应答了
			{
				temp=USART3_RX_BUF[6]-'0';//得到主从模式值
				break;
			}
		}		
	}
	if(retry==0)temp=0XFF;//查询失败.
	return temp;
} 							   
//ATK-HC05设置命令
//此函数用于设置ATK-HC05,适用于仅返回OK应答的AT指令
//atstr:AT指令串.比如:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"等字符串
//返回值:0,设置成功;其他,设置失败.							  
u8 JDY_24M_Set_Cmd(u8* atstr)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		delay_ms(10);
		u3_printf("%s\r\n",atstr);	//发送AT字符串
		for(t=0;t<20;t++) 			//最长等待100ms,来接收HC05模块的回应
		{
			if(USART3_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART3_RX_STA&0X8000)	//接收到一次数据了
		{
			temp=USART3_RX_STA&0X7FFF;	//得到数据长度
			USART3_RX_STA=0;			 
			if(temp==4&&USART3_RX_BUF[0]=='O')//接收到正确的应答了
			{			
				temp=0;
				break;			 
			}
		}		
	}
	if(retry==0)temp=0XFF;//设置失败.
	return temp;
} 
///////////////////////////////////////////////////////////////////////////////////////////////////
//通过该函数,可以利用USMART,调试接在串口3上的ATK-HC05模块
//str:命令串.(这里注意不再需要再输入回车符)
void JDY_24M_CFG_CMD(u8 *str)
{					  
	u8 temp;
	u8 t;		  
	delay_ms(10);
	u3_printf("%s\r\n",(char*)str); //发送指令
	for(t=0;t<50;t++) 				//最长等待500ms,来接收HC05模块的回应
	{
		if(USART3_RX_STA&0X8000)break;
		delay_ms(10);
	}									    
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{
		temp=USART3_RX_STA&0X7FFF;	//得到数据长度
		USART3_RX_STA=0;
		USART3_RX_BUF[temp]=0;		//加结束符		 
		printf("\r\n%s",USART3_RX_BUF);//发送回应数据到串口1
	} 				 
}


*************************/



//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void JDY_MESH_printf(u8 CMD,u16 Target_MADDR, char* fmt,...)  
{ 

//	OS_ERR err;
	u16 i=0,ulen=0; 
	va_list ap; 
	u8 sendbuf[50];
	u8 tmpbuf[50];
	
	//OSSchedLock(&err);
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区

	
	//OSSchedLock(&err);
	
	//格式化字符串
	va_start(ap,fmt);
	ulen=vsprintf((char*)tmpbuf,fmt,ap);
	va_end(ap);
	//初始化sendbuf
	for(i=0;i<50;i++) sendbuf[i]=0x00;
	
	//初始化sendbuf
	//memset(sendbuf,'\0',sizeof(sendbuf));
	//帧头部
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
	
	//拼接
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
//		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
//		USART_SendData(USART2,sendbuf[i]); 
//	}
	//OSSchedUnlock(&err);
	//OSSchedUnlock();
//	OS_CRITICAL_EXIT();	//退出临界区
	
	
	
	//u2_DMA_printf("%s",sendbuf);
	
	printf("JDY TX :%d\r\n",ulen);
	
	
	DMA_USART2_Tx_Data(sendbuf,10+ulen);
	
	
	
//	for(i=0;i<14;i++)
//	{
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
//		USART_SendData(USART3,sendbuf[i]); 
//	}	
	
	
	/*
	strlen所作的是一个计数器的工作，它从内存的某个位置（可以是字符串开头，中间某个位置，
	甚至是某个不确定的内存区域）开始扫描，直到碰到第一个字符串结束符'\0'为止，
	然后返回计数器值(长度不包含'\0')
	*/
	
	
//	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	
//	i = sizeof(USART3_TX_BUF)/sizeof(USART3_TX_BUF[0]);
	
//	printf("%d\r\n",sizeof(USART3_TX_BUF));
	
//	printf("%d\r\n",i);
	
//	for(j=0;j<i;j++)							//循环发送数据
//	{
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
//		USART_SendData(USART3,USART3_TX_BUF[j]); 
//	} 
}




//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void JDY_AT_printf(char* fmt,...)  
{  
	u16 i=0,ulen=0; 
	va_list ap; 
	u8 sendbuf[128];
	
	//初始化sendbuf
	//for(i=0;i<128;i++) sendbuf[i]=0x00;	
	
	//初始化sendbuf
	memset(sendbuf,'\0',sizeof(sendbuf));
	
	//格式化字符串
	va_start(ap,fmt);
	ulen=vsprintf((char*)sendbuf,fmt,ap);
	va_end(ap);
	
//	//发送字符串
//	for(i=0;i<ulen;i++)
//	{
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
//		USART_SendData(USART3,sendbuf[i]); 
//	} 

//	u2_DMA_printf("%s\r\n",sendbuf);
	u2_DMA_printf("%s",sendbuf);
}





