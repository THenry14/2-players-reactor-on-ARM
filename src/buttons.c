#include "MKL46Z4.h" 
#include "buttons.h"
#include "functions.h"
#include "main.h"
#define SW1_PIN 3 
#define SW3_PIN 12


void buttonsInitialize(void){ 
	//same as tpm to be honest
	SIM->SCGC5 |=  SIM_SCGC5_PORTC_MASK; 		//clocking			
	PORTC->PCR[SW1_PIN] |= PORT_PCR_MUX(1);      //enabling muxes and ports for switches
	PORTC->PCR[SW3_PIN] |= PORT_PCR_MUX(1);
	PORTC->PCR[SW1_PIN] |=  PORT_PCR_PE_MASK |	
	 											  PORT_PCR_PS_MASK;		
	PORTC->PCR[SW1_PIN] |= 	PORT_PCR_IRQC(9);		//on falling edge
	PORTC->PCR[SW3_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
  PORTC->PCR[SW3_PIN] |= PORT_PCR_IRQC(9);
		//nvic interrupts
		NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
    NVIC_SetPriority(PORTC_PORTD_IRQn, 1);			//I Had to set the priority for buttons bigger than for tpm

}
//handler
void PORTC_PORTD_IRQHandler(){
    if (PORTC->PCR[SW1_PIN] & PORT_PCR_ISF_MASK && !isGameEnded) {
        game(0);				
        PORTC->PCR[SW1_PIN] |= PORT_PCR_ISF_MASK;
    }
    if (PORTC->PCR[SW3_PIN] & PORT_PCR_ISF_MASK && !isGameEnded) {
        game(1);				
        PORTC->PCR[SW3_PIN] |= PORT_PCR_ISF_MASK;
    }
}
