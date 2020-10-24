#include "dma.h"
#include "usart2.h"
#include "usart3.h"

void DMA1_USART3_init(void)
{
   DMA_InitTypeDef    DMA_Initstructure;
   NVIC_InitTypeDef   NVIC_Initstructure;
    
   /*����DMAʱ��*/
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
   
   /*DMA����*/
	//RX ����
   DMA_DeInit(DMA1_Channel3);
   DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART3->DR);
   DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)USART3_RX_BUF;
   DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_Initstructure.DMA_BufferSize = USART3_MAX_RECV_LEN;
   DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
   DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
   DMA_Initstructure.DMA_Priority = DMA_Priority_High;
   DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel3,&DMA_Initstructure);
     
   //TX ����
   DMA_DeInit(DMA1_Channel2);
   DMA_Initstructure.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);
   DMA_Initstructure.DMA_MemoryBaseAddr = (u32)USART3_TX_BUF;
   DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralDST;
   DMA_Initstructure.DMA_BufferSize = USART3_MAX_SEND_LEN;
   DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_Initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
   DMA_Initstructure.DMA_Priority = DMA_Priority_High;
   DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel2,&DMA_Initstructure);
   
   //DMA1 Channel2 NVIC
   NVIC_Initstructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
   NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_Initstructure);
   
   //DMA1 Channel3 NVIC
   NVIC_Initstructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
   NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_Initstructure);
   
   //ʹ��DMA�ж�
   DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);
   DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);
   
   //ʹ��DMAͨ��
   DMA_Cmd(DMA1_Channel2,DISABLE);	//TX
   DMA_Cmd(DMA1_Channel3,ENABLE);	//RX
   
   //����ʹ��DMAͨ��
   USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
   USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

} 

void DMA1_USART2_init(void)
{
   DMA_InitTypeDef    DMA_Initstructure;
   NVIC_InitTypeDef   NVIC_Initstructure;
    
   /*����DMAʱ��*/
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
   
   /*DMA����*/
	//RX ����
   DMA_DeInit(DMA1_Channel6);
   DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART2->DR);
   DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)USART2_RX_BUF;
   DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_Initstructure.DMA_BufferSize = USART2_MAX_RECV_LEN;
   DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
   DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
   DMA_Initstructure.DMA_Priority = DMA_Priority_High;
   DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel6,&DMA_Initstructure);
     
   //TX ����
   DMA_DeInit(DMA1_Channel7);
   DMA_Initstructure.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
   DMA_Initstructure.DMA_MemoryBaseAddr = (u32)USART2_TX_BUF;
   DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralDST;
   DMA_Initstructure.DMA_BufferSize = USART2_MAX_SEND_LEN;
   DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_Initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
   DMA_Initstructure.DMA_Priority = DMA_Priority_High;
   DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel7,&DMA_Initstructure);
   
   //DMA1 Channel7 NVIC
   NVIC_Initstructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
   NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_Initstructure);
   
   //DMA1 Channel6 NVIC
   NVIC_Initstructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
   NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_Initstructure);
   
   //ʹ��DMA�ж�
   DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);
   DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
   
   //ʹ��DMAͨ��
   DMA_Cmd(DMA1_Channel7,DISABLE);	//TX
   DMA_Cmd(DMA1_Channel6,ENABLE);	//RX
   
   //����ʹ��DMAͨ��
   USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
   USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	
}























