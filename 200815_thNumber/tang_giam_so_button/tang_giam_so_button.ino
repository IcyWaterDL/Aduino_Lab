#include<thNumber.h>
#include<thButton.h>

int button1_pin = 8;
int button2_pin = 7;
int button3_pin = 6;
int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

thButton button_status(button1_pin);
thButton button_tang(button2_pin);
thButton button_giam(button3_pin);

byte DigitFont[10] = {
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

int16_t value = 0;
bool dir = false;
bool run = false;

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

void check() {
  if(button_status.onPress()) {
    run = !run;
  }
  if(button_tang.onPress()) {
    run = true;
    dir = false;
  }
  if(button_giam.onPress()) {
    run = true;
    dir = true;
  }
}

void giam(){
  if(value < -999) value = 9999;
    value--;
}

void tang() {
  if(value > 9999) value = -999;
    value++;
}

void Button() {
 check();
 if(run == false) 
  return;
 if(dir == false) 
  tang();
 else 
  giam();
 display_signNum(value); // hien thi len th7seg
 delay(500);
}

void setup() {
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  display_signNum(value);
}

void loop() {
  Button();
}
