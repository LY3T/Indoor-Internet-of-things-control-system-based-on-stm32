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

#include "Framewin_timesettingDLG.h"
#include "rtc.h" 
#include "usart.h"
#include "stdlib.h"

//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif


// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0        (GUI_ID_USER + 0x00)
#define ID_LISTWHEEL_0        (GUI_ID_USER + 0x01)
#define ID_LISTWHEEL_1        (GUI_ID_USER + 0x02)
#define ID_LISTWHEEL_2        (GUI_ID_USER + 0x03)
#define ID_LISTWHEEL_3        (GUI_ID_USER + 0x04)
#define ID_LISTWHEEL_4        (GUI_ID_USER + 0x05)
#define ID_LISTWHEEL_5        (GUI_ID_USER + 0x06)
#define ID_BUTTON_0        (GUI_ID_USER + 0x07)
#define ID_BUTTON_1        (GUI_ID_USER + 0x08)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

WM_HMEM Fwin_timeset;

char * apText[] = {
"Monday",
"Tuesday",
"Wednesday",
"Thursday",
"Friday",
"Saturday",
"Sunday",
NULL
};


const char * yyyy[] = {
"2020",
"2021",
"2022",
"2023",
"2024",
"2025",
"2026",
"2027",
"2028",
"2029",	
NULL
};

const char * MM[] = {
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",	
"11",
"12",
NULL
};

const char * dd[] = {
"1","2","3","4","5","6","7","8","9","10",\
"11","12","13","14","15","16","17","18","19","20",\
"21","22","23","24","25","26","27","28","29","30",\
"31",\
NULL
};


const char * HH[] = {
"0","1","2","3","4","5","6","7","8","9",\
"10","11","12","13","14","15","16","17","18","19",\
"20","21","22","23",\
NULL
};

const char * mm_ss[] = {
"0","1","2","3","4","5","6","7","8","9",\
"10","11","12","13","14","15","16","17","18","19",\
"20","21","22","23","24","25","26","27","28","29",\
"30","31","32","33","34","35","36","37","38","39",\
"40","41","42","43","44","45","46","47","48","49",\
"50","51","52","53","54","55","56","57","58","59",\
NULL
};


extern OS_Q DATA_Msg;			//定义一个消息队列，用于发送数据
extern OS_ERR err;


// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin_timesetting", ID_FRAMEWIN_0, 0, 20, 240, 180, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_yyyy", ID_LISTWHEEL_0, 35, 5, 64, 30, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_MM", ID_LISTWHEEL_1, 104, 5, 32, 30, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_dd", ID_LISTWHEEL_2, 145, 5, 32, 30, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_HH", ID_LISTWHEEL_3, 35, 40, 32, 30, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_mm", ID_LISTWHEEL_4, 90, 40, 32, 30, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel_ss", ID_LISTWHEEL_5, 145, 40, 32, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button_net_time", ID_BUTTON_0, 80, 80, 80, 32, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button_apply", ID_BUTTON_1, 80, 115, 80, 20, 0, 0x0, 0 },
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

//static void get_time(WM_MESSAGE * pMsg) 
//{
//	u16 year,month,date,hour,min,sec;
//	u8 i;
//	year = calendar.w_year;
//	month = calendar.w_date;
//	date = calendar.w_date;
//	hour = calendar.hour;
//	min = calendar.min;
//	sec = calendar.sec;
//	
//	//年
//	for(i = 0;i<10;i++)
//	{
//		//字符串转整型
//		if(year == atoi(MM[i]))
//		{
//			
//		}
//	}
//	
//}




// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void time_cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
	
  char i;

	u16 year,month,date,hour,min,sec;
	u8 yyyy_buf[4];
	u16 yyyy_MM_dd_HH_mm_ss[6]={2020,10,10,18,12,60};
	
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Button_net_time'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Internet time");
    //
    // Initialization of 'Button_apply'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "Apply");
    // USER START (Optionally insert additional code for further widget initialization)
  
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "Time");
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    FRAMEWIN_SetFont(hItem, GUI_FONT_16_1);
  
	FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);  

	//获取时间
	year = calendar.w_year;
	month = calendar.w_date;
	date = calendar.w_date;
	hour = calendar.hour;
	min = calendar.min;
	sec = calendar.sec;

	//年	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
	LISTWHEEL_SetText(hItem,yyyy);
	
	//修改时间
	for(i = 0;i<10;i++)
	{
		//字符串转整型
		if(year == atoi(yyyy[i]))
		{
			LISTWHEEL_SetPos(hItem,i);
			break;
		}
	}	
	
	
	//LISTWHEEL_GetItemText();
	
//	LISTWHEEL_SetPos(hItem,5);	
//	
//	printf("%d\r\n",LISTWHEEL_GetNumItems(hItem)); 
//	
//	printf("%d\r\n",LISTWHEEL_GetPos(hItem));
//	
//	LISTWHEEL_GetItemText(hItem,LISTWHEEL_GetPos(hItem),text_buf,10);
//	
//	printf("%s\r\n",text_buf);
//	
//	printf("%d\r\n",LISTWHEEL_GetSel(hItem));	
//	
//	printf("%d\r\n",LISTWHEEL_GetSnapPosition(hItem));
	
	//LISTWHEEL_SetSel(hItem,5);
	


