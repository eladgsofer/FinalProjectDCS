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
		
		if (state == Script_Mode_3){
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
	pit_done = 1;
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
	dma_done = 1;
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
	dma_done = 1;
}

void dma_file_trans(void)
{
	DMA_DAR0 = (uint32_t)hd_file_Ptr[index_last];       		// destination
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(file_size[index_last]);      // number of bytes to transfer
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; 				// Enable DMA channel 
	disable_irq(INT_UART0-16);               			    // Disable UART0 interrupt
	UART0_C5 |= UART0_C5_RDMAE_MASK;          				// Enable DMA request for UART0 receiver
	UARTprintf(UART0_BASE_PTR,"Fack\n");
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
		DelayMs(10000); //ToDo: change to PIT
		RED_LED_OFF;
		DelayMs(delay*10000);
		GREEN_LED_ON;
		DelayMs(10000);
		GREEN_LED_OFF;
		DelayMs(delay*10000);
		BLUE_LED_ON;
		DelayMs(1000);
		BLUE_LED_OFF;
		DelayMs(delay*10000);
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
			if(show_num == 10)
			{
				lcd_puts("10");
			}
			else
			{
				lcd_data('0' + show_num);
			}
			DelayMs(delay*10000); //ToDo: add delay d with PIT
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
			if(show_num == 10)
			{
				lcd_puts("10");
			}
			else
			{
				lcd_data('0' + show_num);
			}
			DelayMs(delay*10000); //ToDo: add delay d with PIT
			show_num--;
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

void servo_deg(int degree){
/*	char msg[20] = {0};
	int i = 0;
	WriteServo(degree);
	enable_sensor(TRUE);
	for(i = 0 ; i < DIST_AVG_SIZE + 1; i++){
		distance_ready = FALSE;
		while(!distance_ready);
	}
	
	if (distance_ready){
		build_scan_msg(msg,out_distance,degree);
		send2pc("Sc",msg);
		Print("Telemetry");
		distance_ready = FALSE;
	}
	enable_sensor(FALSE);*/
}
// 07
void servo_scan(int left_angle,int right_angle){
/*	int angle = left_angle;
	char msg[20] = {0};
	WriteServo(left_angle);
	enable_sensor(TRUE);
	while(angle<right_angle){
		while(!distance_ready){
					WaitDelay(10);
		}
		if (distance_ready){
			build_scan_msg(msg,out_distance,angle);
			send2pc("Sc",msg);
			Print("Scanning");
			distance_ready = FALSE;
		}
		angle+=SERVO_DEG_CHANGE;
		WriteServo(angle);

	}
	enable_sensor(FALSE);*/
}

//----------------------------------------------------------------------------------
// Delay for functions
//----------------------------------------------------------------------------------
void Delay_d(void){
	// set pit delay to "delay"*10ms
	set_PIT_max_val(delay*10);
	
	// start pit
	pit_done = 0;
	PIT_enable(1);
	while (!pit_done){ 
		wait(); // wait for pit interrupt
	}
	// shut down pit
	PIT_enable(0);
}

void Delay_Ms(int ms){
	// set pit delay to "ms" ms
	set_PIT_max_val(ms);
	
	// start pit
	pit_done = 0;
	PIT_enable(1);
	while (!pit_done){ 
		wait(); // wait for pit interrupt
	}
	// shut down pit
	PIT_enable(0);
}
