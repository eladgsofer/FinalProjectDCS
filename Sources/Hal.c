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
		
		if ((state == Script_Mode_3) & (files_num >= 1)) { 
			scroll_pushed = 1;
		}
		//Debounce or using PFE field
		while(TFC_PUSH_BUTTON_0_PRESSED)	// wait of release the button
		for(i=50000 ; i>0 ; i--); //delay, button debounce
		
		PORTD_ISFR |= TFC_PUSH_BUTT0N0_LOC; // clear interrupt flag bit of PTD7
		
	}
	
	if (PORTD_ISFR & SW6_POS){  //PTD6 - Move between files in LCD
		
		if ((state == Script_Mode_3) & (files_num >= 2)){
			start_script = 1;
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

//ToDo: assure we need only DMA0
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

void dma_file_trans(void)
{
	DMA_DAR0 = (uint32_t)hd_file_Ptr[index_last];       		// destination
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(file_size[index_last]);      // number of bytes to transfer
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; 				// Enable DMA channel 
	disable_irq(INT_UART0-16);               			    // Disable UART0 interrupt
	UART0_C5 |= UART0_C5_RDMAE_MASK;          				// Enable DMA request for UART0 receiver
	UARTprintf(UART0_BASE_PTR,"ack\n");
}
//-----------------------------------------------------------------
// TPM2_C1 = Interrupt Service Routine
//-----------------------------------------------------------------
void FTM2_IRQHandler(){
	
	static int rising_edge = 1;
	static int sample_sum = 0;
	int cntr_snap;
	
	
	if(TPM2_C1SC&TPM_CnSC_CHF_MASK)		//if channel flag raised
	{
		cntr_snap = TPM2_C1V;			//capture TPM2_C1 counter
		if(rising_edge)
		{
			cntr_start = cntr_snap;		//save TPM2_C1 counter value on rising edge
		}
		else
		{	
			cntr_end = cntr_snap;			//save TPM2_C1 counter value on falling edge and calculate delta
			range = (cntr_end - cntr_start)&0xFFFF;			//calculate range (delta counter)
			
			sample_sum += range;
			
			samp_cnt = (samp_cnt + 1)%8;	//samples counter
			
			//calculate average when got 8 samples
			if( samp_cnt == 0 )
			{
				distance_avg = sample_sum/8;
				sample_sum = 0;
				sample_ready = 1;
				enable_sensor(FALSE);
			}
		}
		
		rising_edge = (rising_edge + 1)%2;
	}
	
	
	TPM2_C1SC |= TPM_CnSC_CHF_MASK; 			//clean interrupt flag
}

//---------------------------------------------------------------
//		Sensor HAL
//---------------------------------------------------------------
void enable_sensor(int enable){
	if (enable){
		samp_cnt = 0;
		StartTPMx(SENSOR_ECHO, TRUE);
		StartTPMx(SENSOR_TRIG, TRUE);
	} else {
		StartTPMx(SENSOR_ECHO, FALSE);
		StartTPMx(SENSOR_TRIG, FALSE);
	}
}
//-------------------------------------
//*********Commands********************
//-------------------------------------
//-----------------------------------------------------------------
//  RGB Serial Show function
//-----------------------------------------------------------------
void blink_rgb(int x){
	int num_of_blinks;
	
	num_of_blinks = x;
	
	while(num_of_blinks > 0)
	{
		RED_LED_ON;
		//ToDo: add small delay
		RED_LED_OFF;
		//ToDo: add delay d
		GREEN_LED_ON;
		//ToDo: add small delay
		GREEN_LED_OFF;
		//ToDo: add delay d
		BLUE_LED_ON;
		//ToDo: add small delay
		BLUE_LED_OFF;
		//ToDo: add delay d
		num_of_blinks--;
	}
}

void lcd_count_up(int x){
	int repeat_num, show_num;
		
	repeat_num = x;
	
	while(repeat_num > 0)
	{
		show_num = 0;
		while(show_num <= 10)
		{
			lcd_clear();
			lcd_puts('0' + show_num);
			//ToDo: add delay d
			show_num++;
		}
		repeat_num--;
	}
	
}

void lcd_count_down(int x){
	int repeat_num, show_num;
		
	repeat_num = x;
	
	while(repeat_num > 0)
	{
		show_num = 10;
		while(show_num >= 0)
		{
			lcd_clear();
			lcd_puts('0' + show_num);
			//ToDo: add delay d
			show_num++;
		}
		repeat_num--;
	}
	
}

void set_delay(int d){
	delay = d;
}

void clear_all_leds(void){
	RED_LED_OFF;
	GREEN_LED_OFF;
	BLUE_LED_OFF;
}

void servo_deg(int p){
	//ToDo: add function - use elad's
}

void servo_scan(int l, int r){
	//ToDo: add function - use elad's (scan between l and r)
}

