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
  for(int pos = 0; pos < 8; pos++){
    thLed.setLed(pos, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int j = 4;
  for(int i=3; i>=0; i--)
  {
    if((i+j)==7)
    {
      thLed.setLed(i,HIGH);
      thLed.setLed(j,HIGH);
      delay(150);
    }
    j++;
  }
  j = 7;
  for(int i=0; i <= 3; i++)
  {
    if((i+j)==7)
    {
      thLed.setLed(i,LOW);
      thLed.setLed(j,LOW);
      delay(100);
    }
    j--;
  }
}
