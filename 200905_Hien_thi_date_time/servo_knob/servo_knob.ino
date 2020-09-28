#include <Servo.h>              // sử dụng thư viện Servo
#include<thNumber.h>

int knob = A3;
int myServo_pin = 9;
int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

Servo myServo;  // khai báo myServo

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(int val) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i))));
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);
  }
}

void display_num(int pos) {
  byte num[4] = {0x00, 0x00, 0x00, FONT7_0};
  int x = 3;
  while(pos > 0) {
    num[x] = DigitFont[pos % 10];
    pos /= 10;
    x--;
  }
  for (int i = 0; i < 4; i++) {
    my_shiftOut(num[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

// Hàm setup() chạy một lần
void setup()
{
  int SG90_minPulse =  700;
  int SG90_maxPulse = 2300;
  Serial.begin(9600);
  myServo.attach(myServo_pin, SG90_minPulse, SG90_maxPulse);    // khởi tạo myServo
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  pinMode(knob, INPUT);
  myServo.write(0);
}

// Hàm loop() chạy lặp lại vô hạn
void loop()
{
  int knob_value = analogRead(knob);
  int angle = (float)knob_value * 180.0 / 1023.0;
  myServo.write(angle);
  Serial.println(angle);
  display_num(angle);
  delay(50);  
}
