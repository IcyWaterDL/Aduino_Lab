#include<thNumber.h>

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(byte val) { //shiftOut
  byte i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void my_shiftOutLed(byte val) { //shiftOut
  byte i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !!(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void mySetNum(int32_t num) {
  byte bNum[4] = {0x00, 0x00, 0x00, FONT7_0};
  byte x = 3;
  if (abs(num) == num) {
    while (num > 0) {
      bNum[x] = DigitFont[num % 10];
      num /= 10;
      x--;
    }
    for (byte i = 0; i < 4; i++) {
      my_shiftOut(bNum[i]);
    }
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
  }
  else {
    int32_t val = abs(num);
    while (val > 0) {
      bNum[x] = DigitFont[val % 10];
      val /= 10;
      x--;
    }
    bNum[x] = SEG7_G;
    for (byte i = 0; i < 4; i++) {
      my_shiftOut(bNum[i]);
    }
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

void loop() {
  for (int32_t i = 10; i > -1000; i--) {
    mySetNum(i);
    delay(100);
  }
}
