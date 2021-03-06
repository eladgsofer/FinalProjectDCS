#include "TFC.h"


//-----------------------------------------------------------------
//  PORTD Input interrupt ISR
//-----------------------------------------------------------------
void PORTD_IRQHandler(void){
	volatile unsigned int i;
	
	// check that the interrupt was for switch
	if (PORTD_ISFR & SW7_POS) { //PTD7 - Choosing file
		
		if ((state == Script_Mode_3) & (files_num >= 1)) { 
			scroll_pushed = 1;
		}
		//Debounce or using PFE field
		while(TFC_PUSH_BUTTON_0_PRESSED)	// wait of release the button
		for(i=50000 ; i>0 ; i--); //delay, button debounce
		
		PORTD_ISFR |= TFC_PUSH_BUTT0N0_LOC; // clear interrupt flag bit of PTD7
		
	}
	
	if (PORTD_ISFR & SW6_POS){  //PTD6 - Move between files in LCD
		
		if (state == Script_Mode_3){
			start_script = 1;
		}
		
		//Debounce or using PFE field
		while(TFC_PUSH_BUTTON_1_PRESSED);// wait of release the button
		for(i=50000 ; i>0 ; i--); //delay, button debounce
		
		PORTD_ISFR |= TFC_PUSH_BUTT0N1_LOC; // clear interrupt flag bit of PTD6  // clear interrupt flag bit of PTD7
		
	}
}



////-----------------------------------------------------------------
//// PIT - ISR = Interrupt Service Routine
////-----------------------------------------------------------------
void PIT_IRQHandler(){
	PIT_TFLG0 = PIT_TFLG_TIF_MASK; //Turn off the Pit 0 Irq flag
	pit_done = 1;
}



//-----------------------------------------------------------------
//  UART0 - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
void UART0_IRQHandler(){
	
	
	uint8_t received_char;
	
	
	if(UART0_S1 & UART_S1_RDRF_MASK){ // RX buffer is full and ready for reading
		
		received_char = UART0_D;
		
		
		if ((received_char & 0x7F) != '\n'){         //insert chars to array until pressing Enter
			PC_msg[char_idx] = received_char & 0x7F;   
			char_idx ++;
		}
		else{
			char_idx = 0;
			if(UART0_S1 & UART_S1_PF_MASK){ // Parity Error
						
				//for (j=1000000; j>0; j--);	  
				
				UARTprintf(UART0_BASE_PTR,"PErr\n"); //send flag to PC so it will resend the data
				
				UART0_S1 |= UART_S1_PF_MASK; //Clear PE Flag
			}
			else
			{
				dataready = 1;
			}
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
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;			// Clear Done Flag
	DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;	    // Disable DMA Channel 0
	
	if ( UART0_S1 & UART_S1_PF_MASK ) // if there was a parity error during the transmition, request to sent the file again
	{
		UART0_S1 |= UART_S1_PF_MASK; //Clear PE Flag
		dma_file_trans();
	}
	else
	{
		UART0_C5 &= ~UART0_C5_RDMAE_MASK; 				// Disabling DMA using UART
		enable_irq(INT_UART0-16);						// Enable UART0 interrupt
		RED_LED_ON;
		int j;
		for (j=1000000; j>0; j--);	                    // Delay
		RED_LED_OFF;                   // Delay
		dma_done = 1;
	}
}

//---------------------------------------------------------------------------------------------------------------------
/*
 * Configures DMA with source and destination.
 * Sends Ack to PC to receive the file.
 */
//---------------------------------------------------------------------------------------------------------------------
void dma_file_trans(void)
{
	DMA_DAR0 = (uint32_t)hd_file_Ptr[index_last];       		// destination
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(file_size[index_last]);      // number of bytes to transfer
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; 				// Enable DMA channel 
	disable_irq(INT_UART0-16);               			    // Disable UART0 interrupt
	UART0_C5 |= UART0_C5_RDMAE_MASK;          				// Enable DMA request for UART0 receiver
	UARTprintf(UART0_BASE_PTR,message_type.FILE_ACK);
}
//-----------------------------------------------------------------
// TPM0_C2 = Interrupt Service Routine
//-----------------------------------------------------------------
void FTM0_IRQHandler(){
	
	static unsigned int rising_edge = 0x1;
	static unsigned int sample_sum = 0x0000;
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
			cntr_end = cntr_snap;			//save TPM0_C2 counter value on falling edge and calculate delta
			range = (cntr_end - cntr_start)&0xFFFF;			//calculate range (delta counter)
			
			sample_sum += range;
			
			samp_cnt = (samp_cnt + 0x1)&0x7;	//samples counter
			
			//calculate average when got 8 samples
			if( samp_cnt == 0x0 )
			{
				distance_avg = sample_sum >> 3; //divide by 8
				sample_sum = 0;
				sample_ready = 1;
				enable_sensor(FALSE);
			}
		}
		
		rising_edge = (rising_edge + 0x1)&0x1;
	}
	
	
	TPM0_C2SC |= TPM_CnSC_CHF_MASK; 			//clean interrupt flag
}

