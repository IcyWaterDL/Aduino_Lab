#include <TimeLib.h>
#include<thNumber.h>

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
  //Serial.println(second());
  Serial.println(now());
  thNumber.setNum2(0, second());
  thNumber.setNum2(2, minute());
  thNumber.showDot(2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
