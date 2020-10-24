/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.26                          *
*        Compiled Aug  8 2014, 14:49:54                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)

#include "Window_bgDLG.h"
#include "Window_bg2DLG.h"

#include "EmWinHZFont.h"
#include "GUI.h"
#include "malloc.h"
#include "ff.h"
#include "ili93xx.h"

#include "led.h"
#include "usart.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif



// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0        (GUI_ID_USER + 0x00)
#define ID_BUTTON_0        (GUI_ID_USER + 0x01)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

static FIL BMPFile;
static char bmpBuffer[BMPPERLINESIZE];


WM_HMEM win_bg;

//�ڴ��豸������
GUI_MEMDEV_Handle hBMP;


// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window_bg", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 0, 0, 80, 80, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)






//�����ݺ���
static int BmpGetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) 
{
	static int readaddress=0;
	FIL * phFile;
	UINT NumBytesRead;
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif
	
	phFile = (FIL *)p;
	
	if (NumBytesReq > sizeof(bmpBuffer)) 
	{
		NumBytesReq = sizeof(bmpBuffer);
	}

	//�ƶ�ָ�뵽Ӧ�ö�ȡ��λ��
	if(Off == 1) readaddress = 0;
	else readaddress=Off;
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
	f_lseek(phFile,readaddress); 
	
	//��ȡ���ݵ���������
	f_read(phFile,bmpBuffer,NumBytesReq,&NumBytesRead);
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ��� 
	#endif
	*ppData = (U8 *)bmpBuffer;
	return NumBytesRead;//���ض�ȡ�����ֽ���
}

//��ָ��λ����ʾ���ص�RAM�е�BMPͼƬ
//BMPFileName:ͼƬ��SD�����������洢�豸�е�·��(���ļ�ϵͳ֧�֣�)
//mode:��ʾģʽ
//		0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
//		1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
//x:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
//y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
//member:  ���ű����ķ�����
//denom:���ű����ķ�ĸ��
//����ֵ:0 ��ʾ����,���� ʧ��
int dispbmp(u8 *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom)
{
	u16 bread;
	char *bmpbuffer;
	char result;
	int XSize,YSize;
	float Xflag,Yflag;

	
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif

	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴�������ļ�����BMPMEMORYSIZE
	if((result != FR_OK) || (BMPFile.fsize>BMPMEMORYSIZE)) 	return 1;

	bmpbuffer = mymalloc(SRAMEX,BMPFile.fsize);//�����ڴ�
	if(bmpbuffer == NULL) return 2;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
		
	result = f_read(&BMPFile,bmpbuffer,BMPFile.fsize,(UINT *)&bread); //��ȡ����
	if(result != FR_OK) return 3;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ���
	#endif
	
	switch(mode)
	{
		case 0:	//��ָ��λ����ʾͼƬ
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				GUI_BMP_Draw(bmpbuffer,x,y);	//��ָ��λ����ʾBMPͼƬ
			}else //����ͼƬ��Ҫ����
			{
				GUI_BMP_DrawScaled(bmpbuffer,x,y,member,denom);
			}
			break;
		case 1:	//��LCD�м���ʾͼƬ
			XSize = GUI_BMP_GetXSize(bmpbuffer);	//��ȡͼƬ��X���С
			YSize = GUI_BMP_GetYSize(bmpbuffer);	//��ȡͼƬ��Y���С
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				//��LCD�м���ʾͼƬ
				GUI_BMP_Draw(bmpbuffer,(lcddev.width-XSize)/2-1,(lcddev.height-YSize)/2-1);
			}else //����ͼƬ��Ҫ����
			{
				Xflag = (float)XSize*((float)member/(float)denom);
				Yflag = (float)YSize*((float)member/(float)denom);
				XSize = (lcddev.width-(int)Xflag)/2-1;
				YSize = (lcddev.height-(int)Yflag)/2-1;
				GUI_BMP_DrawScaled(bmpbuffer,XSize,YSize,member,denom);
			}
			break;
	}
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	myfree(SRAMEX,bmpbuffer);	//�ͷ��ڴ�
	return 0;
}


//ʹ���ڴ��豸��ʾbmp
int LoadBMP_UsingMEMDEV(u8 *BMPFileName,u32 x,u32 y)
{
	u16 bread;
	char *bmpbuffer;
	char result;
	int XSize,YSize;
	float Xflag,Yflag;

	
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif

	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_OPEN_EXISTING |FA_READ);	//���ļ�
	//�ļ��򿪴�������ļ�����BMPMEMORYSIZE
	if((result != FR_OK) || (BMPFile.fsize>BMPMEMORYSIZE)) 	return 1;

	bmpbuffer = mymalloc(SRAMEX,BMPFile.fsize);//�����ڴ�
	if(bmpbuffer == NULL) return 2;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
		
	result = f_read(&BMPFile,bmpbuffer,BMPFile.fsize,(UINT *)&bread); //��ȡ����
	if(result != FR_OK) return 3;
	
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ���
	#endif
	
