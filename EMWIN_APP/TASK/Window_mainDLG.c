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
#include "Window_mainDLG.h"
#include "Window_iconDLG.h"
#include "Framewin_skb_testDLG.h"
#include "Framewin_wifisetingDLG.h"
#include "bmpdisplay.h"

#include "EmWinHZFont.h"

#include "usart2.h"

#include "rtc.h" 

#include "Framewin_timesettingDLG.h"

#include "Framewin_wallpaper_settingDLG.h"

#include <stdbool.h>


//#include "keypad.h"

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
#define ID_WINDOW_0        		(GUI_ID_USER + 0x00)


#define ID_ICONVIEW_3        	(GUI_ID_USER + 0xB3)

#define ID_DROPDOWN_1        	(GUI_ID_USER + 0xB4)

#define ID_BUTTON_0        		(GUI_ID_USER + 0xB5)

#define ID_ICONVIEW_WIFI      	(GUI_ID_USER + 0xC2)
#define ID_TEXT_0      			(GUI_ID_USER + 0xC1)

#define ID_WM_TIMER_0 			(GUI_ID_USER + 0xD0)


#define ID_ICONVIEW_SW        	(GUI_ID_USER + 0x03)
#define ID_ICONVIEW_SW_MAIN     (GUI_ID_USER + 0x04)

#define ID_ICONVIEW_0       	(GUI_ID_USER + 0x02)



// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
extern GUI_CONST_STORAGE GUI_BITMAP bmapic25494_240X320;
//extern GUI_CONST_STORAGE GUI_BITMAP bmoff;
//extern GUI_CONST_STORAGE GUI_BITMAP bmon;

//extern GUI_CONST_STORAGE GUI_BITMAP bmshoudiantong_guan_32;
//extern GUI_CONST_STORAGE GUI_BITMAP bmshoudiantong_kai_32;
//extern GUI_CONST_STORAGE GUI_BITMAP bmsocket_1_32b;
//extern GUI_CONST_STORAGE GUI_BITMAP bmsocket_1_32r;
extern GUI_CONST_STORAGE GUI_BITMAP bmsocket_2_32b;
extern GUI_CONST_STORAGE GUI_BITMAP bmsocket_2_32r;

extern GUI_CONST_STORAGE GUI_BITMAP bmsw_all_32b;
extern GUI_CONST_STORAGE GUI_BITMAP bmsw_all_32r;

extern GUI_CONST_STORAGE GUI_BITMAP bmsw_all2_64b;
extern GUI_CONST_STORAGE GUI_BITMAP bmsw_all2_64r;

extern GUI_CONST_STORAGE GUI_BITMAP bmwifi42_20;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi42_20_off;


WM_HWIN iconview_hItem;
WM_HWIN iconview_wifi_hItem;
WM_HWIN dropdown;
WM_HWIN button;
WM_HWIN iconview_sw;
WM_HWIN iconview_sw_main;


u8 sel_device_id = 0;

u8 sel_dropdown_num = 0;

u8 sel_dropdown_buf[10];

u8 led_state[2]={0,0};

bool sw_flag = false;

bool sw_flag_g[4] = {false,false,false,false};

bool sw_main = false;


bool dropdown_item_flag[3] = {false,false,false};


//窗口定时器计数值
u16 win_timer_count = 0 ;

//子设备心跳包计数值
u16 hb_time_num = 0 ;



extern OS_Q AT_JDY_Msg;			//定义一个消息队列，用于发送数据
extern OS_Q DATA_Msg;			//定义一个消息队列，用于发送数据
extern OS_ERR err;

extern u8 weather[50];

extern u8 *weather_buff;


extern bool sys_init_finish_flag;


// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window_main", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
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
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog_main(WM_MESSAGE * pMsg) {

  int NCode;
  int Id;
  // USER START (Optionally insert additional variables)
  WM_HWIN hItem;
	WM_MESSAGE Message;	
	u8 i;
	
 u8 time_data[9];
	
	GUI_RECT Rect = {10+5,100+10+80+10+5,10+105+10+105-5,100+10+80+10+80-5};	
	
	
	
  // USER END

	
	
	
	
	
  switch (pMsg->MsgId) {
  // USER START (Optionally insert additional message handling)

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		

    case ID_ICONVIEW_0: // Notifications sent by 'Iconview_GuideButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        switch(ICONVIEW_GetSel(pMsg->hWinSrc))
        {
            case 0:
                break;
            case 1:
                break;
            case 5:
				
				Fwin_wallpaper_setting = CreateFramewin_wallpaper_setting();
				
			
                break;			
            default:
                break;
        }
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
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

		
		
		
    case ID_ICONVIEW_3: // Notifications sent by 'Iconview_GuideButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        switch(ICONVIEW_GetSel(pMsg->hWinSrc))
        {
            case 0:
                //GUI_Clear();
                //GUI_DrawBitmap(&bmapic25494_240X320,0,0);

                if(iconview_hItem==0)
                {

					WM_HideWin(dropdown);
					WM_HideWin(iconview_sw);
					WM_HideWin(iconview_sw_main);
                    iconview_hItem = CreateWindow_icon();
                    WM_InvalidateWindow(WM_HBKWIN);
                }



                break;
            case 1:
                //GUI_Clear();
                //GUI_DrawBitmap(&bmapic25494_240X320,0,0);
                //CreateWindow_icon();
                if(iconview_hItem!=0)
                {
                    WM_DeleteWindow(iconview_hItem);
					WM_ShowWin(dropdown);
					WM_ShowWin(iconview_sw);
					WM_ShowWin(iconview_sw_main);
                    WM_InvalidateWindow(WM_HBKWIN);
                //WM_InvalidateWindow(WM_HBKWIN);
                    iconview_hItem=0;
                }
                break;
            default:
                break;
        }
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
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
    // USER START (Optionally insert additional code for further Ids)
	  

    case ID_ICONVIEW_WIFI : // Notifications sent by 'Iconview_GuideButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        switch(ICONVIEW_GetSel(pMsg->hWinSrc))
        {
            case 0:
                //GUI_Clear();
                //GUI_DrawBitmap(&bmapic25494_240X320,0,0);

                if(Framewin_wifiseting==0)
                {
					Framewin_wifiseting = CreateFramewin_wifiseting();

//					WM_HideWin(dropdown);
//                    iconview_hItem = CreateWindow_icon();
//                    WM_InvalidateWindow(WM_HBKWIN);
					
//					iconview_wifi_hItem = keypad_demo();
					
					
					
                }



                break;
            case 1:
                //GUI_Clear();
                //GUI_DrawBitmap(&bmapic25494_240X320,0,0);
                //CreateWindow_icon();
//                if(iconview_wifi_hItem!=0)
//                {
//                    WM_DeleteWindow(iconview_hItem);
//					WM_ShowWin(dropdown);
//                    WM_InvalidateWindow(WM_HBKWIN);
//                //WM_InvalidateWindow(WM_HBKWIN);
//                    iconview_hItem=0;
//                }
                break;
            default:
                break;
        }
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
	  
      case WM_NOTIFICATION_USER + 1 :
        // USER START (Optionally insert code for reacting on notification message)
	  
		printf("win:wifi_on\r\n");
	  
		hItem = WM_GetDialogItem(pMsg->hWin,ID_ICONVIEW_WIFI);
		
		ICONVIEW_SetBitmapItem(hItem,0,&bmwifi42_20);
	  
        // USER END
        break;	  
	  

      case WM_NOTIFICATION_USER + 2 :
        // USER START (Optionally insert code for reacting on notification message)
	  
		printf("win:wifi_off\r\n");
	  
		hItem = WM_GetDialogItem(pMsg->hWin,ID_ICONVIEW_WIFI);
		
		ICONVIEW_SetBitmapItem(hItem,0,&bmwifi42_20_off);
	  
        // USER END
        break;

	  
	  
      // USER END
      }
      break;
	  
    case ID_DROPDOWN_1: // Notifications sent by 'Dropdown'
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
	  hItem = WM_GetDialogItem(pMsg->hWin,ID_DROPDOWN_1);
	  
	  sel_dropdown_num = DROPDOWN_GetSel(hItem);
	  
	  DROPDOWN_GetItemText(hItem,sel_dropdown_num,sel_dropdown_buf,10);
	  
	  
	  sel_device_id = atoi(sel_dropdown_buf) - 2;
	  
	  
	  //sel_device_id = DROPDOWN_GetSel(hItem);
	  
		Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_SW);
		Message.MsgId = WM_NOTIFY_PARENT;
		Message.Data.v = WM_NOTIFICATION_USER + 1;
		WM_SendMessage(pMsg->hWin, &Message);	  
	  
		//WM_InvalidateWindow(WM_HBKWIN);
	  
	  
	  //DROPDOWN_GetItemText(hItem,DROPDOWN_GetSel(hItem),dropdown_seltext_buffer,sizeof(dropdown_seltext_buffer));
	  //EDIT_SetText(WM_GetDialogItem(pMsg->hWin,ID_EDIT_0),dropdown_seltext_buffer);
	  
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;	  
	  
		//
    case ID_BUTTON_0: // Notifications sent by 'update'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		//if(led)
