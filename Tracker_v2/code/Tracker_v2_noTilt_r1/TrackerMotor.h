//Tracker Motor
//ramhdi 27/02/2018

#include <arduino.h>
#ifndef _TrackerMotor_
#define _TrackerMotor_

#define DIR_STOP 0
#define DIR_CW 2
#define DIR_CCW 1

class TrackerMotor
{
	int _pin_len, _pin_ren, _pin_lpwm, _pin_rpwm;

public:
	void attach(int, int, int, int); //attach(int len, int ren, int lpwm, int rpwm)
	void move(int, int); //move(int dir, int pwm)
};

#endif
