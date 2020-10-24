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





//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С	
#define START_STK_SIZE 				1024
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				128
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);

//��������
//�����������ȼ�
#define KEY_TASK_PRIO 				5
//�����ջ��С
#define KEY_STK_SIZE				128
//������ƿ�
OS_TCB KeyTaskTCB;
//�����ջ
CPU_STK KEY_TASK_STK[KEY_STK_SIZE];
//led0����
void key_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				6
//�����ջ��С
#define LED0_STK_SIZE				512
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);

//AT_JDY����
//�����������ȼ�
#define AT_JDY_TASK_PRIO 				7
//�����ջ��С
#define AT_JDY_STK_SIZE				128
//������ƿ�
OS_TCB AT_JDY_TaskTCB;
//�����ջ
CPU_STK AT_JDY_TASK_STK[AT_JDY_STK_SIZE];
//led0����
void AT_JDY_task(void *p_arg);

//�������ȼ�
#define FLAGSPROCESS_TASK_PRIO	8
//�����ջ��С	
#define FLAGSPROCESS_STK_SIZE 	128
//������ƿ�
OS_TCB Flagsprocess_TaskTCB;
//�����ջ	
CPU_STK FLAGSPROCESS_TASK_STK[FLAGSPROCESS_STK_SIZE];
//������
void flagsprocess_task(void *p_arg);

//�ֿ��������
//�����������ȼ�
#define FONTUPDATA_TASK_PRIO		9
//�����ջ��С
#define FONTUPDATA_STK_SIZE			128
//������ƿ�
OS_TCB FontupdataTaskTCB;
//�����ջ
CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
//�ֿ��������
void fontupdata_task(void *p_arg);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			10
//�����ջ��С
#define EMWINDEMO_STK_SIZE			2048
//������ƿ�
OS_TCB EmwindemoTaskTCB;
//�����ջ
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *p_arg);

////////////////////////�ź���//////////////////////////////
OS_SEM	SYNC_SEM;			//����һ���ź�������������ͬ��
////////////////////////��Ϣ����//////////////////////////////
#define DATAMSG_Q_NUM	20	//�������ݵ���Ϣ���е�����
OS_Q DATA_Msg;				//����һ����Ϣ���У����ڷ�������
////////////////////////��Ϣ����//////////////////////////////
#define AT_JDY_MSG_Q_NUM	8	//�������ݵ���Ϣ���е�����
OS_Q AT_JDY_Msg;				//����һ����Ϣ���У����ڷ�������
////////////////////////�¼���־��//////////////////////////////
#define KEY0_FLAG		0x01
#define KEY1_FLAG		0x02
#define KEYFLAGS_VALUE	0X00						
OS_FLAG_GRP	EventFlags;		//����һ���¼���־��
////////////////////////�����ʱ��//////////////////////////////
OS_TMR tmr1;				//��ʱ��1

//��ʱ��1�Ļص�����
void tmr1_callback(void *p_tmr, void *p_arg);




//AP�б����洢����
#define AP_LIST_MAX_NUM 10

//USART3�������ݵı���
u8 USART3_RX_BUF_COPY[USART3_MAX_RECV_LEN];

//AP�б�ṹ��
struct ap_list_parameters
{
	u8 ecn;		//char��
	u8 ssid[40];
	int rssi;	//���������ͣ�Ĭ�Ͼ�Ϊ����
	u8 mac[20];
	u8 channel; //char��
};

//����10����aplist�������ڴ洢ap�б�
struct ap_list_parameters ap_list_para[AP_LIST_MAX_NUM];
//��¼��ǰAP�б�ĸ���
u8 ap_list_num = 0;
//��¼��һ��AP�б�ĸ���
u8 ap_list_num_last = 0;


u8 MQTT_SEND_UPDATE_BUFF[80];

//MESH��������֡
u8 mesh_data[]={0x41,0x54,0x2b,0x4d,0x45,0x53,0x48,0x00,0xff,0xff,0x55,0x66,0x77,0x88,0x0D,0x0A};	

