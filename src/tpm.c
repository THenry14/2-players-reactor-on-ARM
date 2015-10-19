#include "tpm.h"
#include "main.h"
#include "functions.h"
#include "lcd.h"

void tpm_init()
{
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); //clock selection

    MCG->C1 |= MCG_C1_IRCLKEN_MASK; //Enable the internal reference clock for use as MCGIRCLK
    MCG->C1 |= MCG_C1_IREFS_MASK; // internal reference clock 

    TPM0->SC &= ~TPM_SC_CPWMS_MASK;

    TPM0->SC |= TPM_SC_PS(6); // prescaler, division 64

    TPM0->CNT = 0x00; //clear counter
    TPM0->MOD = 500; //max count value
    TPM0->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK; //turn on output comparison mode
	
	//NVIC interrupts
    NVIC_SetPriority(TPM0_IRQn, 3);
    NVIC_ClearPendingIRQ(TPM0_IRQn);
    NVIC_EnableIRQ(TPM0_IRQn);

    TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK; //turn on interrupt
    TPM0->SC |= TPM_SC_CMOD(1); //increment every tick of counter' clock
}
//Handler
void TPM0_IRQHandler(){
    if (TPM0->STATUS & TPM_STATUS_CH0F_MASK && !isGameEnded){
				count(&time);
        if(time>3){
					lcd_disp(time); 
				}
				else{
					lcd_disp(99);
				}
			if (!time){
				isCountdownFinished = 1;
			}
        TPM0->STATUS |= TPM_STATUS_CH0F_MASK;
    }
    TPM0->STATUS |= TPM_STATUS_TOF_MASK;
} //at the end cleansing of flags
