#include <stddef.h>
#include "DIALOG.h"
#include "keypad.h"
//#include "tftlcd.h"
#include "ILI93xx.h"
#include "string.h"
#include "stdlib.h"
#include "usart.h"
#include "pyinput.h"
#include "EmWinHZFont.h"
#include "led.h"
#include "WM.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4/F7������
//STemWin �����
//�˼���ʵ����:Ӣ��(��Сд)�����֣����ţ����Ļ������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/4/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


#define ID_FRAMEWIN_1        (GUI_ID_USER + 0xC4)

static WM_CALLBACK*     _pcbOldFrame;
extern WM_HWIN iconview_wifi_hItem;

WM_HWIN hMulti=0;       //�����ı�
WM_HWIN hFrame;

KEYPADStructTypeDef keypad_dev;		

static int _DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo); 
static int _DrawChineseSkin_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
	
typedef struct 
{
	int          xPos;              //��ťXλ��
	int          yPos;              //��ťYλ��
	int          xSize;             //��ť���
	int          ySize;             //��ť�߶�
	const char * acLabel;           //��ť��������ַ�
	void (* pfDraw)(WM_HWIN hWin);  //��ť�Ļ��ƺ���
    const char * ButString;         //��ť����ʾ���ַ�
} BUTTON_DATA;


//�ڰ�ť�ϻ���λͼ������س�����ɾ������
static void _DrawCentered(WM_HWIN hWin, const GUI_BITMAP * pBM) 
{
	int xSizeWin;
	int ySizeWin;
	int xSizeBMP;
	int ySizeBMP;
	int xPos;
	int yPos;

	xSizeWin = WM_GetWindowSizeX(hWin);
	ySizeWin = WM_GetWindowSizeY(hWin);
	xSizeBMP = pBM->XSize;
	ySizeBMP = pBM->YSize;
	xPos = (xSizeWin - xSizeBMP) >> 1;
	yPos = (ySizeWin - ySizeBMP) >> 1;
	GUI_DrawBitmap(pBM, xPos, yPos);
}

static void _DrawBkSpc (WM_HWIN hWin) {  _DrawCentered(hWin, &bmBackSpace); }	//�����˸��(ɾ����)
static void _DrawEnter (WM_HWIN hWin) {  _DrawCentered(hWin, &bmEnter); }		//���ƻس���
static void _DrawShift (WM_HWIN hWin) {  _DrawCentered(hWin, &bmShift); }		//����shift��
static void _DrawRetern(WM_HWIN hWin) {  _DrawCentered(hWin, &bmReturn); }		//���Ʒ��ؼ�


//Ӣ�ļ���λ��
static  BUTTON_DATA _aEngButtonData[] = {
	{ (ENG_BUTTON_XPAC*1+ENG_BUTTON_WIDTH*0+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "Q",0,"Q" },
	{ (ENG_BUTTON_XPAC*2+ENG_BUTTON_WIDTH*1+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "W",0,"W" },
	{ (ENG_BUTTON_XPAC*3+ENG_BUTTON_WIDTH*2+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "E",0,"E" },
	{ (ENG_BUTTON_XPAC*4+ENG_BUTTON_WIDTH*3+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "R",0,"R" },
	{ (ENG_BUTTON_XPAC*5+ENG_BUTTON_WIDTH*4+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "T",0,"T" },
	{ (ENG_BUTTON_XPAC*6+ENG_BUTTON_WIDTH*5+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "Y",0,"Y" },
	{ (ENG_BUTTON_XPAC*7+ENG_BUTTON_WIDTH*6+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "U",0,"U" },
	{ (ENG_BUTTON_XPAC*8+ENG_BUTTON_WIDTH*7+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "I",0,"I" },
	{ (ENG_BUTTON_XPAC*9+ENG_BUTTON_WIDTH*8+ENG_BUTTONLINE1_XOFFSET),  ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "O",0,"O" },
	{ (ENG_BUTTON_XPAC*10+ENG_BUTTON_WIDTH*9+ENG_BUTTONLINE1_XOFFSET), ENG_BUTTON_LINE1YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "P",0,"P" },

	{ (ENG_BUTTON_XPAC*1+ENG_BUTTON_WIDTH*0+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "A",0,"A" },
	{ (ENG_BUTTON_XPAC*2+ENG_BUTTON_WIDTH*1+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "S",0,"S" },
	{ (ENG_BUTTON_XPAC*3+ENG_BUTTON_WIDTH*2+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "D",0,"D" },
	{ (ENG_BUTTON_XPAC*4+ENG_BUTTON_WIDTH*3+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "F",0,"F" },
	{ (ENG_BUTTON_XPAC*5+ENG_BUTTON_WIDTH*4+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "G",0,"G" },
	{ (ENG_BUTTON_XPAC*6+ENG_BUTTON_WIDTH*5+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "H",0,"H" },
	{ (ENG_BUTTON_XPAC*7+ENG_BUTTON_WIDTH*6+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "J",0,"J" },
	{ (ENG_BUTTON_XPAC*8+ENG_BUTTON_WIDTH*7+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "K",0,"K" },
	{ (ENG_BUTTON_XPAC*9+ENG_BUTTON_WIDTH*8+ENG_BUTTONLINE2_XOFFSET),  ENG_BUTTON_LINE2YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "L",0,"L" },

	{ (ENG_BUTTON_XPAC*1+ENG_BUTTON_WIDTH*0+ENG_BUTTONLINE3_XOFFSET),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONSHIFT_XINC,ENG_BUTTON_HEIGHT, "\x19", _DrawShift },	//shift�ļ�ֵΪ0X19
	{ (ENG_BUTTON_XPAC*2+ENG_BUTTON_WIDTH*1+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "Z",0,"Z" },
	{ (ENG_BUTTON_XPAC*3+ENG_BUTTON_WIDTH*2+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "X",0,"X" },
	{ (ENG_BUTTON_XPAC*4+ENG_BUTTON_WIDTH*3+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "C",0,"C" },
	{ (ENG_BUTTON_XPAC*5+ENG_BUTTON_WIDTH*4+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "V",0,"V" },
	{ (ENG_BUTTON_XPAC*6+ENG_BUTTON_WIDTH*5+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "B",0,"B" },
	{ (ENG_BUTTON_XPAC*7+ENG_BUTTON_WIDTH*6+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "N",0,"N" },
	{ (ENG_BUTTON_XPAC*8+ENG_BUTTON_WIDTH*7+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "M",0,"M" },
	{ (ENG_BUTTON_XPAC*9+ENG_BUTTON_WIDTH*8+ENG_BUTTONLINE3_XOFFSET+ENG_BUTTONSHIFT_XINC),  ENG_BUTTON_LINE3YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONENTER_XINC,ENG_BUTTON_HEIGHT, "\x08",_DrawBkSpc},
	
	{ (ENG_BUTTON_XPAC*1+ENG_BUTTON_WIDTH*0+ENG_BUTTONLINE4_XOFFSET),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONFIGURE_XINC,ENG_BUTTON_HEIGHT, "\x02",0,"��"},						    //�л��������				
	{ (ENG_BUTTON_XPAC*2+ENG_BUTTON_WIDTH*1+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONSYMBOL_XINC,ENG_BUTTON_HEIGHT,  "\x03",0,"��"},	//�л����ż���
	{ (ENG_BUTTON_XPAC*3+ENG_BUTTON_WIDTH*2+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC+ENG_BUTTONSYMBOL_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT,  ",",0,"," },
	{ (ENG_BUTTON_XPAC*4+ENG_BUTTON_WIDTH*3+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC+ENG_BUTTONSYMBOL_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONSPACE_XINC,ENG_BUTTON_HEIGHT,  " ",0,"����"},
	{ (ENG_BUTTON_XPAC*5+ENG_BUTTON_WIDTH*4+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC+ENG_BUTTONSYMBOL_XINC+ENG_BUTTONSPACE_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH,ENG_BUTTON_HEIGHT, "." ,0,"."},
	{ (ENG_BUTTON_XPAC*6+ENG_BUTTON_WIDTH*5+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC+ENG_BUTTONSYMBOL_XINC+ENG_BUTTONSPACE_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONCE_XINC,ENG_BUTTON_HEIGHT, "\x0B",0,"��"},	//�л������ļ���
	{ (ENG_BUTTON_XPAC*7+ENG_BUTTON_WIDTH*6+ENG_BUTTONLINE4_XOFFSET+ENG_BUTTONFIGURE_XINC+ENG_BUTTONSYMBOL_XINC+ENG_BUTTONSPACE_XINC+ENG_BUTTONCE_XINC),  ENG_BUTTON_LINE4YPOS, ENG_BUTTON_WIDTH+ENG_BUTTONBACK_XINC,ENG_BUTTON_HEIGHT, "\x0d",_DrawEnter},
};

//���ּ���λ��
static  BUTTON_DATA _aNumButtonData[] = {
	{ (NUM_BUTTON_XPAC*1+NUM_BUTTON_WIDTH*0+NUM_BUTTON_XOFFSET),  NUM_BUTTON_LINE1YPOS,(NUM_BUTTON_WIDTH-NUM_BUTTONSING_XINC),NUM_BUTTON_HEIGHT, "+",0,"+" },
	{ (NUM_BUTTON_XPAC*2+NUM_BUTTON_WIDTH*1+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE1YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "1" ,0,"1"},
	{ (NUM_BUTTON_XPAC*3+NUM_BUTTON_WIDTH*2+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE1YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "2" ,0,"2"},
	{ (NUM_BUTTON_XPAC*4+NUM_BUTTON_WIDTH*3+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE1YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "3" ,0,"3"},
	{ (NUM_BUTTON_XPAC*5+NUM_BUTTON_WIDTH*4+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE1YPOS, (NUM_BUTTON_WIDTH-NUM_BUTTONBACKSPACE_XINC),NUM_BUTTON_HEIGHT, "\x08",_DrawBkSpc},	//ɾ����
  
	{ (NUM_BUTTON_XPAC*1+NUM_BUTTON_WIDTH*0+NUM_BUTTON_XOFFSET),  NUM_BUTTON_LINE2YPOS,(NUM_BUTTON_WIDTH-NUM_BUTTONSING_XINC),NUM_BUTTON_HEIGHT, "-",0,"-" },
	{ (NUM_BUTTON_XPAC*2+NUM_BUTTON_WIDTH*1+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE2YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "4" ,0,"4"},
	{ (NUM_BUTTON_XPAC*3+NUM_BUTTON_WIDTH*2+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE2YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "5" ,0,"5"},
	{ (NUM_BUTTON_XPAC*4+NUM_BUTTON_WIDTH*3+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE2YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "6" ,0,"6"},
	{ (NUM_BUTTON_XPAC*5+NUM_BUTTON_WIDTH*4+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE2YPOS, (NUM_BUTTON_WIDTH-NUM_BUTTONSPACE_XINC),NUM_BUTTON_HEIGHT,  " ",0,"����" },	//�ո��
  
	{ (NUM_BUTTON_XPAC*1+NUM_BUTTON_WIDTH*0+NUM_BUTTON_XOFFSET),  NUM_BUTTON_LINE3YPOS,(NUM_BUTTON_WIDTH-NUM_BUTTONSING_XINC),NUM_BUTTON_HEIGHT, "/",0,"/" },
	{ (NUM_BUTTON_XPAC*2+NUM_BUTTON_WIDTH*1+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE3YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "7" ,0,"7"},
	{ (NUM_BUTTON_XPAC*3+NUM_BUTTON_WIDTH*2+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE3YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "8" ,0,"8"},
	{ (NUM_BUTTON_XPAC*4+NUM_BUTTON_WIDTH*3+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE3YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "9" ,0,"9"},
	{ (NUM_BUTTON_XPAC*5+NUM_BUTTON_WIDTH*4+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE3YPOS, (NUM_BUTTON_WIDTH-NUM_BUTTONENTER_XINC),NUM_BUTTON_HEIGHT, "\x0d",_DrawEnter},	//�س���
  
	{ (NUM_BUTTON_XPAC*1+NUM_BUTTON_WIDTH*0+NUM_BUTTON_XOFFSET),  NUM_BUTTON_LINE4YPOS,(NUM_BUTTON_WIDTH-NUM_BUTTONSING_XINC),NUM_BUTTON_HEIGHT, "@",0,"@" },
	{ (NUM_BUTTON_XPAC*2+NUM_BUTTON_WIDTH*1+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE4YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "," ,0,","},
	{ (NUM_BUTTON_XPAC*3+NUM_BUTTON_WIDTH*2+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE4YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "0" ,0,"0"},
	{ (NUM_BUTTON_XPAC*4+NUM_BUTTON_WIDTH*3+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE4YPOS, NUM_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "." ,0,"."},
	{ (NUM_BUTTON_XPAC*5+NUM_BUTTON_WIDTH*4+NUM_BUTTON_XOFFSET-NUM_BUTTONSING_XINC),  NUM_BUTTON_LINE4YPOS, (NUM_BUTTON_WIDTH-NUM_BUTTONRETURN_XINC),NUM_BUTTON_HEIGHT, "\x04",_DrawRetern },//���ؼ�
};

//���ż��̲���
static  BUTTON_DATA _aSinButtonData[][20] = {
	{
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "~" ,0,"~"},
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "-" ,0,"-"},
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, ":" ,0,":"},
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "_" ,0,"_"},
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x08",_DrawBkSpc},	//ɾ����
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "\"",0,"\"" },
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "," ,0,","},
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "<" ,0,"<"},
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, ">" ,0,">"},
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT,  "\x05",0,"��"},	//��һҳ
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "*",0,"*" },
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "+",0,"+" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, ".",0,"." },
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "#",0,"#" },
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x06",0,"��"},	//��һҳ
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "%",0,"%"},
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "@",0,"@" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "!",0,"!" },
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "/",0,"/" },
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x04",_DrawRetern },//���ؼ�
	},
	
	{
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "?",0,"?" },
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, ";",0,";" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "`",0,"`" },
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "$",0,"$" },
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE1YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x08",_DrawBkSpc},	//ɾ����
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "^" ,0,"^"},
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "\\",0,"\\" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, "(" ,0,"("},
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, SING_BUTTON_WIDTH,SIGN_BUTTON_HEIGHT, ")" ,0,")"},
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE2YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT,  "\x05",0,"��" },	//��һҳ
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "&",0,"&" },
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "=",0,"=" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "'",0,"'" },
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "|",0,"|" },
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE3YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x06",0,"��"},	//��һҳ
  
		{ (SIGN_BUTTON_XPAC*1+SING_BUTTON_WIDTH*0+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "[",0,"[" },
		{ (SIGN_BUTTON_XPAC*2+SING_BUTTON_WIDTH*1+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "]",0,"]" },
		{ (SIGN_BUTTON_XPAC*3+SING_BUTTON_WIDTH*2+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "{",0,"{" },
		{ (SIGN_BUTTON_XPAC*4+SING_BUTTON_WIDTH*3+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, SING_BUTTON_WIDTH,NUM_BUTTON_HEIGHT, "}",0,"}" },
		{ (SIGN_BUTTON_XPAC*5+SING_BUTTON_WIDTH*4+SIGN_BUTTON_XOFFSET),  SIGN_BUTTON_LINE4YPOS, (SING_BUTTON_WIDTH-SIGN_BUTTONCONTR_XINC),SIGN_BUTTON_HEIGHT, "\x04",_DrawRetern },//���ؼ�
	},
};

//���ļ���1λ��
static  BUTTON_DATA _aChineseButtonData1[] = {
    //���ļ��̵�һ����
	{ (CHIN1_BUTTON_XPAC*1+CHIN1_BUTTON_WIDTH*0+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE1YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, ";" ,0,";" },
	{ (CHIN1_BUTTON_XPAC*2+CHIN1_BUTTON_WIDTH*1+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE1YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "2" ,0,"ABC"},
	{ (CHIN1_BUTTON_XPAC*3+CHIN1_BUTTON_WIDTH*2+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE1YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "3" ,0,"DEF"},
	{ (CHIN1_BUTTON_XPAC*4+CHIN1_BUTTON_WIDTH*3+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE1YPOS, (CHIN1_BUTTON_WIDTH-CHIN1_BUTTONCONTR_XINC),CHIN1_BUTTON_HEIGHT, "\x08",_DrawBkSpc},	//ɾ����
  
	{ (CHIN1_BUTTON_XPAC*1+CHIN1_BUTTON_WIDTH*0+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE2YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "4" ,0,"GHI"},
	{ (CHIN1_BUTTON_XPAC*2+CHIN1_BUTTON_WIDTH*1+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE2YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "5" ,0,"JKL"},
	{ (CHIN1_BUTTON_XPAC*3+CHIN1_BUTTON_WIDTH*2+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE2YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "6" ,0,"MNO"},
	{ (CHIN1_BUTTON_XPAC*4+CHIN1_BUTTON_WIDTH*3+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE2YPOS, (CHIN1_BUTTON_WIDTH-CHIN1_BUTTONCONTR_XINC),CHIN1_BUTTON_HEIGHT,  " ",0,"����" },	//�ո��
  
	{ (CHIN1_BUTTON_XPAC*1+CHIN1_BUTTON_WIDTH*0+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE3YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "7",0,"PQRS" },
	{ (CHIN1_BUTTON_XPAC*2+CHIN1_BUTTON_WIDTH*1+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE3YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "8",0,"TUV" },
	{ (CHIN1_BUTTON_XPAC*3+CHIN1_BUTTON_WIDTH*2+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE3YPOS, CHIN1_BUTTON_WIDTH,CHIN1_BUTTON_HEIGHT, "9",0,"WXYZ"},
	{ (CHIN1_BUTTON_XPAC*4+CHIN1_BUTTON_WIDTH*3+CHIN1_BUTTON_XOFFSET),  CHIN1_BUTTON_LINE3YPOS, (CHIN1_BUTTON_WIDTH-CHIN1_BUTTONCONTR_XINC),CHIN1_BUTTON_HEIGHT, "\x04",_DrawRetern },//���ؼ�   
};
//���ļ���2λ��
static BUTTON_DATA _aChineseButtonData2[] = {
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "",0,"��"},             //����
	{ (CHIN2_BUTTON_XPAC*2+CHIN2_BUTTON_WIDTH*1+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
	{ (CHIN2_BUTTON_XPAC*3+CHIN2_BUTTON_WIDTH*2+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
	{ (CHIN2_BUTTON_XPAC*4+CHIN2_BUTTON_WIDTH*3+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
    { (CHIN2_BUTTON_XPAC*5+CHIN2_BUTTON_WIDTH*4+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
    { (CHIN2_BUTTON_XPAC*6+CHIN2_BUTTON_WIDTH*5+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
    { (CHIN2_BUTTON_XPAC*7+CHIN2_BUTTON_WIDTH*6+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "" },
    { (CHIN2_BUTTON_XPAC*8+CHIN2_BUTTON_WIDTH*7+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE1YPOS, CHIN2_BUTTON_WIDTH,CHIN2_BUTTON_HEIGHT, "",0,"��"},             //����
   
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE2YPOS, (CHIN2_BUTTON_WIDTH+CHIN2_BUTTONPY_XINC),(CHIN2_BUTTON_HEIGHT+CHIN2_BUTTONPY_YINC), "\x05",0,"��"},//��һҳ
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE3YPOS, (CHIN2_BUTTON_WIDTH+CHIN2_BUTTONPY_XINC),(CHIN2_BUTTON_HEIGHT+CHIN2_BUTTONPY_YINC), " " },
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE4YPOS, (CHIN2_BUTTON_WIDTH+CHIN2_BUTTONPY_XINC),(CHIN2_BUTTON_HEIGHT+CHIN2_BUTTONPY_YINC), " " },
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE5YPOS, (CHIN2_BUTTON_WIDTH+CHIN2_BUTTONPY_XINC),(CHIN2_BUTTON_HEIGHT+CHIN2_BUTTONPY_YINC), " " },
    { (CHIN2_BUTTON_XPAC*1+CHIN2_BUTTON_WIDTH*0+CHIN2_BUTTON_XOFFSET),  CHIN2_BUTTON_LINE6YPOS, (CHIN2_BUTTON_WIDTH+CHIN2_BUTTONPY_XINC),(CHIN2_BUTTON_HEIGHT+CHIN2_BUTTONPY_YINC), "\x06",0,"��" },//��һҳ
    
};

//��Сд�л�����
void changecase(u8 change_flag,BUTTON_DATA *buttondata)
{
	u16 i;
	char	   	NumToStr;
	char buffer[5];
	if(keypad_dev.LowerCase)		//Сд,��ť�޸�ΪСд
	{
		//���İ�ť���ַ�
		for (i = 0; i < 27; i++) 	
		{
			if(i==19) continue;
			NumToStr=(char)((int)*(buttondata[i].acLabel)+0x20);  
            sprintf(buffer,"%c",NumToStr);              //ת��Ϊ�ַ�
			BUTTON_SetFont(keypad_dev.EngButton_Handle[i],&GUI_FontHZ24); 
			BUTTON_SetText(keypad_dev.EngButton_Handle[i],buffer);
			BUTTON_SetFocussable(keypad_dev.EngButton_Handle[i], 0);
        }
    }
	else 	//��д����ť�ϵ��ַ���Ϊ��д
	{
		//���İ�ť���ַ�
		for (i = 0; i < 27; i++) 	
		{
			if(i==19) continue;
			BUTTON_SetFont(keypad_dev.EngButton_Handle[i],&GUI_FontHZ24);
			BUTTON_SetText(keypad_dev.EngButton_Handle[i], buttondata[i].acLabel);
			BUTTON_SetFocussable(keypad_dev.EngButton_Handle[i], 0);
		}
	}
}

//����Ӣ�ļ���
//hWin:������
void drawenglish_pad(WM_HWIN hWin)
{
	u16 	i;
	
	//�������̰�ť
	BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); //����BUTTON��Ƥ��	
	for (i = 0; i < GUI_COUNTOF(_aEngButtonData); i++) 
	{
		//������ť
		keypad_dev.EngButton_Handle[i] = BUTTON_CreateEx(_aEngButtonData[i].xPos, _aEngButtonData[i].yPos, _aEngButtonData[i].xSize, _aEngButtonData[i].ySize, 
                             hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
		BUTTON_SetFont(keypad_dev.EngButton_Handle[i],&GUI_FontHZ24);
        BUTTON_SetText(keypad_dev.EngButton_Handle[i], _aEngButtonData[i].ButString);
		BUTTON_SetFocussable(keypad_dev.EngButton_Handle[i], 0);
	}
	changecase(keypad_dev.LowerCase,_aEngButtonData);
}

//�������ּ���
void drawnumber_pad(WM_HWIN hWin)
{
	u16 i;
	for(i=0;i<GUI_COUNTOF(_aNumButtonData);i++)								//�������ּ���
	{
		//������ť
		BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); //����BUTTON��Ƥ��
		keypad_dev.NumButton_Handle[i] = BUTTON_CreateEx(_aNumButtonData[i].xPos, _aNumButtonData[i].yPos, _aNumButtonData[i].xSize, _aNumButtonData[i].ySize, 
                             hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
		BUTTON_SetFont(keypad_dev.NumButton_Handle[i],&GUI_FontHZ24);
		BUTTON_SetText(keypad_dev.NumButton_Handle[i], _aNumButtonData[i].ButString);
		BUTTON_SetFocussable(keypad_dev.NumButton_Handle[i], 0);
	}
}

//���Ʒ��ż���
void drawsign_pad(WM_HWIN hWin)
{
	u16 i;
	for(i=0;i<GUI_COUNTOF(_aSinButtonData[keypad_dev.signpad_flag]);i++)					//�������ż���
	{
		//������ť
      	BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); //����BUTTON��Ƥ��
		keypad_dev.SignButton_Handle[i] = BUTTON_CreateEx(_aSinButtonData[keypad_dev.signpad_flag][i].xPos, _aSinButtonData[keypad_dev.signpad_flag][i].yPos,
											_aSinButtonData[keypad_dev.signpad_flag][i].xSize,_aSinButtonData[keypad_dev.signpad_flag][i].ySize,
											hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
		BUTTON_SetFont(keypad_dev.SignButton_Handle[i],&GUI_FontHZ24);
		BUTTON_SetText(keypad_dev.SignButton_Handle[i],_aSinButtonData[keypad_dev.signpad_flag][i].ButString);
		BUTTON_SetFocussable(keypad_dev.SignButton_Handle[i], 0);
	}
}

//�������ļ���1
void drawchinese1_pad(WM_HWIN hWin)
{
	u16 i;
	for(i=0;i<GUI_COUNTOF(_aChineseButtonData1);i++)					//�������ļ���1
	{
		//������ť
		BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); //����BUTTON��Ƥ��
		keypad_dev.ChineseButton_Handle[i] = BUTTON_CreateEx(_aChineseButtonData1[i].xPos, _aChineseButtonData1[i].yPos, _aChineseButtonData1[i].xSize, _aChineseButtonData1[i].ySize, 
                             hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
		BUTTON_SetFont(keypad_dev.ChineseButton_Handle[i],&GUI_FontHZ24);
		BUTTON_SetText(keypad_dev.ChineseButton_Handle[i], _aChineseButtonData1[i].ButString);
		BUTTON_SetFocussable(keypad_dev.ChineseButton_Handle[i], 0);
	}
}

void drawchinese2_pad(WM_HWIN hWin)
{
    u16 i;
    for(i=0;i<GUI_COUNTOF(_aChineseButtonData2);i++)					//�������ļ���2
	{
		//������ť
		BUTTON_SetDefaultSkin(_DrawChineseSkin_BUTTON); //����BUTTON��Ƥ��
		keypad_dev.ChineseButton_Handle[i+12] = BUTTON_CreateEx(_aChineseButtonData2[i].xPos, _aChineseButtonData2[i].yPos, _aChineseButtonData2[i].xSize, _aChineseButtonData2[i].ySize, 
                             hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i+12);
		BUTTON_SetFont(keypad_dev.ChineseButton_Handle[i+12],&GUI_FontHZ24);
		BUTTON_SetText(keypad_dev.ChineseButton_Handle[i+12], _aChineseButtonData2[i].ButString);
		BUTTON_SetFocussable(keypad_dev.ChineseButton_Handle[i+12], 0);
	}
}

//Ӣ�ļ��̴�����
//buttondata:Ӣ�ļ��̰�ť����
//Id:��ťID
//*pMsg:ָ����Ϣ
void engkeypad_process(BUTTON_DATA *buttondata,int Id,WM_MESSAGE *pMsg)
{
	char 		c;
	WM_MESSAGE 	Msg;
    u8          KeyID;

    KeyID=Id-ID_BUTTON;
	if (buttondata[Id - ID_BUTTON].acLabel) 
	{
		c = buttondata[Id - ID_BUTTON].acLabel[0];
        if(KeyID == 19)                             //��Сд�л�
        {
            keypad_dev.LowerCase ^= 1;		        //��LowerCase����������
			changecase(keypad_dev.LowerCase,buttondata);                
        }
        else  if(KeyID == 28)                       //�л������ּ���
        {
            keypad_dev.padtype=NUMBER_KEYPAD;		//���ּ���
			Msg.MsgId=CHANGE_ENGLISHPADTO_NUMPAD;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg);
        }    
        else if(KeyID == 29)                        //�л������ż���
        {
            keypad_dev.padtype=SIGN_KEYPAD;		
			Msg.MsgId=CHANGE_ENGLISHPADTO_SIGNPAD1;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg);
        }
        else if(KeyID == 33)                        //�л������ļ���
        {
            keypad_dev.padtype=CHINESE_KEYPAD;		
			Msg.MsgId=CHANGE_ENGLISHPADTO_CHINESEPAD;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg);  
        }
        else
        {
            if (keypad_dev.LowerCase && (c>=0X41) && (c<=0X5A)) //Сд
			{
				c += 0x20;
			}
			GUI_StoreKeyMsg(c, 1);	//����Ϣ������̻�����������״̬
			GUI_StoreKeyMsg(c, 0);	//����Ϣ������̻��������ɿ�״̬
        }
	}
}

//���ּ��̴�����
//buttondata:���ּ��̰�ť����
//Id:��ťID
//*pMsg:ָ����Ϣ
void numkeypad_process(BUTTON_DATA *buttondata,int Id,WM_MESSAGE *pMsg)	
{
	char 		c;
	WM_MESSAGE 	Msg;
    u8          KeyID;
    
    KeyID=Id-ID_BUTTON;
	if (buttondata[Id - ID_BUTTON].acLabel) 
	{
		c = buttondata[Id - ID_BUTTON].acLabel[0];

        if(KeyID == 19)                             //����Ӣ�ļ���
        {
            keypad_dev.padtype=ENGLISH_KEYPAD;		//Ӣ�ļ���
			Msg.MsgId=CHANGE_NUMPADTO_ENGLISHPAD;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg); 
        }
        else
        {
            GUI_StoreKeyMsg(c, 1);				//����Ϣ������̻�����������״̬
			GUI_StoreKeyMsg(c, 0);				//����Ϣ������̻��������ɿ�״̬ 
        }
	}
}
//���ż��̴�����
//buttondata:���ּ��̰�ť����
//Id:��ťID
//*pMsg:ָ����Ϣ
void signkeypad_process(BUTTON_DATA *buttondata,int Id,WM_MESSAGE *pMsg)	
{
	char 		c;
	WM_MESSAGE 	Msg;
    u8          KeyID;
    
    KeyID=Id-ID_BUTTON;
	if (buttondata[Id - ID_BUTTON].acLabel) 
	{
		c = buttondata[Id - ID_BUTTON].acLabel[0];
        if(KeyID == 19)                             //���ص�Ӣ�ļ���
        {
            keypad_dev.padtype=ENGLISH_KEYPAD;		//Ӣ�ļ���
			Msg.MsgId=CHANGE_SIGNPADTO_ENGLISHPAD;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg);  
        }
        else if(KeyID == 14)                        //��һ�����ż���
        {
            if(keypad_dev.signpad_flag<(keypad_dev.signpad_num-1))	
			{
				keypad_dev.signpad_flag++;	        //���ż���������һ
				Msg.MsgId=CHANGE_SIGNPAD;
				Msg.hWinSrc=pMsg->hWin;
				WM_SendMessage(keypad_dev.hKeypad,&Msg);
			}
        } 
        else if(KeyID == 9)                         //��һ�����ż���
        {
            if(keypad_dev.signpad_flag>0)	
			{
				keypad_dev.signpad_flag--;          //���ż���������1
				Msg.MsgId=CHANGE_SIGNPAD;
				Msg.hWinSrc=pMsg->hWin;
				WM_SendMessage(keypad_dev.hKeypad,&Msg);
			}  
        }
        else
        {
            GUI_StoreKeyMsg(c, 1);				//����Ϣ������̻�����������״̬
			GUI_StoreKeyMsg(c, 0);				//����Ϣ������̻��������ɿ�״̬ 
        }
	}
}


//���Ĵ�����
//buttondata:���ּ��̰�ť����
//Id:��ťID
//*pMsg:ָ����Ϣ
void chinesekeypad_process(BUTTON_DATA *buttondata,int Id,WM_MESSAGE *pMsg)	
{
	char 		c;
	WM_MESSAGE 	Msg;
    u8          key;
    u8          KeyID;
    u8          TempID;
    u8          i=0;
    
    KeyID=Id-ID_BUTTON;
	if (buttondata[Id - ID_BUTTON].acLabel) 
	{
		c = buttondata[Id - ID_BUTTON].acLabel[0];	
        if(KeyID == 3)                             //ɾ����
        {
            keypad_dev.cur_index=1;                 //��ɾ�������ƴ����ʱ��ǿ��������Ϊ��һ��
            if(keypad_dev.inputlen)
            {
                keypad_dev.inputlen--; 
                keypad_dev.inputstr[keypad_dev.inputlen]='\0';  //��ӽ�����
            }
            else       //û���ַ�������
            {
                GUI_StoreKeyMsg(c, 1);				//����Ϣ������̻�����������״̬
                GUI_StoreKeyMsg(c, 0);				//����Ϣ������̻��������ɿ�״̬
            }
        }else if(KeyID == 11)                       //Ӣ�ļ���
        {
            keypad_dev.padtype=ENGLISH_KEYPAD;		//Ӣ�ļ���
			Msg.MsgId=CHANGE_CHINESEPADTO_ENGLISHPAD;
			Msg.hWinSrc=pMsg->hWin;
			WM_SendMessage(keypad_dev.hKeypad,&Msg);   
        }else if(KeyID == 20)                        //ƴ����һҳ
        {
            if(keypad_dev.pypagenum>0)              
            {
                if(keypad_dev.pynowpage>0)keypad_dev.pynowpage--;
                else keypad_dev.pynowpage=0;
            }  
        }else  if(KeyID == 24)                      //ƴ����һҳ
        {
            if(keypad_dev.pypagenum>0)
            {
                if(keypad_dev.pynowpage<(keypad_dev.pypagenum-1)) keypad_dev.pynowpage++;
                else keypad_dev.pynowpage=keypad_dev.pypagenum-1;
            }
        }else if(KeyID == 12)                        //������һҳ         
        {
            if(keypad_dev.dispagenum>0)
            {
                if(keypad_dev.dispagecur>0) keypad_dev.dispagecur--;
                else keypad_dev.dispagecur=0;
            }
        }else if(KeyID == 19)                       //������һҳ
        {
            if(keypad_dev.dispagenum>0)
            {
                if(keypad_dev.dispagecur<(keypad_dev.dispagenum-1)) keypad_dev.dispagecur++;
                else keypad_dev.dispagecur=keypad_dev.dispagenum-1;
            }
        }else if((KeyID > 12) && (KeyID < 19))      //����
        {
            TempID=KeyID-12;
            TempID=TempID+6*keypad_dev.dispagecur;  //�õ���ǰ�ĺ�������
            if(TempID<=keypad_dev.hznum)
            {
                keypad_dev.cur_hz=keypad_dev.butname[(KeyID-12)-1]; //���ѡ�еĺ���
                if(keypad_dev.cur_hz != NULL)
                {
                    MULTIEDIT_AddText(hMulti,(const char*)keypad_dev.cur_hz);        //�ڶ����ı�����ʾѡ�еĺ���
                }
                keypad_dev.result_num=0;
                keypad_dev.dispagecur=0;
                keypad_dev.dispagenum=0;
                keypad_dev.cur_index=0;
                keypad_dev.pynowpage=0;
                keypad_dev.pypagenum=0;
                keypad_dev.inputlen=0;
                for(i=0;i<7;i++)    keypad_dev.inputstr[i]=0;  //��������
            }
            
        }else if((KeyID > 20) && (KeyID <24))       //����
        {
            TempID=KeyID-20;                        
            TempID=TempID+3*keypad_dev.pynowpage; //�õ���ǰ��ƴ������
            if(TempID<=keypad_dev.result_num)
            {
                keypad_dev.cur_index=TempID;
                keypad_dev.dispagecur=0;
                keypad_dev.dispagenum=0;
            }
        }
        else
        {
            if((c == ';')||(c == ' '))
            {
                GUI_StoreKeyMsg(c, 1);				    //����Ϣ������̻�����������״̬
                GUI_StoreKeyMsg(c, 0);				    //����Ϣ������̻��������ɿ�״̬
            }else
            {
                keypad_dev.inputstr[keypad_dev.inputlen]=c+'\0';   //�����ַ�
                if(keypad_dev.inputlen<6)keypad_dev.inputlen++;
            }
            
        }
        if((keypad_dev.inputstr[0])!=NULL)            
        {
            key=t9.getpymb(keypad_dev.inputstr);        //�õ�ƥ��Ľ����  
            if(key)                                     //�в���ƥ��/��ȫƥ��Ľ��
            {
                keypad_dev.result_num=key&0X7F;         //��ƥ����
                if((keypad_dev.sta&0X80)==0)
                {
                    keypad_dev.sta|=0X80;
                    keypad_dev.cur_index=1;             //Ĭ�ϵ�һ������
                }
                if(key&0x80)                            //����ƥ��
                {
                    keypad_dev.inputlen = key&0x7f;     //��Чƥ��λ��
                    keypad_dev.inputstr[keypad_dev.inputlen]='\0';  //��ƥ���λ��ȥ��
                    if(keypad_dev.inputlen>1)keypad_dev.result_num=t9.getpymb(keypad_dev.inputstr);//���»�ȡ��ȫƥ���ַ���
                }
            }else
            {
                keypad_dev.inputlen--;
                keypad_dev.inputstr[keypad_dev.inputlen]='\0';
            }
        }else
        {
            keypad_dev.sta&=0x7f;           
            keypad_dev.cur_index=0;             //����
            keypad_dev.result_num=0;
            keypad_dev.dispagecur=0;
            keypad_dev.dispagenum=0;
            keypad_dev.pynowpage=0;
            keypad_dev.pypagenum=0;
        }
        if(keypad_dev.result_num&0x80) keypad_dev.result_num=1;
		Msg.MsgId=CHANGE_CHINESE_PY;
		Msg.hWinSrc=pMsg->hWin;
		WM_SendMessage(keypad_dev.hKeypad,&Msg);
	}
}


//����BUTTONҪʹ�õ�Ƥ��
static int _DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) 
{
	static GUI_MEMDEV_Handle ahMemEdges[4];
	GUI_MEMDEV_Handle        hMem;
	WM_HWIN                  hWin;
	unsigned                 i;
	int                      xPos;
	int                      yPos;
	int                      xSize;
	int                      ySize;
	int                      x;
	int                      y;
	int                      Id;
	int                      IsPressed;
    int                      butheigh;
	void (* pfDraw)(WM_HWIN hWin);

	x = 0;
	y = 0;
	switch (pDrawItemInfo->Cmd) 
	{
		case WIDGET_ITEM_CREATE:
			if (ahMemEdges[0] == 0) 
			{
				//����һ��С�İ������ڣ����ǲ��ɼ�
				hWin = WM_CreateWindowAsChild(0, 0, 16, 16, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP, NULL, 0);
				WM_SelectWindow(hWin);
				//Ϊbutton��ÿ����Ե�����洢�豸
				for (i = 0; i < GUI_COUNTOF(ahMemEdges); i++) 
				{
					switch (i) 
					{
						case 0:
							x = 0;
							y = 0;
							break;
						case 1:
							x = -16;
							y = 0;
							break;
						case 2:
							x = -16;
							y = -16;
							break;
						case 3:
							x = 0;
							y = -16;
							break;
					}
					//�����Ŵ��豸
					hMem = GUI_MEMDEV_CreateFixed(0, 0, 16, 16, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUI_COLOR_CONV_8888);
					GUI_MEMDEV_Select(hMem);
					GUI_SetBkColor(GUI_TRANSPARENT);
					GUI_Clear();
					GUI_SetColor(COLOR_BORDER);
					GUI_DrawRoundedFrame(x, y, x + 31, y + 31, 16, 4);	//���ƻ�����İ�ť�Ľǵ�Բ��

					//������ָ���Ĵ�С
					ahMemEdges[i] = GUI_MEMDEV_CreateFixed(0, 0, 4, 4, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUI_COLOR_CONV_8888);
					GUI_MEMDEV_Select(ahMemEdges[i]);
					GUI_SetBkColor(GUI_TRANSPARENT);
					GUI_Clear();
					GUI_MEMDEV_RotateHQ(hMem, ahMemEdges[i], -6, -6, 0, 250);
					GUI_MEMDEV_Delete(hMem);
					GUI_MEMDEV_Select(0);
				}
				WM_DeleteWindow(hWin);
			}
			break;
		case WIDGET_ITEM_DRAW_TEXT:
			//�ڰ�ť����ʾ�Զ������Ĭ�ϵ���ɫ�����ı�
			hWin = pDrawItemInfo->hWin;
			Id   = WM_GetId(hWin);
			i    = Id - ID_BUTTON;
			if(keypad_dev.padtype==ENGLISH_KEYPAD) pfDraw = _aEngButtonData[i].pfDraw;
			else if(keypad_dev.padtype==NUMBER_KEYPAD) pfDraw = _aNumButtonData[i].pfDraw;
			else if(keypad_dev.padtype==SIGN_KEYPAD) pfDraw = _aSinButtonData[keypad_dev.signpad_flag][i].pfDraw;
            else if(keypad_dev.padtype==CHINESE_KEYPAD) pfDraw = _aChineseButtonData1[i].pfDraw;
		
			if (pfDraw) pfDraw(hWin);
			else BUTTON_DrawSkinFlex(pDrawItemInfo);
			break;
		case WIDGET_ITEM_DRAW_BACKGROUND:
			//���ư�ť�ı���
			IsPressed = BUTTON_IsPressed(pDrawItemInfo->hWin); 	//�ж��Ƿ�ť�Ƿ񱻰���
			xPos      = WM_GetWindowOrgX(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�X����ԭ��λ��
			yPos      = WM_GetWindowOrgY(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�Y����ԭ��λ��
			xSize     = WM_GetWindowSizeX(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�X��С
			ySize     = WM_GetWindowSizeY(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�Y��С
			if (IsPressed) 										//�����ť������
			{
				GUI_DrawGradientRoundedV(0, 0, xSize - 1, ySize - 1, 4, BUTTON_COLOR2, BUTTON_COLOR3);//���ƴ�ֱ��ɫ�ݶ�����Բ�Ǿ���
			} 
			else 
			{
				GUI_DrawGradientRoundedV(0, 0, xSize - 1, ySize - 1, 4, BUTTON_COLOR0, BUTTON_COLOR1);//���ƴ�ֱ��ɫ�ݶ�����Բ�Ǿ���
			}
			GUI_SetColor(COLOR_BORDER);
			//���ư�ť�������߽�
			GUI_DrawHLine(        0, 4, xSize - 5);
			GUI_DrawHLine(ySize - 1, 4, xSize - 5);
			GUI_DrawVLine(        0, 4, ySize - 5);
			GUI_DrawVLine(xSize - 1, 4, ySize - 5);
			//�������洢�豸������д�뵱ǰѡ���洢�豸���ƶ�λ��	
            if(keypad_dev.padtype==CHINESE_KEYPAD) butheigh = 77;
            else butheigh = 68;
			GUI_MEMDEV_WriteAt(ahMemEdges[0], xPos +  0, yPos +  0);			    //��ť���Ͻ�Բ��
			GUI_MEMDEV_WriteAt(ahMemEdges[1], xPos + xSize - 4, yPos +  0);		    //��ť���Ͻ�Բ��
			GUI_MEMDEV_WriteAt(ahMemEdges[2], xPos + xSize - 4, yPos + butheigh);   //��ť���½�Բ��
			GUI_MEMDEV_WriteAt(ahMemEdges[3], xPos +  0, yPos + butheigh);			//��ť���½�Բ��
			break;
		default:
			return BUTTON_DrawSkinFlex(pDrawItemInfo);//���������ʹ��Ĭ�ϵ�Ƥ��
	}
	return 0;
}

//�������ļ���Ҫʹ�õ�Ƥ��
static int _DrawChineseSkin_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) 
{
	WM_HWIN                  hWin;
	unsigned                 i;
	int                      xSize;
	int                      ySize;
	int                      Id;
	int                      IsPressed;
	void (* pfDraw)(WM_HWIN hWin);

	switch (pDrawItemInfo->Cmd) 
	{
		case WIDGET_ITEM_DRAW_TEXT:
			//�ڰ�ť����ʾ�Զ������Ĭ�ϵ���ɫ�����ı�
			hWin = pDrawItemInfo->hWin;
			Id   = WM_GetId(hWin);
			i    = Id - ID_BUTTON; 
            pfDraw = _aChineseButtonData1[i].pfDraw;
		
			if (pfDraw) pfDraw(hWin);
			else BUTTON_DrawSkinFlex(pDrawItemInfo);
			break;
		case WIDGET_ITEM_DRAW_BACKGROUND:
			//���ư�ť�ı���
			IsPressed = BUTTON_IsPressed(pDrawItemInfo->hWin); 	//�ж��Ƿ�ť�Ƿ񱻰���
			xSize     = WM_GetWindowSizeX(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�X��С
			ySize     = WM_GetWindowSizeY(pDrawItemInfo->hWin);	//��ȡ��ťС���ߵ�Y��С
			if (IsPressed) 										//�����ť������
			{
                GUI_DrawGradientV(0,0,xSize-1,ySize-1,BUTTON_COLOR2,BUTTON_COLOR3);
			} 
			else 
			{
                GUI_DrawGradientV(0,0,xSize-1,ySize-1,GUI_WHITE,GUI_WHITE);
			}
			GUI_SetColor(COLOR_BORDER);
			//���ư�ť�������߽�
			GUI_DrawHLine(        0, 0, xSize - 1);
			GUI_DrawHLine(ySize - 1, 0, xSize - 1);
			GUI_DrawVLine(        0, 0, ySize - 1);
			GUI_DrawVLine(xSize - 1, 0, ySize - 1);   
			break;
		default:
			return BUTTON_DrawSkinFlex(pDrawItemInfo);//���������ʹ��Ĭ�ϵ�Ƥ��
	}
	return 0;
}

//���º����6����ť
void keypad_hbtn_updc(u8* str)
{
    vu8 i=0;
    if((keypad_dev.dispagecur>=keypad_dev.dispagenum)&&keypad_dev.dispagenum)return;  //��ǰҳ���ڻ��ߴ�����ҳ��
    for(i=0;i<6;i++) keypad_dev.butname[i]=NULL;
    i=0;
    for(i=0;i<6;i++)
    {
        if((i+6*(keypad_dev.dispagecur))>(keypad_dev.hznum-1)) //������Ӧƴ���ĺ�������
        {
            keypad_dev.disbuf[i][0]=' ';
            keypad_dev.disbuf[i][1]=' ';
            keypad_dev.disbuf[i][2]='\0';
            keypad_dev.butname[i]=keypad_dev.disbuf[i];
        }else
        {
            keypad_dev.disbuf[i][0]=*str++;
            keypad_dev.disbuf[i][1]=*str++;
            keypad_dev.disbuf[i][2]='\0';
            keypad_dev.butname[i]=keypad_dev.disbuf[i];
        }
    }
}

//���ƺ����6����ť
void keypad_draw_hbtn(WM_HWIN *handle)
{
    u8 i;
    for(i=0;i<6;i++)
    {
        BUTTON_SetFont(handle[13+i],&GUI_FontHZ24);
        BUTTON_SetText(handle[13+i],(char*)keypad_dev.butname[i]);
    }

}
//keypad���ڵ��õĻص�����
static void _cbKeyPad(WM_MESSAGE * pMsg) 
{
	WM_HWIN    hWin;
	int        Id;
	int        NCode;
	int        xSize;
	int        ySize;
    u16        slen;
	unsigned   i;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:				//����Ϣ�ڴ��ڴ������������ͣ��Ǵ��ڿ��Գ�ʼ���������κ��Ӵ���
			drawenglish_pad(hWin);	//����Ӣ�ļ���
			break;
		case WM_PAINT:
			//���Ʊ���
			xSize = WM_GetWindowSizeX(hWin);
			ySize = WM_GetWindowSizeY(hWin);
			GUI_SetColor(COLOR_BORDER);
			GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
			GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
			break;
		case WM_NOTIFY_PARENT:	//���߸����ڣ��Ӵ��ڷ����˸ı�
			//�뵱ǰ���㴰�ڷ��Ͱ�����Ϣ
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch (NCode) 
			{
				case WM_NOTIFICATION_RELEASED:				//��ť���ͷ�
					if(keypad_dev.padtype==ENGLISH_KEYPAD)	//Ӣ�ļ���
					{
						engkeypad_process(_aEngButtonData,Id,pMsg);		//����Ӣ�ļ���
					}
					else if(keypad_dev.padtype==NUMBER_KEYPAD)			//���ּ���
					{
						numkeypad_process(_aNumButtonData,Id,pMsg);		//�������ּ���
					}
					else if(keypad_dev.padtype==SIGN_KEYPAD)			
					{
						signkeypad_process(_aSinButtonData[keypad_dev.signpad_flag],Id,pMsg);
					}
                    else if(keypad_dev.padtype==CHINESE_KEYPAD) 
                    {
                        chinesekeypad_process(_aChineseButtonData1,Id,pMsg);
                    }
					break;
			}
			break;	
		case CHANGE_ENGLISHPADTO_NUMPAD:			//��Ӣ�ļ����л������ּ���
			for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) WM_DeleteWindow(keypad_dev.EngButton_Handle[i]);	
            for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) keypad_dev.EngButton_Handle[i]=0;
			drawnumber_pad(hWin);
			break;
		case CHANGE_NUMPADTO_ENGLISHPAD:			//�����ּ����л���Ӣ�ļ���
			for(i=0;i<GUI_COUNTOF(_aNumButtonData);i++) WM_DeleteWindow(keypad_dev.NumButton_Handle[i]);	
            for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) keypad_dev.NumButton_Handle[i]=0;
			drawenglish_pad(hWin);					
			break;
		case CHANGE_ENGLISHPADTO_SIGNPAD1:			//��Ӣ�ļ����л������ż���
			for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) WM_DeleteWindow(keypad_dev.EngButton_Handle[i]);
            for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) keypad_dev.SignButton_Handle[i]=0;
		    drawsign_pad(hWin);
			break;
		case CHANGE_SIGNPADTO_ENGLISHPAD:			//�ӷ��ż����л���Ӣ�ļ���
			for(i=0;i<GUI_COUNTOF(_aSinButtonData[keypad_dev.signpad_flag]);i++) WM_DeleteWindow(keypad_dev.SignButton_Handle[i]);
            for(i=0;i<GUI_COUNTOF(_aSinButtonData[keypad_dev.signpad_flag]);i++) keypad_dev.SignButton_Handle[i]=0;
			drawenglish_pad(hWin);
			break;
		case CHANGE_SIGNPAD:						//�л����ż���
			for(i=0;i<GUI_COUNTOF(_aSinButtonData[keypad_dev.signpad_flag]);i++) WM_DeleteWindow(keypad_dev.SignButton_Handle[i]);
            for(i=0;i<GUI_COUNTOF(_aSinButtonData[keypad_dev.signpad_flag]);i++) keypad_dev.SignButton_Handle[i]=0;
		    drawsign_pad(hWin);
			break;
        case CHANGE_ENGLISHPADTO_CHINESEPAD:        //��Ӣ�ļ����л������ļ���
            for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) WM_DeleteWindow(keypad_dev.EngButton_Handle[i]);
            for(i=0;i<GUI_COUNTOF(_aEngButtonData);i++) keypad_dev.EngButton_Handle[i]=0;
            drawchinese1_pad(hWin);
            drawchinese2_pad(hWin);
            break;
        case CHANGE_CHINESEPADTO_ENGLISHPAD:        //�����ļ����л���Ӣ�ļ���
            for(i=0;i<25;i++) WM_DeleteWindow(keypad_dev.ChineseButton_Handle[i]);
            for(i=0;i<25;i++) keypad_dev.ChineseButton_Handle[i]=0;
            memset(keypad_dev.inputstr,0,7);    //����
            keypad_dev.cur_index=0;
            keypad_dev.inputlen=0;
            keypad_dev.result_num=0;
            keypad_dev.pypagenum=0;
            keypad_dev.pynowpage=0;
            keypad_dev.dispagecur=0;
            keypad_dev.dispagenum=0;
            keypad_dev.sta=0;
            drawenglish_pad(hWin);
            break;
        case CHANGE_CHINESE_PY:                                                             //��ʾ�Ź��������ƴ��ѡ��
            if(keypad_dev.cur_index>0)                                                      //keypad_dev.curindex>0˵����ƴ��ѡ��
            {
                keypad_dev.disstr=t9.pymb[keypad_dev.cur_index-1]->pymb;                    //��õ�ǰ���
                slen=strlen((const char*)keypad_dev.disstr);                                //�õ���ǰѡ�е�ƴ����Ӧ�ĺ����ַ����ĳ���
                keypad_dev.hznum=slen/2;                                                    //��Ϊ�����ģ�ÿ������Ϊ2���ַ��� 
            }else                                                                           //û��ƴ��ѡ��
            {
                keypad_dev.disstr=NULL;
                slen=0;
                keypad_dev.hznum=0;     
            }
            keypad_dev.dispagenum=keypad_dev.hznum/6+(keypad_dev.hznum%6?1:0);              //�õ������ַ�������ҳ��
            keypad_dev.pypagenum=keypad_dev.result_num/3+(keypad_dev.result_num%3?1:0);     //�õ�ƴ��ҳ��
            if(keypad_dev.inputstr[0]!=NULL)
            {
                for(i=0;i<3;i++)
                {   
                    BUTTON_SetFont(keypad_dev.ChineseButton_Handle[21+i],&GUI_FontHZ24);
                    if((i+3*(keypad_dev.pynowpage))>(keypad_dev.result_num-1)) 
                    {
                        BUTTON_SetText(keypad_dev.ChineseButton_Handle[21+i]," ");
                    }else
                    {
                        BUTTON_SetText(keypad_dev.ChineseButton_Handle[21+i],(const char*)t9.pymb[i+3*(keypad_dev.pynowpage)]->py);
                    }
                }
                
                keypad_hbtn_updc(keypad_dev.disstr+(keypad_dev.dispagecur*6*2));        //���º���ť����
                keypad_draw_hbtn(keypad_dev.ChineseButton_Handle);                      //���ƺ���ť

            }else                                                                       //û�������κ�ƴ��
            {
                for(i=0;i<3;i++)
                {   
                    BUTTON_SetFont(keypad_dev.ChineseButton_Handle[21+i],&GUI_FontHZ24);
                    BUTTON_SetText(keypad_dev.ChineseButton_Handle[21+i]," ");
                }  
                
                for(i=0;i<6;i++)
                {
                    keypad_dev.disbuf[i][0]=' ';
                    keypad_dev.disbuf[i][1]=' ';
                    keypad_dev.disbuf[i][2]='\0';
                    keypad_dev.butname[i]=keypad_dev.disbuf[i]; 
                }
                keypad_draw_hbtn(keypad_dev.ChineseButton_Handle);                  //���ƺ���ť
            }
            break;
			
				
			
			
	}
}


//�������ڻص�����
static void _cbBk(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_DrawGradientV(0, 0,lcddev.width,lcddev.height, COLOR_BACK0, COLOR_BACK1);
			break;
	}
}


//FRAMEWIN���ڻص�����
static void _cbFRAMEWIN(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
//		case WM_PAINT:
//			//GUI_DrawGradientV(0, 0,lcddev.width,lcddev.height, COLOR_BACK0, COLOR_BACK1);
//			break;
		
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
			{
				int id = WM_GetId(pMsg->hWinSrc);
				if(id == GUI_ID_CLOSE )
				{
					iconview_wifi_hItem = 0;
				}
			}
			break;
			
		
			
			
	}
	
	if (_pcbOldFrame) 
	{
		(*_pcbOldFrame)(pMsg);
	}
}


/*******************************************************************
*
*       _cbChild
*/
static void _cbChild(WM_MESSAGE * pMsg) {
//  WM_HWIN hWin = (FRAMEWIN_Handle)(pMsg->hWin);
  switch (pMsg->MsgId) {
//  case WM_PAINT:
//    //
//    // Handle the paint message
//    //
//    GUI_SetBkColor(GUI_WHITE);
//    GUI_SetColor(GUI_BLACK);
//    GUI_SetFont(&GUI_FontComic24B_ASCII);
//    GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
//    GUI_Clear();
//    GUI_DispStringHCenterAt("Client window", 
//                            WM_GetWindowSizeX(hWin) / 2, 
//                            WM_GetWindowSizeY(hWin) / 2);
//    break;
  
	case WM_TOUCH:
		{
			const GUI_PID_STATE * pState;
			pState = (const GUI_PID_STATE *)pMsg->Data.p;
			if(pState)
			{ 
				if(pState->Pressed)	
				{  
					WM_SetCaptureMove(hMulti, pState, 0, 0);
				}
			}
		}
	  break;  
  
  
  
  default:
    WM_DefaultProc(pMsg);
  }
}









WM_HWIN keypad_demo(void) 
{
//	WM_HWIN hFrame;
	WM_HWIN myFrame;
//	WM_HWIN Frame_text;	
	WM_HWIN hChild;
	
	//WM_SetCallback(WM_HBKWIN, _cbBk);		        //��ָ�������ڻص�����
	
	keypad_dev.xpos=0;
	keypad_dev.ypos=(lcddev.height*5)/10;
	keypad_dev.width=lcddev.width;
	keypad_dev.height=lcddev.height-((lcddev.height*5)/10);
	keypad_dev.padtype=ENGLISH_KEYPAD;				//Ĭ��ΪӢ�ļ���
	keypad_dev.signpad_flag=0;	
	keypad_dev.signpad_num=2;
    keypad_dev.inputlen=0;
    keypad_dev.pynowpage=0;
    keypad_dev.cur_index=0;
    keypad_dev.sta=0;
	
	//����keypad��ʹ�õİ�ť��Ƥ��
//	BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); 	//����BUTTON��Ƥ��
	
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);	
	
	
	myFrame = FRAMEWIN_CreateEx(0,30,
								240,180, 
								WM_HBKWIN, 
								WM_CF_SHOW |WM_CF_STAYONTOP,
								FRAMEWIN_CF_MOVEABLE,
								ID_FRAMEWIN_1,
								"soft keyboard",
								0
								);	
	
	_pcbOldFrame = WM_SetCallback(myFrame, _cbFRAMEWIN);	
	
	hChild = WM_GetClientWindow(myFrame);
	WM_SetCallback(hChild, _cbChild);	
	
	
	
	
	//FRAMEWIN_SetBorderSize(myFrame,0);
	//FRAMEWIN_SetMoveable(myFrame,1);
	
	//FRAMEWIN_AddMaxButton()
	
	FRAMEWIN_SetTextColor(myFrame, GUI_BLUE);
	FRAMEWIN_SetFont(myFrame, &GUI_Font20_ASCII);
	FRAMEWIN_AddCloseButton(myFrame,FRAMEWIN_BUTTON_RIGHT,0);
	FRAMEWIN_AddMaxButton(myFrame, FRAMEWIN_BUTTON_RIGHT, 1);
	FRAMEWIN_AddMinButton(myFrame, FRAMEWIN_BUTTON_RIGHT, 2);
	FRAMEWIN_SetClientColor(myFrame, GUI_WHITE);	
	
	
	//����keypad��ʹ�õİ�ť��Ƥ��
	BUTTON_SetDefaultSkin(_DrawSkinFlex_BUTTON); 	//����BUTTON��Ƥ��	
	//����keypad
//	keypad_dev.hKeypad = WM_CreateWindowAsChild(keypad_dev.xpos,keypad_dev.ypos-20,keypad_dev.width-10,keypad_dev.height, WM_GetClientWindow(myFrame), WM_CF_SHOW , _cbKeyPad, 0);
	
	keypad_dev.hKeypad = WM_CreateWindowAsChild(0,0,240-FRAMEWIN_GetBorderSize(myFrame)*2,150, WM_GetClientWindow(myFrame), WM_CF_SHOW , _cbKeyPad, 0);

	
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	
	
	//����notepad����
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	FRAMEWIN_SetDefaultTextAlign(GUI_TA_HCENTER);

	//����FRAME����
	hFrame = FRAMEWIN_CreateEx(0, 220, 240, 60, WM_HBKWIN,WM_CF_SHOW |WM_CF_STAYONTOP, 0, 0, "ALIENTEK NOTEPAD", 0);
	FRAMEWIN_SetTextColor(hFrame, GUI_YELLOW);
	FRAMEWIN_SetFont(hFrame, &GUI_Font20_ASCII);
	FRAMEWIN_SetClientColor(hFrame, GUI_WHITE);
	
	FRAMEWIN_AddCloseButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 0);
	FRAMEWIN_AddMaxButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 1);
	FRAMEWIN_AddMinButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 2);
	
	
	//����һ��multi edit(�����ı�С����)С����
	hMulti = MULTIEDIT_CreateEx(0, 0, 0, 0, WM_GetClientWindow(hFrame), WM_CF_SHOW, 0, GUI_ID_MULTIEDIT0, 100, NULL);
	MULTIEDIT_EnableBlink(hMulti,500,1);			//�������,����500ms
    MULTIEDIT_SetInsertMode(hMulti,1);  //��������ģʽ
	MULTIEDIT_SetFont(hMulti, &GUI_FontHZ24);
	WM_SetFocus(hMulti);
	
//	WM_SetCapture(hMulti,1);

	
//	while(1)
//	{
//		GUI_Delay(100);
//	}


	return myFrame;

}


