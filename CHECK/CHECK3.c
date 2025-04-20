/* TRANSITION IS HAPPENNING BUT NOT SMOOTHLY (17/02/2025)*/
#include "F28x_Project.h"
#include "math.h"
void InitTimer0(void);
void InitTimer0ISR(void);
void gpioInit(void);
void SysControl(void);
void pwm1(void);
void pwm2(void);
void pwm3(void);
void pwm4(void);
void PWM5(void);
void PWM6(void);
void equal(void);
void pwgen(void);
void QEPInit(void);
void BLDCMOTOR();
void NEWBLDCMOTOR();
void Adca_init();
void NEW_CURRENT_WAVEFORMS(void);
void counter(void);
__interrupt void Timer0ISR(void);
__interrupt void pwm1ISR(void);
__interrupt void pwm2ISR(void);
__interrupt void pwm3ISR(void);
__interrupt void pwm4ISR(void);
__interrupt void pwm5ISR(void);
__interrupt void pwm6ISR(void);
__interrupt void UTOISR(void);
__interrupt void adcaISR(void);
long Pre_Value,Curr_Value,Timer_Value, Period_I, Period_A, Period_B,Period_S, Phase_B,Phase_S,latchvalue[300],H1,H2,H3,prd,a;
long int pos, pos2, pos3;
double fre, fr, Timer_Period,D4,D5,D6;
long DC,New,Fre_Avg,Period4;
unsigned long New_Prd,CMP4,CMP5,CMP6;
int Ia[0],Ib[0],Ic[0];
int i,j,k,pmsm;
long b;
int PMSM, BLDC;
long FreArray[200];
unsigned long Fre_Sum=0;
long Fre_Average, Timer_Average;
int y, u,freq,frequ;
int A_count,count,theta,theta1,theta2,Prev_Value;
int Flag = 0;
//long Period = 40000;
void main(void)
{
      SysControl();
      gpioInit();
      InitTimer0();
      pwm1();
      pwm2();
      pwm3();
      pwm4();
      PWM5();
      PWM6();
      Adca_init();
      QEPInit();

       EALLOW;
    //disable the global interrupt PG 94
    DINT;
    //enable the PIE module
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    //copy the address PIE vector table
    PieVectTable.TIMER0_INT = &Timer0ISR;//& and function gives the address of the function
    //enable the timer0 interrupt in PIE module
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    //clear the ACK register flag
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;//WRITE 1 TO CLEAR BIT(W1C bit)
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM1_INT = &pwm1ISR;  // directs ISR of EPWM 1
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM2_INT = &pwm2ISR;  // directs ISR of EPWM 1
    PieCtrlRegs.PIEIER3.bit.INTx3= 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM3_INT = &pwm3ISR;  // directs ISR of EPWM 1
    PieCtrlRegs.PIEIER3.bit.INTx4 = 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM4_INT = &pwm4ISR;  // directs ISR of EPWM 1
    PieCtrlRegs.PIEIER3.bit.INTx5 = 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM5_INT = &pwm5ISR;  // directs ISR of EPWM 1
    PieCtrlRegs.PIEIER3.bit.INTx6= 1;    // enable PIE interrupt - EPWM 1
    PieVectTable.EPWM6_INT = &pwm6ISR;
    PieCtrlRegs.PIEACK.bit.ACK3 =1;
    PieVectTable.EQEP1_INT = &UTOISR;//eqep isr enable
    PieCtrlRegs.PIEACK.bit.ACK5=0x01;
    PieCtrlRegs.PIEIER5.bit.INTx1 = 1;    // enable PIE interrupt - Eqep
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;    // ADC ISR
    PieVectTable.ADCA1_INT = &adcaISR;//eqep isr enable

    //Clear interrupt flag
    IFR = 0;
    //enable the interrupt in the CPU
    IER = 0xffff;
    //enable global interrupt
    EINT;
    EDIS;
    while(1){
//        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
//        for(b=0;b<16000000;b++);
//        if(GpioDataRegs.GPATOGGLE.bit.GPIO31 == 1) GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
          equal();
          pwgen();
//          A_count=GpioDataRegs.GPADAT.bit.GPIO2;
//          counter();
//          if((j+=1)==200) j=0;
//              latchvalue[j] = EQep1Regs.QPOSSLAT; // Read the position/counter value into to a variable
//             pos=((latchvalue[j]*180.00)/360);
//             if(pos2>360) pos2 = pos2 - 360;
//             if(pos3>360) pos3 = pos3 - 360;
          BLDCMOTOR();
//          Phase_B = (Period_A*0.25);
//          EPwm3Regs.TBPHS.all = Phase_B;

//          if((j+=1)==200) j=0;
//              latchvalue[j] = EQep1Regs.QPOSSLAT; // Read the position/counter value into to a variable
//             pos=((latchvalue[j])/4);
//             pos2 = pos + 120;
//             pos3 = pos + 240;
//             if(pos2>360) pos2 = pos2 - 360;
//             if(pos3>360) pos3 = pos3 - 360;
             EPwm1Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//             EPwm2Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//             EPwm2Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//             EPwm2Regs.TBPHS.bit.TBPHS = 0;
//             EPwm3Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//             EPwm3Regs.TBPHS.bit.TBPHS = 0;
//             if((fre < 100.0))
//             {
//PMSM = 1;
//BLDCMOTOR();
//             }
//             else if (fre >= 100.0 && fre < 700)
//             {
//PMSM = 0;
//NEWBLDCMOTOR();
//             }

//             if((FreArray[u]<FreArray[u+1])
//             {
//
//             }
//             switch(PMSM)
//             {
//             case 0 :BLDCMOTOR();
//             case 1 :NEWBLDCMOTOR();
//             default :BLDCMOTOR();
//             }
    }
}
void BLDCMOTOR(void)
{
    EPwm4Regs.TBCTL.bit.CLKDIV=4;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV=1;
    EPwm5Regs.TBCTL.bit.CLKDIV=4;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV=1;
    EPwm6Regs.TBCTL.bit.CLKDIV=4;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV=1;

    New_Prd = 4000;
      EPwm4Regs.TBPRD= New_Prd;
      EPwm5Regs.TBPRD= New_Prd;
      EPwm6Regs.TBPRD= New_Prd;

      H3=GpioDataRegs.GPDDAT.bit.GPIO111;
      H2=GpioDataRegs.GPCDAT.bit.GPIO94;
      H1=GpioDataRegs.GPBDAT.bit.GPIO52;

  if((GpioDataRegs.GPBDAT.bit.GPIO52==1)&&(GpioDataRegs.GPCDAT.bit.GPIO94==0)&&(GpioDataRegs.GPDDAT.bit.GPIO111==1))
  {
      EPwm4Regs.CMPA.bit.CMPA=4000;
      EPwm5Regs.CMPB.bit.CMPB=0;//on
      EPwm4Regs.CMPB.bit.CMPB=4010;
      EPwm5Regs.CMPA.bit.CMPA=0;
      EPwm6Regs.CMPA.bit.CMPA=0;
      EPwm6Regs.CMPB.bit.CMPB=4010;

  }
  else if((GpioDataRegs.GPBDAT.bit.GPIO52==1)&&(GpioDataRegs.GPCDAT.bit.GPIO94==0)&&(GpioDataRegs.GPDDAT.bit.GPIO111==0))
  {
      EPwm4Regs.CMPA.bit.CMPA=4000;
      EPwm5Regs.CMPB.bit.CMPB=4010;
      EPwm4Regs.CMPB.bit.CMPB=4010;
      EPwm5Regs.CMPA.bit.CMPA=0;
      EPwm6Regs.CMPA.bit.CMPA=0;
      EPwm6Regs.CMPB.bit.CMPB=0;//on
  }
  else if((GpioDataRegs.GPBDAT.bit.GPIO52==1)&&(GpioDataRegs.GPCDAT.bit.GPIO94==1)&&(GpioDataRegs.GPDDAT.bit.GPIO111==0))
  {
      EPwm4Regs.CMPA.bit.CMPA=0;
      EPwm5Regs.CMPB.bit.CMPB=4010;
      EPwm4Regs.CMPB.bit.CMPB=4010;
      EPwm5Regs.CMPA.bit.CMPA=4010;
      EPwm6Regs.CMPA.bit.CMPA=0;
      EPwm6Regs.CMPB.bit.CMPB=0;//on
  }
  else if((GpioDataRegs.GPBDAT.bit.GPIO52==0)&&(GpioDataRegs.GPCDAT.bit.GPIO94==1)&&(GpioDataRegs.GPDDAT.bit.GPIO111==0))
  {
      EPwm4Regs.CMPA.bit.CMPA=0;
      EPwm5Regs.CMPB.bit.CMPB=4010;
      EPwm4Regs.CMPB.bit.CMPB=0;//on
         EPwm5Regs.CMPA.bit.CMPA=4000;
         EPwm6Regs.CMPA.bit.CMPA=0;
         EPwm6Regs.CMPB.bit.CMPB=4010;
     }
     else if((GpioDataRegs.GPBDAT.bit.GPIO52==0)&&(GpioDataRegs.GPCDAT.bit.GPIO94==1)&&(GpioDataRegs.GPDDAT.bit.GPIO111==1))
     {
         EPwm4Regs.CMPA.bit.CMPA=0;
         EPwm5Regs.CMPB.bit.CMPB=4010;
         EPwm4Regs.CMPB.bit.CMPB=0;//on
         EPwm5Regs.CMPA.bit.CMPA=0;
         EPwm6Regs.CMPA.bit.CMPA=4000;
         EPwm6Regs.CMPB.bit.CMPB=4010;
     }
     else if((GpioDataRegs.GPBDAT.bit.GPIO52==0)&&(GpioDataRegs.GPCDAT.bit.GPIO94==0)&&(GpioDataRegs.GPDDAT.bit.GPIO111==1))
     {
         EPwm4Regs.CMPA.bit.CMPA=0;
         EPwm5Regs.CMPB.bit.CMPB=0;//on
         EPwm4Regs.CMPB.bit.CMPB=4010;
         EPwm5Regs.CMPA.bit.CMPA=0;
         EPwm6Regs.CMPA.bit.CMPA=4000;
         EPwm6Regs.CMPB.bit.CMPB=4010;
     }

     }

