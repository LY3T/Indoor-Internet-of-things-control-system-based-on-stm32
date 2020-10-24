#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "sdio_sdcard.h"
#include "malloc.h"
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "fontupd.h"
#include "EmWinHZFont.h"

#include "includes.h"
#include "WM.h"
#include "DIALOG.h"

#include "bmpdisplay.h"
#include "Window_mainDLG.h"
#include "Window_StatusBarDLG.h"
#include "Window_GuideButtonDLG.h"
#include "Window_iconDLG.h"
#include "WindowSKBDLG.h"
#include "Framewin_skb_testDLG.h"
#include "Framewin_wifisetingDLG.h"
#include "Framewin_timesettingDLG.h"

#include "usart3.h"	
#include "dma.h"
#include "esp8266.h"

#include "usart2.h"	
#include "JDY_24M.h"

#include "rtc.h" 

#include "stdlib.h" 


//USER STRAT DATA 





//USER END DATA





//任务优先级
#define START_TASK_PRIO				3
//任务堆栈大小	
#define START_STK_SIZE 				1024
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//TOUCH任务
//设置任务优先级
#define TOUCH_TASK_PRIO				4
//任务堆栈大小
#define TOUCH_STK_SIZE				128
//任务控制块
OS_TCB TouchTaskTCB;
//任务堆栈
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch任务
void touch_task(void *p_arg);

//按键任务
//设置任务优先级
#define KEY_TASK_PRIO 				5
//任务堆栈大小
#define KEY_STK_SIZE				128
//任务控制块
OS_TCB KeyTaskTCB;
//任务堆栈
CPU_STK KEY_TASK_STK[KEY_STK_SIZE];
//led0任务
void key_task(void *p_arg);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO 				6
//任务堆栈大小
#define LED0_STK_SIZE				512
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0任务
void led0_task(void *p_arg);

//AT_JDY任务
//设置任务优先级
#define AT_JDY_TASK_PRIO 				7
//任务堆栈大小
#define AT_JDY_STK_SIZE				128
//任务控制块
OS_TCB AT_JDY_TaskTCB;
//任务堆栈
CPU_STK AT_JDY_TASK_STK[AT_JDY_STK_SIZE];
//led0任务
void AT_JDY_task(void *p_arg);

//任务优先级
#define FLAGSPROCESS_TASK_PRIO	8
//任务堆栈大小	
#define FLAGSPROCESS_STK_SIZE 	128
//任务控制块
OS_TCB Flagsprocess_TaskTCB;
//任务堆栈	
CPU_STK FLAGSPROCESS_TASK_STK[FLAGSPROCESS_STK_SIZE];
//任务函数
void flagsprocess_task(void *p_arg);

//字库更新任务
//设置任务优先级
#define FONTUPDATA_TASK_PRIO		9
//任务堆栈大小
#define FONTUPDATA_STK_SIZE			128
//任务控制块
OS_TCB FontupdataTaskTCB;
//任务堆栈
CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
//字库更新任务
void fontupdata_task(void *p_arg);

//EMWINDEMO任务
//设置任务优先级
#define EMWINDEMO_TASK_PRIO			10
//任务堆栈大小
#define EMWINDEMO_STK_SIZE			2048
//任务控制块
OS_TCB EmwindemoTaskTCB;
//任务堆栈
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task任务
void emwindemo_task(void *p_arg);

////////////////////////信号量//////////////////////////////
OS_SEM	SYNC_SEM;			//定义一个信号量，用于任务同步
////////////////////////消息队列//////////////////////////////
#define DATAMSG_Q_NUM	20	//发送数据的消息队列的数量
OS_Q DATA_Msg;				//定义一个消息队列，用于发送数据
////////////////////////消息队列//////////////////////////////
#define AT_JDY_MSG_Q_NUM	8	//发送数据的消息队列的数量
OS_Q AT_JDY_Msg;				//定义一个消息队列，用于发送数据
////////////////////////事件标志组//////////////////////////////
#define KEY0_FLAG		0x01
#define KEY1_FLAG		0x02
#define KEYFLAGS_VALUE	0X00						
OS_FLAG_GRP	EventFlags;		//定义一个事件标志组
////////////////////////软件定时器//////////////////////////////
OS_TMR tmr1;				//定时器1

//定时器1的回调函数
void tmr1_callback(void *p_tmr, void *p_arg);




//AP列表最大存储容量
#define AP_LIST_MAX_NUM 10

//USART3接收数据的备份
u8 USART3_RX_BUF_COPY[USART3_MAX_RECV_LEN];

//AP列表结构体
struct ap_list_parameters
{
	u8 ecn;		//char型
	u8 ssid[40];
	int rssi;	//带符号整型，默认均为负数
	u8 mac[20];
	u8 channel; //char型
};

//定义10个的aplist变量用于存储ap列表
struct ap_list_parameters ap_list_para[AP_LIST_MAX_NUM];
//记录当前AP列表的个数
u8 ap_list_num = 0;
//记录上一次AP列表的个数
u8 ap_list_num_last = 0;


