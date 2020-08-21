// Kết nối Arduino với thLed:
//    Arduino pin       thLed pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     V3
//       GND      ---     GND
#include<thLed.h>
int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5; 
int thLED_SCK_pin = 6;
int t[8];
void setup(){
  thLed.begin(thLED_SDI_pin, thLED_RCK_pin, thLED_SCK_pin);
  for(int i = 0; i < 8; i++){
    thLed.setLed(i, LOW);
  }
  for(int i = 0; i < 7; i++){
    t[i] = 0;
  }
  t[7] = 1;
}
void loop(){
    for(int i = 0; i < 8; i++){
      if(t[i] == 1){
        thLed.setLed(i, HIGH);
      }
    }
    delay(2000);
    for(int i = 0; i < 8; i++){
      thLed.setLed(i, LOW);
    }
    delay(2000);
    int j = 7;
    while(j >= 0 && t[j] == 1) j--;
    if(j >= 0){
      t[j] = 1;
      for(int i = j+1; i < 8; i++){
        t[i] = 0;
      }
    }
}
