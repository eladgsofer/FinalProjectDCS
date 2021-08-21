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

enum State {IDLE_STATE_0 = 0, FILE_TRANS_1 = 1};
enum State state;

char* hd_file_Ptr[20];		//Array of Pointers to head of files
char* file_name_Ptr[20];	//Array of Pointers to file names
char* last_addr;
char* mem_start_addr, *mem_end_addr;
char garbage[3912];
char files[10000];
int file_size[20];			//Array of integers - file's size
int files_num;				//current number of files
int index_last;				//Index of last file added to array
int index_first;			//Index of first file added to array
int next_index;				//Save index into a global variable to be handled in int_handler when scroll button pressed
int curr_index;				//Save index into a global variable to be handled in int_handler when scroll button pressed and file shown
int file_to_send_idx;
char PC_msg[40]; 			//Received message from pc
//char files_names[300];		//Data base contains names of files
int dataready;  		//flag which indicates if data received from UART is ready to be used 
int char_idx;
unsigned int rfile_mode;


#endif /* TFC_H_ */
