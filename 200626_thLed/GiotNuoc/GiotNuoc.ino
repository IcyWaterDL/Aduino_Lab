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

int t[8];
#include <thLed.h>


// Hàm setup() chạy một lần:
void setup()
{ 
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);  // cài đặt thLed
}

// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  int led = 7;
  while(led >= 0){
    for(int i = 0; i < led; i++){
        thLed.setLed(i, HIGH);
        delay(200);
        thLed.setLed(i, LOW);
    }
    thLed.setLed(led, HIGH);
    delay(200);
    led--;
  }
  for(int i = 7; i >= 0; i--){
    thLed.setLed(i, LOW);
    delay(30);
  }
}
