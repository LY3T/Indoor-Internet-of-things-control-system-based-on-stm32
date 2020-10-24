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
#include "Framewin_wifisetingDLG.h"
#include "WindowSKBDLG.h"
#include "EmWinHZFont.h"
#include "usart.h"
#include "esp8266.h"

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
#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x00)
#define ID_TEXT_0  (GUI_ID_USER + 0x01)
#define ID_TEXT_1  (GUI_ID_USER + 0x02)
#define ID_EDIT_0  (GUI_ID_USER + 0x03)
#define ID_EDIT_1  (GUI_ID_USER + 0x04)
#define ID_TEXT_2  (GUI_ID_USER + 0x05)
#define ID_TEXT_3  (GUI_ID_USER + 0x06)
#define ID_BUTTON_0  (GUI_ID_USER + 0x07)

#define ID_DROPDOWN_0        (GUI_ID_USER + 0x08)
#define ID_BUTTON_1        (GUI_ID_USER + 0x09)



// USER START (Optionally insert additional defines)

#define AP_LIST_MAX_NUM 10

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
WM_HMEM Framewin_wifiseting;

char ssid_buff[20],pwd_buff[20];
char at_jap[40];
char flag_at_jap_ok = 1;



extern OS_SEM	SYNC_SEM;		//定义一个信号量，用于任务同步
extern OS_Q DATA_Msg;			//定义一个消息队列，用于发送数据
OS_ERR err;

//AP列表结构体
extern struct ap_list_parameters
{
	u8 ecn;		//char型
	u8 ssid[40];
	int rssi;	//带符号整型，默认均为负数
	u8 mac[20];
	u8 channel; //char型
};

extern struct ap_list_parameters ap_list_para[AP_LIST_MAX_NUM];

extern u8 ap_list_num;

//记录上一次AP列表的个数
extern u8 ap_list_num_last;


//extern struct ap_list_parameters ap_list_par;

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin_wifiseting", ID_FRAMEWIN_0, 0, 20, 240, 270, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text_WIFI_SSID", ID_TEXT_0, 40, 30, 40, 16, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text_WIFI_PWD", ID_TEXT_1, 40, 60, 40, 16, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit_WIFI_SSID", ID_EDIT_0, 90, 30, 80, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit_WIFI_PWD", ID_EDIT_1, 90, 60, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text_WIFI_STATE", ID_TEXT_2, 30, 110, 80, 16, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text_WIFI_STATE", ID_TEXT_3, 130, 110, 80, 16, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button_WIFI_OK", ID_BUTTON_0, 65, 170, 80, 20, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 40, 0, 140, 22, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "update", ID_BUTTON_1, 185, 0, 40, 22, 0, 0x0, 0 },  
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  u8 i = 0;
	//存放dropdown选中项的文本
	u8 dropdown_seltext_buffer[40];
	
	
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin_wifiseting'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "WIFI");
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    FRAMEWIN_SetFont(hItem, GUI_FONT_16_1);
  
	FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
    //
    // Initialization of 'Text_WIFI_SSID'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    TEXT_SetText(hItem, "SSID:");
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'Text_WIFI_PWD'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "PWD:");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Edit_WIFI_SSID'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "abc");
    EDIT_SetFont(hItem, GUI_FONT_16_1);
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
	EDIT_EnableBlink(hItem,500,1);
    //
    // Initialization of 'Edit_WIFI_PWD'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "38100221at");
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    EDIT_SetFont(hItem, GUI_FONT_16_1);
	EDIT_EnableBlink(hItem,500,1);
    //
    // Initialization of 'Text_WIFI_STATE'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    TEXT_SetText(hItem, "WIFI STATE:");
    //
    // Initialization of 'Text_WIFI_STATE'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "connect");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button_WIFI_OK'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "OK");
    // USER START (Optionally insert additional code for further widget initialization)
	
    //	
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    //DROPDOWN_SetFont(hItem, GUI_FONT_16_1);
    DROPDOWN_SetListHeight(hItem, 200);
	DROPDOWN_SetAutoScroll(hItem,1);
	DROPDOWN_SetFont(hItem,&GUI_FontHZ16);
    //	
    // Initialization of 'update'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "get");	
	
	
	
	
	//查询链接状态
	OSQPost((OS_Q*		)&DATA_Msg,		
			(void*		)&"a",
			(OS_MSG_SIZE)1,
			(OS_OPT		)OS_OPT_POST_FIFO,
			(OS_ERR*	)&err);
	//列出周围的AP
	if(OS_ERR_NONE == err )
		OSQPost((OS_Q*		)&DATA_Msg,		
				(void*		)&"b",
				(OS_MSG_SIZE)1,
				(OS_OPT		)OS_OPT_POST_FIFO,
				(OS_ERR*	)&err);
	
	
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'Edit_WIFI_SSID'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
		show_skb(pMsg);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit_WIFI_PWD'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button_WIFI_OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