//		hItem = WM_GetDialogItem(pMsg->hWin,ID_BUTTON_0);
//		BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,led_state[sel_device_id]?&bmon:&bmoff,10+105+10+20,100+10+8);
//		if(led_state[sel_device_id])
//		{
//			if(sel_device_id)
//			{
//				printf("rev :ID1 led on\r\n");
//				
//				//jdy_send = 1;
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"E",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);					
//			}
//			else
//			{
//				printf("rev :ID0 led on\r\n");
//				
//				//jdy_send = 1;
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"C",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);					
//			}
//			
//		}
//		else
//		{
//			if(sel_device_id)
//			{
//				printf("rev :ID1 led off\r\n");
//				
//				//jdy_send = 1;
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"F",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);					
//			}
//			else
//			{
//				printf("rev :ID0 led off\r\n");
//				
//				//jdy_send = 1;
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"D",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);					
//			}			
//		}
	  
	  
		// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break; 	  









    case ID_TEXT_0: // Notifications sent by 'update'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
	  if(Fwin_timeset == 0)
	  {
		  Fwin_timeset = CreateFramewin_timesetting();
	  }
		
		// USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break; 	  


    case ID_ICONVIEW_SW: // Notifications sent by 'update'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
	  
		
		//总开关打开才能操作SW区
		if(sw_main)
		{
			switch(ICONVIEW_GetSel(pMsg->hWinSrc))
			{
				case 0:
					mesh_dev[sel_device_id].Read_write_value[0] = mesh_dev[sel_device_id].Read_write_value[0] == true ? false :true;
					
					
					if(mesh_dev[sel_device_id].Read_write_value[0])
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,0,&bmsocket_2_32b);

						switch(sel_device_id)
						{
							case 0:
								printf("0002 SW1 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"D",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;
							
							case 1:
								printf("0003 SW1 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"H",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
										
							case 2:
								printf("0004 SW1 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"L",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;										
							
							default:
								break;
						}

						
					}
					else
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,0,&bmsocket_2_32r);
						
						switch(sel_device_id)
						{
							case 0:
								printf("0002 SW1 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"C",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;
							
							case 1:
								printf("0003 SW1 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"G",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
							case 2:
								printf("0004 SW1 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"K",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
										
							default:
								break;
						}					
						
						
						
					}
					
					break;
					
				case 1:
					mesh_dev[sel_device_id].Read_write_value[1] = mesh_dev[sel_device_id].Read_write_value[1] == true ? false :true;
				
					if(mesh_dev[sel_device_id].Read_write_value[1])
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,1,&bmsocket_2_32b);
						
						switch(sel_device_id)
						{
							case 0:
								printf("0002 SW2 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"F",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;
							
							case 1:
								printf("0003 SW2 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"J",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
										
							case 2:
								printf("0004 SW2 ON\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"N",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;										
							
							default:
								break;
						}
						
						
					}
					else
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,1,&bmsocket_2_32r);
						
						switch(sel_device_id)
						{
							case 0:
								printf("0002 SW2 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"E",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;
							
							case 1:
								printf("0003 SW2 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"I",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
							case 2:
								printf("0004 SW2 OFF\r\n");
								OSQPost((OS_Q*		)&AT_JDY_Msg,		
										(void*		)&"M",
										(OS_MSG_SIZE)1,
										(OS_OPT		)OS_OPT_POST_FIFO,
										(OS_ERR*	)&err);								
								break;	
										
							default:
								break;
						}						
						
					}
					
					break;				
					
				case 2:
					mesh_dev[sel_device_id].Read_write_value[2] = mesh_dev[sel_device_id].Read_write_value[2] == true ? false :true;
				
					if(mesh_dev[sel_device_id].Read_write_value[2])
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,2,&bmsocket_2_32b);
					}
					else
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,2,&bmsocket_2_32r);
					}
					
					break;

				case 3:
					mesh_dev[sel_device_id].Read_write_value[3] = mesh_dev[sel_device_id].Read_write_value[3] == true ? false :true;
				
				
	//				//所有设备相同 
	//				mesh_dev[0].Read_write_value[3] = mesh_dev[sel_device_id].Read_write_value[3];
	//			
	//				mesh_dev[1].Read_write_value[3] = mesh_dev[sel_device_id].Read_write_value[3];
				
				
					if(mesh_dev[sel_device_id].Read_write_value[3])
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,3,&bmsocket_2_32b);
						
	//					printf("ALL LED ON\r\n");
	//					OSQPost((OS_Q*		)&AT_JDY_Msg,		
	//							(void*		)&"A",
	//							(OS_MSG_SIZE)1,
	//							(OS_OPT		)OS_OPT_POST_FIFO,
	//							(OS_ERR*	)&err);					
					}
					else
					{
						ICONVIEW_SetBitmapItem(pMsg->hWinSrc,3,&bmsocket_2_32r);
						
	//					printf("ALL LED OFF\r\n");
	//					OSQPost((OS_Q*		)&AT_JDY_Msg,		
	//							(void*		)&"B",
	//							(OS_MSG_SIZE)1,
	//							(OS_OPT		)OS_OPT_POST_FIFO,
	//							(OS_ERR*	)&err);						
					}
					
					break;				
					
				default:
					break;
			}	  
		}
	  
	  
	  
		// USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;


	  
	  
      // USER START (Optionally insert additional code for further notification handling)
	  
	  case WM_NOTIFICATION_USER + 1:
		for(i=0;i<4;i++) 
		{
			if(mesh_dev[sel_device_id].Read_write_value[i])
			{
				ICONVIEW_SetBitmapItem(pMsg->hWinSrc,i,&bmsocket_2_32b);
			}
			else
			{
				ICONVIEW_SetBitmapItem(pMsg->hWinSrc,i,&bmsocket_2_32r);
			}			
		}

		WM_InvalidateWindow(WM_HBKWIN);	
		

		
		break;
	  
	  
	  
      // USER END
      }
      break;


    case ID_ICONVIEW_SW_MAIN: // Notifications sent by 'Iconview_GuideButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        switch(ICONVIEW_GetSel(pMsg->hWinSrc))
        {
            case 0:
				
				//判断总开关
				sw_main = sw_main == true ? false : true;

				//总开关-开
				if(sw_main)
				{
					//改变图标
					ICONVIEW_SetBitmapItem(pMsg->hWinSrc,0,&bmsw_all2_64b);
//					//打开全部开关，可以去除
//					printf("ALL LED ON\r\n");
//					OSQPost((OS_Q*		)&AT_JDY_Msg,		
//							(void*		)&"A",
//							(OS_MSG_SIZE)1,
//							(OS_OPT		)OS_OPT_POST_FIFO,
//							(OS_ERR*	)&err);					
				}
				else
				{
					//改变图标
					ICONVIEW_SetBitmapItem(pMsg->hWinSrc,0,&bmsw_all2_64r);
					
					//所有设备的开关状态置零
					memset(mesh_dev[0].Read_write_value,0,sizeof(mesh_dev[0].Read_write_value));
					memset(mesh_dev[1].Read_write_value,0,sizeof(mesh_dev[1].Read_write_value));	
					memset(mesh_dev[2].Read_write_value,0,sizeof(mesh_dev[2].Read_write_value));	
					
					
					//发消息刷新SW区
					Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_SW);
					Message.MsgId = WM_NOTIFY_PARENT;
					Message.Data.v = WM_NOTIFICATION_USER + 1;
					WM_SendMessage(pMsg->hWin, &Message);	  
				  										
					//关闭全部开关，不可以去除
					printf("ALL SW OFF\r\n");
					OSQPost((OS_Q*		)&AT_JDY_Msg,		
							(void*		)&"A",
							(OS_MSG_SIZE)1,
							(OS_OPT		)OS_OPT_POST_FIFO,
							(OS_ERR*	)&err);						
				}			
                break;
            case 1:

                break;
            default:
                break;
        }
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
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
	  
	  
	  










	  
	  
	  
    // USER END
    }
    break;
	
	
	
	  case WM_TIMER:
		  WM_RestartTimer(pMsg->Data.v,1000); 
	  
			if(win_timer_count == 29)
			{
				win_timer_count = 0;
				
				//查询链接状态
				OSQPost((OS_Q*		)&DATA_Msg,		
						(void*		)&"a",
						(OS_MSG_SIZE)1,
						(OS_OPT		)OS_OPT_POST_LIFO,
						(OS_ERR*	)&err);
//				//查询子设备状态
//				printf("check subset\r\n");
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"O",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);
			}
			
			win_timer_count++;
			