void NEWBLDCMOTOR(void){
    EPwm4Regs.TBCTL.bit.CLKDIV=4;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV=1;
    EPwm5Regs.TBCTL.bit.CLKDIV=4;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV=1;
    EPwm6Regs.TBCTL.bit.CLKDIV=4;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV=1;
//    if((j+=1)==200) j=0;
//        latchvalue[j] = EQep1Regs.QPOSSLAT; // Read the position/counter value into to a variable
//       pos=((latchvalue[j])/4);
//       pos2 = pos + 120;
//       pos3 = pos + 240;
//       if(pos2>360) pos2 = pos2 - 360;
//       if(pos3>360) pos3 = pos3 - 360;
//    Period4 = (2500000/(Fre_Average*0.01));       //recalculation of index pulses
    New_Prd=(50000000/frequ);
    EPwm4Regs.TBPRD=New_Prd;
    EPwm5Regs.TBPRD=New_Prd;
    EPwm6Regs.TBPRD=New_Prd;

    EPwm6Regs.CMPA.bit.CMPA=(0.5*New_Prd)*((1+sin((theta*3.14)/180) + 4*3.14/3));
    EPwm5Regs.CMPA.bit.CMPA=(0.5*New_Prd)*(1+sin(((theta1*3.14)/180) + 2*3.14/3));
    EPwm4Regs.CMPA.bit.CMPA=(0.5*New_Prd)*(1+sin(((theta2*3.14)/180)));

    EPwm6Regs.CMPB.bit.CMPB=(0.5*New_Prd)*((1+sin((theta*3.14)/180) + 4*3.14/3));
    EPwm5Regs.CMPB.bit.CMPB=(0.5*New_Prd)*(1+sin(((theta1*3.14)/180) + 2*3.14/3));
    EPwm4Regs.CMPB.bit.CMPB=(0.5*New_Prd)*(1+sin(((theta2*3.14)/180)));
}

