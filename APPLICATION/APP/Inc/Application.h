#ifndef APPLICATION_H
#define APPLICATION_H
#include "Driver.h"

#define REQUESTTIME		(5000)
#define TCPSENTDELAY		(15000)
#define NULL 			((void*)0)

typedef enum
{
     False = 0,
     True = 1
}Bool_E;

typedef struct
{
    	unsigned char CanRxInt		: 1;
	unsigned char CanTx		: 1;
	unsigned char SentTCP		: 1;
}_FLAGS;
extern _FLAGS	flag;

typedef struct
{
	unsigned int volt1;
	unsigned int volt2;
	unsigned int volt3;
	unsigned int volt4;
	unsigned int cur1;
	unsigned int cur2;
	unsigned int cur3;
	unsigned int cur4;
}TcpData_St;
extern TcpData_St	TCPdata;

enum
{
	PAGE0 = 0,
	PAGE1,
	PAGE2,
	PAGE3,
	PAGE4,
	PAGE5
};



static void CAN_Polling(void);
void Rtc(void);
void Can_Frame_Prepare(void);
void SignalHmuInit(void);
void ComHmu_Polling(void);
void Delay_Ms(uint16_t Cnt);
void AppOneMsCallback(void);
void PrepareAndSendToTCP(void);
void ProcessedRecvData(void);
#endif