u8 MQTT_SEND_UPDATE_BUFF[80];

//MESH测试数据帧
u8 mesh_data[]={0x41,0x54,0x2b,0x4d,0x45,0x53,0x48,0x00,0xff,0xff,0x55,0x66,0x77,0x88,0x0D,0x0A};	

//天气信息缓存
u8 *weather_buff = NULL;
u8 weather[50]={0};

//初始化结构体数组的方法
//1.
//extern struct dev_info Device[5]={
//	{0,0,0,{0,0,0,0,0,0,0,0,0,0},0,{false,false,false,false,false,false,false,false,false,false}},
//	{0,0,0,{0,0,0,0,0,0,0,0,0,0},0,{false,false,false,false,false,false,false,false,false,false}},
//	{0,0,0,{0,0,0,0,0,0,0,0,0,0},0,{false,false,false,false,false,false,false,false,false,false}},
//	{0,0,0,{0,0,0,0,0,0,0,0,0,0},0,{false,false,false,false,false,false,false,false,false,false}},
//	{0,0,0,{0,0,0,0,0,0,0,0,0,0},0,{false,false,false,false,false,false,false,false,false,false}}	
//};
//2.
//memset(Device,0,sizeof(struct dev_info)*5);
//3.如下
extern struct dev_info mesh_dev[5] = {0};
//系统初始化标志
bool sys_init_finish_flag = false;
//心跳包比较
u32 hb_num_tem[3]={0};


//窗口控件ID
#define ID_ICONVIEW_WIFI		(GUI_ID_USER + 0xC2)
#define ID_TEXT_3				(GUI_ID_USER + 0x06)


//处理获取的AP列表
void get_APlist(void)
{
	u8 *ap_list_temp=0;
	u8 *ap_list_end=0;
	u8 i=0;
	
	//	u8 ap_list_num = 0;
	
	//中间字符串，用于rssi字符串的临时变换 字符串->char
	//u8 rssi_tempstr[6];
	

	//清ap_list_para
	memset(ap_list_para,0,sizeof(struct ap_list_parameters)*AP_LIST_MAX_NUM);
	//清空USART3_RX_BUF_COPY
	memset(USART3_RX_BUF_COPY,0,sizeof(u8)*USART3_MAX_RECV_LEN);
	//备份列表
	strcpy(USART3_RX_BUF_COPY,(const char *)USART3_RX_BUF);
	//获取列表首地址
	ap_list_temp = USART3_RX_BUF_COPY;
	//分离
	while(*ap_list_temp != '\r' && i != AP_LIST_MAX_NUM)
	{
//		//检索 ODOA 回车换行 \r\n
//		ap_list_end = strstr(ap_list_temp,"\r\n");
		
//		//检索 OD 回车 \r
//		ap_list_end = strchr(ap_list_temp,'\r');
		
		//使用strcpy加结束符
		//strcpy(ap_list_end,"\0\0");
		
//		//直接加结束符
//		*ap_list_end = '\0';
		
		//打印验证
		//printf("%s\r\n",ap_list_temp);
		
		//这里可以二次处理，也可以不处理
		
		//这里直接将数据拆分保存到ap结构体//

		//截取ecn
		ap_list_temp = ap_list_temp+8;
		
		ap_list_para[i].ecn=(char)atoi(ap_list_temp);
		
		printf("%d\r\n",ap_list_para[i].ecn);
		
		//截取ssid
		ap_list_temp = ap_list_temp + 3;
		
		ap_list_end = strchr(ap_list_temp,'\"');
		
		*ap_list_end = '\0';
		
		sprintf(ap_list_para[i].ssid,ap_list_temp);
		
		*ap_list_end = '\"';
		
		printf("%s\r\n",ap_list_para[i].ssid);
		
		//截取rssi
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,',');
		
		*ap_list_end = '\0';
		
		//sprintf(rssi_tempstr,ap_list_temp);
		
		ap_list_para[i].rssi = atoi(ap_list_temp);
		
		*ap_list_end = ',';
		
		printf("%d\r\n",ap_list_para[i].rssi);
		
		//截取mac
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,'\"');
		
		*ap_list_end = '\0';

		sprintf(ap_list_para[i].mac,ap_list_temp);
		
		*ap_list_end = '\"';
		
		printf("%s\r\n",ap_list_para[i].mac);
		
		//截取channel
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,')');
		
		*ap_list_end = '\0';
		
		ap_list_para[i].channel = (char)atoi(ap_list_temp);
		
		*ap_list_end = ')';
		
		printf("%d\r\n",ap_list_para[i].channel);		
		
		//
		//printf("%s\r\n",ap_lit[i]);	

		//更新首地址，跳转到下一行aplist
		ap_list_temp = ap_list_end + 3;

		//总览
		printf("ecn:%d,ssid:%s,rssi:%d,mac:%s,channel:%d\r\n",ap_list_para[i].ecn,ap_list_para[i].ssid,ap_list_para[i].rssi,ap_list_para[i].mac,ap_list_para[i].channel);
		
		//记录AP个数
		i++;
		
		//------------------------------//
		
		
		
		