void InitTimer0(void)
   {
       EALLOW;
       CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
       CpuTimer0Regs.TCR.bit.TSS = 1;
       CpuTimer0Regs.PRD.all = 3000000;
       CpuTimer0Regs.TPR.all= 128;//162 set the prescale to system clock clock frequency to get the output of 1HHz
       CpuTimer0Regs.TCR.bit.FREE = 0 ;
       CpuTimer0Regs.TCR.bit.TIE = 1;
       CpuTimer0Regs.TCR.bit.TRB = 1;
       CpuTimer0Regs.TCR.bit.TIF = 1;
       CpuTimer0Regs.TCR.bit.TSS = 0;

       EDIS;
   }


void gpioInit(void)
{
    EALLOW;
        GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 00;
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 01;

//        GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 00;
//        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 00;
//        GpioCtrlRegs.GPADIR.bit.GPIO31=1;
//
//        GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 00;
//        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 00;
//        GpioCtrlRegs.GPBDIR.bit.GPIO34=1;

        GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 00;
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 01;
        GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 00;
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 01;

        GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 00;
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 01;
        GpioCtrlRegs.GPADIR.bit.GPIO4=01;//direction as output

        GpioCtrlRegs.GPCGMUX2.bit.GPIO95 = 00;
        GpioCtrlRegs.GPCMUX2.bit.GPIO95 = 00;
        GpioCtrlRegs.GPCDIR.bit.GPIO95 = 0;

        GpioCtrlRegs.GPAGMUX1.bit.GPIO6=00;//0 for gmux & 1 for mux
        GpioCtrlRegs.GPAMUX1.bit.GPIO6=01;// by muxed pins we have to select pwm value
        GpioCtrlRegs.GPAQSEL1.bit.GPIO6=02;
//         GpioCtrlRegs.GPADIR.bit.GPIO6=01;//direction as output
//         GpioCtrlRegs.GPAPUD.bit.GPIO6=01;//GPIO CONFIGURATION

         GpioCtrlRegs.GPAGMUX1.bit.GPIO8=00;//0 for gmux & 1 for mux
              GpioCtrlRegs.GPAMUX1.bit.GPIO8=01;// by muxed pins we have to select pwm value
              GpioCtrlRegs.GPAQSEL1.bit.GPIO8=02;
              GpioCtrlRegs.GPADIR.bit.GPIO8=01;//direction as output
              GpioCtrlRegs.GPAPUD.bit.GPIO8=01;

            GpioCtrlRegs.GPAGMUX1.bit.GPIO10=00;//0 for gmux & 1 for mux
            GpioCtrlRegs.GPAMUX1.bit.GPIO10=01;// by muxed pins we have to select pwm value
            GpioCtrlRegs.GPAQSEL1.bit.GPIO10=02;
           GpioCtrlRegs.GPADIR.bit.GPIO10=01;//direction as output
           GpioCtrlRegs.GPAPUD.bit.GPIO10=01;

           GpioCtrlRegs.GPAGMUX1.bit.GPIO7=00;//0 for gmux & 1 for mux
           GpioCtrlRegs.GPAMUX1.bit.GPIO7=01;// by muxed pins we have to select pwm value
           GpioCtrlRegs.GPAQSEL1.bit.GPIO7=02;
//           GpioCtrlRegs.GPADIR.bit.GPIO7=01;//direction as output
//           GpioCtrlRegs.GPAPUD.bit.GPIO7=01;

           GpioCtrlRegs.GPAGMUX1.bit.GPIO9=00;//0 for gmux & 1 for mux
            GpioCtrlRegs.GPAMUX1.bit.GPIO9=01;// by muxed pins we have to select pwm value
            GpioCtrlRegs.GPAQSEL1.bit.GPIO9=02;
            GpioCtrlRegs.GPADIR.bit.GPIO9=01;//direction as output
            GpioCtrlRegs.GPAPUD.bit.GPIO9=01;

       GpioCtrlRegs.GPAGMUX1.bit.GPIO11=00;//0 for gmux & 1 for mux
       GpioCtrlRegs.GPAMUX1.bit.GPIO11=01;// by muxed pins we have to select pwm value
       GpioCtrlRegs.GPAQSEL1.bit.GPIO11=02;
        GpioCtrlRegs.GPADIR.bit.GPIO11=01;//direction as output
        GpioCtrlRegs.GPAPUD.bit.GPIO11=01;

/************* H1, H2, H3 **************/

        GpioCtrlRegs.GPDGMUX1.bit.GPIO111=00;//0 for gmux & 1 for mux
        GpioCtrlRegs.GPDMUX1.bit.GPIO111=00;// by muxed pins we have to select pwm value
         GpioCtrlRegs.GPDDIR.bit.GPIO111=00;//direction as output
         GpioCtrlRegs.GPDPUD.bit.GPIO111=01;
         GpioDataRegs.GPDCLEAR.bit.GPIO111=01;

         GpioCtrlRegs.GPBGMUX2.bit.GPIO52=00;//0 for gmux & 1 for mux
         GpioCtrlRegs.GPBMUX2.bit.GPIO52=00;// by muxed pins we have to select pwm value
          GpioCtrlRegs.GPBDIR.bit.GPIO52=00;//direction as output
          GpioCtrlRegs.GPBPUD.bit.GPIO52=01;
          GpioCtrlRegs.GPBQSEL2.bit.GPIO52=2;
          GpioDataRegs.GPBCLEAR.bit.GPIO52=01;

          GpioCtrlRegs.GPCGMUX2.bit.GPIO94=00;//0 for gmux & 1 for mux
          GpioCtrlRegs.GPCMUX2.bit.GPIO94=00;// by muxed pins we have to select pwm value
           GpioCtrlRegs.GPCDIR.bit.GPIO94=00;//direction as output
           GpioCtrlRegs.GPCPUD.bit.GPIO94=01;
           GpioDataRegs.GPCCLEAR.bit.GPIO94=01;


       EDIS;

}
void SysControl(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL=00;//PRIMARY OSCILLATOR SELECT
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN=0;//BYPASS PLL
    for(i=0;i<120;i++);//wait for 120 oscialltor cycle
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=0;//binary num
    for(i=0;i<5;i++)
    {
     ClkCfgRegs.SYSPLLCTL1.bit.PLLEN=0;//lock PLL
     ClkCfgRegs.SYSPLLMULT.bit.IMULT=16;//162Mhx PLL raw clock
     ClkCfgRegs.SYSPLLMULT.bit.FMULT=0;//0.25 fractional mult
     while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS !=1);
    }
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=1;//desired+1
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN=1;//switch to PLL
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV=0;//divides by 1, 162Mhz clock
   // ClkCfgRegs.LOSPCP.bit.LSPCLKDIV=1;//80Mhz LSP clock
    EDIS;
}

