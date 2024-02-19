#include "Driver.h"
#include "r_cg_adc.h"
#include "r_cg_dsadc.h"
#include "r_cg_rtc.h"
#include "math.h"
_Flags 		uartFlg = {0};
FLAGS__		DrvFlags = {0};
signed long long int voltcnt = 0;
signed long long int currentcnt = 0;
unsigned long long int Accumulation = 0, AccumulationIch0 = 0, AccumulationIch1 = 0, AccumulationIch2 = 0, AccumulationIch3 = 0;
unsigned long SampleCnt = 0;
volatile unsigned int VoltageCh1 = 0;
volatile unsigned int VoltageCh2 = 0;
volatile unsigned int VoltageCh3 = 0;
volatile unsigned int VoltageCh4 = 0;
volatile unsigned int CurrentCh1 = 0;
volatile unsigned int CurrentCh2 = 0;
volatile unsigned int CurrentCh3 = 0;
volatile unsigned int CurrentCh4 = 0;
ADS_CHANNEL_E VoltageCh = CHANNEL_2;
rtc_counter_value_t GetClock;
uint8_t GsmBuf[100] = {0};
uint16_t GsmCnt = 0;
uint16_t GsmInterFrameTmout	= 0;
unsigned char DeviceID = 0x01;
//rtc_counter_value_t SetClock{.sec=0,.min=10,.hour=3,.day=23,.week=4,.month=12,.year=2023};
//rtc_counter_value_t SetClock = {.sec = 0, .min = 10, .hour = 3, .day = 23, .week = 4, .month = 12, .year = 2023 };
//rtc_counter_value_t SetClock = {0x00,0x0A,0x03,0x17,0x04,0x0C,0x17};

/*
** Initialize All Drivers
*/
void DriverInit(void)
{
    OneMs_Timer_Start();
   
    R_UART1_Start();
    R_UART2_Start();
    R_CSI30_Start();
   // R_RTC_Set_CalendarCounterValue(SetClock);
    R_RTC_Set_ConstPeriodInterruptOn(SEC1);
    R_RTC_Create();
    R_RTC_Start();
}
/*
** one millisecond interrupt Handler
*/
void OneMsISRhandler(void)
{
    R_WDT_Restart();
    AppOneMsCallback();
    
    if(GsmInterFrameTmout != 0)
    {
    	GsmInterFrameTmout--;
	if(GsmInterFrameTmout == 0)
	{
	    uartFlg.gsm_rx = True;
	    GsmCnt = 0;
	}
    }
}
/*
** debug uart transmit
*/
void Debug_Print_U1(uint8_t *buf, uint16_t len)
{
    uartFlg.dbg_wifi_tx = True;
    R_UART1_Send(buf, len);
    while(uartFlg.dbg_wifi_tx);
}

void GSM_Print_U2(uint8_t *buf, uint16_t len)
{
    uartFlg.gsm_tx = True;
    R_UART2_Send(buf, len);
    while(uartFlg.gsm_tx);
}

void GSM_Receive_U2(uint8_t mesrx)
{
    GsmInterFrameTmout = 200;
    GsmBuf[GsmCnt++] = mesrx;
}


/*
**RTC Polling
*/
void Rtc(void)
{
    R_RTC_Get_CalendarCounterValue(&GetClock);
}
/*
**Switch Polling Process
*/
void Switch_Polling(void)
{
    DeviceID = (SWITCH_1 << 8);
    DeviceID = DeviceID | (SWITCH_8 << 7);
    DeviceID = DeviceID | (SWITCH_7 << 6);
    DeviceID = DeviceID | (SWITCH_6 << 5);
    DeviceID = DeviceID | (SWITCH_5 << 4);
    DeviceID = DeviceID | (SWITCH_4 << 3);
    DeviceID = DeviceID | (SWITCH_3 << 2);
    DeviceID = DeviceID | (SWITCH_2 << 1);
    DeviceID = DeviceID | (SWITCH_1);
}