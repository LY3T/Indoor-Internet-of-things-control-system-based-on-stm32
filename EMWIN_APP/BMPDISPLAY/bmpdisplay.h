#ifndef _BMPDISPLAY_H
#define _BMPDISPLAY_H
#include "sys.h"
#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103ս��������
//STemwin BMPͼƬ��ʾ 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//ʹ��GUI_BMP_Draw()��������BMPͼƬ�Ļ�
//ͼƬ�Ǽ��ص�RAM�еģ���˲��ܴ���BMPMEMORYSIZE
//ע�⣺��ʾBMPͼƬʱ�ڴ�����ʹ�õ�EMWIN���ڴ����뺯�������
//BMPMEMORYSIZE���ܴ������Ǹ�EMWIN������ڴ�ش�С
#define BMPMEMORYSIZE	500*1024	//ͼƬ��С������500kb

//����������ص�RAM�е�BMPͼƬʱ��ͼƬÿ�е��ֽ���
#define BMPPERLINESIZE	2*1024		



//�ڴ��豸������
extern GUI_MEMDEV_Handle hBMP;
//���Ƽ��ص�RAM�е�BMPͼƬ��RAM.bmp��
int dispbmp(u8 *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom);
//����������ص�RAM�е�BMPͼƬ��SD��.bmp��
int dispbmpex(u8 *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom);
//���Ƽ��ص�RAM�е�BMP��λͼ��RAM.dat��
int showstreambitmap(u8 *BMPFileName,u32 x,u32 y);
//ʹ���ڴ��豸��ʾbmp��RAM.bmp��
int LoadBMP_UsingMEMDEV(u8 *BMPFileName,u32 x,u32 y);

//��ͼ
void create_bmppicture(u8 *filename,int x0,int y0,int Xsize,int Ysize);
//��������
void bmpdisplay_demo(void);


#endif
