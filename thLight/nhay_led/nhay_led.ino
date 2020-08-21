// Kết nối Arduino với cảm biến ánh sáng:
//    Arduino pin       thLight pin
//       A3        ---     OUT
//       VCC       ---     V3
//       GND       ---     GND

int light_sensor_pin = A3;
int thLED_SDI_pin = 4;  
int thLED_RCK_pin = 5;  
int thLED_SCK_pin = 6;

#include <thLed.h>

// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(light_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int light_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  Serial.println(light_value);  // in kết quả ra màn hình
  if(light_value > 500) {
    for (int i = 0; i < 8; i++)
      thLed.setLed(i, HIGH);
    //delay(100);
  }
  else{
    for (int i = 0; i < 8; i++)
      thLed.setLed(i, LOW);
  }
  delay(50);  // thời gian trễ giữa mỗi lần đọc
}
