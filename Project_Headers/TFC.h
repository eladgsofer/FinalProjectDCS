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
#include "arm_cm0.h"
#include "UART.h"
#include "Hal.h"
#include "main_functions.h"
#include "servo.h"

enum State {IDLE_STATE_0 = 0, Radar_Detector_1 = 1, Telemeter_2 = 2, Script_Mode_3 = 3, Script_Receive_4 = 4, UART_Configuration_5 = 5};
enum State state;


//ToDo: erase unnecessary variables
char* hd_file_Ptr[3];		//Array of Pointers to head of files
char* file_name_Ptr[3];	//Array of Pointers to file names
//char* last_addr;
//char* mem_start_addr, *mem_end_addr;
char files[3000];
int file_size[3];			//Array of integers - file's size
int files_num;				//current number of files
int index_last;				//Index of last file added to array
//int index_first;			//Index of first file added to array
//int next_index;				//Save index into a global variable to be handled in int_handler when scroll button pressed
int curr_index;				//Save index into a global variable to be handled in int_handler when scroll button pressed and file shown
int file_to_send_idx;
char PC_msg[40]; 			//Received message from pc
//char files_names[300];		//Data base contains names of files
int dataready;  		//flag which indicates if data received from UART is ready to be used
int start_script, scroll_pushed;
int dma_done, pit_done;
int char_idx;
int scanDegree;
unsigned int cntr_end, cntr_start, range;
unsigned int samp_cnt, distance_avg;
int sample_ready;


int delay;	// in ms

#endif /* TFC_H_ */