void pwm1(void){
    EALLOW;
          ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;   //EPWMCLK=PLLSYSCLK/1
          CpuSysRegs.PCLKCR2.bit.EPWM1=1;
          CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
          EPwm1Regs.TBCTL.bit.CLKDIV = 4;          //Divides the EPWMCLK by 1 (3 bits - binary)
           EPwm1Regs.TBCTL.bit.HSPCLKDIV = 1;       //Divides the EPWMCLK by 1 : TBCLK = EPWMCLK / (HSPCLKDIV x CLKDIV)

           EPwm1Regs.TBCTL.bit.CTRMODE = 0;        // 0 for up counter
           EPwm1Regs.TBCTR = 0x0000;              // Clear counter

           EPwm1Regs.CMPB.bit.CMPB = 500;          // EPWM compare value

           EPwm1Regs.AQCTLA.bit.CAU = 1;           // Action qualifier
           EPwm1Regs.AQCTLA.bit.ZRO = 2;           // Action qualifier


           EPwm1Regs.ETSEL.bit.INTEN = 1;          // EPWM 1 interrupt enable
           EPwm1Regs.ETSEL.bit.INTSEL = 1;             // Interrupt when TBCTR = zero
           EPwm1Regs.ETPS.bit.INTPRD = 1;          // Interrupt at period
           EPwm1Regs.ETCLR.bit.INT = 1;            // Clear interrupt
   // Phase is 0
           EPwm1Regs.TBCTL.bit.PRDLD = 0;
           EDIS;
}

void pwm2(void){
    EALLOW;
      ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;   //EPWMCLK=PLLSYSCLK/1
      CpuSysRegs.PCLKCR2.bit.EPWM2=1;
      CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
      EPwm2Regs.TBCTL.bit.CLKDIV = 3;          //Divides the EPWMCLK by 1 (3 bits - binary)
       EPwm2Regs.TBCTL.bit.HSPCLKDIV = 1;       //Divides the EPWMCLK by 1 : TBCLK = EPWMCLK / (HSPCLKDIV x CLKDIV)

       EPwm2Regs.TBCTL.bit.CTRMODE = 0;        // 0 for up counter
       EPwm2Regs.TBCTR = 0x0000;              // Clear counter

       EPwm2Regs.CMPB.bit.CMPB = 500;          // EPWM compare value


       EPwm2Regs.AQCTLA.bit.CAU = 1;           // Action qualifier
       EPwm2Regs.AQCTLA.bit.ZRO = 2;           // Action qualifierm
       EPwm2Regs.AQCTLB.bit.CBU = 1;           // Action qualifier
       EPwm2Regs.AQCTLB.bit.ZRO = 2;           // Action qualifier

       EPwm2Regs.ETSEL.bit.INTEN = 1;          // EPWM 1 interrupt enable
       EPwm2Regs.ETSEL.bit.INTSEL = 1;             // Interrupt when TBCTR = zero
       EPwm2Regs.ETPS.bit.INTPRD = 1;          // Interrupt at period
       EPwm2Regs.ETCLR.bit.INT = 1;            // Clear interrupt

       EPwm2Regs.TBCTL.bit.PRDLD = 0;
       EDIS;
}

