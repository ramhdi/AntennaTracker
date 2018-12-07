#include "BTS7960.h"

BTS7960 pan(7, 8, 5, 6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pan.attach();
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
    pan.move(DIR_CW, 35);
    delay(5000);
  */

  for (int i = 24; i <= 40; i++)
  {
    pan.move(DIR_CW, i);
    delay(5000);
    pan.move(0, 0);
    delay(500);
    Serial.println(i);
  }

  pan.move(0, 0);
  delay(2500);

  /*
    pan.move(DIR_CCW, 55);
    delay(5000);
  */

  for (int i = 20; i <= 40; i++)
  {
    pan.move(DIR_CCW, i);
    delay(2500);
    Serial.println(i);
  }

  pan.move(0, 0);
  delay(2500);
}