//	for(i=0;i<10;i++)
//	{
//		LISTWHEEL_AddString(hItem,yyyy[i]);
//	}
	
//	//修改时间
//	for(i = 0;i<10;i++)
//	{
//		//字符串转整型
//		if(year == atoi(MM[i]))
//		{
//			
//		}
//	}	
	
	//月	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
//	for(i=0;i<12;i++)
//	{
//		LISTWHEEL_AddString(hItem,MM[i]);
//	}
	
	LISTWHEEL_SetText(hItem,MM);
	
	//修改时间
	LISTWHEEL_SetPos(hItem,month-1);
	
	
	
	
	//日
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
//	for(i=0;i<31;i++)
//	{		
//		LISTWHEEL_AddString(hItem,dd[i]);
//	}

	LISTWHEEL_SetText(hItem,dd);
	
		//修改时间
	LISTWHEEL_SetPos(hItem,date-1);
	
	
	//时
	hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_3);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
//	for(i=0;i<24;i++)
//	{		
//		LISTWHEEL_AddString(hItem,HH[i]);
//	}

	LISTWHEEL_SetText(hItem,HH);
	
	//修改时间
	LISTWHEEL_SetPos(hItem,hour);	
	
	
	//分
	hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_4);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
//	for(i=0;i<60;i++)
//	{		
//		LISTWHEEL_AddString(hItem,mm_ss[i]);
//	}

	LISTWHEEL_SetText(hItem,mm_ss);
	
		//修改时间
	LISTWHEEL_SetPos(hItem,min);	

	//秒
	hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_5);
	LISTWHEEL_SetFont(hItem,GUI_FONT_32_1);
	
//	for(i=0;i<60;i++)
//	{		
//		LISTWHEEL_AddString(hItem,mm_ss[i]);
//	}	

	LISTWHEEL_SetText(hItem,mm_ss);
	
		//修改时间
	LISTWHEEL_SetPos(hItem,sec);	
	
	
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTWHEEL_0: // Notifications sent by 'Listwheel_yyyy'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_1: // Notifications sent by 'Listwheel_MM'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_2: // Notifications sent by 'Listwheel_dd'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_3: // Notifications sent by 'Listwheel_HH'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_4: // Notifications sent by 'Listwheel_mm'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_5: // Notifications sent by 'Listwheel_ss'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button_net_time'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

	  
	  
	//	if(OS_ERR_NONE == err )
			OSQPost((OS_Q*		)&DATA_Msg,		
					(void*		)&"g",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);	  
	  
	  
	//	if(OS_ERR_NONE == err )
			OSQPost((OS_Q*		)&DATA_Msg,		
					(void*		)&"f",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
					
					
					

					
					


	  
	  
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button_apply'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
//		for(i=ID_LISTWHEEL_0;i<=ID_LISTWHEEL_5;i++)
//		{

//			
//			if(i==ID_LISTWHEEL_0)
//			{
//				hItem = WM_GetDialogItem(pMsg->hWin,i);
//				LISTWHEEL_GetItemText(hItem,LISTWHEEL_GetPos(hItem),text_buf,10);
//				printf("%s\r\n",text_buf);
//				yyyy_MM_dd_HH_mm_ss[i] = atoi(text_buf);
//				printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[i]);
//			}
//			else
//			{
//				hItem = WM_GetDialogItem(pMsg->hWin,i);
//				yyyy_MM_dd_HH_mm_ss[i] = LISTWHEEL_GetPos(hItem);
//				printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[i]);
//			}
//			
//			
//		}

		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_0);
		LISTWHEEL_GetItemText(hItem,LISTWHEEL_GetPos(hItem),yyyy_buf,10);
		printf("%s\r\n",yyyy_buf);
		yyyy_MM_dd_HH_mm_ss[0] = atoi(yyyy_buf);
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[0]);
		
		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_2);
		yyyy_MM_dd_HH_mm_ss[1] = LISTWHEEL_GetPos(hItem)+1;
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[1]);

		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_2);
		yyyy_MM_dd_HH_mm_ss[2] = LISTWHEEL_GetPos(hItem)+1;
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[2]);				

		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_3);
		yyyy_MM_dd_HH_mm_ss[3] = LISTWHEEL_GetPos(hItem);
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[3]);

		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_4);
		yyyy_MM_dd_HH_mm_ss[4] = LISTWHEEL_GetPos(hItem);
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[4]);

		hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTWHEEL_5);
		yyyy_MM_dd_HH_mm_ss[5] = LISTWHEEL_GetPos(hItem);
		printf("%d\r\n",yyyy_MM_dd_HH_mm_ss[5]);
				
		RTC_Set(yyyy_MM_dd_HH_mm_ss[0],yyyy_MM_dd_HH_mm_ss[1],yyyy_MM_dd_HH_mm_ss[2],yyyy_MM_dd_HH_mm_ss[3],yyyy_MM_dd_HH_mm_ss[4],yyyy_MM_dd_HH_mm_ss[5]);
	  
			
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
	
	  case WM_DELETE:
		  Fwin_timeset = 0;
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
*       CreateFramewin_timesetting
*/

WM_HWIN CreateFramewin_timesetting(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), time_cbDialog, WM_HBKWIN, 0, 0);
	
	//设置模态窗口
	WM_MakeModal(hWin);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