//			if(hb_time_num == 19)
//			{
//				hb_time_num = 0;
//				
//				//查询子设备状态
//				printf("check subset\r\n");
//				OSQPost((OS_Q*		)&AT_JDY_Msg,		
//						(void*		)&"O",
//						(OS_MSG_SIZE)1,
//						(OS_OPT		)OS_OPT_POST_FIFO,
//						(OS_ERR*	)&err);
//	
//			}			
//			
//			hb_time_num++;
			

		Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_SW);
		Message.MsgId = WM_NOTIFY_PARENT;
		Message.Data.v = WM_NOTIFICATION_USER + 1;
		WM_SendMessage(pMsg->hWin, &Message);



			
		  //printf("%d\r\n",calendar.sec);
		//WM_SendMessageNoPara(pMsg->hWin,ID_TEXT_0);
	      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		  sprintf(time_data,"%2d:%2d:%2d",calendar.hour,calendar.min,calendar.sec);
	      TEXT_SetText(hItem,time_data);
		 
			
			WM_InvalidateWindow(WM_HBKWIN);
			
			
		  break;

    case WM_PAINT:

        //GUI_Clear();
        //GUI_DrawBitmap(&bmapic25494_240X320,0,0);
		bmpdisplay_demo();
        if(iconview_hItem==0)
        {
            GUI_EnableAlpha(1);
            GUI_SetColor((0xa0uL << 24) | GUI_WHITE);
			
			//绘制透明圆角框
			
			
            GUI_FillRoundedRect(10,50,10+105,50+50,8);
			
            GUI_FillRoundedRect(10+105+10,50,10+105+10+105,50+50,8);
			
			GUI_FillRoundedRect(10,100+10,10+105,100+10+80,8);
			
			GUI_FillRoundedRect(10+105+10,100+10,10+105+10+105,100+10+80,8);	
			
			
			

			GUI_FillRoundedRect(10,100+10+80+10,10+105+10+105,100+10+80+10+80,8);

			
			
			
            GUI_SetAlpha(0);

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetColor(GUI_BLUE);
//	GUI_SetFont(&GUI_FontHZ12);
//	GUI_DispStringAt("12号字体：广州星翼电子 ALIENTEK!",10,10);
//	GUI_SetFont(&GUI_FontHZ16);
//	GUI_DispStringAt("16号字体：广州星翼电子 ALIENTEK!",10,30);
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringAt("温度",20,55);	
	GUI_SetFont(&GUI_Font32_1);	
			
	//????		
	//GUI_DispDecSpace(JDY_RX_BUFF[0][6],2);
	//GUI_DispStringLen(JDY_RX_BUFF[sel_device_id]+6,2);
	
	GUI_DispDec(mesh_dev[sel_device_id].Read_only_value[0],2);
	
	
	
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringAt("湿度",10+105+10+10,55);
	GUI_SetFont(&GUI_Font32_1);
	//GUI_DispStringLen(JDY_RX_BUFF[sel_device_id]+10,2);
	
	GUI_DispDec(mesh_dev[sel_device_id].Read_only_value[1],2);
	
	
	//GUI_DispDec(mesh_dev[sel_device_id].STAT,1);
	GUI_SetFont(&GUI_FontHZ24);
	if(mesh_dev[sel_device_id].STAT)
	{
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringAt("在线",100,20);
	}
	else
	{
		GUI_SetColor(GUI_RED);
		GUI_DispStringAt("离线",100,20);
		GUI_SetColor(GUI_BLUE);
	}
		
	
	
	
	
		
	//GUI_DispStringAt("空气质量",15,110+5);
	
//	if(weather !=NULL)
//	{
//		//GUI_DispStringAt(weather,15,100+10+80+10+5);
//		GUI_DispStringInRectWrap(weather, &Rect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
//	}
//	else
//	{
//		
//		printf("weather null \r\n");
		//GUI_SetColor(GUI_RED);
		if(sys_init_finish_flag)
		{
			//GUI_DispStringInRectWrap("天气请求失败，请检查服务器是否开启并重试！", &Rect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
			//GUI_SetColor(GUI_RED);
			GUI_SetColor(GUI_BLUE);
			GUI_DispStringInRectWrap(weather, &Rect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);

		}
		else
		{
			GUI_SetColor(GUI_RED);
			GUI_DispStringInRectWrap("系统初始化，正在获取天气...", &Rect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
			GUI_SetColor(GUI_BLUE);
		}
		//GUI_SetColor(GUI_BLUE);
	//}
	
	
	
	
	//

	
	
	
	
	
        //GUI_EnableAlpha(0);//不关闭，CPU有影响
        }




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
*       CreateWindow_main
*/

WM_HWIN CreateWindow_main(void) {
	
	WM_HWIN hWin;
	
	WM_HTIMER  hTimer;
	
	hTimer = WM_CreateTimer(WM_HBKWIN,ID_WM_TIMER_0,1000,0);
	
	
	dropdown = DROPDOWN_CreateEx(10,20,80,60,WM_HBKWIN,WM_CF_SHOW,DROPDOWN_CF_AUTOSCROLLBAR,ID_DROPDOWN_1);
	
	//DROPDOWN_SetFont(dropdown,&GUI_FontHZ16);
	DROPDOWN_SetFont(dropdown,&GUI_Font20_1);
	
	DROPDOWN_AddString(dropdown,"0002");
	DROPDOWN_AddString(dropdown,"0003");
	DROPDOWN_AddString(dropdown,"0004");
	
//	DROPDOWN_SetItemDisabled(dropdown,0,0);
//	DROPDOWN_SetItemDisabled(dropdown,1,0);
//	DROPDOWN_SetItemDisabled(dropdown,2,0);

//	button = BUTTON_CreateEx(10+105+10+20,100+10+8,
//					64,64,
//					WM_HBKWIN,
//					WM_CF_SHOW|WM_CF_HASTRANS,
//					0,
//					ID_BUTTON_0
//	);

//	BUTTON_SetBitmap(button,BUTTON_BI_UNPRESSED,&bmshoudiantong_guan_32);


  iconview_sw = ICONVIEW_CreateEx(10+105+10+20,100+10+8,
                           64,64,
                           WM_HBKWIN,
                           WM_CF_SHOW|WM_CF_HASTRANS,
                           0,
                           ID_ICONVIEW_SW,
                           32,32
                           );

    ICONVIEW_SetIconAlign(iconview_sw, ICONVIEW_IA_HCENTER|ICONVIEW_IA_VCENTER);

    ICONVIEW_SetTextColor(iconview_sw, ICONVIEW_CI_UNSEL, GUI_BLUE);

    ICONVIEW_SetTextColor(iconview_sw, ICONVIEW_CI_SEL, GUI_GREEN);

    ICONVIEW_SetBkColor(iconview_sw, ICONVIEW_CI_SEL, GUI_WHITE | 0xF0000000);	
	
	
    ICONVIEW_SetFrame(iconview_sw, GUI_COORD_X, 0); //设置图标到IconView边框的间距

    ICONVIEW_SetFrame(iconview_sw, GUI_COORD_Y, 0);

    ICONVIEW_SetSpace(iconview_sw, GUI_COORD_X, 0);//设置图标和图标之间的间距

    ICONVIEW_SetSpace(iconview_sw, GUI_COORD_Y, 0);

    ICONVIEW_SetFont(iconview_sw, GUI_FONT_10_1);	
	
	
	
	
	//
    ICONVIEW_AddBitmapItem(iconview_sw, &bmsocket_2_32r, "");//添加图标项
	ICONVIEW_AddBitmapItem(iconview_sw, &bmsocket_2_32r, "");//添加图标项
	ICONVIEW_AddBitmapItem(iconview_sw, &bmsocket_2_32r, "");//添加图标项
	ICONVIEW_AddBitmapItem(iconview_sw, &bmsocket_2_32r, "");//添加图标项
	
	
	

  iconview_sw_main = ICONVIEW_CreateEx(10+5,100+10+5,
                           64,64,
                           WM_HBKWIN,
                           WM_CF_SHOW|WM_CF_HASTRANS,
                           0,
                           ID_ICONVIEW_SW_MAIN,
                           64,64
                           );

    ICONVIEW_SetIconAlign(iconview_sw_main, ICONVIEW_IA_HCENTER|ICONVIEW_IA_VCENTER);

    ICONVIEW_SetTextColor(iconview_sw_main, ICONVIEW_CI_UNSEL, GUI_BLUE);

    ICONVIEW_SetTextColor(iconview_sw_main, ICONVIEW_CI_SEL, GUI_GREEN);

    ICONVIEW_SetBkColor(iconview_sw_main, ICONVIEW_CI_SEL, GUI_WHITE | 0xF0000000);	
	
	
    ICONVIEW_SetFrame(iconview_sw_main, GUI_COORD_X, 0); //设置图标到IconView边框的间距

    ICONVIEW_SetFrame(iconview_sw_main, GUI_COORD_Y, 0);

    ICONVIEW_SetSpace(iconview_sw_main, GUI_COORD_X, 0);//设置图标和图标之间的间距

    ICONVIEW_SetSpace(iconview_sw_main, GUI_COORD_Y, 0);

    ICONVIEW_SetFont(iconview_sw_main, GUI_FONT_10_1);	
	
	//总开关图标
    ICONVIEW_AddBitmapItem(iconview_sw_main, &bmsw_all2_64r, "");//添加图标项

  //hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    WM_SetCallback(WM_HBKWIN,_cbDialog_main);

  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
