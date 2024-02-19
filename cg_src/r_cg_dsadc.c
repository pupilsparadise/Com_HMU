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
* Copyright (C) 2015, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_dsadc.c
* Version      : Code Generator for RL78/I1C V1.01.07.02 [08 Nov 2021]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for DSADC module.
* Creation Date: 25-01-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dsadc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DSADC_Create
* Description  : This function initializes the DSAD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Create(void)
{
    DSADCK = 0U;
    DSADRES = 1U;   /* reset DSAD converter */
    DSADRES = 0U;   /* reset release of DSAD converter */
    DSADCEN = 1U;   /* enables input clock supply */
    DSAMK = 1U;     /* disable INTDSAD interrupt */
    DSAIF = 0U;     /* clear INTDSAD interrupt flag */
    DSAZMK0 = 1U;   /* disable INTDSADZC0 interrupt */
    DSAZIF0 = 0U;   /* clear INTDSADZC0 interrupt flag */
    DSAZMK1 = 1U;   /* disable INTDSADZC1 interrupt */
    DSAZIF1 = 0U;   /* clear INTDSADZC1 interrupt flag */
    /* Set INTDSAD level 2 priority */
    DSAPR1 = 1U;
    DSAPR0 = 0U;
    DSADMR = _0000_DSAD_SAMPLING_FREQUENCY_0 | _0000_DSAD_RESOLUTION_24BIT;
    DSADGCR0 = _10_DSAD_CH1_PGAGAIN_2 | _01_DSAD_CH0_PGAGAIN_2;
    DSADGCR1 = _10_DSAD_CH3_PGAGAIN_2 | _01_DSAD_CH2_PGAGAIN_2;
    DSADHPFCR = _C0_DSAD_CUTOFF_FREQUENCY_3 | _00_DSAD_CH3_HIGHPASS_FILTER_ENABLE | 
                _00_DSAD_CH2_HIGHPASS_FILTER_ENABLE | _00_DSAD_CH1_HIGHPASS_FILTER_ENABLE | 
                _00_DSAD_CH0_HIGHPASS_FILTER_ENABLE;
    DSADPHCR0 = _0000_DSAD_PHCR0_VALUE;
    DSADPHCR1 = _0000_DSAD_PHCR1_VALUE;
    DSADPHCR2 = _0000_DSAD_PHCR2_VALUE;
    DSADPHCR3 = _0000_DSAD_PHCR3_VALUE;
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Start
* Description  : This function starts the DSAD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Start(void)
{
    DSAIF = 0U;     /* clear INTDSAD interrupt flag */
    DSAMK = 0U;     /* enable INTDSAD interrupt */
    DSADMR |= _0008_DSAD_CH3_OPERATION | _0004_DSAD_CH2_OPERATION | _0002_DSAD_CH1_OPERATION | _0001_DSAD_CH0_OPERATION;
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Stop
* Description  : This function stops the DSAD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Stop(void)
{
    DSADMR &= (uint16_t) ~(_0008_DSAD_CH3_OPERATION | _0004_DSAD_CH2_OPERATION | _0002_DSAD_CH1_OPERATION | 
              _0001_DSAD_CH0_OPERATION);
    DSAMK = 1U;     /* disable INTDSAD interrupt */
    DSAIF = 0U;     /* clear INTDSAD interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Set_OperationOn
* Description  : This function power-on control.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Set_OperationOn(void)
{
    DSADMR |= _0800_DSAD_CH3_POWER_ON | _0400_DSAD_CH2_POWER_ON | _0200_DSAD_CH1_POWER_ON | _0100_DSAD_CH0_POWER_ON;
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Set_OperationOff
* Description  : This function power-down control.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Set_OperationOff(void)
{
    DSADMR &= (uint16_t) ~(_0800_DSAD_CH3_POWER_ON | _0400_DSAD_CH2_POWER_ON | _0200_DSAD_CH1_POWER_ON | 
              _0100_DSAD_CH0_POWER_ON);
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Channel0_Get_Result
* Description  : This function returns the conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Channel0_Get_Result(uint32_t * const buffer)
{
    *buffer = DSADCR0H;
    *buffer = (uint32_t)((*buffer << 16U) + DSADCR0);
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Channel1_Get_Result
* Description  : This function returns the conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Channel1_Get_Result(uint32_t * const buffer)
{
    *buffer = DSADCR1H;
    *buffer = (uint32_t)((*buffer << 16U) + DSADCR1);
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Channel2_Get_Result
* Description  : This function returns the conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Channel2_Get_Result(uint32_t * const buffer)
{
    *buffer = DSADCR2H;
    *buffer = (uint32_t)((*buffer << 16U) + DSADCR2);
}
/***********************************************************************************************************************
* Function Name: R_DSADC_Channel3_Get_Result
* Description  : This function returns the conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_DSADC_Channel3_Get_Result(uint32_t * const buffer)
{
    *buffer = DSADCR3H;
    *buffer = (uint32_t)((*buffer << 16U) + DSADCR3);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
