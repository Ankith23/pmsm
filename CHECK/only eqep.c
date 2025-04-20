/*
chutiya chetan
 * Modified:- 8/6/2024
 */
#include "F28x_Project.h"
void SysCtrl(void);
void pwm(void);
void PWM2(void);
void PWM3(void);
void PWM4(void);
void gpioinit(void);
void encoder(void);
__interrupt void pwmISR(void);
__interrupt void pwm2ISR(void);
__interrupt void pwm3ISR(void);
__interrupt void pwm4ISR(void);
__interrupt void EQEPISR(void);
long COUNTER_VALUE[100],LATCH_POSITION,i;
void main(void)
{
    SysCtrl();
    gpioinit();
    pwm();
   PWM2();
   PWM3();
   PWM4();
encoder();
DINT;
EALLOW;
PieCtrlRegs.PIECTRL.bit.ENPIE=1;

PieCtrlRegs.PIEIER3.bit.INTx1=1;
 PieVectTable.EPWM1_INT=&pwmISR;
 PieCtrlRegs.PIEACK.bit.ACK3=01;

PieCtrlRegs.PIEIER3.bit.INTx2=1;
PieVectTable.EPWM2_INT=&pwm2ISR;
PieCtrlRegs.PIEACK.bit.ACK3=01;

PieCtrlRegs.PIEIER3.bit.INTx3=1;
PieVectTable.EPWM3_INT=&pwm3ISR;
PieCtrlRegs.PIEACK.bit.ACK3=01;

PieCtrlRegs.PIEIER3.bit.INTx4=1;
PieVectTable.EPWM4_INT=&pwm4ISR;
PieCtrlRegs.PIEACK.bit.ACK3=01;

PieCtrlRegs.PIEIER5.bit.INTx1=1;
PieVectTable.EQEP1_INT=&EQEPISR;
PieCtrlRegs.PIEACK.bit.ACK5=01;

IFR=0;
IER=0xffff;
EDIS;
EINT;
    while(1);
}
void gpioinit(void)
{
    EALLOW;
//1A
    GpioCtrlRegs.GPAGMUX1.bit.GPIO0=00;//0 for gmux & 1 for mux
       GpioCtrlRegs.GPAMUX1.bit.GPIO0=01;// by muxed pins we have to select pwm value
       GpioCtrlRegs.GPADIR.bit.GPIO0=01;//direction as output
       GpioCtrlRegs.GPAPUD.bit.GPIO0=01;//GPIO CONFIGURATION
//2A
     GpioCtrlRegs.GPAGMUX1.bit.GPIO2=00;//0 for gmux & 1 for mux
     GpioCtrlRegs.GPAMUX1.bit.GPIO2=01;// by muxed pins we have to select pwm value
    GpioCtrlRegs.GPADIR.bit.GPIO2=01;//direction as output
    GpioCtrlRegs.GPAPUD.bit.GPIO2=01;
//3A
    GpioCtrlRegs.GPAGMUX1.bit.GPIO4=00;//0 for gmux & 1 for mux
    GpioCtrlRegs.GPAMUX1.bit.GPIO4=01;// by muxed pins we have to select pwm value
   GpioCtrlRegs.GPADIR.bit.GPIO4=01;//direction as output
   GpioCtrlRegs.GPAPUD.bit.GPIO4=01;
//4A
   GpioCtrlRegs.GPAGMUX1.bit.GPIO6=00;//0 for gmux & 1 for mux
   GpioCtrlRegs.GPAMUX1.bit.GPIO6=01;// by muxed pins we have to select pwm value
  GpioCtrlRegs.GPADIR.bit.GPIO6=01;//direction as output
  GpioCtrlRegs.GPAPUD.bit.GPIO6=01;

  GpioCtrlRegs.GPAGMUX2.bit.GPIO20=00;//clk input
  GpioCtrlRegs.GPAMUX2.bit.GPIO20=01;//J14 PIN - 1
  GpioCtrlRegs.GPADIR.bit.GPIO20=00;
  GpioCtrlRegs.GPAPUD.bit.GPIO20=01;

  GpioCtrlRegs.GPAGMUX2.bit.GPIO21=01;// dir input
   GpioCtrlRegs.GPAMUX2.bit.GPIO21=01;//J14 PIN - 2
   GpioCtrlRegs.GPADIR.bit.GPIO21=00;
   GpioCtrlRegs.GPAPUD.bit.GPIO21=01;

   GpioCtrlRegs.GPDGMUX1.bit.GPIO99=00;// output INDEX
    GpioCtrlRegs.GPDMUX1.bit.GPIO99=01;//
    GpioCtrlRegs.GPDDIR.bit.GPIO99=01;
    GpioCtrlRegs.GPDPUD.bit.GPIO99=01;

    GpioCtrlRegs.GPAGMUX2.bit.GPIO22=00;// output STROBE
     GpioCtrlRegs.GPAMUX2.bit.GPIO22=01;//J1 8
     GpioCtrlRegs.GPADIR.bit.GPIO22=01;
     GpioCtrlRegs.GPAPUD.bit.GPIO22=01;
 EDIS;
}