void pwm3(void){
    EALLOW;
      ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;   //EPWMCLK=PLLSYSCLK/1
      CpuSysRegs.PCLKCR2.bit.EPWM3=1;
      CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
      EPwm3Regs.TBCTL.bit.CLKDIV = 4;          //Divides the EPWMCLK by 1 (3 bits - binary)
       EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;       //Divides the EPWMCLK by 1 : TBCLK = EPWMCLK / (HSPCLKDIV x CLKDIV)

       EPwm3Regs.TBCTL.bit.CTRMODE = 0;        // 0 for up counter
       EPwm3Regs.TBCTR = 0x0000;              // Clear counter

       EPwm3Regs.CMPB.bit.CMPB = 500;          // EPWM compare value

       EPwm3Regs.AQCTLA.bit.CAU = 1;           // Action qualifier
       EPwm3Regs.AQCTLA.bit.ZRO = 2;           // Action qualifier


       EPwm3Regs.ETSEL.bit.INTEN = 1;          // EPWM 1 interrupt enable
       EPwm3Regs.ETSEL.bit.INTSEL = 1;             // Interrupt when TBCTR = zero
       EPwm3Regs.ETPS.bit.INTPRD = 1;          // Interrupt at period
       EPwm3Regs.ETCLR.bit.INT = 1;            // Clear interrupt
//       EPwm3Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//       EPwm3Regs.TBPHS.bit.TBPHS = 5500;          // Phase is 0
       EPwm3Regs.TBCTL.bit.PRDLD = 0;
       EDIS;
}
void pwm4(void)
{
    EALLOW;
         //EPWM2
         ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
         CpuSysRegs.PCLKCR2.bit.EPWM4=1;
         CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;

  //      EPwm4Regs.TBPRD=4000;
         //double check//
         EPwm4Regs.TBCTR=0x0000;
         EPwm4Regs.TBCTL.bit.CTRMODE=0;
              EPwm4Regs.AQCTLA.bit.CAU=1;//clear
              EPwm4Regs.AQCTLA.bit.ZRO=2;//set
              EPwm4Regs.AQCTLB.bit.CBU=2;//set
              EPwm4Regs.AQCTLB.bit.ZRO=1;//clear
              EPwm4Regs.TBCTL.bit.PHSEN = 1;
              EPwm4Regs.TBPHS.bit.TBPHS= 0;

         EPwm4Regs.ETSEL.bit.INTSEL= 2;
         EPwm4Regs.ETSEL.bit.INTEN=1;
         EPwm4Regs.ETCLR.bit.INT=1;
         EPwm4Regs.ETPS.bit.INTPRD=1;
         EDIS;

    }
void PWM5(void)
{
    EALLOW;
         //EPWM2
         ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
         CpuSysRegs.PCLKCR2.bit.EPWM5=1;
         CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
         EPwm5Regs.TBCTL.bit.CLKDIV=4;
         EPwm5Regs.TBCTL.bit.HSPCLKDIV=1;
  //      EPwm5Regs.TBPRD=4000;
         //double check//
         EPwm5Regs.TBCTR=0x0000;
         EPwm5Regs.TBCTL.bit.CTRMODE=0;
              EPwm5Regs.AQCTLA.bit.CAU=1;//clear
              EPwm5Regs.AQCTLA.bit.ZRO=2;//set
              EPwm5Regs.AQCTLB.bit.CBU=2;//set
              EPwm5Regs.AQCTLB.bit.ZRO=1;//clear
              EPwm5Regs.TBCTL.bit.PHSEN = 1;
              EPwm5Regs.TBPHS.bit.TBPHS= 0;

         EPwm5Regs.ETSEL.bit.INTSEL= 2;
         EPwm5Regs.ETSEL.bit.INTEN=1;
         EPwm5Regs.ETCLR.bit.INT=1;
         EPwm5Regs.ETPS.bit.INTPRD=1;
         EDIS;
}
void PWM6(void)
{
    EALLOW; //EPWM3
           ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=1;
           CpuSysRegs.PCLKCR2.bit.EPWM6=1;
           CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;
           EPwm6Regs.TBCTL.bit.CLKDIV=4;
           EPwm6Regs.TBCTL.bit.HSPCLKDIV=1;
 //          EPwm6Regs.TBPRD=4000;
//           EPwm6Regs.CMPA.bit.CMPA=2000;
//               EPwm6Regs.CMPB.bit.CMPB=2000;
           //double check//
           EPwm6Regs.TBCTR=0x0000;
           EPwm6Regs.TBCTL.bit.CTRMODE=0;
                EPwm6Regs.AQCTLA.bit.CAU=1;//clear
                EPwm6Regs.AQCTLA.bit.ZRO=2;//set
                EPwm6Regs.AQCTLB.bit.CBU=2;//set
                EPwm6Regs.AQCTLB.bit.ZRO=1;//clear
                EPwm6Regs.TBCTL.bit.PHSEN = 1;
                EPwm6Regs.TBPHS.bit.TBPHS= 0;
           EPwm6Regs.ETSEL.bit.INTSEL= 2;
           EPwm6Regs.ETSEL.bit.INTEN=1;
           EPwm6Regs.ETCLR.bit.INT=1;
           EPwm6Regs.ETPS.bit.INTPRD=1;

           EDIS;
}

