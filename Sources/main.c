/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


//#include "derivative.h" /* include peripheral declarations */
# include "TFC.h"
# #include "servo.c"

// Declarations of externs
volatile int distance_ready = FALSE;
volatile int signal_taken = FALSE;
volatile unsigned int acc_distance = 0;
volatile unsigned int out_distance = 0;
volatile unsigned int distance = 0;
volatile unsigned int rising_edge = 0;
volatile unsigned int falling_edge = 0;
		
int print_files_menu(int file_index);
void receive_script();
void state_decode();


int main(void){
	
	int print_script_idx;

	char_idx = 0;
	dataready = 0;
	ClockSetup();
	InitGPIO();
	InitPIT();

	InitServo();
	InitSensors();
	lcd_init();
	dma_init();
	
	InitUARTs(9600);
	InitUARTConf();
	
	RGB_LED_OFF;
	lcd_clear();
	
	files_num = 0;
	index_last = -1;
	//last_addr = &files;
	state = IDLE_STATE_0;
	
	while(1){

		// FSM Mode - IDLE_STATE_0, Radar_Detector_1, Telemeter_2, Script_Mode_3, Script_Receive_4

		while (dataready)
		{ 	
			state_decode();
			dataready = 0;
		}

		switch (state)
		{
			case Radar_Detector_1:
				// START scan command - PIT_MCR &= ~PIT_MCR_MDIS_MASK; //Enable the PIT module 
				//sensor's TPM start:
				/*
					TPM2_SC |= TPM_SC_CMOD(1); //Start the TPM2 counter
					TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter
				 */
				break;
				
			case Telemeter_2:
				// START scan command - PIT_MCR &= ~PIT_MCR_MDIS_MASK; //Enable the PIT module 
				//sensor's TPM start:
				/*
					TPM2_SC |= TPM_SC_CMOD(1); //Start the TPM2 counter
					TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter
				 */
				break;
				
			case Script_Mode_3:
				print_script_idx = index_last;
				while(!done_script)
				{
					print_script_idx = print_files_menu(print_script_idx);
					//ToDo: add function that waits for button push or exit from mode
				}
				break;
				
			case Script_Receive_4:
				//---------------------------------------------------------------------------------------------------------------------
				// Script Mode - Receive Files from PC
				//---------------------------------------------------------------------------------------------------------------------
				receive_script();
				break;
		}
			
	} // End of while(1)
	return 0;
}

//Modified
int print_files_menu(int file_idx){
	int j;
	char* temp_ptr;
	char str_size[5];
	int row = 0;
	int i = file_idx; //index_last;
	int print_num;
	
	lcd_clear();
	for (j=10000; j>0; j--);	 	   // Delay
	do{
		temp_ptr = file_name_Ptr[i];
		
		//Print file name using it's pointer 
		lcd_puts(temp_ptr);
		
		//Space
		lcd_cursor_right();					  
				
		//Print file's size 
		print_num = file_size[i];
		sprintf(str_size, "%d", print_num);
		lcd_puts(str_size);
		memset(str_size,0,5); 
		
		//Print 'B'
		lcd_data('B');
		
		if ( row == 0 )
		{
			lcd_new_line();        	      //second line
		}
		
		i = (i == index_first) ? index_last : ((i - 1)%20);
			
		row += 1;
	}while ((files_num > 1) && ( row < 2 ));	//Prints only 2 rows, or 1 in case it's the last file
	
	return (file_idx == index_first) ? index_last : ((file_idx - 1)%20);
}

void receive_script(void){
		int i = 8;
		int str_size = 0;		// count size of file
		int cont_flag, index;
		char* file_name_addr;
		
		lcd_clear();
		
		//calc current index
		index = (index_last + 1) % 3;
		if (files_num != 3) 
		{
			files_num += 1;
		}
		
		//calculate file's size and save in file_size array 
		while (PC_msg[i] != ',')
		{
			str_size = str_size*10 + (PC_msg[i] - '0');
			i++;
		}
		file_size[index] = str_size;
		i++;
		
		//Calculate start address
		file_name_addr = hd_file_Ptr[index_last] + file_size[index_last] + 1;
		file_name_Ptr[index] = file_name_addr;
		
		//Save file's name
		cont_flag = 1;
		while (cont_flag){
			*file_name_addr++ = PC_msg[i++];
			if(i > 10)
			{
				if((PC_msg[i-4] == '.') & (PC_msg[i-3] == 't') & (PC_msg[i-2] == 'x') & (PC_msg[i-1] == 't'))
					cont_flag = 0;
			}
		}
		*file_name_addr++ = '\0';
		
		memset(PC_msg,0,40);                   //memset - clears the array
		
		hd_file_Ptr[index] = file_name_addr;
		
		*(hd_file_Ptr[index] + str_size) = '\0';
		
		index_last = index;
		
		//transfer file using DMA
		DMA_DAR0 = (uint32_t)hd_file_Ptr[index];       			// destination
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(file_size[index]);       // number of bytes to transfer
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; 				// Enable DMA channel 
		disable_irq(INT_UART0-16);               			    // Disable UART0 interrupt
		UART0_C5 |= UART0_C5_RDMAE_MASK;          				// Enable DMA request for UART0 receiver
		UARTprintf(UART0_BASE_PTR,"ack\n");  
}


void state_decode(){
	if (strncmp(PC_msg, "RScript", 7) == 0) 
	{
		state = Script_Receive_4;
	}
	else if(strncmp(PC_msg, "RadDec", 6) == 0)
	{
		state = Radar_Detector_1;
	}
	else if(strncmp(PC_msg, "Tele", 4) == 0)
	{
		state = Telemeter_2;
	}
	else if(strncmp(PC_msg, "ScriptM", 7) == 0)
	{
		state = Script_Mode_3;
	}
	else
	{
		state = IDLE_STATE_0;
	}
	
	if(state != Script_Receive_4)
		memset(PC_msg,0,40);                   //memset - clears the array
}
