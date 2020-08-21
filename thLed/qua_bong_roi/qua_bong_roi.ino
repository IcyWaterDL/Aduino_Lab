// Kết nối Arduino với thLed:
//    Arduino pin       thLed pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     V3
//       GND      ---     GND

int thLED_SDI_pin = 4;  
int thLED_RCK_pin = 5;  
int thLED_SCK_pin = 6; 

#include <thLed.h>


// Hàm setup() chạy một lần:
void setup()
{ 
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);  // cài đặt thLed
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  //int led = 7;
  thLed.setLed(7, LED_ON);
  delay(500);
  thLed.setLed(7, LED_OFF);
  for(int i = 6; i >= 0; i--){
    thLed.setLed(i, LED_ON);
    delay(25);
    thLed.setLed(i, LOW);
  }
  for(int i = 0; i < 6; i++){
    if(i < 3){
      thLed.setLed(i, LED_ON);
      delay(30);
      thLed.setLed(i, LOW);
    }
    else{
      thLed.setLed(i, LED_ON);
      delay(40);
      thLed.setLed(i, LOW);
    }
  }
  thLed.setLed(6, LED_ON);
  delay(100);
  for(int i = 6; i >= 0; i--){
    thLed.setLed(i, LED_ON);
    delay(30);
    thLed.setLed(i, LOW);
  }
  for(int i = 0; i < 3; i++){
    if(i < 3){
      thLed.setLed(i, LED_ON);
      delay(35);
      thLed.setLed(i, LOW);
    }
    else{
      thLed.setLed(i, LED_ON);
      delay(45);
      thLed.setLed(i, LOW);
    }
  }
  thLed.setLed(4, LED_ON);
  delay(100);
  for(int i = 4; i >= 0; i--){
    thLed.setLed(i, LED_ON);
    delay(35);
    thLed.setLed(i, LOW);
  }
  for(int i = 0; i < 3; i++){
    if(i < 2){
      thLed.setLed(i, LED_ON);
      delay(45);
      thLed.setLed(i, LOW);
    }
    else{
      thLed.setLed(i, LED_ON);
      delay(55);
      thLed.setLed(i, LOW);
    }
  }
  thLed.setLed(3, LED_ON);
  delay(100);
  thLed.setLed(3, LED_OFF);
  for(int i = 3; i >= 0; i--){
    thLed.setLed(i, LED_ON);
    delay(50);
    thLed.setLed(i, LOW);
  }
  for(int i = 0; i < 3; i++){
    if(i < 1){
      thLed.setLed(i, LED_ON);
      delay(65);
      thLed.setLed(i, LOW);
    }
    else{
      thLed.setLed(i, LED_ON);
      delay(75);
      thLed.setLed(i, LOW);
    }
  }
  thLed.setLed(2, LED_ON);
  delay(100);
  thLed.setLed(2, LED_OFF);
  int x = 8;
  while(x >= 0){
    for(int i = 1; i >= 0; i--){
      thLed.setLed(i, LED_ON);
      delay(80);
      thLed.setLed(i, LOW);
    }
    for(int i = 0; i < 2; i++){
      thLed.setLed(i, LED_ON);
      delay(80);
      thLed.setLed(i, LOW);
    }
    x--;
  }
  thLed.setLed(1, LED_ON);
  delay(50);
  thLed.setLed(1, LED_OFF);
  thLed.setLed(0, LED_ON);
  delay(5000);
  thLed.setLed(0, LED_OFF);
  delay(2000);
}