//������Ϣ����
u8 *weather_buff = NULL;
u8 weather[50]={0};

//��ʼ���ṹ������ķ���
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
//3.����
extern struct dev_info mesh_dev[5] = {0};
//ϵͳ��ʼ����־
bool sys_init_finish_flag = false;
//�������Ƚ�
u32 hb_num_tem[3]={0};


//���ڿؼ�ID
#define ID_ICONVIEW_WIFI		(GUI_ID_USER + 0xC2)
#define ID_TEXT_3				(GUI_ID_USER + 0x06)


//�����ȡ��AP�б�
void get_APlist(void)
{
	u8 *ap_list_temp=0;
	u8 *ap_list_end=0;
	u8 i=0;
	
	//	u8 ap_list_num = 0;
	
	//�м��ַ���������rssi�ַ�������ʱ�任 �ַ���->char
	//u8 rssi_tempstr[6];
	

	//��ap_list_para
	memset(ap_list_para,0,sizeof(struct ap_list_parameters)*AP_LIST_MAX_NUM);
	//���USART3_RX_BUF_COPY
	memset(USART3_RX_BUF_COPY,0,sizeof(u8)*USART3_MAX_RECV_LEN);
	//�����б�
	strcpy(USART3_RX_BUF_COPY,(const char *)USART3_RX_BUF);
	//��ȡ�б��׵�ַ
	ap_list_temp = USART3_RX_BUF_COPY;
	//����
	while(*ap_list_temp != '\r' && i != AP_LIST_MAX_NUM)
	{
//		//���� ODOA �س����� \r\n
//		ap_list_end = strstr(ap_list_temp,"\r\n");
		
//		//���� OD �س� \r
//		ap_list_end = strchr(ap_list_temp,'\r');
		
		//ʹ��strcpy�ӽ�����
		//strcpy(ap_list_end,"\0\0");
		
//		//ֱ�Ӽӽ�����
//		*ap_list_end = '\0';
		
		//��ӡ��֤
		//printf("%s\r\n",ap_list_temp);
		
		//������Զ��δ���Ҳ���Բ�����
		
		//����ֱ�ӽ����ݲ�ֱ��浽ap�ṹ��//

		//��ȡecn
		ap_list_temp = ap_list_temp+8;
		
		ap_list_para[i].ecn=(char)atoi(ap_list_temp);
		
		printf("%d\r\n",ap_list_para[i].ecn);
		
		//��ȡssid
		ap_list_temp = ap_list_temp + 3;
		
		ap_list_end = strchr(ap_list_temp,'\"');
		
		*ap_list_end = '\0';
		
		sprintf(ap_list_para[i].ssid,ap_list_temp);
		
		*ap_list_end = '\"';
		
		printf("%s\r\n",ap_list_para[i].ssid);
		
		//��ȡrssi
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,',');
		
		*ap_list_end = '\0';
		
		//sprintf(rssi_tempstr,ap_list_temp);
		
		ap_list_para[i].rssi = atoi(ap_list_temp);
		
		*ap_list_end = ',';
		
		printf("%d\r\n",ap_list_para[i].rssi);
		
		//��ȡmac
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,'\"');
		
		*ap_list_end = '\0';

		sprintf(ap_list_para[i].mac,ap_list_temp);
		
		*ap_list_end = '\"';
		
		printf("%s\r\n",ap_list_para[i].mac);
		
		//��ȡchannel
		
		ap_list_temp = ap_list_end + 2;
		
		ap_list_end = strchr(ap_list_temp,')');
		
		*ap_list_end = '\0';
		
		ap_list_para[i].channel = (char)atoi(ap_list_temp);
		
		*ap_list_end = ')';
		
		printf("%d\r\n",ap_list_para[i].channel);		
		
		//
		//printf("%s\r\n",ap_lit[i]);	

		//�����׵�ַ����ת����һ��aplist
		ap_list_temp = ap_list_end + 3;

		//����
		printf("ecn:%d,ssid:%s,rssi:%d,mac:%s,channel:%d\r\n",ap_list_para[i].ecn,ap_list_para[i].ssid,ap_list_para[i].rssi,ap_list_para[i].mac,ap_list_para[i].channel);
		
		//��¼AP����
		i++;
		
		//------------------------------//
		
		
		
		
