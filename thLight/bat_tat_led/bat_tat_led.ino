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
int do_sang[8] = {114, 228, 342, 456, 570, 684, 798, 912};

// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int light_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  Serial.println(light_value);// in kết quả ra màn hình
  if(light_value < do_sang[0]) {
    for (int i = 0; i < 8; i++)
      thLed.setLed(i, LOW);
  }
  else if( do_sang[0] <= light_value && light_value < do_sang[1]){
    for (int i = 0; i < 1; i++){
         thLed.setLed(i, HIGH);
      }
    for (int i = 1; i < 8; i++){
      thLed.setLed(i, LOW); 
    }
  }
  else if( do_sang[1] <= light_value && light_value < do_sang[2]){
    for (int i = 0; i < 2; i++){
         thLed.setLed(i, HIGH);
      }
    for (int i = 2; i < 8; i++){
      thLed.setLed(i, LOW);
    }
  }
  else if( do_sang[2] <= light_value && light_value < do_sang[3]){
    for (int i = 0; i < 3; i++){
       thLed.setLed(i, HIGH);
    }
    for (int i = 3; i < 8; i++){
      thLed.setLed(i, LOW);
    }
  }
  else if( do_sang[3] <= light_value && light_value < do_sang[4]){
    for (int i = 0; i < 4; i++){
         thLed.setLed(i, HIGH);
      }
    for (int i = 4; i < 8; i++){
      thLed.setLed(i, LOW);
    }  
  }
  else if( do_sang[4] <= light_value && light_value < do_sang[5]){
    for (int i = 0; i < 5; i++){
       thLed.setLed(i, HIGH);
    }
    for (int i = 5; i < 8; i++){
      thLed.setLed(i, LOW);
    }
  }
  else if( do_sang[5] <= light_value && light_value < do_sang[6]){
    for (int i = 0; i < 6; i++){
       thLed.setLed(i, HIGH);
    }
    for (int i = 6; i < 8; i++){
      thLed.setLed(i, LOW);
    }
  }
  else if( do_sang[6] <= light_value && light_value < do_sang[7]){
    for (int i = 0; i < 7; i++){
      thLed.setLed(i, HIGH);
    }
    for (int i = 7; i < 8; i++){
      thLed.setLed(i, LOW);
    }   
  }
  else{
    for (int i = 0; i < 8; i++){
      thLed.setLed(i, HIGH);
    }
  }
  delay(50);  // thời gian trễ giữa mỗi lần đọc
}
