#ifndef DRIVER_H
#define DRIVER_H

#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
#include "r_cg_rtc.h"
#include "Application.h"
#include "r_cg_wdt.h"
#include "r_cg_sau.h"

#define SAMPLES			3906
/*==============================GPIO=======================================*/
#define	POWER_LED			P15_bit.no1
#define ACK_LED				P6_bit.no2
#define COMM_LED			P15_bit.no2
#define FAULT_LED			P4_bit.no3

#define	VOLT_MON_CH1			P3_bit.no0
#define VOLT_MON_CH2			P3_bit.no1
#define VOLT_MON_CH3			P3_bit.no2
#define VOLT_MON_CH4			P3_bit.no3

#define	CURR_MON_CH1			P3_bit.no4
#define CURR_MON_CH2			P3_bit.no5
#define CURR_MON_CH3			P3_bit.no6
#define CURR_MON_CH4			P3_bit.no7

#define SWITCH_1			P1_bit.no1
#define SWITCH_2			P1_bit.no2
#define SWITCH_3			P1_bit.no3
#define SWITCH_4			P1_bit.no4
#define SWITCH_5			P1_bit.no5
#define SWITCH_6			P1_bit.no6
#define SWITCH_7			P1_bit.no7
#define SWITCH_8			P8_bit.no0

#define HIGH				1
#define LOW				0
/*=============================Timer=======================================*/
#define OneMs_Timer_Start() 		R_TAU0_Channel0_Start()
#define OneMs_Timer_Stop() 		R_TAU0_Channel0_Stop()

#define DbgUart_Start()			R_UART1_Start()
#define DbgUart_Stop()			R_UART1_Stop()

void OneMsISRhandler(void);

/*==============================WatchDog Timer===============================*/

#define WatchDog_Restart()		R_WDT_Restart()

/*================================UART========================================*/
typedef struct
{
	unsigned char dbg_wifi_tx  	: 1;
	unsigned char gsm_tx		: 1;
	unsigned char gsm_rx		: 1;
	unsigned char dbg_wifi_rx 	: 1;
	unsigned char dbg_wifi_buff	: 1;
}_Flags;
extern _Flags uartFlg;
void Debug_Print_U1(uint8_t *buf, uint16_t len);
void GSM_Print_U2(uint8_t *buf, uint16_t len);
/*===============================================================================*/
typedef struct
{
	unsigned char adcSamplesRdy	: 1;

}FLAGS__;
extern FLAGS__	DrvFlags;

typedef enum
{
    CHANNEL_2 = 2,
    CHANNEL_3,
    CHANNEL_4,
    CHANNEL_5,   
}ADS_CHANNEL_E;

extern ADS_CHANNEL_E VoltageCh;
extern signed long long int voltcnt;
extern signed long long int currentcnt;
extern unsigned long long int Accumulation,AccumulationIch0, AccumulationIch1, AccumulationIch2, AccumulationIch3;
extern unsigned long SampleCnt;
extern volatile unsigned int VoltageCh1;
extern volatile unsigned int VoltageCh2;
extern volatile unsigned int VoltageCh3;
extern volatile unsigned int VoltageCh4;
extern volatile unsigned int CurrentCh1;
extern volatile unsigned int CurrentCh2;
extern volatile unsigned int CurrentCh3;
extern volatile unsigned int CurrentCh4;
extern unsigned char DeviceID;
extern rtc_counter_value_t GetClock;

void DriverInit(void);
void Switch_Polling(void);
void GSM_Receive_U2(uint8_t mesrx);

#endif