//		//���浽������
//		sprintf(ap_lit[i++],ap_list_temp);
//		//��ӡ��֤
//		//printf("%s\r\n",ap_lit[i++]);
//		//�ظ��������׵�ַ
//		ap_list_temp = ap_list_end + 2;
	}
	
	ap_list_num = i;
	
	//��ӡ��֤
	for(i=0;i<ap_list_num;i++)
		printf("ecn:%d,ssid:%s,rssi:%d,mac:%s,channel:%d\r\n",ap_list_para[i].ecn,ap_list_para[i].ssid,ap_list_para[i].rssi,ap_list_para[i].mac,ap_list_para[i].channel);

	//��ӡ��֤
	printf("%s\r\n",USART3_RX_BUF_COPY);
	
	
}







/***************************������******************************/

int main(void)
{	
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init();	    	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��	
	KEY_Init();	 			//������ʼ��
	BEEP_Init();			//��ʼ��������
	RTC_Init();	  			//RTC��ʼ��
	
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
	
//	//���Ͳ���֡
//	DMA_USART2_Tx_Data(mesh_data,14);
//	delay_ms(1000);
//	DMA_USART2_Tx_Data(mesh_data,14);
//	delay_ms(1000);		
	
		
	FSMC_SRAM_Init();		//��ʼ��SRAM
	my_mem_init(SRAMIN); 	//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);  	//��ʼ���ⲿ�ڴ��
	
	exfuns_init();			//Ϊfatfs�ļ�ϵͳ�����ڴ�
	f_mount(fs[0],"0:",1);	//����SD��
	f_mount(fs[1],"1:",1);	//����FLASH
	
	while(SD_Init())		//���SD��
	{
		LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
		delay_ms(200);
		LCD_Fill(30,90,200+30,70+16,WHITE);
		delay_ms(200);		    
	}
	
	while(font_init())		//��ʼ���ֿ�
	{
		LCD_ShowString(30,70,200,16,16,"Font Error!");
		update_font(30,90,16,"0:");	//����ֿⲻ���ھ͸����ֿ�
		delay_ms(2000);
		LCD_Clear(WHITE);	//����
		break;
	}
	TP_Init();				//��������ʼ��
	
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//����CRCʱ��
	
	
	//���������д��ڵĴ洢�豸 ��STemWin��ʼ�� STemWin�ĵ�Ҫ��
	WM_SetCreateFlags(WM_CF_MEMDEV); //�������д��ڵĴ洢�豸
	GUI_Init();  			//STemWin��ʼ��
	OS_CRITICAL_ENTER();	//�����ٽ���
	
	//����һ���ź���
	OSSemCreate ((OS_SEM*	)&SYNC_SEM,
                 (CPU_CHAR*	)"SYNC_SEM",
                 (OS_SEM_CTR)0,		
                 (OS_ERR*	)&err);	
	
	//������Ϣ����DATA_Msg
	OSQCreate ((OS_Q*		)&DATA_Msg,	
                (CPU_CHAR*	)"DATA Msg",	
                (OS_MSG_QTY	)DATAMSG_Q_NUM,	
                (OS_ERR*	)&err);		
				
	//������Ϣ����AT_JDY_Msg
	OSQCreate ((OS_Q*		)&AT_JDY_Msg,	
                (CPU_CHAR*	)"AT_JDY Msg",	
                (OS_MSG_QTY	)AT_JDY_MSG_Q_NUM ,	
                (OS_ERR*	)&err);						
				
	//����һ���¼���־��
	OSFlagCreate((OS_FLAG_GRP*)&EventFlags,		//ָ���¼���־��
                 (CPU_CHAR*	  )"Event Flags",	//����
                 (OS_FLAGS	  )KEYFLAGS_VALUE,	//�¼���־���ʼֵ
                 (OS_ERR*  	  )&err);

	//����һ�������ʱ��
	OSTmrCreate((OS_TMR*	)&tmr1, 
				(CPU_CHAR*	)"tmr1", 
				(OS_TICK 	)20, 
				(OS_TICK 	)100, 
				(OS_OPT		)OS_OPT_TMR_PERIODIC, 
				(OS_TMR_CALLBACK_PTR)tmr1_callback, 
				(void*   	)0, 
				(OS_ERR*	)&err);

	//STemWin Demo����	
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
	//����������
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
	//LED0����
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
	//AT_JDY����
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
	//����MSGDIS����
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
	//�ֿ��������
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
	//��������
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
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

//EMWINDEMO����
void emwindemo_task(void *p_arg)
{
	//����Ƥ��
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
	
	//�����洢�豸
	//LoadBMP_UsingMEMDEV("0:/image/sea_and_cloud.bmp",0,0);
	
	//�����洢�豸
	LoadBMP_UsingMEMDEV("0:/wallpaper/SQ_240X320.bmp",0,0);	
	
	
	//ɾ���洢�豸
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

//�ֿ��������
//KEY_UP������2s�����ֿ�
void fontupdata_task(void *pdata)
{
	OS_ERR err;
	while(1)
	{
		if(WK_UP == 1)				//KEY_UP������
		{
			OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_PERIODIC,&err);//��ʱ2s
			if(WK_UP == 1)			//����KEY_UP��
			{
				LCD_Clear(WHITE);
				OSSchedLock(&err);		//����������
				LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
				update_font(10,70,16,"0:");//�����ֿ�
				LCD_Clear(WHITE);
				POINT_COLOR = RED;
				LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
				OSSchedUnlock(&err);	//����������
			}
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//��ʱ10ms
	}
}

//������������
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
	
				OSSchedLock(&err);		//����������
				LED1 = 0;
				//create_bmppicture("0:/SCREENSHORT/��Ļ��ͼ0.bmp",0,0,800,480);
				LED1 = 1;
				OSSchedUnlock(&err);	//����������
				break;
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//��ʱ10ms
	}
}

