#include<thNumber.h>

#define sdi       7
#define sck       8
#define rck       9
#define trigger   10
#define echo      11
#define buzzer    12
#define knob      A0
#define time_out  30000

void my_shiftOut(int val) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(sdi, !(val & (1 << (7 - i)))); // mặc định là MSB
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
  }
}

int digitFont[] = {FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, FONT7_5,
                    FONT7_6, FONT7_7, FONT7_7, FONT7_8, FONT7_9};

void display_distance(int num) {
  int b[4] = {0x00, 0x00, 0x00, FONT7_0};
  int x = 3;
  while (num > 0) {
    b[x] = digitFont[num % 10];
    num /= 10;
    x--;
  }
  for (int i = 0; i < 4; i++) {
    my_shiftOut(b[i]);
  }
  digitalWrite(rck, HIGH);
  digitalWrite(rck, LOW);
}

// Lấy khoảng cách
int get_distance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int duration = pulseIn(echo, HIGH, time_out);

  if (duration == 0) return 500;
  return (float)duration / 29.4 / 2.0;
}

int get_threshold() {
  int knob_value = analogRead(knob);
  return (float)knob_value * 500.0 / 1023.0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thNumber.begin(sck, rck, sdi);
  pinMode(buzzer, OUTPUT);
  pinMode(knob, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = get_distance();
  int threshold = get_threshold();
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.print("\tthreshold = ");
  Serial.println(threshold);
  display_distance(distance);
  if (distance < threshold) {
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer);
  }
  delay(250);
}
