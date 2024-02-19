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
* File Name    : r_cg_port.c
* Version      : Code Generator for RL78/I1C V1.01.07.02 [08 Nov 2021]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Port module.
* Creation Date: 25-01-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
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
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    PFSEG0 = _00_PFSEG07_PORT | _00_PFSEG06_PORT | _00_PFSEG05_PORT | _10_PFSEG04_SEG;
    PFSEG1 = _80_PFSEG15_SEG | _40_PFSEG14_SEG | _20_PFSEG13_SEG | _00_PFSEG12_PORT | _00_PFSEG11_PORT | 
             _00_PFSEG10_PORT | _00_PFSEG09_PORT | _00_PFSEG08_PORT;
    PFSEG2 = _80_PFSEG23_SEG | _40_PFSEG22_SEG | _20_PFSEG21_SEG | _10_PFSEG20_SEG | _08_PFSEG19_SEG | 
             _04_PFSEG18_SEG | _02_PFSEG17_SEG | _01_PFSEG16_SEG;
    PFSEG3 = _00_PFSEG31_PORT | _00_PFSEG30_PORT | _00_PFSEG29_PORT | _00_PFSEG28_PORT | _00_PFSEG27_PORT | 
             _00_PFSEG26_PORT | _00_PFSEG25_PORT | _00_PFSEG24_PORT;
    PFSEG4 = _80_PFSEG39_SEG | _40_PFSEG38_SEG | _20_PFSEG37_SEG | _00_PFSEG36_PORT | _00_PFSEG35_PORT | 
             _04_PFSEG34_SEG | _00_PFSEG33_PORT | _01_PFSEG32_SEG;
    PFSEG5 = _02_PFSEG41_SEG | _01_PFSEG40_SEG;
    P3 = _00_Pn7_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn3_OUTPUT_0 | 
         _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    P4 = _00_Pn3_OUTPUT_0;
    P5 = _10_Pn4_OUTPUT_1 | _08_Pn3_OUTPUT_1 | _00_Pn1_OUTPUT_0;
    P6 = _00_Pn2_OUTPUT_0;
    P15 = _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0;
    PU4 = _01_PUn0_PULLUP_ON;
    PIM1 = _00_PIMn6_TTL_OFF | _00_PIMn5_TTL_OFF;
    PIM8 = _00_PIMn0_TTL_OFF;
    PM1 = _80_PMn7_MODE_INPUT | _40_PMn6_MODE_INPUT | _20_PMn5_MODE_INPUT | _10_PMn4_MODE_INPUT | 
          _08_PMn3_MODE_INPUT | _04_PMn2_MODE_INPUT | _02_PMn1_MODE_INPUT;
    PM3 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | 
          _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    PM4 = _F0_PM4_DEFAULT_VALUE | _00_PMn3_MODE_OUTPUT;
    PM5 = _00_PMn4_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT;
    PM6 = _F8_PM6_DEFAULT_VALUE | _00_PMn2_MODE_OUTPUT;
    PM8 = _C0_PM8_DEFAULT_VALUE | _01_PMn0_MODE_INPUT;
    PM15 = _F8_PM15_DEFAULT_VALUE | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
