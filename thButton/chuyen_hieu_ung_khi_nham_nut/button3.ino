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

int hieu_ung = 0;

int check_button(){
  if(button0.onPress()){
    hieu_ung = 0;
    return 0;
  }
  if(button1.onPress()){
    hieu_ung = 1;
    return 1;
  }
  if(button2.onPress()) 
  {
    hieu_ung = 2;
    return 2;
  }
  if(button3.onPress()) {
    hieu_ung = 3;
    return 3;
  }
  if(button4.onPress()) {
    hieu_ung = 4;
    return 4;
  }
  return -1;
}

void snake(){
  while(1){
    int led = 1;
    while(led < 8){
      thLed.setLed(7, HIGH);//moi sang
      delay(200);
      for(int i = 0; i < 8; i++){//ran chay tu 0-7
        for(int j = i-led; j < i; j++){//do dai cua ran sang
          thLed.setLed(j, HIGH);
        }
        delay(200);
//        int check = check_button();
//        if(check != -1){
//          hieu_ung = check;
//          return;
//          }
        if(check_button() != -1 ){
          return;
        }
        thLed.setLed(i-led, LOW);//tat led o duoi ran
      }
      for(int i = 8-led; i < 8; i++){//tat het led duoi
        thLed.setLed(i, LOW);
        delay(200);
//        int check = check_button();
//        if(check != -1){
//          hieu_ung = check;
//          return;
//          }
          if(check_button() != -1){
            //hieu_ung = check_button();
            return;
          }
      }
      delay(1000);
      led++;
    }
  }
}


void canh_buom(){
  while(1){
    int j = 4;
    for(int i=3; i>=0; i--)
    {
      if((i+j)==7)
      {
        thLed.setLed(i,HIGH);
        thLed.setLed(j,HIGH);
        delay(150);
//        int check = check_button();
//        if(check != -1){
//          hieu_ung = check;
//          return;
//        }
        if(check_button() != -1){
         // hieu_ung = check_button();
          return;
      }
      j++;
    }
    }
    j = 7;
    for(int i=0; i <= 3; i++)
    {
      if((i+j)==7)
      {
        thLed.setLed(i,LOW);
        thLed.setLed(j,LOW);
        delay(100);
//        int check = check_button();
//        if(check != -1){
//          hieu_ung = check;
//          return;
//        }
        if(check_button() != -1){
          return;
        }
      }
      j--;
    }
}
}
void giot_nuoc(){
  while(1){
    int led = 7;
    while(led >= 0){
      for(int i = 0; i < led; i++){
          thLed.setLed(i, HIGH);
          delay(200);
          
          thLed.setLed(i, LOW);
      }
      thLed.setLed(led, HIGH);
      delay(200);
      if(check_button() != -1){
        return;
      }
      led--;
    }
    for(int i = 7; i >= 0; i--){
      thLed.setLed(i, LOW);
      delay(30);
      if(check_button() != -1){
            return;
        }
    }
  }
}
void sang_duoi(){
  while(1){
    for(int i = 0; i < 8; i++){
        thLed.setLed(i, HIGH);
        delay(200);
        if(check_button() != -1){
            return;
          }
        thLed.setLed(i, LOW);
    }
  }
}
void nhay_led(){
  while(1){
    for(int i = 0; i < 8; i++){
        thLed.setLed(i, HIGH);
    }
    delay(200);
    if(check_button() != -1){
            return;
          }
    for(int i = 0; i < 8; i++){
        thLed.setLed(i, LOW);
    }
    delay(200);
    if(check_button() != -1){
      return;
    }
  }
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  //check hieu ung
  switch (hieu_ung) {
    case 0:
      snake();
      for(int i = 0; i < 8; i++)
         thLed.setLed(i, LOW);
      break;
    case 1:
      canh_buom();
      for(int i = 0; i < 8; i++)
         thLed.setLed(i, LOW);
      break;
    case 2:
      sang_duoi();
      for(int i = 0; i < 8; i++)
         thLed.setLed(i, LOW);
      break;
    case 3:
      giot_nuoc();
      for(int i = 0; i < 8; i++)
         thLed.setLed(i, LOW);
      break;
    case 4:
      nhay_led();
      for(int i = 0; i < 8; i++)
         thLed.setLed(i, LOW);
      break;
  }
  delay(50);  // thời gian trễ giữa mỗi lần đọc
}
