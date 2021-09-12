/*
 * servo.h
 *
 *  Created on: Sep 7, 2021
 *      Author: katri
 */

#ifndef SERVO_H_
#define SERVO_H_

#define SERVO_DEG_MAX 180
#define SERVO_DEG_MIN 0

void InitServo();
void InitSensors();
void WriteServo(int deg);
void SweepServo();

#define MOTOR_MUDULO_REGISTER  9373 //   40Hz = 24Mhz/(64x9375) 64 is the prescaler. 
#define MIN_T_ON 0.6 // minimum Minimum Duty cycle in MS
#define MAX_T_ON 2.3 // suppose to be 2.5, although 0.2 is an offset for maximum accuracy 
#define WAVE_PERIOD 25.0
#define MAX_SERVO_DEGREE 180.0
#define MIN_SERVO_DEGREE 0



#endif /* SERVO_H_ */