//		//保存到数组中
//		sprintf(ap_lit[i++],ap_list_temp);
//		//打印验证
//		//printf("%s\r\n",ap_lit[i++]);
//		//重复，更新首地址
//		ap_list_temp = ap_list_end + 2;
	}
	
	ap_list_num = i;
	
	//打印验证
	for(i=0;i<ap_list_num;i++)
		printf("ecn:%d,ssid:%s,rssi:%d,mac:%s,channel:%d\r\n",ap_list_para[i].ecn,ap_list_para[i].ssid,ap_list_para[i].rssi,ap_list_para[i].mac,ap_list_para[i].channel);

	//打印验证
	printf("%s\r\n",USART3_RX_BUF_COPY);
	
	
}







/***************************主函数******************************/

int main(void)
{	
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init();	    	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			    //LED端口初始化
	TFTLCD_Init();			//LCD初始化	
	KEY_Init();	 			//按键初始化
	BEEP_Init();			//初始化蜂鸣器
	RTC_Init();	  			//RTC初始化
	
	usart3_DMA_init(115200);
	printf("USART3_DMA_IDLE_WIFI\r\n");
	ESP8266_Init(115200);
	//delay_ms(1000);	
	
	usart2_DMA_init(115200);
	printf("USART2_DMA_IDLE_MESH\r\n");
	//delay_ms(1000);	
	
	JDY_AT_printf("AT+ROLE5\r\n");
	delay_ms(100);
	JDY_AT_printf("AT+NETID1122\r\n");
	delay_ms(100);
	JDY_AT_printf("AT+MADDR0001\r\n");
	delay_ms(100);
	JDY_AT_printf("AT+RESET\r\n");
	delay_ms(100);	
	
//	//发送测试帧
//	DMA_USART2_Tx_Data(mesh_data,14);
//	delay_ms(1000);
//	DMA_USART2_Tx_Data(mesh_data,14);
//	delay_ms(1000);		
	
		
	FSMC_SRAM_Init();		//初始化SRAM
	my_mem_init(SRAMIN); 	//初始化内部内存池
	my_mem_init(SRAMEX);  	//初始化外部内存池
	
	exfuns_init();			//为fatfs文件系统分配内存
	f_mount(fs[0],"0:",1);	//挂载SD卡
	f_mount(fs[1],"1:",1);	//挂载FLASH
	
	while(SD_Init())		//检测SD卡
	{
		LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
		delay_ms(200);
		LCD_Fill(30,90,200+30,70+16,WHITE);
		delay_ms(200);		    
	}
	
	while(font_init())		//初始化字库
	{
		LCD_ShowString(30,70,200,16,16,"Font Error!");
		update_font(30,90,16,"0:");	//如果字库不存在就更新字库
		delay_ms(2000);
		LCD_Clear(WHITE);	//清屏
		break;
	}
	TP_Init();				//触摸屏初始化
	
	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//开启CRC时钟
	
	
	//先启动所有窗口的存储设备 再STemWin初始化 STemWin文档要求
	WM_SetCreateFlags(WM_CF_MEMDEV); //启动所有窗口的存储设备
	GUI_Init();  			//STemWin初始化
	OS_CRITICAL_ENTER();	//进入临界区
	
	//创建一个信号量
	OSSemCreate ((OS_SEM*	)&SYNC_SEM,
                 (CPU_CHAR*	)"SYNC_SEM",
                 (OS_SEM_CTR)0,		
                 (OS_ERR*	)&err);	
	
	//创建消息队列DATA_Msg
	OSQCreate ((OS_Q*		)&DATA_Msg,	
                (CPU_CHAR*	)"DATA Msg",	
                (OS_MSG_QTY	)DATAMSG_Q_NUM,	
                (OS_ERR*	)&err);		
				
	//创建消息队列AT_JDY_Msg
	OSQCreate ((OS_Q*		)&AT_JDY_Msg,	
                (CPU_CHAR*	)"AT_JDY Msg",	
                (OS_MSG_QTY	)AT_JDY_MSG_Q_NUM ,	
                (OS_ERR*	)&err);						
				
	//创建一个事件标志组
	OSFlagCreate((OS_FLAG_GRP*)&EventFlags,		//指向事件标志组
                 (CPU_CHAR*	  )"Event Flags",	//名字
                 (OS_FLAGS	  )KEYFLAGS_VALUE,	//事件标志组初始值
                 (OS_ERR*  	  )&err);

	//创建一个软件定时器
	OSTmrCreate((OS_TMR*	)&tmr1, 
				(CPU_CHAR*	)"tmr1", 
				(OS_TICK 	)20, 
				(OS_TICK 	)100, 
				(OS_OPT		)OS_OPT_TMR_PERIODIC, 
				(OS_TMR_CALLBACK_PTR)tmr1_callback, 
				(void*   	)0, 
				(OS_ERR*	)&err);

	//STemWin Demo任务	
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,		
				 (CPU_CHAR*   )"Emwindemo task", 		
                 (OS_TASK_PTR )emwindemo_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,     
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//触摸屏任务
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);			 
	//LED0任务
	OSTaskCreate((OS_TCB*     )&Led0TaskTCB,		
				 (CPU_CHAR*   )"Led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK*    )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//AT_JDY任务
	OSTaskCreate((OS_TCB*     )&AT_JDY_TaskTCB,		
				 (CPU_CHAR*   )"AT_JDY task", 		
                 (OS_TASK_PTR )AT_JDY_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )AT_JDY_TASK_PRIO ,     
                 (CPU_STK*    )&AT_JDY_TASK_STK[0],	
                 (CPU_STK_SIZE)AT_JDY_STK_SIZE/10,	
                 (CPU_STK_SIZE)AT_JDY_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//创建MSGDIS任务
	OSTaskCreate((OS_TCB*     )&Flagsprocess_TaskTCB,		
				 (CPU_CHAR*   )"Flagsprocess task", 		
                 (OS_TASK_PTR )flagsprocess_task, 			
                 (void* 	  )0,					
                 (OS_PRIO	  )FLAGSPROCESS_TASK_PRIO,     
                 (CPU_STK* 	  )&FLAGSPROCESS_TASK_STK[0],	
                 (CPU_STK_SIZE)FLAGSPROCESS_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLAGSPROCESS_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void* 	  )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR* 	  )&err);	
	//字库更新任务
	OSTaskCreate((OS_TCB*     )&FontupdataTaskTCB,		
				 (CPU_CHAR*   )"Fontupdata task", 		
                 (OS_TASK_PTR )fontupdata_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )FONTUPDATA_TASK_PRIO,     
                 (CPU_STK*    )&FONTUPDATA_TASK_STK[0],	
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE/10,	
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//按键任务
	OSTaskCreate((OS_TCB*     )&KeyTaskTCB,		
				 (CPU_CHAR*   )"Key task", 		
                 (OS_TASK_PTR )key_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )KEY_TASK_PRIO,     
                 (CPU_STK*    )&KEY_TASK_STK[0],	
                 (CPU_STK_SIZE)KEY_STK_SIZE/10,	
                 (CPU_STK_SIZE)KEY_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);					 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//退出临界区
}

