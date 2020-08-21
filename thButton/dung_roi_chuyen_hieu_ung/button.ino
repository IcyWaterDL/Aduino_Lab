// Kết nối Arduino với nút bấm:
//    Arduino pin       thButton pin
//       9         ---     B1
//       8         ---     B2
//       GND       ---     GND
// kết nối arduino với thLed:
//    arduino pin       thLedpin
//        4                SDI
//        5                RCK
//        6                SCK
//        vcc              vcc
//        GND              GND
int button0_pin = 10; 
int button1_pin = 9;
int button2_pin = 8;
int button3_pin = 7;
int button4_pin = 11;
int thLED_SDI_pin = 4;  
int thLED_RCK_pin = 5;  
int thLED_SCK_pin = 6;
#include <thButton.h>
#include <thLed.h>
thButton button0(button0_pin);
thButton button1(button1_pin); 
thButton button2(button2_pin); 
thButton button3(button3_pin); 
thButton button4(button4_pin); 
// Hàm setup() chạy một lần:
void setup() 
{
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);
  Serial.begin(115200);  // khởi tạo kết nối tới máy tính với tốc độ 9600
}
int snake(){
  int led = 1;
  while(led < 8){
    thLed.setLed(7, HIGH);//moi sang
    delay(200);
    for(int i = 0; i < 8; i++){//ran chay tu 0-7
      for(int j = i-led; j < i; j++){//do dai cua ran sang
        thLed.setLed(j, HIGH);
      }
      delay(200);
      if(button1.onPress() || button2.onPress() || button3.onPress()|| button4.onPress()){
        Serial.println();
        Serial.println("stop");
        return false;
      }
      thLed.setLed(i-led, LOW);//tat led o duoi ran
    }
    for(int i = 8-led; i < 8; i++){//tat het led duoi
      thLed.setLed(i, LOW);
      delay(200);
      if(button1.onPress() || button2.onPress() || button3.onPress()|| button4.onPress()){
        Serial.println("stop");
        return false; 
      }
    }
    //if(button1.onPress()) return;
    delay(1000);
    led++;
  }
  return true;
}
int canh_buom(){
  int j = 4;
  for(int i=3; i>=0; i--)
  {
    if((i+j)==7)
    {
      thLed.setLed(i,HIGH);
      thLed.setLed(j,HIGH);
      delay(150);
      if(button0.onPress() || button2.onPress() || button3.onPress()|| button4.onPress()) return false;
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
      if(button0.onPress() || button2.onPress() || button3.onPress()|| button4.onPress()) return false;
    }
    j--;
  }
  return true;
}
bool giot_nuoc(){
  int led = 7;
  while(led >= 0){
    for(int i = 0; i < led; i++){
        thLed.setLed(i, HIGH);
        delay(200);
        if(button0.onPress() || button1.onPress() || button3.onPress()|| button4.onPress()){ 
          
          return false;
        }
        thLed.setLed(i, LOW);
    }
    thLed.setLed(led, HIGH);
    delay(200);
    if(button0.onPress() || button1.onPress() || button3.onPress()|| button4.onPress()) return false;
    led--;
  }
  for(int i = 7; i >= 0; i--){
    thLed.setLed(i, LOW);
    delay(30);
    if(button0.onPress() || button1.onPress() || button3.onPress()|| button4.onPress()) return false;
  }
  return true;
}
bool sang_duoi(){
  for(int i = 0; i < 8; i++){
      thLed.setLed(i, HIGH);
      delay(200);
      if(button0.onPress() || button1.onPress() || button2.onPress()|| button4.onPress()) return false;
      thLed.setLed(i, LOW);
  }
  return true;
}
bool nhay_led(){
  for(int i = 0; i < 8; i++){
      thLed.setLed(i, HIGH);
  }
  delay(200);
  if(button0.onPress() || button1.onPress() || button2.onPress()|| button3.onPress()) return false;
  for(int i = 0; i < 8; i++){
      thLed.setLed(i, LOW);
  }
  delay(200);
  if(button0.onPress() || button1.onPress() || button2.onPress()|| button3.onPress()) return false;
  return true;
}
// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  if (button0.onPress())  // nếu button0 được bấm
  {
    Serial.println();
    Serial.println("button 0 onPress");
    while(1){
      if(snake() == false){
        for(int i = 0; i < 8; i++){
          thLed.setLed(i, LOW);
        }
        break;
      }
    }
  }
  if (button1.onPress())  // nếu button1 được bấm
  {
    Serial.println();
    Serial.println("button 1 onPress");
    while(1){
      if(canh_buom() == false){
        for(int i = 0; i < 8; i++){
          thLed.setLed(i, LOW);
        }
        break;
      }
    }
  }
   
  if (button2.onPress())  // nếu button2 được bấm
  {
    Serial.println();
    Serial.println("button 2 onPress");
    while(1){
      if(giot_nuoc() == false){
        for(int i = 0; i < 8; i++){
          thLed.setLed(i, LOW);
        }
        break;
      }
    }
  }
  
  if (button3.onPress())  // nếu button3 được bấm
  {
    Serial.println();
    Serial.println("button 3 onPress");
    while(1){
      if(sang_duoi() == false){
        for(int i = 0; i < 8; i++){
          thLed.setLed(i, LOW);
        }
        break;
      }
    }
  }
  if (button4.onPress())  // nếu button4 được bấm
  {
    Serial.println();
    Serial.println("button 4 onPress");
    while(1){
      if(nhay_led() == false){
        for(int i = 0; i < 8; i++){
          thLed.setLed(i, LOW);
        }
        break;
      }
    }
  }
  delay(50);  // thời gian trễ giữa mỗi lần đọc
}
