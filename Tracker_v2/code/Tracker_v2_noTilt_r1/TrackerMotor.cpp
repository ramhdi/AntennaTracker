//Tracker Motor
//ramhdi 27/02/2018

#include "TrackerMotor.h"

void TrackerMotor::attach(int len, int ren, int lpwm, int rpwm)
{
	//assign pin values to class members
	_pin_len = len;
	_pin_ren = ren;
	_pin_lpwm = lpwm;
	_pin_rpwm = rpwm;

	//activate pins
	pinMode(_pin_len, OUTPUT);
	pinMode(_pin_ren, OUTPUT);
	pinMode(_pin_lpwm, OUTPUT);
	pinMode(_pin_rpwm, OUTPUT);

	//engage motor driver len and ren
	digitalWrite(_pin_len, HIGH);
	digitalWrite(_pin_ren, HIGH);
}

void TrackerMotor::move(int dir, int pwm)
{
	//dir == 0 then stop motor
	if (dir == 0)
	{
		digitalWrite(_pin_lpwm, LOW);
		digitalWrite(_pin_rpwm, LOW);
	}

	//dir == 1 then rotate CCW
	else if (dir == 1)
	{
		analogWrite(_pin_lpwm, 0);
		analogWrite(_pin_rpwm, pwm);
	}

	//dir == 2 then rotate CW
	else if (dir == 2)
	{
		analogWrite(_pin_lpwm, pwm);
		analogWrite(_pin_rpwm, 0);
	}
}