//EMWINDEMO任务
void emwindemo_task(void *p_arg)
{
	//更换皮肤
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	
	//创建存储设备
	//LoadBMP_UsingMEMDEV("0:/image/sea_and_cloud.bmp",0,0);
	
	//创建存储设备
	LoadBMP_UsingMEMDEV("0:/wallpaper/SQ_240X320.bmp",0,0);	
	
	
	//删除存储设备
	//GUI_MEMDEV_Delete(hBMP);
	CreateWindow_main();
	CreateWindow_StatusBar();
	CreateWindow_GuideButton();
	win_skb = CreateWindowSKB();
//	WM_AttachWindow(win_skb,frame_test);
	WM_HideWindow(win_skb);

	while(1)
	{
		GUI_Delay(10);
	}
}

//字库更新任务
//KEY_UP键长按2s更新字库
void fontupdata_task(void *pdata)
{
	OS_ERR err;
	while(1)
	{
		if(WK_UP == 1)				//KEY_UP键按下
		{
			OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_PERIODIC,&err);//延时2s
			if(WK_UP == 1)			//还是KEY_UP键
			{
				LCD_Clear(WHITE);
				OSSchedLock(&err);		//调度器上锁
				LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
				update_font(10,70,16,"0:");//更新字库
				LCD_Clear(WHITE);
				POINT_COLOR = RED;
				LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
				OSSchedUnlock(&err);	//调度器解锁
			}
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//延时10ms
	}
}

//按键处理任务
void key_task(void *pdata)
{
	u8 key;
	OS_ERR err;
	while(1)
	{		
		key = KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:
	
				OSSchedLock(&err);		//调度器上锁
				LED1 = 0;
				//create_bmppicture("0:/SCREENSHORT/屏幕截图0.bmp",0,0,800,480);
				LED1 = 1;
				OSSchedUnlock(&err);	//调度器解锁
				break;
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//延时10ms
	}
}

//TOUCH任务
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
}

