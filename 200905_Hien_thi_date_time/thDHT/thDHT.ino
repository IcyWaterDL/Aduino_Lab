#include<thNumber.h>

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

int dht11_pin = 9;

#include <dht.h>  // https://arduino-info.wikispaces.com/file/view/DHT-lib.zip/545470280/DHT-lib.zip
dht  DHT;

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(byte val) { //shiftOut
  byte i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void display(int humidity, int temp) { //Hiển thị thời gian lên thNumber
  byte bNum[8] = {FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0};
  byte do_am = 5, nhiet_do = 1;
  while (humidity > 0) {              
    bNum[do_am] = DigitFont[humidity % 10];
    humidity /= 10;
    do_am--;
  }
  
  while (temp > 0) {
    bNum[nhiet_do] = DigitFont[temp % 10];
    temp /= 10;
    nhiet_do--;
  }
  bNum[1] |= _BV(6);
  bNum[5] |= _BV(6);
  for (byte i = 0; i < 8; i++) {
    my_shiftOut(bNum[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}


// Hàm setup() chạy một lần:
void setup()
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.println("Humidity (%)\tTemperature (C)");
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  DHT.read11(dht11_pin);  // kích hoạt cảm biến DHT11

  // in kết quả ra màn hình:
  Serial.print(DHT.humidity);       // độ ẩm (%)
  Serial.print("\t\t");
  Serial.println(DHT.temperature);  // nhiệt độ (C)
  display(DHT.humidity, DHT.temperature);
  delay(1000);  // thời gian trễ giữa mỗi lần đọc
}
