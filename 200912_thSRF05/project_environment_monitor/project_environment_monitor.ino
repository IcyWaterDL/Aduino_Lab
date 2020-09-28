#include<thNumber.h>
#include<thButton.h>
#include<dht.h>
#include <OneWire.h>            
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library/archive/master.zip

#define light_sensor  A3
#define rck           5
#define sck           6
#define sdi           7
#define button1       8
#define button3       9
#define button4       10
#define dht11_pin     11
#define temperature   12 

OneWire  oneWire(temperature);
DallasTemperature  sensors(&oneWire);
dht DHT;

thButton b1(button1);
thButton b3(button3);
thButton b4(button4);

// lấy giá trị độ sáng 
int get_brightness() {
  return analogRead(light_sensor); // trả về giá trị độ sáng
}

// lấy giá trị độ ẩm
float get_humidity() {
  DHT.read11(dht11_pin); // kích hoạt cảm biến độ ẩm
  return DHT.humidity; // trả về giá trị độ ẩm
}

//lấy giá trị nhiệt độ
float get_temperature() {
  sensors.requestTemperatures();   // kích hoạt cảm biến nhiệt độ
  return sensors.getTempCByIndex(0); // trả về giá trị cảm biến nhiệt độ
}

void my_shiftOut(int val) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(sdi, !(val & (1 << (7 - i))));
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
  }
}

int digitFont[] = {FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, FONT7_5,
                   FONT7_6, FONT7_7, FONT7_8, FONT7_9};

void display_num(float num) {
  int b[4] = {0x00, 0x00, 0x00, FONT7_0};
  int x = 3;
  if ((int)num == num) {
    int number = (int)num;
    while (number > 0) {
      b[x] = digitFont[number % 10];
      number /= 10;
      x--;  
    }
  }
  else {
    int number = num * 100.0;
    while (number > 0) {
      b[x] = digitFont[number % 10];
      number /= 10;
      x--;  
    }
    b[1] |= _BV(6);
  }
  for (int i =  0; i < 4; i++) {
    my_shiftOut(b[i]);
  }
  digitalWrite(rck, HIGH);
  digitalWrite(rck, LOW);
}

int button = -1;

int check() {
  if (b1.onPress()) {
    button = 0;
    return;
  }
  if (b3.onPress()) {
    button = 1;
    return;
  }
  if (b4.onPress()) {
    button = 2;
    return;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thNumber.begin(sck,rck,sdi);
  sensors.begin();  // cài đặt cảm biến nhiệt độ
  pinMode(light_sensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  check();
  if (button == 0) {
    while (1) {
      int bright = get_brightness();
      Serial.print("Độ sáng = ");
      Serial.println(bright);
      display_num((float)bright);
      check();
      if(button != 0) break;
    }
  }
  else if (button == 1) {
    while (1) {
      float humidity = get_humidity();
      Serial.print("Độ ẩm = ");
      Serial.println(humidity, 2);
      display_num(humidity);
      check();
      if(button != 1) break;
    }
  }
  else if (button == 2) {
    while(1) {
      float temp = get_temperature();
      Serial.print("Nhiệt độ = ");
      Serial.println(temp, 2);
      display_num(temp);
      check();
      if(button != 2) break;
    }
    
  }
}
