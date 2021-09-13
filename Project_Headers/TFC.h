/*
 * TFC.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */

#ifndef TFC_H_
#define TFC_H_

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Derivative.h"
#include "Bsp.h"
#include "LCD.h"
#include "PIT.h"
#include "arm_cm0.h"
#include "UART.h"
#include "Hal.h"
#include "main_functions.h"
#include "servo.h"
#include "Commands.h"

#define DELAY_DEF	50

enum State {IDLE_STATE_0 = 0, Radar_Detector_1 = 1, Telemeter_2 = 2, Script_Mode_3 = 3, Script_Receive_4 = 4, UART_Configuration_5 = 5};
enum State state;


struct Message_Type {
   char  FILE_ACK[6];
   char  CONN_ACK[6];
   char  GUI_CLEAR[6];
   char  SCRIPT_DONE[6];
};

struct Message_Type message_type;


//Global Variables
char PC_msg[40]; 			//Received message from pc
int delay;					// in ms

//Data Base
char* hd_file_Ptr[3];		//Array of Pointers to head of files
char* file_name_Ptr[3];	//Array of Pointers to file names
char files[3000];
int file_size[3];			//Array of integers - file's size
int files_num;				//current number of files
int index_last;				//Index of last file added to array

//Global Flags
int dataready;  		//flag which indicates if data received from UART is ready to be used
int start_script, scroll_pushed;
int dma_done, pit_done;
int sample_ready;

//Global calculation variables
int char_idx;
int scanDegree;
unsigned int cntr_end, cntr_start, range;
unsigned int samp_cnt, distance_avg;


#endif /* TFC_H_ */