/* �����ڴ��豸 */
    hBMP = GUI_MEMDEV_CreateEx(x, y,            /* ��ʼ���� */
                    GUI_BMP_GetXSize(bmpbuffer), /* x����ߴ� */
                    GUI_BMP_GetYSize(bmpbuffer), /* y����ߴ� */
                    GUI_MEMDEV_HASTRANS);        /* ��͸���ȵ��ڴ��豸 */
    /* ѡ���ڴ��豸 */
    GUI_MEMDEV_Select(hBMP);
    /* ����BMP���ڴ��豸�� */
    GUI_BMP_Draw(bmpbuffer, x, y);
    /* ѡ���ڴ��豸��0��ʾѡ��LCD */
    GUI_MEMDEV_Select(0);	
	
	myfree(SRAMEX,bmpbuffer);	//�ͷ��ڴ�
	return 0;
}





static GUI_BITMAP Bitmap;
static GUI_LOGPALETTE Palette;
static char *bmpbuffer;

//ʹ����λͼ��ʾbmp
int showstreambitmap(u8 *BMPFileName,u32 x,u32 y)
{
	u16 bread;

	char result;
	int XSize,YSize;
	float Xflag,Yflag;

	
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif

	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_OPEN_EXISTING |FA_READ);	//���ļ�
	//�ļ��򿪴�������ļ�����BMPMEMORYSIZE
	if((result != FR_OK) || (BMPFile.fsize>BMPMEMORYSIZE)) 	return 1;

	bmpbuffer = mymalloc(SRAMEX,BMPFile.fsize);//�����ڴ�
	if(bmpbuffer == NULL) return 2;
	
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
		
	result = f_read(&BMPFile,bmpbuffer,BMPFile.fsize,(UINT *)&bread); //��ȡ����
	if(result != FR_OK) return 3;
	
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ���
	#endif
	
	
	GUI_CreateBitmapFromStream(&Bitmap, &Palette, bmpbuffer);

	
	
	
	GUI_DrawStreamedBitmapAuto(bmpbuffer, x, y);

	myfree(SRAMEX,bmpbuffer);	//�ͷ��ڴ�
	return 0;
}


























void bmpdisplay_demo(void)
{
	dispbmp("0:/image/bg1.bmp",0,0,	0,	1,1);
	//showstreambitmap("0:/data/bg1.dta",0,0);
}


// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  int NCode;
  int Id;
	
	int t0=0,t1=0;
	

  // USER START (Optionally insert additional variables)
	
	//bmpdisplay_demo();
	//printf("inti\r\n");
	
	
	//GUI_DrawBitmap(&Bitmap, 0, 0);
	
  // USER END

  switch (pMsg->MsgId) {
	  
 case WM_INIT_DIALOG:
//	t0 = GUI_GetTime();
//	bmpdisplay_demo();
//	t1 = GUI_GetTime();
//	printf("paint: %dms\r\n",t1-t0);
	//WM_Paint(WM_HBKWIN);
	 break;
	  
 
//	//�����ػ�
//	case WM_PAINT:
//		
//	t0 = GUI_GetTime();
//		
//	bmpdisplay_demo();
//	
//	t1 = GUI_GetTime();
//	
//	printf("paint: %dms\r\n",t1-t0);	
//	
//	//printf("paint\r\n");
//	
//	//GUI_DrawBitmap(&Bitmap, 0, 0);
//	
//	//GUI_DrawStreamedBitmapAuto(bmpbuffer, 0, 0);
//	
//	/* ���ڴ��豸д��LCD */
//	//GUI_MEMDEV_CopyToLCDAt(hBMP,0,0);
//	//GUI_MEMDEV_WriteAt(hBMP,0,0);
//	//GUI_MEASDEV_Select(0);
//	
//	break; 
 
 
 
 
 
	  
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
//		WM_HideWin(win_bg);
//		WM_ShowWin(win_bg2);
	  
	  //WM_HideWin(win_bg);
		GUI_EndDialog(pMsg->hWin,0);
		CreateWindow_bg2();
	  
	  
		//WM_Paint(WM_HBKWIN);
//	  	t0 = GUI_GetTime();
//		bmpdisplay_demo();
//		t1 = GUI_GetTime();
//		printf("paint: %dms\r\n",t1-t0);
	  //GUI_MEMDEV_CopyToLCDAt(hBMP,0,0);
	  
	  
		//LED0 =~LED0;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
	
	
	//	//�����ػ�
	case WM_PAINT:
		
	t0 = GUI_GetTime();
		
	bmpdisplay_demo();
	
	//LoadBMP_UsingMEMDEV("0:/image/bg1.bmp",0,0);
	
	//GUI_MEMDEV_WriteAt(hBMP,0,0);
	
	//GUI_MEMDEV_WriteAt(hBMP,0,0);
	//GUI_MEASDEV_Select(0);
	
	t1 = GUI_GetTime();
	
	printf("paint: %dms\r\n",t1-t0);	
	
	//printf("paint\r\n");
	
	//GUI_DrawBitmap(&Bitmap, 0, 0);
	
	//GUI_DrawStreamedBitmapAuto(bmpbuffer, 0, 0);
	
	/* ���ڴ��豸д��LCD */
	//GUI_MEMDEV_CopyToLCDAt(hBMP,0,0);
	//GUI_MEMDEV_WriteAt(hBMP,0,0);
	//GUI_MEASDEV_Select(0);
	
	break; 
	
	
	
	
	
	
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow_bg
*/

WM_HWIN CreateWindow_bg(void) {
	WM_HWIN hWin;

	//bmpdisplay_demo();
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/