//AT_JDY任务
void AT_JDY_task(void *p_arg)
{
	OS_ERR err;
	//消息队列
	OS_MSG_SIZE size;
	u8 *msg;
	
	while(1)
	{
		//使用消息队列接收任务消息
		msg = OSQPend((OS_Q*		  )&AT_JDY_Msg,
				(OS_TICK	  )0,
				(OS_OPT 	  )OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE* )&size,
				(CPU_TS*	  )0,
				(OS_ERR*	  )&err);
		switch(*msg)
		{
			case 'A':
				JDY_MESH_printf(0x00,0xffff,"ALL_OFF\r\n");
				break;
			case 'B':
				JDY_MESH_printf(0x00,0xffff,"ALL_ON\r\n");
				break;
			
			case 'C':
				JDY_MESH_printf(0x00,0x0002,"SW1:0\r\n");
				break;
			case 'D':
				JDY_MESH_printf(0x00,0x0002,"SW1:1\r\n");
				break;			
			case 'E':
				JDY_MESH_printf(0x00,0x0002,"SW2:0\r\n");
				break;
			case 'F':
				JDY_MESH_printf(0x00,0x0002,"SW2:1\r\n");
				break;
			
			case 'G':
				JDY_MESH_printf(0x00,0x0003,"SW1:0\r\n");
				break;
			case 'H':
				JDY_MESH_printf(0x00,0x0003,"SW1:1\r\n");
				break;			
			case 'I':
				JDY_MESH_printf(0x00,0x0003,"SW2:0\r\n");
				break;
			case 'J':
				JDY_MESH_printf(0x00,0x0003,"SW2:1\r\n");
				break;			
			
			case 'K':
				JDY_MESH_printf(0x00,0x0004,"SW1:0\r\n");
				break;
			case 'L':
				JDY_MESH_printf(0x00,0x0004,"SW1:1\r\n");
				break;			
			case 'M':
				JDY_MESH_printf(0x00,0x0004,"SW2:0\r\n");
				break;
			case 'N':
				JDY_MESH_printf(0x00,0x0004,"SW2:1\r\n");
			
			case 'O':
				
				hb_num_tem[0] = mesh_dev[0].HB_NUM;
				hb_num_tem[1] = mesh_dev[1].HB_NUM;
				hb_num_tem[2] = mesh_dev[2].HB_NUM;
			
				JDY_MESH_printf(0x00,0xffff,"H_Beat\r\n");	

				delay_ms(1500);
			
				if(mesh_dev[0].HB_NUM-hb_num_tem[0] > 0)
				{
					printf("0002 online\r\n");
					mesh_dev[0].STAT = true;
				}
				else
				{
					printf("0002 offline\r\n");
					mesh_dev[0].STAT = false;
				}
				
				if(mesh_dev[1].HB_NUM-hb_num_tem[1] > 0)
				{
					printf("0003 online\r\n");
					mesh_dev[1].STAT = true;
				}
				else
				{
					printf("0003 offline\r\n");
					mesh_dev[1].STAT = false;
				}	

				if(mesh_dev[2].HB_NUM-hb_num_tem[2] > 0)
				{
					printf("0004 online\r\n");
					mesh_dev[2].STAT = true;
				}
				else
				{
					printf("0004 offline\r\n");
					mesh_dev[2].STAT = false;
				}

				
				
			
			
				break;
		
		}
		
		
		LED1 = !LED1;
		
		LED_G = !LED_G;
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);//延时50ms
	}
}







//LED0任务
void led0_task(void *p_arg)
{
	OS_ERR err;
	
	WM_MESSAGE Message;
	
	OS_FLAGS flags_num;	
	
	//消息队列
	OS_MSG_SIZE size;
	u8 *msg;
	
	u8 at_timeout;
	u8 *temp = NULL;
	
	//2020-10-12-04-58-25 19个字符 预留一个终止符\0 19+1=20
	u8 net_time[20];
	
	u8 time_buff[4];
	
	u8 len;
	
	u8 len2;
	
	u8 rx_data_len;
	
	u8 rx_data_len_len;
	
	//分割字符
	const char s[2] = "-";
	const char s2[2] = ",";
	char *token;	
	
	u16 yyyy_MM_dd_HH_mm_ss[6]={2020,10,10,18,12,60};
	
	int i = 10;
	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区	
//	OS_CRITICAL_EXIT();	//退出临界区

	//ESP8266设置
	while(!ESP8266_Send_AT_Cmd("AT+CWMODE=1","OK","no change",3));
	while(!ESP8266_Send_AT_Cmd("AT+CWJAP=\"123\",\"38100221at\"","OK",0,15));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTUSERCFG=0,1,\"ESP_ATK\",\"yong\",\"123\",0,0,\"\"","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTCONN=0,\"47.106.68.4\",1883,0","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTSUB=0,\"ledctl\",1","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTSUB=0,\"master_server_sub\",1","OK",0,5));

	//向事件标志组EventFlags发送标志
	flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
						 (OS_FLAGS	  )KEY0_FLAG,
						 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
						 (OS_ERR*	  )&err);
	printf("事件标志组EventFlags的值:%d\r\n",flags_num);
	
//	//获取时间
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"f",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//	//获取天气
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"g",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//	//获取WiFi状态
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"a",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);				

		//系统初始化请求
		OSQPost((OS_Q*		)&DATA_Msg,		
				(void*		)&"h",
				(OS_MSG_SIZE)1,
				(OS_OPT		)OS_OPT_POST_FIFO,
				(OS_ERR*	)&err);	

