/*
*/
#include<thNumber.h>
#include<thButton.h>

int button0_pin = 9;
int button1_pin = 8;
int button2_pin = 7;
int button3_pin = 6;
int button4_pin = 5;
int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

thButton button_start_finish(button0_pin);
thButton button_phut(button1_pin); 
thButton button_giay(button2_pin); 
thButton button_tang(button3_pin);
thButton button_giam(button4_pin);  
 
int phut = 0, giay = 0;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  thNumber.setNum2(0, giay);
  thNumber.setNum2(2, phut);
  thNumber.showDot(2);
}

int check_button() {
  if (button_start_finish.onPress()) return 1;
  return 0;
}

void loop() {
  if (button_start_finish.onPress()) {
    while(1){
      if (phut > 59) phut = 0;
      for (int i = phut; i < 60; i++) {
        if (check_button() == 1) return;
        if (giay > 59) giay = 0;
        thNumber.setNum2(2, i);
        for (int j = giay; j < 60; j++) {
          if (check_button() == 1) return;
          thNumber.setNum2(0, j);
          thNumber.showDot(2);
          delay(500);
          if (check_button() == 1) return;
          thNumber.hideDot(2);
          delay(500);
          if (check_button() == 1) return;
          giay++;
        }
        phut++;
      }
    }
  }
  else if (button_phut.onPress()) {
    while(1){
      if (button_tang.onPress()) {
        if (phut < 59) phut++;
        thNumber.setNum2(2, phut);
        thNumber.showDot(2);
      }
      else if (button_giam.onPress()) {
        if (phut > 0) phut--;
        thNumber.setNum2(2, phut);
        thNumber.showDot(2);
      }
      if (check_button() == 1) return;
    }
  }
  else if (button_giay.onPress()) {
    while(1) {
      if (button_tang.onPress()) {
        if (giay < 59) giay++;
        thNumber.setNum2(0, giay);
        thNumber.showDot(2);
      }
      else if (button_giam.onPress()) {
        if(giay > 0) giay--;
        thNumber.setNum2(0, giay);
        thNumber.showDot(2);
      }
      if (check_button() == 1) return;
    }
  }
}
