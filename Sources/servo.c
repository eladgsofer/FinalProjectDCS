#include "TFC.h"


//////////////////////////////////
//	Inits Servo
/////////////////////////////////
void InitServo() {
	ClockSetup(); // initialise tpm clock
	InitTPM(SERVO_TPM);		 // configure pit 0
	StartTPMx(SERVO_TPM, TRUE); // start pit 
}
/////////////////////////////////////
//  Inits Sensors
/////////////////////////////////////
void InitSensors() {
	ClockSetup(); // initialise tpm clock
	InitTPM(SENSOR_TRIG);
	InitTPM(SENSOR_ECHO);
}
//////////////////////////////////
//	Change Servo's deg
/////////////////////////////////
void WriteServo(int deg) {
	int dutyCycle;
	/*
	// check if deg is valid
	if (SERVO_DEG_MAX < deg || deg < SERVO_DEG_MIN) {
		return;
	}

	StartTPMx(SERVO_TPM, FALSE);
	dutyCycle = TPM_DC_VAL_MIN + (TPM_DC_VAL_MAX - TPM_DC_VAL_MIN) * (float)deg / (float)SERVO_DEG_MAX;
	SetTPMxDutyCycle(SERVO_TPM, dutyCycle);
	StartTPMx(SERVO_TPM, TRUE);
	DelayMs(100);
	*/
}

//////////////////////////////////////
//	Sweep Servo 180 deg from 0 to 180
//////////////////////////////////////
void SweepServo() {

	int deg;
	for (deg = 0; deg < 180; deg += 9)
		WriteServo(deg);
}
