/*
 * PIT.c
 *
 *  Created on: Sep 13, 2021
 *      Author: katri
 */
#include "TFC.h"
#include "mcg.h"
#include "servo.h"

//-----------------------------------------------------------------
// PIT - Initialisation
//-----------------------------------------------------------------
void InitPIT(){
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable the Clock to the PIT Modules
	// Timer 0
	PIT_LDVAL0 = MODULO_REG_15HZ; // setup timer 0 for 15hz counting period
	//PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; //enable PIT0 and its interrupt
	PIT_MCR |= PIT_MCR_FRZ_MASK; // stop the pit when in debug mode
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	
	enable_irq(INT_PIT-16); //  //Enable PIT IRQ on the NVIC
	set_irq_priority(INT_PIT-16,0);  // Interrupt priority = 0 = max
}
//------------------------------------------------------------------
// PIT Config
//------------------------------------------------------------------
void set_PIT_max_val(int ms)
{
	unsigned int timer_val = ms*24000; //calc timer start value
	PIT_LDVAL0 = timer_val;
}

void PIT_enable(int start)
{
	if(start)
	{
		PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	}
	else if(!start)
	{
		PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
	}
}