void equal(void)
{
    Fre_Sum = 0;
    {
    Curr_Value = GpioDataRegs.GPBDAT.bit.GPIO52;
    if((Curr_Value == 1)&(Pre_Value == 0))
    {
        CpuTimer0Regs.TCR.bit.TSS = 0;
        if((Curr_Value == 1)&(Pre_Value == 0))
        {
            Timer_Value = CpuTimer0Regs.TIM.all;
//            fre = ((124100273/CpuTimer0Regs.PRD.all-Timer_Value));//1230769.2308/const
            CpuTimer0Regs.TCR.bit.TRB = 1;
        }

    }
    Pre_Value = Curr_Value;
        }
    if(fre>70.00) fre=0;


    /************************************** AVERAGE FREQUENCY ****************************************************/
        //ARRAY STORAGE
        if((y++) == 49) y=0;
        {
//               if(FreArray[y] != FreArray[y-1])
//               {
//                   FreArray[y+1] = fre;
//               }
//               else if(FreArray[y] == FreArray[y-1])
//               {
//                   FreArray[15] = fre;
//               }
            FreArray[y] = CpuTimer0Regs.PRD.all-Timer_Value;
        }
        //AVERAGE CALCULATION
//           if((a++) == 5) a=0;
        for(a=0;a<50;a++)
        {
//            Fre_Sum = FreArray[0] + FreArray[1] + FreArray[2] + FreArray[3] + FreArray[4] + FreArray[5] + FreArray[6] + FreArray[7] + FreArray[8] + FreArray[9] + FreArray[10] + FreArray[11] + FreArray[12] + FreArray[13] + FreArray[14] + FreArray[15] + FreArray[16] + FreArray[17] + FreArray[18] + FreArray[19] + FreArray[20] + FreArray[21] + FreArray[22] + FreArray[23] + FreArray[24] + FreArray[25] + FreArray[26] + FreArray[27] + FreArray[28] + FreArray[29] + FreArray[30] + FreArray[31] + FreArray[32] + FreArray[33] + FreArray[34] + FreArray[35] + FreArray[36] + FreArray[37] + FreArray[38] + FreArray[39] + FreArray[40] + FreArray[41] + FreArray[42] + FreArray[43] + FreArray[44] + FreArray[45] + FreArray[46] + FreArray[47] + FreArray[48] + FreArray[49] + FreArray[50] + FreArray[51] + FreArray[52] + FreArray[53] + FreArray[54] + FreArray[55] + FreArray[56] + FreArray[57] + FreArray[58] + FreArray[59] + FreArray[60] + FreArray[61] + FreArray[62] + FreArray[63] + FreArray[64] + FreArray[65] + FreArray[66] + FreArray[67] + FreArray[68] + FreArray[69] + FreArray[70] + FreArray[71] + FreArray[72] + FreArray[73] + FreArray[74] + FreArray[75] + FreArray[76] + FreArray[77] + FreArray[78] + FreArray[79] + FreArray[80] + FreArray[81] + FreArray[82] + FreArray[83] + FreArray[84] + FreArray[85] + FreArray[86] + FreArray[87] + FreArray[88] + FreArray[89] + FreArray[90] + FreArray[91] + FreArray[92] + FreArray[93] + FreArray[94] + FreArray[95] + FreArray[96] + FreArray[97] + FreArray[98] + FreArray[99];
//            Fre_Sum = Fre_Sum + FreArray[a];
            Fre_Sum = Fre_Sum + FreArray[0] + FreArray[1] + FreArray[2] + FreArray[3] + FreArray[4] + FreArray[5] + FreArray[6] + FreArray[7] + FreArray[8] + FreArray[9] + FreArray[10] + FreArray[11] + FreArray[12] + FreArray[13] + FreArray[14] + FreArray[15] + FreArray[16] + FreArray[17] + FreArray[18] + FreArray[19] + FreArray[20] + FreArray[21] + FreArray[22] + FreArray[23] + FreArray[24] + FreArray[25] + FreArray[26] + FreArray[27] + FreArray[28] + FreArray[29] + FreArray[30] + FreArray[31] + FreArray[32] + FreArray[33] + FreArray[34] + FreArray[35] + FreArray[36] + FreArray[37] + FreArray[38] + FreArray[39] + FreArray[40] + FreArray[41] + FreArray[42] + FreArray[43] + FreArray[44] + FreArray[45] + FreArray[46] + FreArray[47] + FreArray[48] + FreArray[49];
        }
        Fre_Average = Fre_Sum*0.04;
        fre = ((124100273.00/Fre_Average));//1230769.2308/const
        freq = fre*100;
        frequ = freq*0.1;
//        Timer_Average = Fre_Average & 0xffff1000;
//        Fre_Avg= (Fre_Average*0.01);
}

void counter(void)
{
//    A_count=0;


//  if((count%512)==0)    GpioDataRegs.GPDTOGGLE.bit.GPIO97 = 1;


//if(count%512 == 0) GpioDataRegs.GPDTOGGLE.bit.GPIO97 = 1;

//       GpioDataRegs.GPDCLEAR.bit.GPIO97 = 1;}
//   EPwm1Regs.CMPA.bit.CMPA = 1000*0.5*((1+sin(pi*theta/180)));
}


