//Mapping PWM from Pixhawk to Motor Driver
//by ramhdi, 23/02/2018, 20.23

//Tracker_v2.0, updated 20/03/2018
//added tilt feature
//uses TrackerMotor.h
// 02/06/2018
// removed tilt
// 26/08/2018
// added map

#include "TrackerMotor.h"
#include "PWM.hpp"
#include <math.h>

//deklarasi param motor pan dan tilt
TrackerMotor pan;

//deklarasi pembacaan pwm
PWM pwm_pan;
int pan_val, pan_speed, pan_val_last = 0;
const int pan_speed_lim = 30;

void setup()
{
  Serial.begin(115200); // Serial for debug

  pwm_pan.begin(2, 1); //1 = high

  pan.attach(7, 8, 5, 6); //attach(len, ren, lpwm, rpwm)
}

void loop()
{
  //baca nilai pwm pan dan tilt
  pan_val_last = pwm_pan.getValue();
  //print nilai pwm pan dan tilt
  Serial.print("PWM pan last val = "); Serial.println(pan_val_last);
  //melakukan aksi pan
  /*
  if (!inIntervalPWM(pan_val_last))
  {
    //motor pan diam
    pan.move(DIR_STOP, 0);
    Serial.println("Pan diam");
  }

  else if (pan_val_last >= 1095 && pan_val_last < 1475)
  {
    //motor pan ccw, map ke 63 (255 kekencengan)
    //pan_speed = pan_speed_lim;
    pan_speed = map(pan_val_last, 1474, 1095, 18, pan_speed_lim);
    pan.move(DIR_CW, pan_speed);
    Serial.print("Pan CW = "); Serial.println(pan_speed);
  }

  else if (pan_val_last > 1525 && pan_val_last <= 1905)
  {
    //motor pan cw, map ke 63 (255 kekencengan)
    //pan_speed = pan_speed_lim;
    pan_speed = map(pan_val_last, 1526, 1905, 18, pan_speed_lim);
    pan.move(DIR_CCW, pan_speed);
    Serial.print("Pan CCW = "); Serial.println(pan_speed);
  }
  */
  delay(10);
}

bool inIntervalPWM(int n)
{
  if (n >= 1095 && n <= 1475)
  {
    return true;
  }

  else if (n >= 1525 && n <= 1905)
  {
    return true;
  }

  else return false;
}

