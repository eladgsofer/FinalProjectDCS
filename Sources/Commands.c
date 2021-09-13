/*
 * Commands.c
 *
 *  Created on: Sep 13, 2021
 *      Author: EladS
 */
#include "TFC.h"

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
		BLUE_LED_OFF;
		RED_LED_ON;
		
		Delay_d();
		
		RED_LED_OFF;
		GREEN_LED_ON;
		
		Delay_d();
		
		GREEN_LED_OFF;
		BLUE_LED_ON;
		
		Delay_d();
		
		num_of_blinks--;
	}
}

void lcd_count_up(int x){
	int repeat_num, show_num;
	char num_str[3];
		
	repeat_num = x;
	
	while(repeat_num > 0)
	{
		show_num = 0;
		while(show_num <= 10)
		{
			sprintf(num_str,"%d",show_num);
			
			lcd_clear();
			DelayMs(250);
			
			lcd_puts(num_str);
			cursor_off();
			
			Delay_d();
			
			show_num++;
		}
		repeat_num--;
	}
	lcd_clear();
}

void lcd_count_down(int x){
	int repeat_num, show_num;
	char num_str[3];
		
	repeat_num = x;
	
	while(repeat_num > 0)
	{
		show_num = 10;
		while(show_num >= 0)
		{
			sprintf(num_str,"%d",show_num);
			
			lcd_clear();
			DelayMs(250);
			
			lcd_puts(num_str);
			cursor_off();
			
			Delay_d();
			
			show_num--;
		}
		repeat_num--;
	}
	lcd_clear();
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
	volatile unsigned int i;
	
	SetServoDeg(degree);
		
	for(i=0; i<7; i++)
	{
		servo_dist_in_deg(degree);
		Delay_Ms(5);
	}
}

void servo_dist_in_deg(int degree){
	char msg[13] = {0};

	SetServoDeg(degree);
	enable_sensor(TRUE);
	
	while(!sample_ready);
	
	sprintf(msg,"scan%3d%4X\n",degree,distance_avg);
	UARTprintf(UART0_BASE_PTR,msg);
	
	sample_ready = 0;
}
// 07
void servo_scan(int left_angle,int right_angle){
	int angle = left_angle;
	
	while(angle<right_angle){
		
		servo_dist_in_deg(angle);
		
		angle += DEG_DIFF;
		
		Delay_Ms(50);
	}
	
	enable_sensor(FALSE);
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
