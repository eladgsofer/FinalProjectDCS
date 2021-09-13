/*
 * Commands.h
 *
 *  Created on: Sep 13, 2021
 *      Author: EladS
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_



void setServoAtDegree(void);
void blink_rgb(int x);
void lcd_count_down(int x);
void lcd_count_up(int x);
void set_delay(int d);
void clear_all_leds(void);
void servo_deg(int p);
void servo_scan(int l, int r);

void Delay_d(void);
void Delay_Ms(int ms);



#endif /* COMMANDS_H_ */
