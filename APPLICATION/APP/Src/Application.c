#include "Application.h"
#include "SmdLed.h"
#include "CAN.h"
#include "string.h"
#include "stdio.h"
#include "OtdGsm_TcpApp.h"
#include "OtdUART.h"

extern OtdGsm_TcpApp_DataPrepare ServerDataPrepare;
uint16_t TCPframe_LENGTH = 1024;
char TCPframe[1024] = {0};

volatile unsigned int DelayMsCnt 	= 0;
_FLAGS		flag 			= {0};
TcpData_St	TCPdata			= {0};
unsigned char CanRecBuffer[10] 		= {0};
unsigned int RequestHmuCnt		= 0;
unsigned int sentTCPframeCnt		= 0;
unsigned long CanID 			= 0;
unsigned char DataReq[8]          = {0};
unsigned char CanFramePage_1[8]		= {0};
unsigned char CanFramePage_2[8]		= {0};
unsigned char CanFramePage_3[8]		= {0};
unsigned char CanFramePage_4[8]		= {0};
unsigned char 	stmp[8]			= {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint16_t RxCanDevID			= 0;

unsigned char RxCanDataFlg 		= 0;
/*
** Initialize the MCU
*/
void SignalHmuInit(void)
{  
    Debug_Print_U1((uint8_t*)"          SIGNAL HMU          \n", 31);
    SmdLed_Init();
    CANFD_init();
    Debug_Print_U1((uint8_t*)"[APP]          System Initialized.\n", 35);
}
/*
** MCU Polling
*/
void ComHmu_Polling(void)
{
     CAN_Polling();
     PrepareAndSendToTCP();
     ProcessedRecvData();
}
/*
** CAN Function Polling
*/
static void CAN_Polling(void)
{    
    if(flag.CanTx)
    {
	flag.CanTx = 0;
	Can_Frame_Prepare();
    }
    
    if(flag.CanRxInt)
    {
	flag.CanRxInt = 0;
	
	mcp2517_recv_interrupt();
	
	/*
	OtdUart_DebugSend("CAN Rcvd");
	
	readMsgBuf(&len, CanRxBuffer);
	CanID = getCanId();
	for(i = 0; i < len; i++) 
	{
    		CanRecBuffer[i] = CanRxBuffer[i];
	}
	ProcessedRecvData();
	*/
	
    }
}
void Can_Frame_Prepare(void)
{
    DataReq[0] = 0x00;
    DataReq[1] = 0X01;
    DataReq[2] = 0x01;
    DataReq[3] = 0x00;
    DataReq[4] = 0x00;
    DataReq[5] = 0x00;
    DataReq[6] = 0x0D;
    DataReq[7] = 0x0A;
    Can_TXD(CAN_ID, STANDARD_FRAME, 8, DataReq);
}

void PrepareAndSendToTCP(void)
{
	flag.SentTCP =1;//TODO: remove later
	
	if(flag.SentTCP)
	{
		flag.SentTCP = 0;
		
		/*TCPdata.volt1 = 155;
		TCPdata.volt2 = 255;
		TCPdata.volt3 = 355;
		TCPdata.volt4 = 455;
		TCPdata.cur1 = 5;
		TCPdata.cur2 = 6;
		TCPdata.cur3 = 7;
		TCPdata.cur4 = 8;)*/
		memset((void*)TCPframe,0,TCPframe_LENGTH);
		sprintf(TCPframe, "{\"DEVID\":\"SHMU001\",\"VC\":{\"v1\":%d,\"v2\":%d,\"v3\":%d,\"v4\":%d},\"CC\":{\"i1\":%d,\"i2\":%d,\"i3\":%d,\"i4\":%d},\"SIGSTATUS\":{\"status\":\"OK\"}}\n\n\r",TCPdata.volt1, TCPdata.volt2, TCPdata.volt3, TCPdata.volt4,TCPdata.cur1, TCPdata.cur2, TCPdata.cur3, TCPdata.cur4);
		OtdUart_DebugSend(TCPframe);
		//strcpy(TCPframe, "HELLO FROM COM");
		//Delay_Ms(500);
		OtdGsmTcpApp_ServerPrepareData(TCPframe, strlen(TCPframe));
		Delay_Ms(500);

		TCPdata.volt1=TCPdata.volt2=TCPdata.volt3=TCPdata.volt4=0;
		TCPdata.cur1=TCPdata.cur2=TCPdata.cur3=TCPdata.cur4=0;
	}
}

char CANframe[32] = {0};
void ProcessedRecvData(void)
{
    if(RxCanDataFlg)
    {
	//Can_TXD(CAN_ID, STANDARD_FRAME, 8, CanRecBuffer);
	//RxCanDataFlg = 0;
	//sprintf(CANframe,"\n CAN Data: %s",CanRecBuffer);
	//OtdUart_DebugSend(CANframe);
	//OtdUart_DebugSend(CanRecBuffer);
	//RxCanDevID = (CanRecBuffer[0] << 8) | CanRecBuffer[1];
	//if(RxCanDevID == 1)
	//{
		switch(DataReq[1])
		{
			case 1:
				TCPdata.volt1 	= (CanRecBuffer[0] << 8) | CanRecBuffer[1];
				TCPdata.volt2 	= (CanRecBuffer[2] << 8) | CanRecBuffer[3];
				TCPdata.volt3 	= (CanRecBuffer[4] << 8) | CanRecBuffer[5];
				TCPdata.volt4 	= (CanRecBuffer[6] << 8) | CanRecBuffer[7];
				flag.SentTCP =1;
			break;
			case 2:
				TCPdata.cur1	= (CanRecBuffer[0] << 8) | CanRecBuffer[1];
				TCPdata.cur2	= (CanRecBuffer[2] << 8) | CanRecBuffer[3];
				TCPdata.cur3	= (CanRecBuffer[4] << 8) | CanRecBuffer[5];
				TCPdata.cur4	= (CanRecBuffer[6] << 8) | CanRecBuffer[7];
				flag.SentTCP =1;
			break;
			default:
			break;
		}
		
	//}else{
	//	__nop();
	//}
	
	RxCanDataFlg = 0;
    }
}
/*
** Delay Function
*/
void Delay_Ms(uint16_t Cnt)
{
    DelayMsCnt = Cnt;
    while(1)
    {
	if(DelayMsCnt != 0) {
	      __nop();
	}else {
	      break;
	}
    }
}

/*
** One Millisecond CallBack Function
*/
void AppOneMsCallback(void)
{
    if(DelayMsCnt != 0)
    {
        DelayMsCnt--;
    }
    
    if(RequestHmuCnt++ >= REQUESTTIME)
    {
    	RequestHmuCnt = 0;
	flag.CanTx = 1;
    }
    
    if(sentTCPframeCnt++ >= TCPSENTDELAY)
    {
	//RequestHmuCnt=0;
	sentTCPframeCnt = 0;
    	//flag.SentTCP = 1;
    }
}



