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
  int led = 1;
  while(led < 8){
    thLed.setLed(7, HIGH);//moi sang
    delay(200);
    for(int i = 0; i < 8; i++){//ran chay tu 0-7
      for(int j = i-led; j < i; j++){//do dai cua ran sang
        thLed.setLed(j, HIGH);
      }
      delay(200);
      thLed.setLed(i-led, LOW);//tat led o duoi ran
    }
    for(int i = 8-led; i < 8; i++){//tat het led duoi
      thLed.setLed(i, LOW);
      delay(200);  
    }
    delay(1000);
    led++;
  }
}
