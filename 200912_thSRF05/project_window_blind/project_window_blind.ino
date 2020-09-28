#include<Wire.h>
#include<TimeLib.h>
#include<DS1307RTC.h>
#include<thButton.h>
#include <Stepper.h>

#define button3       8
#define button1       9
#define I3            10
#define I2            11
#define I1            12
#define I0            13
#define light_sensor  A3
#define SDA_pin       A4
#define SCL_pin       A5
#define stepsPerRevolution 2048  // số bước để động cơ quay đủ 1 vòng


thButton b1(button1); // keo rem len
thButton b3(button3); // ha rem xuong
Stepper myStepper(64, I0, I2, I1, I3);

tmElements_t tm;

int get_brightness() {
  return analogRead(light_sensor);
}

tmElements_t getTime(const char *str)
{
  int Hour, Min, Sec;
  sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec);
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec + 9; 
  return tm;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(light_sensor, INPUT);
  myStepper.setSpeed(300);
  getTime(__TIME__);
  RTC.write(tm);
}

bool keo = true;

void keo_len() {
  if (keo != true) {
    myStepper.step(stepsPerRevolution); // keo len
    keo = true;
  }
}

void ha_xuong() {
  if (keo != false) {
    myStepper.step(-stepsPerRevolution); // ha xuong
    keo = false;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (b1.onPress()) keo_len();
  else if (b3.onPress()) ha_xuong();

  int a = get_brightness();
  if(a > 600) {
    keo_len();
  }
  RTC.read(tm);
  if(tm.Hour == 7 && tm.Minute == 30) {
    keo_len();
  }
  else if (tm.Hour == 12 && tm.Minute == 15) {
    ha_xuong();
  }
}