void pwgen(void)
{
//    Period_I = (25000000/frequ);                       //((80000000/128)/14) = 44342
////    Period_I = 178571/fre;                       //((80000000/128)/14) = 44342
//     EPwm1Regs.TBPRD = (Period_I/20);                 // using as strobe for 8 degree resolution
//     EPwm1Regs.CMPA.bit.CMPA = (Period_I/240);   // EPWM compare value
//
//
//     Period_A = Period_I/90;
//     EPwm2Regs.TBPRD = Period_A;                 // EPWM 2
//     EPwm2Regs.CMPA.bit.CMPA = (Period_A*0.5);   // EPWM compare value
//     EPwm2Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//     EPwm2Regs.TBPHS.bit.TBPHS = 0;          // Phase is 0
//
////     Period_B = Period_I/90;
//     EPwm3Regs.TBPRD = Period_A;                 // EPWM 3
//     EPwm3Regs.CMPA.bit.CMPA = ((Period_A*0.5));   // EPWM compare value
//
//     Phase_B = (Period_A*0.25);
//     EPwm3Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
//     EPwm3Regs.TBPHS.bit.TBPHS = Phase_B;          // Phase is 0

//    void pwgen(void)
//    {
    Period_I = (500000000/freq);    //    Period_I = 178571/fre;                       //((80000000/128)/14) = 44342
         EPwm1Regs.TBPRD = Period_I/20;                 // EPWM 1
         EPwm1Regs.CMPA.bit.CMPA = (Period_I/220);   // EPWM compare value

         Period_A = Period_I/360;
         EPwm2Regs.TBPRD = Period_A;                 // EPWM 2
         EPwm2Regs.CMPA.bit.CMPA = (Period_A*0.5);   // EPWM compare value

         Period_B = Period_I/90;
         EPwm3Regs.TBPRD = Period_B;                 // EPWM 3
         EPwm3Regs.CMPA.bit.CMPA = ((Period_B*0.5));   // EPWM compare value

         Phase_B = (Period_B/4);
//         EPwm3Regs.TBCTL.bit.PHSEN = 1;          // enable phase loading
         EPwm3Regs.TBPHS.bit.TBPHS = Phase_B;          // Phase is 0

//    }

//         A_count=0;
         {
//         A_count=GpioDataRegs.GPADAT.bit.GPIO2;
           if(GpioDataRegs.GPADAT.bit.GPIO2==1 && Prev_Value==0)
           {
               if(count>=360) count=0;
               count = count+1;
        //if((count % 10 == 0) && (count<1024)) count_10 = 1;
        //       else count++;
           }
          Prev_Value = GpioDataRegs.GPADAT.bit.GPIO2;
         }
         if(count%1 == 0)
          {
              theta = count;
              theta1 =count+120;
              if(theta1>=360) theta1 = theta1-360;
              theta2 =count+240;
              if(theta2>=360) theta2 = theta2-360;
          }


}
void QEPInit(void)
{
        EALLOW;
        GpioCtrlRegs.GPAGMUX2.bit.GPIO20=0;//EQEP1A pin Mux for 1A
        GpioCtrlRegs.GPAGMUX2.bit.GPIO21=0;//EQEP1B pin Mux for1B
        GpioCtrlRegs.GPAGMUX2.bit.GPIO22=0;//1S-Strobe
        GpioCtrlRegs.GPDGMUX1.bit.GPIO99=1;//1I-Index
        GpioCtrlRegs.GPAMUX2.bit.GPIO20=1;
        GpioCtrlRegs.GPAMUX2.bit.GPIO21=1;
        GpioCtrlRegs.GPAMUX2.bit.GPIO22=1;
        GpioCtrlRegs.GPDMUX1.bit.GPIO99=1;
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20=2;
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21=2;
        GpioCtrlRegs.GPAQSEL2.bit.GPIO22=2;
        GpioCtrlRegs.GPDQSEL1.bit.GPIO99=2;


        CpuSysRegs.PCLKCR4.bit.EQEP1 = 1;// Enable clock to the QEP module
        //EQep1Regs.QEPCTL.bit.FREE_SOFT=2;//Unaffected by emulation suspend
        EQep1Regs.QEPCTL.bit.FREE_SOFT=0;
        EQep1Regs.QEPCTL.bit.PCRM = 0;//03;Position counter reset on Unit time count event; 00:position counter reset on an index event1
        EQep1Regs.QEPCTL.bit.SEI=0; // Does nothing (Strobe event initialization of position counter
        //EQep1Regs.QEPCTL.bit.IEI=3;//Initialize position counter on falling edge of index event QEPI Event
       // EQep1Regs.QEPCTL.bit.IEI=0;//Do nothing
        EQep1Regs.QPOSINIT=0x0000000;   // position counter initialization
        EQep1Regs.QEPCTL.bit.SWI=1; //Initialize the position counter with the value stored in QPOSINIT
        EQep1Regs.QEPCTL.bit.SEL=2;//Position counter is latched on the rising event of Strobe signal QEPS
        EQep1Regs.QEPCTL.bit.IEL= 0;//
        EQep1Regs.QEPCTL.bit.QCLM=1;//1;//Latch on unit time out; Positon couter, capture timer, capture period register
       // EQep1Regs.QUPRD=5000; //80*EPwm1Regs.TBPRD;        // Unit time out period for 10ms
        EQep1Regs.QUPRD=80000;
        EQep1Regs.QPOSMAX=1440;      // Maximum Value of position Counter #4000

        EQep1Regs.QEPCTL.bit.WDE=0;//Disable unit timer


        EQep1Regs.QDECCTL.bit.QSRC=00;//Quadrature count mode
        EQep1Regs.QDECCTL.bit.XCR=1;// Count the raising edges only
        EQep1Regs.QDECCTL.bit.QSP=0;// Dont invert the Strobe signal
        EQep1Regs.QCAPCTL.bit.CEN=1;//Enable the Capture moduele
        EQep1Regs.QCAPCTL.bit.UPPS= 0;//9;//Unit position event pre-scalar
        EQep1Regs.QCAPCTL.bit.CCPS=7;//Capture timer clock pre-scalar
        EQep1Regs.QEPCTL.bit.QPEN=1;//Enable the eQEP position counter
        EQep1Regs.QEINT.bit.UTO = 0;//Unit time out interrupt disable
        EQep1Regs.QEINT.bit.PCO=1;
        EQep1Regs.QEINT.bit.PCU=1;
        EQep1Regs.QEINT.bit.PCR=1;
        EQep1Regs.QEINT.bit.PCE=1;
        EQep1Regs.QEINT.bit.QDC=1;
        EQep1Regs.QEINT.bit.QPE=1;
        EQep1Regs.QEINT.bit.SEL=1;
        EQep1Regs.QCLR.bit.UTO=1;//Clear UTO Flag
        EQep1Regs.QEPCTL.bit.UTE=0; // disable unit timer

        EQep1Regs.QCLR.bit.PCO=0;
        EQep1Regs.QCLR.bit.PCU=0;
        EDIS;
    }
