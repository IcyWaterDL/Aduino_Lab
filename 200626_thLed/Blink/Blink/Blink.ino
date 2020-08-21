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
  for(int i = 0; i < 8; i++){
      thLed.setLed(i, HIGH);
  }
  delay(500);
  for(int i = 0; i < 8; i++){
      thLed.setLed(i, LOW);
  }
  delay(500);
}
