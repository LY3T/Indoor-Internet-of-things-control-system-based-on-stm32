#ifndef _JDY_24M_H
#define _JDY_24M_H	 
#include "sys.h" 
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

#define JDY_24M_STAT PAin(15)		//��������״̬�ź�
  
//u8 JDY_24M_Init(void);

////��־
//extern u8 jdy_send;

//void JDY_24M_CFG_CMD(u8 *str);
//u8 JDY_24M_Get_Role(void);
//u8 JDY_24M_Set_Cmd(u8* atstr);	

void JDY_MESH_printf(u8 CMD,u16 Target_MADDR, char* fmt,...);
void JDY_AT_printf(char* fmt,...);
#endif  
















