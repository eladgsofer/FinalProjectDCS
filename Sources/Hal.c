#include "TFC.h"

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


////-----------------------------------------------------------------
//// PIT - ISR = Interrupt Service Routine
////-----------------------------------------------------------------
//void PIT_IRQHandler(){
//}
//-----------------------------------------------------------------
// ADC0 - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
//void ADC0_IRQHandler(){
//	
//}
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



