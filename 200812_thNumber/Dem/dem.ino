#include <thNumber.h>
#include <thButton.h>

int button1_pin = 9;
int button2_pin = 8;
int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

thButton button1(button1_pin); 
thButton button2(button2_pin); 

float count = 0;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
  if(count >= 0){
        if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else if (count < 10 && count >= 0) {
          thNumber.setDigit(0, count);
          thNumber.setBitmap(1, SEG7_NONE);
        }
        else if (count >= 10 && count < 100) {
          thNumber.setNum2(0, count);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else
          thNumber.setNum4(0, count);
      }
      else {
        if (count > -10 && count < 0) {
          thNumber.setDigit(0, abs(count));
          thNumber.setBitmap(1, SEG7_G);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count <= -10 && count > -100) {
          thNumber.setNum2(0, abs(count));
          thNumber.setBitmap(2, SEG7_G);
          thNumber.setBitmap(3, SEG7_NONE);
        }
        else if (count <= -100 && count > -1000) {
          thNumber.setNum3(0, abs(count));
          thNumber.setBitmap(3, SEG7_G);
        } 
      }
}

void loop() {
  // put your main code here, to run repeatedly:
    if(button1.onPress()){
      count++;
      Serial.println(count);
      if(count >= 0){
        if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else if (count < 10 && count >= 0) {
          thNumber.setDigit(0, count);
          thNumber.setBitmap(1, SEG7_NONE);
        }
        else if (count >= 10 && count < 100) {
          thNumber.setNum2(0, count);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else
          thNumber.setNum4(0, count);
      }
      else {
        if (count > -10 && count < 0) {
          thNumber.setDigit(0, abs(count));
          thNumber.setBitmap(1, SEG7_G);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count <= -10 && count > -100) {
          thNumber.setNum2(0, abs(count));
          thNumber.setBitmap(2, SEG7_G);
          thNumber.setBitmap(3, SEG7_NONE);
        }
        else if (count <= -100 && count > -1000) {
          thNumber.setNum3(0, abs(count));
          thNumber.setBitmap(3, SEG7_G);
        } 
      }
    delay(100);
    }
    else if(button2.onPress()) {
      count--;
      Serial.println(count);
      if(count >= 0){
        if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else if (count < 10 && count >= 0) {
          thNumber.setDigit(0, count);
          thNumber.setBitmap(1, SEG7_NONE);
        }
        else if (count >= 10 && count < 100) {
          thNumber.setNum2(0, count);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count >= 100 && count < 1000) {
          thNumber.setNum3(0, count);
          thNumber.setBitmap(3, SEG7_NONE);
        } 
        else
          thNumber.setNum4(0, count);
      }
      else {
        if (count > -10 && count < 0) {
          thNumber.setDigit(0, abs(count));
          thNumber.setBitmap(1, SEG7_G);
          thNumber.setBitmap(2, SEG7_NONE);
        }
        else if (count <= -10 && count > -100) {
          thNumber.setNum2(0, abs(count));
          thNumber.setBitmap(2, SEG7_G);
          thNumber.setBitmap(3, SEG7_NONE);
        }
        else if (count <= -100 && count > -1000) {
          thNumber.setNum3(0, abs(count));
          thNumber.setBitmap(3, SEG7_G);
        } 
      }
    delay(100);
    }
}
