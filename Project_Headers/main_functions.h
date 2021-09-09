/*
 * main_functions.h
 *
 *  Created on: Sep 6, 2021
 *      Author: katri
 */

#ifndef MAIN_FUNCTIONS_H_
#define MAIN_FUNCTIONS_H_

#define MIN_DEG	0
#define MAX_DEG	180

int print_script_idx, next_script_idx;

void InitApp(void);
void script_receive_flow(void);
void script_mode(void);
void set_uart_configurations(void);

int print_files_menu(int file_idx);
void receive_script(void);
void state_decode(void);



#endif /* MAIN_FUNCTIONS_H_ */