//TOUCH����
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
	}
}

//AT_JDY����
void AT_JDY_task(void *p_arg)
{
	OS_ERR err;
	//��Ϣ����
	OS_MSG_SIZE size;
	u8 *msg;
	
	while(1)
	{
		//ʹ����Ϣ���н���������Ϣ
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
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);//��ʱ50ms
	}
}







//LED0����
void led0_task(void *p_arg)
{
	OS_ERR err;
	
	WM_MESSAGE Message;
	
	OS_FLAGS flags_num;	
	
	//��Ϣ����
	OS_MSG_SIZE size;
	u8 *msg;
	
	u8 at_timeout;
	u8 *temp = NULL;
	
	//2020-10-12-04-58-25 19���ַ� Ԥ��һ����ֹ��\0 19+1=20
	u8 net_time[20];
	
	u8 time_buff[4];
	
	u8 len;
	
	u8 len2;
	
	u8 rx_data_len;
	
	u8 rx_data_len_len;
	
	//�ָ��ַ�
	const char s[2] = "-";
	const char s2[2] = ",";
	char *token;	
	
	u16 yyyy_MM_dd_HH_mm_ss[6]={2020,10,10,18,12,60};
	
	int i = 10;
	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//�����ٽ���	
//	OS_CRITICAL_EXIT();	//�˳��ٽ���

	//ESP8266����
	while(!ESP8266_Send_AT_Cmd("AT+CWMODE=1","OK","no change",3));
	while(!ESP8266_Send_AT_Cmd("AT+CWJAP=\"123\",\"38100221at\"","OK",0,15));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTUSERCFG=0,1,\"ESP_ATK\",\"yong\",\"123\",0,0,\"\"","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTCONN=0,\"47.106.68.4\",1883,0","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTSUB=0,\"ledctl\",1","OK",0,5));
	while(!ESP8266_Send_AT_Cmd("AT+MQTTSUB=0,\"master_server_sub\",1","OK",0,5));

	//���¼���־��EventFlags���ͱ�־
	flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
						 (OS_FLAGS	  )KEY0_FLAG,
						 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
						 (OS_ERR*	  )&err);
	printf("�¼���־��EventFlags��ֵ:%d\r\n",flags_num);
	