void SysCtrl(void)
{
    long  i;
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL=00;
      ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN=0;// Bypass the PLL by clearing
      for(i=0;i<120;i++);
      ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=000000;
      for(i=0;i<5;i++)
      {
      ClkCfgRegs.SYSPLLCTL1.bit.PLLEN= 0;
      ClkCfgRegs.SYSPLLMULT.bit.FMULT=0;
      ClkCfgRegs.SYSPLLMULT.bit.IMULT=16;// 160MHZ systemclk
      while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS!=1);
      }
      ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=1;//desired+1
      ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN=1;
      ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=000000;
      EDIS;
}
void pwm(void)
{
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
      CpuSysRegs.PCLKCR2.bit.EPWM1=1;
      CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
      EPwm1Regs.TBCTL.bit.CLKDIV=010;
      EPwm1Regs.TBCTL.bit.HSPCLKDIV=000;
   EPwm1Regs.TBPRD=4000;
   EPwm1Regs.CMPA.bit.CMPA=2000;
      //double check//
      EPwm1Regs.TBCTR=0x0000;
      EPwm1Regs.TBCTL.bit.CTRMODE=00;
      EPwm1Regs.AQCTLA.bit.CAU=2;//set
      EPwm1Regs.AQCTLA.bit.ZRO=1;//clear
      EPwm1Regs.AQCTLB.bit.CBU=2;//set
      EPwm1Regs.AQCTLB.bit.ZRO=1;//clear
      EPwm1Regs.ETSEL.bit.INTSEL= 2;
      EPwm1Regs.ETSEL.bit.INTEN=1;
      EPwm1Regs.ETCLR.bit.INT=1;
      EPwm1Regs.ETPS.bit.INTPRD=1;
      EPwm1Regs.TBCTL.bit.PHSEN=1;
      EPwm1Regs.TBPHS.bit.TBPHS=0;
      EDIS;

    }

