#include <Servo.h>              // sử dụng thư viện Servo
#include<thNumber.h>

int myServo_pin = 9;

Servo myServo;                  // khai báo myServo

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

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
  myServo.attach(myServo_pin, SG90_minPulse, SG90_maxPulse);    // khởi tạo myServo
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

// Hàm loop() chạy lặp lại vô hạn
void loop()
{
  int waittime = 15;            // thời gian đợi servo quay (ms)
  int pos = 90;                 // vị trí servo
  
  for (; pos <= 180; pos += 1)  // quay servo từ 90 đến 180 độ
  { 
    myServo.write(pos);         // quay myServo đến vị trí 'pos'
    display_num(pos);
    delay(waittime);            // đợi servo quay
  }
  for (; pos >= 90; pos -= 1)   // quay servo từ 180 đến 90 độ
  { 
    myServo.write(pos);         // quay myServo đến vị trí 'pos'
    display_num(pos);
    delay(waittime);
  }

  delay(2000);                  // dừng 2 giây
  
  for (; pos >= 0; pos -= 1)    // quay servo từ 90 đến 0 độ
  { 
    myServo.write(pos);
    display_num(pos);
    delay(waittime);
  }
  for (; pos <= 90; pos += 1)   // quay servo từ 0 đến 90 độ
  { 
    myServo.write(pos);
    display_num(pos);
    delay(waittime);
  }

  delay(2000);                  // dừng 2 giây
}
