#include<thNumber.h>
#include<thButton.h>

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

void my_shiftOut(byte val) {
  uint8_t i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void set_digit(uint16_t value) {
  my_shiftOut(DigitFont[value]);
  my_shiftOut(DigitFont[value]);
  my_shiftOut(DigitFont[value]);
  my_shiftOut(DigitFont[value]);
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

void display_num(uint16_t value) {
  if( value >= 0 && value < 10) {
    my_shiftOut(0x00);
    my_shiftOut(0x00);
    my_shiftOut(0x00);
    my_shiftOut(DigitFont[value]);
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
  }
  else if( value >= 10 && value < 100) {
    my_shiftOut(0x00);
    my_shiftOut(0x00);
    my_shiftOut(DigitFont[value / 10]);
    value = value%10;
    my_shiftOut(DigitFont[value]);
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
  }
  else if( value >= 100 && value < 1000) {
    my_shiftOut(0x00);
    my_shiftOut(DigitFont[value / 100]);
    value = value%100;
    my_shiftOut(DigitFont[value / 10]);
    value = value%10;
    my_shiftOut(DigitFont[value]);
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
  }
  else {
    set_digit(value);
  }
}

void display_signNum(int16_t value) {
  if (value >= 0) {
     display_num(value);
  }
  else {
    if(value < 0 && value > -10) {
    my_shiftOut(0x00);
    my_shiftOut(0x00);
    my_shiftOut(SEG7_G);
    my_shiftOut(DigitFont[abs(value)]);
    digitalWrite(RCK_pin, HIGH);
    digitalWrite(RCK_pin, LOW);
    }
    else if( value <= -10 && value > -100) {
      uint16_t x = abs(value);
      my_shiftOut(0x00);
      my_shiftOut(SEG7_G);
      my_shiftOut(DigitFont[x / 10]);
      x = x%10;
      my_shiftOut(DigitFont[x]);
      digitalWrite(RCK_pin, HIGH);
      digitalWrite(RCK_pin, LOW);
    }
    else if( value <= -100 && value > -1000) {
      uint16_t x = abs(value);
      my_shiftOut(SEG7_G);
      my_shiftOut(DigitFont[x / 100]);
      x = x%100;
      my_shiftOut(DigitFont[x / 10]);
      x = x%10;
      my_shiftOut(DigitFont[x]);
      digitalWrite(RCK_pin, HIGH);
      digitalWrite(RCK_pin, LOW);
    }
  }
}

void setup() {
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  display_signNum(value);
}

void loop() {
  set_digit(1000);
}