//获取ntp时间	
/**************	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG?","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPMUX=1","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"1.cn.pool.ntp.org\",\"ntp.sjtu.edu.cn\"","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"cn.pool.ntp.org\",\"cn.ntp.org.cn\",\"ntp.aliyun.com\"","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"1.cn.pool.ntp.org\"","OK",0,10));
	
	//while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPTIME?","OK",0,10));
************/	
		
/*
strstr

char *strstr(const char *str1, const char *str2);
功能：判断字符串str2是否是str1的子串。

参数
str1 - 要查找的字符串或字符串指针
str2 - 要查找的子串

返回值
函数返回str2在str1中首次出现的地址；否则，返回NULL。
*/	
	delay_ms(1000);
	
	while(1)
	{	
//		//使用信号量进行任务同步
//		OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); //请求信号量
//		//flag_at_jap_ok = 0;
//		while(!ESP8266_Send_AT_Cmd(at_jap,"OK",0,15));
//		flag_at_jap_ok = 1;
		
		//使用消息队列接收任务消息
		msg = OSQPend((OS_Q*		  )&DATA_Msg,
				(OS_TICK	  )0,
				(OS_OPT 	  )OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE* )&size,
				(CPU_TS*	  )0,
				(OS_ERR*	  )&err);
		switch(*msg)
		{
			case 0:
				//响应超时后重连，重连超出相应次数后重启模块
				while(!ESP8266_Send_AT_Cmd(at_jap,"OK",0,15));
				flag_at_jap_ok = 1;	
				break;
			case 'a':
				while(!ESP8266_Send_AT_Cmd("AT+CIPSTATUS","OK",0,5));
				
				if(strstr(USART3_RX_BUF,"STATUS:2"))
				{
					printf("wifi_on\r\n");
					Message.MsgId = WM_NOTIFY_PARENT;
					Message.Data.v = WM_NOTIFICATION_USER + 1;
					Message.hWinSrc = WM_GetDialogItem(WM_HBKWIN, ID_ICONVIEW_WIFI);
					WM_SendMessage(WM_HBKWIN,&Message);
					
					//先判断设置页面是否被删除了
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}
						
					
				}
				else
				{
					printf("wifi_off\r\n");
					Message.MsgId = WM_NOTIFY_PARENT;
					Message.Data.v = WM_NOTIFICATION_USER + 2;
					Message.hWinSrc = WM_GetDialogItem(WM_HBKWIN, ID_ICONVIEW_WIFI);
					WM_SendMessage(WM_HBKWIN,&Message);

					//先判断设置页面是否被删除了
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}

					
				}
				
				break;
			case 'b':
				
//				OSSchedLock(&err);		//调度器上锁
//				
//				ESP8266_Send_AT_Cmd("AT+CWLAP","OK",0,5);
//			
//				OSSchedUnlock(&err);	//调度器解锁
			
//				//处理获取的AP列表
//				
//				//备份列表
//				
//				u8 *ap_list_temp; 
				//test();
				//get_APlist();
			
				
				//先判断设置页面是否被删除了
				if(Framewin_wifiseting != 0)
					WM_SendMessageNoPara(WM_GetClientWindow(Framewin_wifiseting),WM_USER + 2);
				break;
				
			case 'c':
				
//				sprintf(MQTT_SEND_UPDATE_BUFF,"AT+MQTTPUB=0,\"update\",\"{\"MADDR\":%d,\"T\";%d,\"H\":%d,\"SW1\":%d,\"SW2\":%d}\",1,0",mesh_dev[0].MADDR,mesh_dev[0].Read_only_value[0],mesh_dev[0].Read_only_value[1],mesh_dev[0].Read_write_value[0],mesh_dev[0].Read_write_value[1]);
//			 
//				ESP8266_Send_AT_Cmd(MQTT_SEND_UPDATE_BUFF,"OK",0,5);
			
//				sprintf(MQTT_SEND_UPDATE_BUFF,"AT+MQTTPUB=0,\"update\",\"%2d%2d%2d%2d%2d\",1,0",mesh_dev[1].MADDR,mesh_dev[1].Read_only_value[0],mesh_dev[1].Read_only_value[1],mesh_dev[1].Read_write_value[0],mesh_dev[1].Read_write_value[1]);

				sprintf(MQTT_SEND_UPDATE_BUFF,"AT+MQTTPUB=0,\"update\",\"%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d\",1,0",mesh_dev[0].MADDR,mesh_dev[0].Read_only_value[0],mesh_dev[0].Read_only_value[1],mesh_dev[0].Read_write_value[0],mesh_dev[0].Read_write_value[1],\
																															  mesh_dev[1].MADDR,mesh_dev[1].Read_only_value[0],mesh_dev[1].Read_only_value[1],mesh_dev[1].Read_write_value[0],mesh_dev[1].Read_write_value[1],\
																															  mesh_dev[2].MADDR,mesh_dev[2].Read_only_value[0],mesh_dev[2].Read_only_value[1],mesh_dev[2].Read_write_value[0],mesh_dev[2].Read_write_value[1]
																																);
			
				ESP8266_Send_AT_Cmd(MQTT_SEND_UPDATE_BUFF,"OK",0,5);
			
