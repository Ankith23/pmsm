/*
 * GlobalVariableDef.c
 *
 *  Created on: 26-Jan-2021
 *      Author: gurum
 */

/*
 * GlobalVariableDef.c
 *
 *  Created on: 08-Apr-2020
 *      Author: gurum
 */

/*
 * GlobalVariableDef.c
 *
 *  Created on: 26-Feb-2020
 *      Author: gurum
 */



#include "F2837xD_device.h"// F2837xD Headerfile Include File
#include "math.h"

//---------------------------------------------------------------------------
// Define Global Peripheral Variables:
//
//----------------------------------------

//----------------------------------------
#pragma DATA_SECTION(ClkCfgRegs,"ClkCfgRegsFile");
volatile struct CLK_CFG_REGS ClkCfgRegs;

//----------------------------------------
#pragma DATA_SECTION(CpuSysRegs,"CpuSysRegsFile");
volatile struct CPU_SYS_REGS CpuSysRegs;

//----------------------------------------
#pragma DATA_SECTION(DevCfgRegs,"DevCfgRegsFile");
volatile struct DEV_CFG_REGS DevCfgRegs;



#pragma DATA_SECTION(PieCtrlRegs,"PieCtrlRegsFile");
volatile struct PIE_CTRL_REGS PieCtrlRegs;


#pragma DATA_SECTION(PieVectTable,"PieVectTableFile");
volatile struct PIE_VECT_TABLE PieVectTable;


#pragma DATA_SECTION(CpuTimer0Regs,"CpuTimer0RegsFile");
volatile struct CPUTIMER_REGS CpuTimer0Regs;


#pragma DATA_SECTION(AdcaRegs,"AdcaRegsFile");

volatile struct ADC_REGS AdcaRegs;


#pragma DATA_SECTION(AdcbRegs,"AdcbRegsFile");

volatile struct ADC_REGS AdcbRegs;


#pragma DATA_SECTION(AdccRegs,"AdccRegsFile");

volatile struct ADC_REGS AdccRegs;


#pragma DATA_SECTION(AdcdRegs,"AdcdRegsFile");

volatile struct ADC_REGS AdcdRegs;


#pragma DATA_SECTION(AdcaResultRegs,"AdcaResultFile");

volatile struct ADC_RESULT_REGS AdcaResultRegs;


#pragma DATA_SECTION(AdcbResultRegs,"AdcbResultFile");

volatile struct ADC_RESULT_REGS AdcbResultRegs;


#pragma DATA_SECTION(AdccResultRegs,"AdccResultFile");

volatile struct ADC_RESULT_REGS AdccResultRegs;


#pragma DATA_SECTION(AdcdResultRegs,"AdcdResultFile");

volatile struct ADC_RESULT_REGS AdcdResultRegs;

#pragma DATA_SECTION(GpioCtrlRegs,"GpioCtrlRegsFile");

volatile struct GPIO_CTRL_REGS GpioCtrlRegs;


#pragma DATA_SECTION(GpioDataRegs,"GpioDataRegsFile");

volatile struct GPIO_DATA_REGS GpioDataRegs;

#pragma DATA_SECTION(PieVectTable,"PieVectTableFile");
volatile struct PIE_VECT_TABLE PieVectTable;



#pragma DATA_SECTION(SciaRegs,"SciaRegsFile");
volatile struct SCI_REGS SciaRegs;


#pragma DATA_SECTION(ScibRegs,"ScibRegsFile");
volatile struct SCI_REGS ScibRegs;


#pragma DATA_SECTION(ScicRegs,"ScicRegsFile");
volatile struct SCI_REGS ScicRegs;


#pragma DATA_SECTION(ScidRegs,"ScidRegsFile");
volatile struct SCI_REGS ScidRegs;

#pragma DATA_SECTION(EQep1Regs,"EQep1RegsFile");
volatile struct EQEP_REGS EQep1Regs;

#pragma DATA_SECTION(EQep3Regs,"EQep3RegsFile");
volatile struct EQEP_REGS EQep3Regs;

#pragma DATA_SECTION(EPwm1Regs,"EPwm1RegsFile");
volatile struct EPWM_REGS EPwm1Regs;
#pragma DATA_SECTION(EPwm2Regs,"EPwm2RegsFile");
volatile struct EPWM_REGS EPwm2Regs;
#pragma DATA_SECTION(EPwm3Regs,"EPwm3RegsFile");
volatile struct EPWM_REGS EPwm3Regs;
#pragma DATA_SECTION(EPwm4Regs,"EPwm4RegsFile");
volatile struct EPWM_REGS EPwm4Regs;
#pragma DATA_SECTION(EPwm5Regs,"EPwm5RegsFile");
volatile struct EPWM_REGS EPwm5Regs;
#pragma DATA_SECTION(EPwm6Regs,"EPwm6RegsFile");
volatile struct EPWM_REGS EPwm6Regs;
#pragma DATA_SECTION(EPwm7Regs,"EPwm7RegsFile");
volatile struct EPWM_REGS EPwm7Regs;
#pragma DATA_SECTION(EPwm8Regs,"EPwm8RegsFile");
volatile struct EPWM_REGS EPwm8Regs;
#pragma DATA_SECTION(EPwm9Regs,"EPwm9RegsFile");
volatile struct EPWM_REGS EPwm9Regs;
#pragma DATA_SECTION(EPwm10Regs,"EPwm10RegsFile");
volatile struct EPWM_REGS EPwm10Regs;
#pragma DATA_SECTION(EPwm11Regs,"EPwm11RegsFile");
volatile struct EPWM_REGS EPwm11Regs;

#pragma DATA_SECTION(InputXbarRegs,"InputXbarRegsFile");
volatile struct INPUT_XBAR_REGS InputXbarRegs;

#pragma DATA_SECTION(ECap1Regs,"ECap1RegsFile");
volatile struct ECAP_REGS ECap1Regs;


