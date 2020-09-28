#include<thLed.h>

int sck = 9;
int rck = 8;
int sdi = 7;
int l7 = 10;
int l6 = 11;
int l5 = 12;

void my_analogWrite(int led, int value) {
  int T_on = ((float)value * 2048.0) / 255.0;
  int T_off = 2048.0 - T_on;
  digitalWrite(led, HIGH);
  delayMicroseconds(T_on);
  digitalWrite(led, LOW);
  delayMicroseconds(T_off);
}

void setup() {
//  thLed.begin(sdi, sck, rck);
  Serial.begin(9600);
  pinMode(l5, OUTPUT);
  pinMode(l6, OUTPUT);
  pinMode(l7, OUTPUT);
  //analogWrite(l6, 255);
  
}

void loop() {
  //my_analogWrite(l7, 255);
  for (int i = 0; i <= 255; i++) {
    analogWrite(l7, i);
//    my_analogWrite(l7, i);
    my_analogWrite(l6, i);
    //delay(20);
  }
  //thLed.setLed(6, HIGH);
}
