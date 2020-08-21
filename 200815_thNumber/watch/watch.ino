#include<thNumber.h>
#include<thButton.h>

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;
int button1_pin = 9;
int button2_pin = 8;
int button3_pin = 7;
int button4_pin = 6;

thButton down(button1_pin); 
thButton start_stop(button2_pin); 
thButton set_up(button3_pin);
thButton up(button4_pin);  

int min = 0, sec = 0; // mặc định thời gian ban đầu là 00:00
int set = 0;
bool run = 0, up = false, down = false;

void blink_num() {
  if (set == 1) {
    thNumber.setNum2(0, min);
    my_delay();
    thNumber.setBitmap(0, 0x00);
  }
}

void check() { // kiểm tra nút bấm nào được bấm
  if (start_stop.onPress()) {
    run = true;
    set = 0;
  }
  if (set.onPress()) {
    if (set > 1) 
      set--;
    else set++;
  }
  if (up.onPress()) {
    up = true;
  }
  if (down.onPress()) {
    down = true;
  }
}

void button() {
  if (set == 1) {
    blink_num();
    if (up == true && set == 1) {
      if (min < 59) min++;
    }
    if (down == true && set == 1) {
      if (sec > 0) sec--; 
    }
  }
  else if(set == 2) {
    if (up == true && set == 2) {
      if (sec < 59) sec++;
    }
    if (down == true && set == 1) {
      if (min > 0) min--;
    }
  }
}

void my_delay() { // dừng đê check button sau mỗi 10ms
  for (byte i = 0; i < 50; i++) {
    check();
    delay(10);
  }
}

void watch() { // hiển thị thời gian đang chạy
  for (byte i = min; i < 60; i++) {
    thNumber.setNum2(2, i);
    for (byte j = sec; j < 60; j++) {
      thNumber.setNum2(0, j);
      my_delay();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  thNumber.setNum2(0, min);
  thNumber.setNum2(2, sec);
  check();
}

void loop() {
  // put your main code here, to run repeatedly:
  watch();
}
