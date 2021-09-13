/*
 * main_functions.c
 *
 *  Created on: Sep 6, 2021
 *      Author: katri
 */
#include "TFC.h"


//---------------------------------------------------------------------------------------------------------------------
// Application Init
//---------------------------------------------------------------------------------------------------------------------
void InitApp(void)
{
	//Init Flags
	char_idx = 0;
	dataready = 0;
	
	//Init Board
	InitGPIO();
	InitPIT();
	InitServo();
	InitSensors();
	lcd_init();
	dma_init();
	InitUARTs(9600);
	
	//Init Visual
	RGB_LED_OFF;
	lcd_clear();
	
	//Init Global Vars
	files_num = 0;
	index_last = -1;
	samp_cnt = 0;
	delay = DELAY_DEF;
	state = IDLE_STATE_0;
	
	 strcpy( message_type.FILE_ACK, "Fack\n");
	 strcpy( message_type.CONN_ACK, "Cack\n");
	 strcpy( message_type.GUI_CLEAR, "Gclr\n");
	 strcpy( message_type.SCRIPT_DONE, "fnsc\n");
	
}

//--------------------------------------------------------------------------------------------------------------------
// Exit State
//--------------------------------------------------------------------------------------------------------------------
exit_state()
{
	//Clear LCD
	lcd_clear();
	
	//Clear UART messages from PC and ready to accept new once
	dataready = 0;
	memset(PC_msg,0,40);
	
	//Return Servo to starting point
	WriteServo(MIN_DEG);
	
	
	//Enter Idle Mode
	state = IDLE_STATE_0;
}
//------------------------------------------------------------------------------------------------------------------
//           Scan
//------------------------------------------------------------------------------------------------------------------
void rad_detect_sys(){
	int exit = 0;
	int degree = MIN_DEG;

	lcd_puts("Scanning");
	
	while(1){

		if (degree> MAX_DEG)
			degree = MIN_DEG;
		
		while( degree <= MAX_DEG ){
			
			servo_dist_in_deg(degree);
			
			degree += DEG_DIFF;
			
			Delay_Ms(50);
			
			//Check if PC exit Radar
			if (dataready)
			{
				if(strncmp(PC_msg, "Exit", 4) == 0)
				{
					exit_state();
					exit = 1;
					
					//Exit state
					break;
				}
			}
		}
		
		if(exit)
		{
			break;
		}
	}
}