//		ESP8266_Send_AT_Cmd(at_jap,"OK",0,15);
		
		if(flag_at_jap_ok)
		{
			flag_at_jap_ok = 0;
			hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
			EDIT_GetText(hItem,ssid_buff,sizeof(ssid_buff));
			hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
			EDIT_GetText(hItem,pwd_buff,sizeof(pwd_buff));
			printf("ssid:%s pwd:%s\r\n",ssid_buff,pwd_buff);
			sprintf(at_jap,"AT+CWJAP=\"%s\",\"%s\"", ssid_buff, pwd_buff);			
			//OSSemPost(&SYNC_SEM,OS_OPT_POST_1,&err);//发送信号量
			//发送消息
			OSQPost((OS_Q*		)&DATA_Msg,		
					(void*		)&flag_at_jap_ok,
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
					
		}
			
	  
	  
	    
		// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
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
	  hItem = WM_GetDialogItem(pMsg->hWin,ID_DROPDOWN_0);
	  DROPDOWN_GetItemText(hItem,DROPDOWN_GetSel(hItem),dropdown_seltext_buffer,sizeof(dropdown_seltext_buffer));
	  EDIT_SetText(WM_GetDialogItem(pMsg->hWin,ID_EDIT_0),dropdown_seltext_buffer);
	  
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'update'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		//列出周围的AP
	  

	  
		if(OS_ERR_NONE == err )
			OSQPost((OS_Q*		)&DATA_Msg,		
					(void*		)&"b",
					(OS_MSG_SIZE)1,
					(OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);        
		// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break; 


    case ID_TEXT_3: // Notifications sent by 'Text_WIFI_STATE'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)        
		// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
	  case WM_NOTIFICATION_USER + 1 :
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "connect");
		TEXT_SetFont(hItem, GUI_FONT_16_1);		  
		break;

	  case WM_NOTIFICATION_USER + 2 :
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "disconnect");
		TEXT_SetFont(hItem, GUI_FONT_16_1);		  
		break;

	  
	  
      // USER END
      }
      break; 
	  
	  



	  
	// USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
	
	
	  case WM_USER + 2:
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
	  
	  
//			ap_list_num_last = DROPDOWN_GetNumItems(hItem);
	  
//			for(i=0;i<ap_list_num_last;i++)
//			{
//				DROPDOWN_DeleteItem(hItem,i);
//			}
	  
//			if(ap_list_num_last!=0)
//			{
//				for(i=3;i>0;i--)
//				{
//					DROPDOWN_DeleteItem(hItem,i);
//				}				
//			}
			//ap_list_num_last = ap_list_num;
	  
	//  	  hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
	  
			ap_list_num_last = DROPDOWN_GetNumItems(hItem);
	  
			for(i=0;i<ap_list_num_last;i++)
			{
				DROPDOWN_DeleteItem(hItem,0); 
			}
	  
			
	  
		  for(i=0;i<ap_list_num;i++)
		  {
			DROPDOWN_AddString(hItem,ap_list_para[i].ssid);
	      }
//		  DROPDOWN_AddString(hItem,ap_list_para[0].ssid);
//		  DROPDOWN_AddString(hItem,ap_list_para[1].ssid);
//	      DROPDOWN_AddString(hItem,ap_list_para[2].ssid);
			
	  //DROPDOWN_AddString(hItem,"aa");
			
		  DROPDOWN_GetItemText(hItem,DROPDOWN_GetSel(hItem),dropdown_seltext_buffer,sizeof(dropdown_seltext_buffer));
		  
	  
		  hItem = WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
		  
		  EDIT_SetText(hItem,dropdown_seltext_buffer);
		  
		  
		  break;
	
	
	  case WM_DELETE:
		  //断开窗口与其父窗口的关联。窗口管理器将不会重绘分离的窗口。
		  WM_DetachWindow(win_skb);
		  Framewin_wifiseting = 0;
		  WM_HideWindow(win_skb);
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
*       CreateFramewin_wifiseting
*/

WM_HWIN CreateFramewin_wifiseting(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	//给定窗口将从父窗口分离，并附加到新的父窗口。新父窗口在窗口坐标中的新原点将与旧父窗口在窗口坐标中的旧原点相同。
	WM_AttachWindow(win_skb,hWin);
	
	//设置模态窗口
	WM_MakeModal(hWin);
	
  WM_SetFocus(hWin);


	
  return hWin;
}



// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/



