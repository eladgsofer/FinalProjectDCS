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
#define MOTOR_MUDULO_REGISTER  9375
#define MIN_T_ON 0.6
#define MAX_T_ON 2.5
#define WAVE_PERIOD 25.0
#define MAX_SERVO_DEGREE 180.0
#define MIN_SERVO_DEGREE 0



#endif /* SERVO_H_ */
