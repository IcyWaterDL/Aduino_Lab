#include<thNumber.h>
#include<OneWire.h>
#include<DallasTemperature.h>

int temperature_pin = 2; // out của thTemperature
int SDI_PIN = 10; // data input
int SCK_PIN = 11; // clock
int RCK_PIN = 12; // latch pin

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

OneWire oneWire(temperature_pin);
DallasTemperature sensors(&oneWire);

void my_shiftOut(byte val) { //shiftOut
  byte i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_PIN, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_PIN, HIGH);
    digitalWrite(SCK_PIN, LOW);    
  }
}

float readTemp() {
  float sum = 0;
  for (int i = 0; i < 10; i++) {
    sensors.requestTemperatures();
    sum += sensors.getTempCByIndex(0);
  }
  return sum / (float)10;
}

void mySetNum(float temperature) {
  byte bNum[4] = {0x00, 0x00, 0x00, FONT7_0};
  int num = (int)(temperature * 100);
  byte x = 3;
  while (num > 0) {
    bNum[x] = DigitFont[num % 10];
    num /= 10;
    x--;
  }
  bNum[1] = bNum[1] | _BV(6);
  for (byte i = 0; i < 4; i++) {
    my_shiftOut(bNum[i]);
  }
  digitalWrite(RCK_PIN, HIGH);
  digitalWrite(RCK_PIN, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // khởi tạo kết nối với máy tính với tốc độ 9600
  sensors.begin(); // cài đặt cảm biến nhiệt độ
  thNumber.begin(SDI_PIN, SCK_PIN, RCK_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
//  sensors.requestTemperatures();
//  float temperature = sensors.getTempCByIndex(0);
  float x = readTemp();
  Serial.println(x);
  mySetNum(x);
}
