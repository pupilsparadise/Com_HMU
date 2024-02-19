#ifndef OTDGSMTCPAPP_H
#define OTDGSMTCPAPP_H

#include "OtdGsm_App.h"

#define DISCONNECTED	0U
#define CONNECTED	1U
// This sub-state are used only for TCP intitialisation & sending data
//SubState Processing
typedef enum
{
	/**< TCP Init Command */
	TCP_QICSGP = 0,
	TCP_CMGF,
	/**< TCP Open and send Command */
	TCP_IDLESTATE,
	TCP_NETWORK_CHECK,
	TCP_SERVER_CHECK,
	TCP_NETWORK_CONNECT,
	TCP_SERVER_CONNECT,
	TCP_PREPARE_SEND,
	TCP_SEND_DATA,
	TCP_CLOSE_SERVER,
	TCP_NETWORK_CLOSE,
	Tcp_MaxSubState
}OtdGsmTcpApp_SubState_ten;

typedef struct
{
	OtdGsmTcpApp_SubState_ten TcpCurrent_en; //stores the current state
	OtdGsmTcpApp_SubState_ten TcpPrevious_en;//stores the previous state
	volatile uint8_t TcpCmdSendFlag;
	volatile uint8_t TcpTrials;//tracks the number of times the frame executed
	volatile int16_t TcpTimeOut; // tracks the time
}OtdGsmTcpApp_SubState_tst;

void OtdGsmTcpApp_TcpStateInit(void);
void OtdGsmTcpApp_TcpSendStateInit(void);

void OtdGsmTcpApp_ServerPrepareData(char *data, uint16_t data_length);

OtdGsmApp_Status_ten OtdGsmTcpApp_TcpInitCmdProcess(void);
OtdGsmApp_Status_ten OtdGsmTcpApp_TcpSendCmdProcess(void);

#endif