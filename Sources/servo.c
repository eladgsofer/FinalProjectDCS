#include "TFC.h"
#include "servo.h"

#define PIT_RISING 0
#define PIT_FALLING 1
#define SERVO_TPM 1
#define SENSOR_TRIG 2
#define SENSOR_ECHO 0
#define SERVO_DEG_MAX 180
#define SERVO_DEG_MIN 0
#define TPM_DC_VAL_MIN 750 //900 // ~5% * 20ms = 1ms 
#define TPM_DC_VAL_MAX 3550//3750// ~10% * 20ms = 2ms

#define SERVO_DEG_CHANGE 1

//////////////////////////////////
//	Inits Servo
/////////////////////////////////
void InitServo() {
	ClockSetupTPM(); // initialise tpm clock
	InitTPMx(SERVO_TPM);		 // configure pit 0
	StartTPMx(SERVO_TPM, TRUE); // start pit 
}
/////////////////////////////////////
//  Inits Sensors
/////////////////////////////////////
void InitSensors() {
	//ClockSetup(); // initialise tpm clock
	InitTPMx(SENSOR_TRIG);
	InitTPMx(SENSOR_ECHO);
}
//////////////////////////////////
//	Change Servo's deg
/////////////////////////////////
void WriteServo(int deg) {
	float T_on;
	int dutyCycle;
<<<<<<< Updated upstream
=======
	
	// check if deg is valid
	if (SERVO_DEG_MAX < deg || deg < SERVO_DEG_MIN) {
		return;
	}
>>>>>>> Stashed changes

	T_on = MIN_T_ON + (deg / MAX_SERVO_DEGREE) * (MAX_T_ON - MIN_T_ON);
	dutyCycle = (T_on / WAVE_PERIOD) * MOTOR_MUDULO_REGISTER;
	StartTPMx(SERVO_TPM, FALSE);
	SetTPMxDutyCycle(SERVO_TPM, dutyCycle);
	StartTPMx(SERVO_TPM, TRUE);
	DelayMs(100);
<<<<<<< Updated upstream
=======
	
>>>>>>> Stashed changes
}

//////////////////////////////////////
//	Sweep Servo 180 deg from 0 to 180
//////////////////////////////////////
void SweepServo() {

	int deg;
	for (deg = 0; deg < 180; deg += 9)
		WriteServo(deg);
}
