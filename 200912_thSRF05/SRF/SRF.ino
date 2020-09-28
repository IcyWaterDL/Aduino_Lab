#include<thNumber.h>
#define timeout 30000

int TRIGGER_PIN = 9;
int ECHO_PIN    = 8;
int sdi = 10;
int sck = 11;
int rck = 12; 

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(int val) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(sdi, !(val & (1 << (7 - i))));
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
  }
}

void display_num(int num) {
  int b[4] = {0x00, 0x00, 0x00, FONT7_0};
  int x = 3;
  while (num > 0) {
    b[x] = DigitFont[num % 10];
    num /= 10;
    x--;
  }
  for (int i = 0; i < 4; i++) {
    my_shiftOut(b[i]);
  }
  digitalWrite(rck, HIGH);
  digitalWrite(rck, LOW);
}

// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  thNumber.begin(sck, rck, sdi);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int get_distance() {
  //phát xung trên chân trig
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH, timeout); //tính thời gian phát và nhận sóng

  return duration / 29.4 / 2; // tra ve khoang cach
  
}

// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int distance_cm = get_distance();  // đo khoảng cách (đơn vị cm)
  if (distance_cm <= 0) {
    Serial.println(500);
    display_num(500);
  }
  else {
    Serial.println(distance_cm);  // in kết quả ra màn hình
    display_num(distance_cm);
  }
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}
