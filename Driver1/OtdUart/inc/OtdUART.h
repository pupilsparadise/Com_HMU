/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : OtdUART.h
* Version      : 
* Device(s)    : R5F104ML
* Tool-Chain   : CCRL
* Description  : This file implements device driver for UART module.
* Creation Date: 15-08-2023
***********************************************************************************************************************/

#ifndef OTDUART_H
#define OTDUART_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define DEBUG_UART 	1U //only to transimit debug messages
#define GSM_UART	2U //interface with GSM modem	
#define INVALID_UART	3U //no UART selected
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
	OTD_UART_STATUS_PASS,
	OTD_UART_STATUS_FAIL
}Otd_Uart_Status;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void OtdUart_Init(void);


//UART Tx

void OtdUart_CallbackSend(void);
void OtdUart_CallbackRecieve(void);
Otd_Uart_Status OtdUart_Send(const uint8_t *buf, uint16_t len , uint8_t uart);
Otd_Uart_Status OtdUart_Recieve(uint8_t *buf, uint16_t len);
void OtdUart_DebugSend(volatile const char *s);
uint16_t OtdDelay_GetTicks(void);

#endif