void Adca_init(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A=01;// enable the clock
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ=01; // enable the power to the adc
  AdcaRegs.ADCCTL2.bit.SIGNALMODE=00;//signal mode selection
  AdcaRegs.ADCCTL2.bit.RESOLUTION=00;// resolution selection
  //vrefhi,vreflo -> external
  AdcaRegs.ADCCTL2.bit.PRESCALE=13; //set the adc frequency
  AdcaRegs.ADCSOC0CTL.bit.CHSEL=02;
  AdcaRegs.ADCSOC1CTL.bit.CHSEL=03;
  AdcaRegs.ADCSOC2CTL.bit.CHSEL=04;
  AdcaRegs.ADCSOC0CTL.bit.ACQPS=64; // for 500ns of sampling time for system clock of 130MHZ
  AdcaRegs.ADCBURSTCTL.bit.BURSTEN=00; //SOC initialization
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL=01;
  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL=01;//1 FOR timer0 triggering
  AdcaRegs.ADCSOC2CTL.bit.TRIGSEL=01;
  AdcaRegs.ADCSOC1CTL.bit.ACQPS=64; // for 500ns of sampling time for system clock of 130MHZ
  AdcaRegs.ADCSOC2CTL.bit.ACQPS=64;
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS=01;//interrupt pulse position EOC\SOC
  AdcaRegs.ADCINTSOCSEL1.bit.SOC0=01;
  AdcaRegs.ADCINTSOCSEL1.bit.SOC1=01;
  AdcaRegs.ADCINTSOCSEL1.bit.SOC2=01;
  AdcaRegs.ADCINTSEL1N2.bit.INT1E=01; //enable the interrupt(timer 0 )
  //AdcaRegs.ADCINTSOCSEL1.bit.SOC0=01; //select the interrupt source SOCX
  AdcaRegs .ADCINTFLGCLR.bit.ADCINT1=01; //clear the interrupt flag
  EDIS;
}

__interrupt void Timer0ISR(void){

    CpuTimer0Regs.TCR.bit.TIF=1;
     PieCtrlRegs.PIEACK.bit.ACK1=1;

}
__interrupt void pwm1ISR(void){
    EPwm1Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
__interrupt void pwm2ISR(void){
    EPwm2Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
__interrupt void pwm3ISR(void){

    EPwm3Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
__interrupt void pwm4ISR(void){
    EPwm4Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
__interrupt void pwm5ISR(void){
    EPwm5Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}
__interrupt void pwm6ISR(void){
    EPwm6Regs.ETCLR.bit.INT = 1;            // Clear interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
__interrupt void adcaISR(void)

{
    if(++k==99)k=0;
    {
    Ia[k]=AdcaResultRegs.ADCRESULT0;
    Ib[k]=AdcaResultRegs.ADCRESULT1;
    Ic[k]=AdcaResultRegs.ADCRESULT2;
    }

AdcaRegs.ADCINTFLGCLR.bit.ADCINT1=01;// clear the interrupt flag
PieCtrlRegs.PIEACK.bit.ACK1 =1;//clear the acknowledge bit
CpuTimer0Regs.TCR.bit.TIF=1;  //as we not selected the timer0 for trigger

}
__interrupt void UTOISR(void)
{

    EQep1Regs.QCLR.bit.SEL=1;
    EQep1Regs.QCLR.bit.UTO=1;//Clear UTO Flag
    EQep1Regs.QCLR.bit.PCO=1;//Clear Overflow Flag
    EQep1Regs.QCLR.bit.PCU=1;//Clear Underflow Flag
    EQep1Regs.QCLR.bit.INT=1; // clear global interrupt bit
    EQep1Regs.QCLR.bit.QDC=1;
    EQep1Regs.QCLR.bit.PCE =1;
    EQep1Regs.QCLR.bit.PHE =1;
    EQep1Regs.QEPSTS.bit.UPEVNT=01;
    PieCtrlRegs.PIEACK.bit.ACK1=01;

}