void PWM2(void)
{
    EALLOW;
         //EPWM2
         ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
         CpuSysRegs.PCLKCR2.bit.EPWM2=1;
         CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
         EPwm2Regs.TBCTL.bit.CLKDIV=010;
         EPwm2Regs.TBCTL.bit.HSPCLKDIV=000;
         EPwm2Regs.TBCTL.bit.PHSEN=1;
        EPwm2Regs.TBPRD=4000;
        EPwm2Regs.CMPA.bit.CMPA=2000;
         //double check//
         EPwm2Regs.TBCTR=0x0000;
         EPwm2Regs.TBCTL.bit.CTRMODE=00;
              EPwm2Regs.AQCTLA.bit.CAU=2;//clear
              EPwm2Regs.AQCTLA.bit.ZRO=1;//set
              EPwm2Regs.AQCTLB.bit.CBU=2;//set
              EPwm2Regs.AQCTLB.bit.ZRO=1;//clear

         EPwm2Regs.ETSEL.bit.INTSEL= 2;
         EPwm2Regs.ETSEL.bit.INTEN=1;
         EPwm2Regs.ETCLR.bit.INT=1;
         EPwm2Regs.ETPS.bit.INTPRD=1;
         EPwm2Regs.TBPHS.bit.TBPHS=45;
         EDIS;
}
void PWM3(void)
{
    EALLOW; //EPWM3
           ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
           CpuSysRegs.PCLKCR2.bit.EPWM3=1;
           CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
           EPwm3Regs.TBCTL.bit.CLKDIV=010;
           EPwm3Regs.TBCTL.bit.HSPCLKDIV=000;
           EPwm3Regs.TBPRD=16000;
           EPwm3Regs.CMPA.bit.CMPA=15960;
//           EPwm4Regs.CMPA.bit.CMPA=2000;
//               EPwm4Regs.CMPB.bit.CMPB=2000;
           //double check//
           EPwm3Regs.TBCTR=0x0000;
           EPwm3Regs.TBCTL.bit.CTRMODE=00;
                EPwm3Regs.AQCTLA.bit.CAU=2;//clear
                EPwm3Regs.AQCTLA.bit.ZRO=1;//set
                EPwm3Regs.AQCTLB.bit.CBU=2;//set
                EPwm3Regs.AQCTLB.bit.ZRO=1;//clear

           EPwm3Regs.ETSEL.bit.INTSEL= 2;
           EPwm3Regs.ETSEL.bit.INTEN=1;
           EPwm3Regs.ETCLR.bit.INT=1;
           EPwm3Regs.ETPS.bit.INTPRD=1;

           EDIS;
}
void PWM4(void)
{
    EALLOW; //EPWM3
           ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
           CpuSysRegs.PCLKCR2.bit.EPWM4=1;
           CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
           EPwm4Regs.TBCTL.bit.CLKDIV=010;
           EPwm4Regs.TBCTL.bit.HSPCLKDIV=000;
           EPwm4Regs.TBPRD=30000;
           EPwm4Regs.CMPA.bit.CMPA=28000;
//           EPwm4Regs.CMPA.bit.CMPA=2000;
//               EPwm4Regs.CMPB.bit.CMPB=2000;
           //double check//
           EPwm4Regs.TBCTR=0x0000;
           EPwm4Regs.TBCTL.bit.CTRMODE=02;
                EPwm4Regs.AQCTLA.bit.CAU=2;//clear
                EPwm4Regs.AQCTLA.bit.CAD=1;//set
                EPwm4Regs.AQCTLB.bit.CBU=2;//set
                EPwm4Regs.AQCTLB.bit.CBD=1;//clear

           EPwm4Regs.ETSEL.bit.INTSEL= 2;
           EPwm4Regs.ETSEL.bit.INTEN=1;
           EPwm4Regs.ETCLR.bit.INT=1;
           EPwm4Regs.ETPS.bit.INTPRD=1;

           EDIS;
}
void encoder(void)
{

    EALLOW;
    CpuSysRegs.PCLKCR4.bit.EQEP1 = 1;// Enable clock to the QEP module
    //EQep1Regs.QEPCTL.bit.FREE_SOFT=2;//Unaffected by emulation suspend
    EQep1Regs.QEPCTL.bit.FREE_SOFT=1;
    EQep1Regs.QEPCTL.bit.PCRM = 00;//03;Position counter reset on Unit time count event; 00:position counter reset on an index event1
    EQep1Regs.QEPCTL.bit.SEI=0; // Does nothing (Strobe event initialization of position counter
    EQep1Regs.QEPCTL.bit.IEI=3;//Initialize position counter on falling edge of index event QEPI Event
   // EQep1Regs.QEPCTL.bit.IEI=0;//Do nothing
    EQep1Regs.QPOSINIT=0x00;   // position counter initialization
    EQep1Regs.QEPCTL.bit.SWI=1; //Initialize the position counter with the value stored in QPOSINIT
    EQep1Regs.QEPCTL.bit.SEL=0;//Position counter is latched on the rising event of Strobe signal QEPS
    EQep1Regs.QEPCTL.bit.IEL= 1;//Position counter is latched on the rising event of index signal

    EQep1Regs.QEPCTL.bit.QCLM=1;//1;//Latch on unit time out; Positon couter, capture timer, capture period register
    EQep1Regs.QUPRD= 4000;//0x007E8480; //0x001E8480;        // Unit time out period for 10ms

    EQep1Regs.QPOSMAX=90000;      // Maximum Value of position Counter #4000
   // EQep1Regs.QPOSMAX= 100;      // Maximum Value of position Counter #4000

    EQep1Regs.QEPCTL.bit.WDE=0;//Disable unit timer


    EQep1Regs.QDECCTL.bit.QSRC=00;//Quadrature count mode
    EQep1Regs.QDECCTL.bit.XCR=1;// Count the raising edges only

    EQep1Regs.QCAPCTL.bit.CEN=1;//Enable the Capture moduele
    EQep1Regs.QCAPCTL.bit.UPPS= 0;//9;//Unit position event pre-scalar
    EQep1Regs.QCAPCTL.bit.CCPS=7;//Capture timer clock pre-scalar
    EQep1Regs.QEPCTL.bit.QPEN=1;//Enable the eQEP position counter
    EQep1Regs.QEINT.bit.UTO = 1;//Unit time out interrupt enable
    EQep1Regs.QEINT.bit.PCO=1;
    EQep1Regs.QEINT.bit.PCU=1;
    EQep1Regs.QCLR.bit.UTO=1;//Clear UTO Flag
    EQep1Regs.QEPCTL.bit.UTE=1; // Disable unit timer

    EQep1Regs.QCLR.bit.PCO=0;
    EQep1Regs.QCLR.bit.PCU=0;
    EDIS;
}
__interrupt void pwmISR(void)
{
    EALLOW;

    EPwm1Regs.ETCLR.bit.INT=01;//clear the interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK3=01;
    EDIS;
}
__interrupt void pwm2ISR(void)
{
    EALLOW;

    EPwm2Regs.ETCLR.bit.INT=01;//clear the interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK3=01;
    EDIS;
}
__interrupt void pwm3ISR(void)
{
    EALLOW;

    EPwm3Regs.ETCLR.bit.INT=01;//clear the interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK3=01;
    EDIS;
}
__interrupt void pwm4ISR(void)
{
    EALLOW;

    EPwm4Regs.ETCLR.bit.INT=01;//clear the interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK3=01;
    EDIS;
}
__interrupt void EQEPISR(void)
{
    if(i++==100) i=0;
   COUNTER_VALUE[i] = EQep1Regs.QPOSLAT;
    EQep1Regs.QCLR.bit.PCO=1;
    EQep1Regs.QCLR.bit.PCU=1;
    EQep1Regs.QCLR.bit.SEL=1;
    EQep1Regs.QCLR.bit.QDC=1;
    EQep1Regs.QCLR.bit.UTO=1;
    EQep1Regs.QCLR.bit.PCE=1;
    EQep1Regs.QEPSTS.bit.UPEVNT=1;
    PieCtrlRegs.PIEACK.bit.ACK5=01;
}