//------------------------------------------------------------------------------------------------------------------
//   Telemetry
//------------------------------------------------------------------------------------------------------------------
void telemeter(void){
	
	char str[16] = {0};
	int degree;
	
	sscanf(PC_msg,"Tele%d", &degree);
	memset(PC_msg,0,40);
	
	lcd_puts("Telemetry");
	
	WriteServo(degree);
	
	while(1){
		enable_sensor(TRUE);
		// wait until sample ready
		while(!sample_ready);
		sample_ready = 0;
		
		sprintf(str,"tele%4X\n",distance_avg);
		UARTprintf(UART0_BASE_PTR,str);
		
		Delay_Ms(50);
	
		//Check if PC exit Telemeter
		if (dataready)
		{
			if(strncmp(PC_msg, "Exit", 4) == 0)
			{
				exit_state();
				
				//Exit state
				break;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Command Parser
//---------------------------------------------------------------------------------------------------------------------
int commandsParser(int fileIndex) {
    char leftDegree[3], rightDegree[3],  fullOperand[10];
    int operandVal =0, leftAngle, rightAngle, opcode;
    char* char_addr;
    int i = 0;
    char ch;
    char token[7];
    
    // loop through the scriptData to extract all other tokens
    char_addr = hd_file_Ptr[fileIndex];
    
    ch = (*char_addr) & 0x7F;
    while( ch != '\0' )
    {
    	i = 0;
    	ch = (*char_addr++) & 0x7F;
    	while(ch != '\n' && ch != '\0' )
    	{
    		token[i++] = ch;
    		ch = (*char_addr++) & 0x7F;
    	}
    	token[i] = '\0';
    	
    	// Extract opcode and operand
		sscanf(token, "%2d%s", &opcode, fullOperand);
		
		// convert Hex string to int
		operandVal = (int)strtol(fullOperand, NULL, 16);

		switch(opcode)
		{

			case 1  :
				blink_rgb(operandVal);
				break;
			case 2  :
				lcd_count_up(operandVal);
				break;
			case 3:
				lcd_count_down(operandVal);
				break;
			case 4:
				set_delay(operandVal);
				break;
			case 5:
				clear_all_leds();
				break;
			case 6:
				servo_deg(operandVal);
				break;
			case 7:
				// Extract scanning range
				sscanf(fullOperand, "%2c%2c", leftDegree, rightDegree);
				leftAngle = (int)strtol(leftDegree, NULL, 16);
				rightAngle = (int)strtol(rightDegree, NULL, 16);
				servo_scan(leftAngle, rightAngle);
				break;
			case 8:
				clear_all_leds();
				set_delay(DELAY_DEF); //set delay default
				UARTprintf(UART0_BASE_PTR,message_type.SCRIPT_DONE);
				exit_state();
				break;
				/* you can have any number of case statements */
			default : /* Optional */
				break;
		}
		if ( opcode == 7 || opcode == 6 )
			UARTprintf(UART0_BASE_PTR,message_type.GUI_CLEAR);
    }
    
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------
// Set UART Configurations
//---------------------------------------------------------------------------------------------------------------------
void set_uart_configurations()
{
	int i,j;
	
	i = 17;
	
	UARTprintf(UART0_BASE_PTR,message_type.CONN_ACK);
	for (j=10000; j>0; j--);
	
	InitUARTConf(PC_msg[i], PC_msg[i+1], PC_msg[i+2]);
	exit_state();
}

//---------------------------------------------------------------------------------------------------------------------
// Script Mode - scroll and select script
//---------------------------------------------------------------------------------------------------------------------
void script_mode(void)
{
	int exit = 0;
	
	while( state == Script_Mode_3 )
	{
		next_script_idx = index_last;
		start_script = scroll_pushed = 0;
		while(!start_script)
		{
			//Check if PC exit Script Mode
			if(dataready)
			{
				if(strncmp(PC_msg, "Exit", 4) == 0)
				{
					exit_state();
					
					//Exit state
					exit = 1;
					break;
				}
			}
			
			print_script_idx = next_script_idx;
			next_script_idx	= print_files_menu(print_script_idx);
			while(!(scroll_pushed || start_script || dataready));
			scroll_pushed = 0;
		}
		
		lcd_clear();
		
		if(exit)
		{
			break;
		}
		
		commandsParser(print_script_idx);
	}	
}


//---------------------------------------------------------------------------------------------------------------------
// Script Mode - Receive Files from PC
//---------------------------------------------------------------------------------------------------------------------
void script_receive_flow(void)
{
	dma_done = 0;

	receive_script();

	while(!dma_done);
	
	commandsParser(index_last);
	
	exit_state();
}

int print_files_menu(int file_idx){
	int j;
	char* temp_ptr;
	char str_size[5];
	int row = 0;
	int next_idx, i_next, i = file_idx; //index_last;
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
		
		if( i > 0 )
			i_next = i - 1;
		else
			i_next = 2;
		
		i = ((files_num < 3) && (i == 0)) ? index_last : i_next;
			
		row += 1;
	}while ((files_num > 1) && ( row < 2 ));	//Prints only 2 rows, or 1 in case it's the last file
	
	if( file_idx > 0 )
		next_idx = file_idx - 1;
	else
		next_idx = 2;
	
	return ((files_num < 3) && (file_idx == 0)) ? index_last : next_idx;
}


//---------------------------------------------------------------------------------------------------------------------
// Other Functions
//---------------------------------------------------------------------------------------------------------------------
void receive_script(void){
	int i = 8;
	int str_size = 0;		// count size of file
	int cont_flag, index;
	char* file_name_addr;
	
	//calc current index
	index = index_last + 1;
	if ( index == 3 )
	{
		index = 0;
	}
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
	if( index_last == -1)
	{
		file_name_addr = &files;
	}
	else
	{
		file_name_addr = hd_file_Ptr[index_last] + file_size[index_last] + 1;
	}
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
	
	dma_file_trans();  
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
	else if (strncmp(PC_msg,"ConnectionParams", 16) == 0)
	{
		state = UART_Configuration_5;
	}
	else
	{
		state = IDLE_STATE_0;
	}
	
	if(state != Script_Receive_4 && state != UART_Configuration_5 && state != Telemeter_2)
		memset(PC_msg,0,40);                   //memset - clears the array
}


