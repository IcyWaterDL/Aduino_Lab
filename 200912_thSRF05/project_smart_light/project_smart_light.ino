#define light_sensor A3
#define knob         A0
#define sdi          7
#define sck          8
#define rck          9
#define echo         10
#define trigger      11

#define time_out 3000

void my_shiftOut(int led) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(sdi, !!(led & (1 << (7 - i)))); // mặc định là msb
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
  }
}

int output = 0x00;

void set_led(int index, int state) {
  // put your setup code here, to run once:
  output = output & ~_BV(index) | (state << index); // (y|0)   ~(1 << index)
  my_shiftOut(output);
  digitalWrite(rck, HIGH);
  digitalWrite(rck, LOW);
}

// Lấy khoảng cách từ SRF đến vật cản
int get_distance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int duration = pulseIn(echo, HIGH, time_out);
  if (duration == 0) return 500;
  return duration / 29.4 / 2;
}

//Lấy giá trị ngưỡng bật đèn
int get_threshold() {
  int knob_value = analogRead(knob);
  //đặt ngưỡng bật đèn lớn nhất là 300
  return (float)knob_value * 1023.0 / 1023.0;
}
// Lấy giá trị độ sáng phòng
int get_brightness() {
  return analogRead(light_sensor);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(light_sensor, INPUT);
  pinMode(knob, INPUT);
  pinMode(sdi, OUTPUT);
  pinMode(rck, OUTPUT);
  pinMode(sck, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int threshold = get_threshold();
  int distance = get_distance();
  int bright = get_brightness();

  Serial.print("threshold = ");
  Serial.print(threshold);
  Serial.print("\tdistance = ");
  Serial.print(distance);
  Serial.print("\tbright = ");
  Serial.println(bright);
  
  if (bright >= threshold && distance > 50) { // nếu khoảng cách lớn hơn 50 và độ sáng > ngưỡng thì bật đèn theo độ sáng
    int so_led = (float)bright * 8.0 / 1023.0; // càng tối bật càng nhiều đèn
    
    for (int i = 0; i < so_led; i++) {
      set_led(i, HIGH);
    }
    for (int i = so_led; i < 8; i++) {
      set_led(i, LOW);
    }
  }
  else if (bright <= threshold && distance < 50) { // nếu khoảng cách < 50 và độ sáng < ngưỡng thì bật đèn theo khoảng cách
    int so_led = (float)(50 - distance) * 8.0 / 50.0; // càng gần bật càng nhiều đèn
    
    for (int i = 0; i < so_led; i++) {
      set_led(i, HIGH);
    }
    for (int i = so_led; i < 8; i++) {
      set_led(i, LOW);
    }
  }
  else if (bright >= threshold && distance < 50) { // nếu khoảng cách < 50 và độ sáng > ngưỡng thì bật hết
    for (int i = 0; i < 8; i++) {
      set_led(i, HIGH);
    }
  }
  else {
    for (int i = 0; i < 8; i++) { // không thỏa mãn điều kiện thì tắt hết
      set_led(i, LOW);
    }
  }
  delay(500);
}