//				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"update\",\"hello\",1,0","OK",0,5);
				break;	

			case 'd':
				
			
				break;
				
			case 'e':
				
				at_timeout = 5;
			
//				while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"cn.pool.ntp.org\",\"cn.ntp.org.cn\",\"ntp.aliyun.com\"","OK",0,10));
//			
//				while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPTIME?","OK",0,10));
			
				//OSSchedLock(&err);		//调度器上锁
//				ESP8266_Send_AT_Cmd("AT+CIPSNTPCFG=1,8,\"cn.pool.ntp.org\",\"cn.ntp.org.cn\",\"ntp.aliyun.com\"","OK",0,10);
//				delay_ms(1000);
//				delay_ms(1000);
			
				//ESP8266_Send_AT_Cmd("AT+CIPSNTPTIME?","OK",0,10);
				while(!ESP8266_Send_AT_Cmd("AT+CIPSNTPTIME?","OK",0,2));
				//delay_ms(1000);
				//delay_ms(1000);
				//USART3_RX_BUF[25] = '\0';
			
				//date = atoi(&USART3_RX_BUF[22]);
			
				//printf("%d\r\n",date);
				
				
				//将获取的字符串分割
				
				temp = &USART3_RX_BUF[17];
				
				printf("%s\r\n",temp);
				
				printf("%s\r\n",&USART3_RX_BUF[17]);
				
				
				strncpy(net_time,&USART3_RX_BUF[17],20);
				
				printf("%s\r\n",net_time);
				
				strncpy(time_buff,net_time,3);
				
				//OSSchedUnlock(&err);	//调度器解锁
			
				break;	

			case 'f':
				
				i = 0;
			
				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"master_server_pub\",\"get_time\",1,0","OK",0,5);
			
			
				/*********计算截取长度
				//len = strspn(USART3_RX_BUF,"+MQTTSUBRECV:0,\"master_server_sub\",19,");
			
				//printf("%d\r\n",len);
			
				//printf("%s\r\n",&USART3_RX_BUF[len]);
				//
				**********/
			
				strncpy(net_time,&USART3_RX_BUF[38],19);
				net_time[19] = '\0';
				printf("%s\r\n",net_time);
					
				/* 获取第一个子字符串 */
				token = strtok(net_time, s);
   
				/* 继续获取其他的子字符串 */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					yyyy_MM_dd_HH_mm_ss[i] = atoi(token);
					printf( "%d\r\n", yyyy_MM_dd_HH_mm_ss[i] );
					token = strtok(NULL, s);
					i++;
				}
				
				RTC_Set(yyyy_MM_dd_HH_mm_ss[0],yyyy_MM_dd_HH_mm_ss[1],yyyy_MM_dd_HH_mm_ss[2],yyyy_MM_dd_HH_mm_ss[3],yyyy_MM_dd_HH_mm_ss[4],yyyy_MM_dd_HH_mm_ss[5]);
				
				break;
				
			case 'g':
				
				i = 0;
				
				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"master_server_pub\",\"get_weather\",1,0","OK",0,5);
			
				delay_ms(100);
			
			
