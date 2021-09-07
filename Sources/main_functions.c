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
	ClockSetup();
	InitGPIO();
	InitPIT();

	InitServo();
	InitSensors();
	lcd_init();
	dma_init();
	
	InitUARTConf();
	
	RGB_LED_OFF;
	lcd_clear();
	
	files_num = 0;
	index_last = -1;
	samp_cnt = 0;
	//last_addr = &files;
	state = IDLE_STATE_0;
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
        printf( "%s\n", token ); //printing each token
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
// Script Mode - scroll and select script
//---------------------------------------------------------------------------------------------------------------------
void script_mode(void)
{
	next_script_idx = 0;
	start_script = scroll_pushed = 0;
	while(!start_script)
	{
		print_script_idx = next_script_idx;
		next_script_idx	= print_files_menu(print_script_idx);
		while(!(scroll_pushed || start_script));
	}
	commandsParser(print_script_idx);
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
		
		i = (i == 0) ? index_last : ((i - 1)%20);
			
		row += 1;
	}while ((files_num > 1) && ( row < 2 ));	//Prints only 2 rows, or 1 in case it's the last file
	
	return (file_idx == 0) ? index_last : ((file_idx - 1)%20);
}


//---------------------------------------------------------------------------------------------------------------------
// Other Functions
//---------------------------------------------------------------------------------------------------------------------
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
	else
	{
		state = IDLE_STATE_0;
	}
	
	if(state != Script_Receive_4)
		memset(PC_msg,0,40);                   //memset - clears the array
}