//	//��ȡʱ��
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"f",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//	//��ȡ����
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"g",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//	//��ȡWiFi״̬
//		OSQPost((OS_Q*		)&DATA_Msg,		
//				(void*		)&"a",
//				(OS_MSG_SIZE)1,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);				

		//ϵͳ��ʼ������
		OSQPost((OS_Q*		)&DATA_Msg,		
				(void*		)&"h",
				(OS_MSG_SIZE)1,
				(OS_OPT		)OS_OPT_POST_FIFO,
				(OS_ERR*	)&err);	

//��ȡntpʱ��	
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
���ܣ��ж��ַ���str2�Ƿ���str1���Ӵ���

����
str1 - Ҫ���ҵ��ַ������ַ���ָ��
str2 - Ҫ���ҵ��Ӵ�

����ֵ
��������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��
*/	
	delay_ms(1000);
	
	while(1)
	{	
//		//ʹ���ź�����������ͬ��
//		OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); //�����ź���
//		//flag_at_jap_ok = 0;
//		while(!ESP8266_Send_AT_Cmd(at_jap,"OK",0,15));
//		flag_at_jap_ok = 1;
		
		//ʹ����Ϣ���н���������Ϣ
		msg = OSQPend((OS_Q*		  )&DATA_Msg,
				(OS_TICK	  )0,
				(OS_OPT 	  )OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE* )&size,
				(CPU_TS*	  )0,
				(OS_ERR*	  )&err);
		switch(*msg)
		{
			case 0:
				//��Ӧ��ʱ������������������Ӧ����������ģ��
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
					
					//���ж�����ҳ���Ƿ�ɾ����
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

					//���ж�����ҳ���Ƿ�ɾ����
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}

					
				}
				
				break;
			case 'b':
				
//				OSSchedLock(&err);		//����������
//				
//				ESP8266_Send_AT_Cmd("AT+CWLAP","OK",0,5);
//			
//				OSSchedUnlock(&err);	//����������
			
