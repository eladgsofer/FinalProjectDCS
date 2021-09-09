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
	char_idx = 0;
	dataready = 0;
	InitGPIO();
	InitPIT();
	InitServo();
	InitSensors();

	lcd_init();
	dma_init();
	
	InitUARTs(9600);
	
	RGB_LED_OFF;
	lcd_clear();
	
	files_num = 0;
	index_last = -1;
	samp_cnt = 0;
	delay = 5;
	state = IDLE_STATE_0;
	UARTprintf(UART0_BASE_PTR,"\n");
}

//////////////////////////////
//           Scan
//////////////////////////////
StateModes rad_detect_sys(){
	int degree = 0;
	//char msg[20] = {0};
	lcd_puts("Scanning");
	servo_scan(MIN_DEG,MAX_DEG);
}
////////////////////////
//   Telemetry
///////////////////////
void telemeter(void){
	char str[16] = {0};
	enable_sensor(TRUE);
	lcd_puts("Telemetry");
	//while(1){
		// wait until sample ready
		while(!sample_ready);
		sample_ready = 0;
		
		sprintf(str,"tele%4X",distance_avg);
		UARTprintf(UART0_BASE_PTR,str);
	
//		if (enterON || stopRadar){
//			enterON = FALSE;
//			enable_sensor(FALSE);
//			Print_two_lines("Telemetry","Stopped");
//			return state;
//		}
		//Delay_Ms(50);
	//}
}

//---------------------------------------------------------------------------------------------------------------------
// Command Parser
//---------------------------------------------------------------------------------------------------------------------
int commandsParser(int fileIndex) {
    //char string[50] = "0102\n041E\n0201\n0302\n05\n0623\n0101\n07143C\n08";
	char* string = hd_file_Ptr[fileIndex];
    char leftDegree[3], rightDegree[3],  fullOperand[10];
    int operandVal =0, leftAngle, rightAngle, opcode;

    // Extract the first token
    char * token = strtok(string, "\n");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        // Extract opcode and operand
        sscanf(token, "%2d%s", &opcode, fullOperand);
        token = strtok(NULL, "\n");
        // convert Hex string to int
        operandVal = (int)strtol(fullOperand, NULL, 16);

        switch(opcode)
        {

            case 1  :
            	blink_rgb(operandVal);
                break;
            case 2  :
            	lcd_count_down(operandVal);
                break;
            case 3:
            	lcd_count_up(operandVal);
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
                wait(); //sleep();
                break;
                /* you can have any number of case statements */
            default : /* Optional */
                break;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------
// Set UART Configurations
//---------------------------------------------------------------------------------------------------------------------
void set_uart_configurations()
{
	int j;
	UARTprintf(UART0_BASE_PTR,"Cack\n");
	for (j=10000; j>0; j--);

	int i,a,b,c;
	i = 0;
	a = 17;
	b = 22;
	c = 26;

	switch (PC_msg[a]){    //Check baud rate
		case '1': b+=1; c+=1; break;
		case '3': b+=1; c+=1; break;
	}

	switch (PC_msg[b]){   //Check parity bit
		case 'N': c+=1 ; break;       // Parity = none
		case 'E': c+=1 ; break;       // Parity = even
	}

	InitUARTConf(PC_msg[a], PC_msg[b], PC_msg[c]);
	memset(PC_msg,0,40);  //memset - clears the array
}

//---------------------------------------------------------------------------------------------------------------------
// Script Mode - scroll and select script
//---------------------------------------------------------------------------------------------------------------------
void script_mode(void)
{
	int exit = 0;
	
	while(1)
	{
		next_script_idx = 0;
		start_script = scroll_pushed = 0;
		while(!start_script)
		{
			print_script_idx = next_script_idx;
			next_script_idx	= print_files_menu(print_script_idx);
			while(!(scroll_pushed || start_script || dataready));
			scroll_pushed = 0;
			
			//Check if PC exit Script Mode
			if(dataready)
			{
				if(strncmp(PC_msg, "SMExit", 6) == 0)
				{
					dataready = 0;
					exit = 1;
					break;
				}
			}
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
}

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
		
		i = (i == 0) ? index_last : ((i - 1)%3);
			
		row += 1;
	}while ((files_num > 1) && ( row < 2 ));	//Prints only 2 rows, or 1 in case it's the last file
	
	return (file_idx == 0) ? index_last : ((file_idx - 1)%3);
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
	if ( index == 4 )
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
	
	if(state != Script_Receive_4 && state != UART_Configuration_5)
		memset(PC_msg,0,40);                   //memset - clears the array
}


