#include "TFC.h"

#define MOTOR_MUDULO_REGISTER  9375 // PWM frequency of 40Hz = 24Mhz/64x9375

//-----------------------------------------------------------------
//  PORTD Input interrupt ISR
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//  PORTD - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
void PORTD_IRQHandler(void){
	volatile unsigned int i;
	
	// check that the interrupt was for switch
	if (PORTD_ISFR & SW7_POS) { //PTD7 - Choosing file
		
		if ((state == FILE_TRANS_1) & (files_num >= 1)) { 
			
			rfile_mode ^= 0x01;	//Toggle - first press shows file, second sends
			if (rfile_mode == 0)
			{
				print_file(curr_index);
			}
			else 
			{
				file_to_send_idx = curr_index;
				send_file();	
			}
		}
		//Debounce or using PFE field
		while(TFC_PUSH_BUTTON_0_PRESSED)	// wait of release the button
		for(i=50000 ; i>0 ; i--); //delay, button debounce
		
		PORTD_ISFR |= TFC_PUSH_BUTT0N0_LOC; // clear interrupt flag bit of PTD7
		
	}
	
	if (PORTD_ISFR & SW6_POS){  //PTD6 - Move between files in LCD
		
		if ((state == FILE_TRANS_1) & (files_num >= 2)){
			curr_index = next_index;
			next_index = print_files_menu(curr_index);
		}
		
		//Debounce or using PFE field
		while(!(GPIOD_PDIR & SW6_POS) );// wait of release the button
		for(i=30000 ; i>0 ; i--); //delay, button debounce
		PORTD_ISFR |= TFC_PUSH_BUTT0N1_LOC; // clear interrupt flag bit of PTD6  // clear interrupt flag bit of PTD7
		
	}
}



//-----------------------------------------------------------------
// ADC0 - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
//void ADC0_IRQHandler(){
//	
//}


////-----------------------------------------------------------------
//// PIT - ISR = Interrupt Service Routine
////-----------------------------------------------------------------
void PIT_IRQHandler(){
	PIT_TFLG0 = PIT_TFLG_TIF_MASK; //Turn off the Pit 0 Irq flag
	setServoAtDegree();
}

void setServoAtDegree()
{
	scanDegree+=1;
	scanDegree%=180;
	float T_on = 0.6 + scanDegree/180.0 * (2.5-0.6);
	int deg_cnt = T_on/25.0*MOTOR_MUDULO_REGISTER;

	TPM0_SC &= ~TPM_SC_CMOD(1); //Stop the TPM0 counter
	TPM0_C0V = deg_cnt;
	TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter	 
	if (scanDegree==0)
		TPM0_SC &= ~TPM_SC_CMOD(1); //Turn off the TPM0 counter
}

//-----------------------------------------------------------------
//  UART0 - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
void UART0_IRQHandler(){
	
	
	uint8_t received_char;
		
	if(UART0_S1 & UART_S1_RDRF_MASK){ // RX buffer is full and ready for reading
		
		received_char = UART0_D;
		if (received_char != '\n'){         //insert chars to array until pressing Enter
			PC_msg[char_idx] = received_char;   
			char_idx ++;
		}
		else{
			char_idx = 0;
			dataready = 1;
		}	
	}
}
//-----------------------------------------------------------------
//  		DMA
//-----------------------------------------------------------------
/*
 * Handles DMA0 interrupt
 * Resets the BCR register and clears the DONE flag
 * */
void DMA0_IRQHandler(void)
{
	//disable_irq(INT_DMA0 - 16);
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;			// Clear Done Flag
	DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;	    // Disable DMA Channel 0
	UART0_C5 &= ~UART0_C5_RDMAE_MASK; 				// Disabling DMA using UART
	enable_irq(INT_UART0-16);						// Enable UART0 interrupt
	RED_LED_ON;
	int j;
	for (j=1000000; j>0; j--);	                    // Delay
	RED_LED_OFF;                   // Delay
}
void DMA1_IRQHandler(void)
{
	DMA_DSR_BCR1 |= DMA_DSR_BCR_DONE_MASK;		    // Clear Done Flag
	DMAMUX0_CHCFG1 &= ~DMAMUX_CHCFG_ENBL_MASK;	    // Disable DMA Channel 1
	UART0_C5 &= ~UART0_C5_TDMAE_MASK; 				// Disabling DMA using UART
	enable_irq(INT_UART0-16);						// Enable UART0 interrupt
	RED_LED_ON;
	int j;
	for (j=1000000; j>0; j--);	                    // Delay
	RED_LED_OFF;                // Delay
}

//-----------------------------------------------------------------
// TPM0_C2 = Interrupt Service Routine
//-----------------------------------------------------------------
void FTM0_IRQHandler(){
	
	static int rising_edge = 1;
	int cntr_snap;
	
	
	if(TPM0_C2SC&TPM_CnSC_CHF_MASK)		//if channel flag raised
	{
		cntr_snap = TPM0_C2V;			//capture TPM0_C2 counter
		if(rising_edge)
			{
				cntr_start = cntr_snap;		//save TPM0_C2 counter value on rising edge
			}
			else
			{
				cntr_end = cntr_snap;		//save TPM0_C2 counter value on falling edge and calculate delta
				if(cntr_end > cntr_start)
				{
					range = cntr_end - cntr_start;			//calculate range (delta counter)
				}
				
			}
			
			rising_edge = (rising_edge + 1)%2;
	}
	
	
	TPM0_C2SC |= TPM_CnSC_CHF_MASK; 			//clean interrupt flag
}