//				//�����ȡ��AP�б�
//				
//				//�����б�
//				
//				u8 *ap_list_temp; 
				//test();
				//get_APlist();
			
				
				//���ж�����ҳ���Ƿ�ɾ����
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
			
				//OSSchedLock(&err);		//����������
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
				
				
				//����ȡ���ַ����ָ�
				
				temp = &USART3_RX_BUF[17];
				
				printf("%s\r\n",temp);
				
				printf("%s\r\n",&USART3_RX_BUF[17]);
				
				
				strncpy(net_time,&USART3_RX_BUF[17],20);
				
				printf("%s\r\n",net_time);
				
				strncpy(time_buff,net_time,3);
				
				//OSSchedUnlock(&err);	//����������
			
				break;	

			case 'f':
				
				i = 0;
			
				ESP8266_Send_AT_Cmd("AT+MQTTPUB=0,\"master_server_pub\",\"get_time\",1,0","OK",0,5);
			
			
				/*********�����ȡ����
				//len = strspn(USART3_RX_BUF,"+MQTTSUBRECV:0,\"master_server_sub\",19,");
			
				//printf("%d\r\n",len);
			
				//printf("%s\r\n",&USART3_RX_BUF[len]);
				//
				**********/
			
				strncpy(net_time,&USART3_RX_BUF[38],19);
				net_time[19] = '\0';
				printf("%s\r\n",net_time);
					
				/* ��ȡ��һ�����ַ��� */
				token = strtok(net_time, s);
   
				/* ������ȡ���������ַ��� */
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
			
			
//				/* ��ȡ��һ�����ַ��� */
//				token = strtok(USART3_RX_BUF, s2);
//   
//				/* ������ȡ���������ַ��� */
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
				

				/* ��ȡ��һ�����ַ��� */
				token = strtok(USART3_RX_BUF, s2);
   
				/* ������ȡ���������ַ��� */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					if(i==3)
					{
						
						//������Ķ�����
						//strcpy(weather,token);
						
						//rx_data_len_len = strlen(token);
						//printf("rx_data_len_len: %d\r\n",rx_data_len_len);
						
						
						//��Ϊȥ�����һ�ε�\r\n ��Ϊ��ֹ��\0
						*strchr(token,'\r') = '\0';
						//�������һ�ε�����
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
				/* ��ȡ��һ�����ַ��� */
				token = strtok(net_time, s);
				/* ������ȡ���������ַ��� */
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
				/* ��ȡ��һ�����ַ��� */
				token = strtok(USART3_RX_BUF, s2);
				/* ������ȡ���������ַ��� */
				while( token != NULL ) 
				{
					printf( "%s\r\n", token );
					if(i==3)
					{
						//��Ϊȥ�����һ�ε�\r\n ��Ϊ��ֹ��\0
						*strchr(token,'\r') = '\0';
						//�������һ�ε�����
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
					
					//���ж�����ҳ���Ƿ�ɾ����
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

					//���ж�����ҳ���Ƿ�ɾ����
					if(Framewin_wifiseting != 0)
					{
						Message.hWinSrc = WM_GetDialogItem(WM_GetClientWindow(Framewin_wifiseting), ID_TEXT_3);
						WM_SendMessage(WM_GetClientWindow(Framewin_wifiseting),&Message);
					}
				}

				
				sys_init_finish_flag = true;
				
				USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�   
				//DMA_Cmd(DMA1_Channel6,ENABLE);	//RX
			
				BEEP = 1;
				delay_ms(1000);
				BEEP = 0;
				
				LED_R = 1;
				
				//���¼���־��EventFlags���ͱ�־
				flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
									 (OS_FLAGS	  )KEY1_FLAG,
									 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
									 (OS_ERR*     )&err);
				printf("�¼���־��EventFlags��ֵ:%d\r\n",flags_num);

				break;

			
		}
			
		LED0 = !LED0;
		LED_B = !LED_B;
		
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
		//printf("used:%d\r\n",GUI_ALLOC_GetNumUsedBytes);
		//printf("free:%d\r\n",GUI_ALLOC_GetNumFreeBytes);
	}
}


//�¼���־�鴦������
void flagsprocess_task(void *p_arg)
{
	OS_ERR err; 
	while(1)
	{
		//�ȴ��¼���־��
		OSFlagPend((OS_FLAG_GRP*)&EventFlags,
				   (OS_FLAGS	)KEY0_FLAG+KEY1_FLAG,
		     	   (OS_TICK     )0,
				   (OS_OPT	    )OS_OPT_PEND_FLAG_SET_ALL+OS_OPT_PEND_FLAG_CONSUME,
				   (CPU_TS*     )0,
				   (OS_ERR*	    )&err);
		OSTmrStart(&tmr1,&err);//������ʱ��1		   
		printf("�¼���־��EventFlags��ֵ:%d\r\n",EventFlags.Flags);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}




//��ʱ��1�Ļص�����
void tmr1_callback(void *p_tmr, void *p_arg)
{
	LED_R = !LED_R;
	printf("time1\r\n");
}