//				/* 获取第一个子字符串 */
//				token = strtok(USART3_RX_BUF, s2);
//   
//				/* 继续获取其他的子字符串 */
//				while( token != NULL ) 
//				{
//					printf( "%s\r\n", token );
//					if(i==2)
//					{
//						rx_data_len_len = strlen(token);
//						printf("rx_data_len_len: %d\r\n",rx_data_len_len);
//						rx_data_len = atoi(token);
//						printf("rx_data_len: %d\r\n",rx_data_len);
//					}
//					token = strtok(NULL, s2);
//					i++;
//				}
//			
//				
//				
//				len = strspn(USART3_RX_BUF,"+MQTTSUBRECV:0,\"master_server_sub\",4,");
//			
//				printf("%d\r\n",len);
//			
//				printf("%s\r\n",&USART3_RX_BUF[len]);
//			
//				strncpy(weather,&USART3_RX_BUF[strlen("+MQTTSUBRECV:0,\"master_server_sub\",")+rx_data_len_len+1],rx_data_len);
//				
//				//*(weather_buff+4) = '\0';
//				weather[rx_data_len] = '\0';
//				
//				printf("%s\r\n",weather);
//				
//				
//				len = strlen("+MQTTSUBRECV:0,\"master_server_sub\",");
//				
//				printf("%d\r\n",len);
				

				/* 获取第一个子字符串 */
				token = strtok(USART3_RX_BUF, s2);
   
				/* 继续获取其他的子字符串 */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					if(i==3)
					{
						
						//保存第四段内容
						//strcpy(weather,token);
						
						//rx_data_len_len = strlen(token);
						//printf("rx_data_len_len: %d\r\n",rx_data_len_len);
						
						
						//人为去除最后一段的\r\n 改为终止符\0
						*strchr(token,'\r') = '\0';
						//保存最后一段的内容
						strcpy(weather,token);
						
						//rx_data_len_len = strlen(weather);
						//printf("rx_data_len_len: %d\r\n",rx_data_len_len);						
						
						
						//strcpy()
					}
					token = strtok(NULL, s2);
					i++;
				}				
				
				
				printf("%s\r\n",weather);
				
				
				
				WM_InvalidateWindow(WM_HBKWIN);
			
				break;
				
			case 'h':
				
				i = 0;
				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"master_server_pub\",\"get_time\",1,0","OK",0,5);
				strncpy(net_time,&USART3_RX_BUF[38],19);
				net_time[19] = '\0';
				printf("%s\r\n",net_time);
				/* 获取第一个子字符串 */
				token = strtok(net_time, s);
				/* 继续获取其他的子字符串 */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					yyyy_MM_dd_HH_mm_ss[i] = atoi(token);
					printf( "%d\r\n", yyyy_MM_dd_HH_mm_ss[i] );
					token = strtok(NULL, s);
					i++;
				}
				RTC_Set(yyyy_MM_dd_HH_mm_ss[0],yyyy_MM_dd_HH_mm_ss[1],yyyy_MM_dd_HH_mm_ss[2],yyyy_MM_dd_HH_mm_ss[3],yyyy_MM_dd_HH_mm_ss[4],yyyy_MM_dd_HH_mm_ss[5]);
			

				i = 0;
				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"master_server_pub\",\"get_weather\",1,0","OK",0,5);
				delay_ms(100);			
				/* 获取第一个子字符串 */
				token = strtok(USART3_RX_BUF, s2);
				/* 继续获取其他的子字符串 */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					if(i==3)
					{
						//人为去除最后一段的\r\n 改为终止符\0
						*strchr(token,'\r') = '\0';
						//保存最后一段的内容
						strcpy(weather,token);
					}
					token = strtok(NULL, s2);
					i++;
				}				
				printf("%s\r\n",weather);
				WM_InvalidateWindow(WM_HBKWIN);				
				
				while(!ESP8266_Send_AT_Cmd("AT+CIPSTATUS","OK",0,5));
				if(strstr(USART3_RX_BUF,"STATUS:2"))
				{
					printf("wifi_on\r\n");
					Message.MsgId = WM_NOTIFY_PARENT;
					Message.Data.v = WM_NOTIFICATION_USER + 1;
					Message.hWinSrc = WM_GetDialogItem(WM_HBKWIN, ID_ICONVIEW_WIFI);
					WM_SendMessage(WM_HBKWIN,&Message);
					
					//先判断设置页面是否被删除了
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}
				}
				else
				{
					printf("wifi_off\r\n");
					Message.MsgId = WM_NOTIFY_PARENT;
					Message.Data.v = WM_NOTIFICATION_USER + 2;
					Message.hWinSrc = WM_GetDialogItem(WM_HBKWIN, ID_ICONVIEW_WIFI);
					WM_SendMessage(WM_HBKWIN,&Message);

					//先判断设置页面是否被删除了
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}
				}

				
				sys_init_finish_flag = true;
				
				USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启中断   
				//DMA_Cmd(DMA1_Channel6,ENABLE);	//RX
			
				BEEP = 1;
				delay_ms(1000);
				BEEP = 0;
				
				LED_R = 1;
				
				//向事件标志组EventFlags发送标志
				flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
									 (OS_FLAGS	  )KEY1_FLAG,
									 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
									 (OS_ERR*     )&err);
				printf("事件标志组EventFlags的值:%d\r\n",flags_num);

				break;

			
		}
			
		LED0 = !LED0;
		LED_B = !LED_B;
		
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err);//延时500ms
		//printf("used:%d\r\n",GUI_ALLOC_GetNumUsedBytes);
		//printf("free:%d\r\n",GUI_ALLOC_GetNumFreeBytes);
	}
}


//事件标志组处理任务
void flagsprocess_task(void *p_arg)
{
	OS_ERR err; 
	while(1)
	{
		//等待事件标志组
		OSFlagPend((OS_FLAG_GRP*)&EventFlags,
				   (OS_FLAGS	)KEY0_FLAG+KEY1_FLAG,
		     	   (OS_TICK     )0,
				   (OS_OPT	    )OS_OPT_PEND_FLAG_SET_ALL+OS_OPT_PEND_FLAG_CONSUME,
				   (CPU_TS*     )0,
				   (OS_ERR*	    )&err);
		OSTmrStart(&tmr1,&err);//开启定时器1		   
		printf("事件标志组EventFlags的值:%d\r\n",EventFlags.Flags);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//延时500ms
	}
}




//定时器1的回调函数
void tmr1_callback(void *p_tmr, void *p_arg)
{
	LED_R = !LED_R;
	printf("time1\r\n");
}


