int clockPin = 10; //SCK
int latchPin = 11; //RCK
int dataPin = 12;  //SDI

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  shiftOut(dataPin, clockPin, MSBFIRST, 0x80);  
  digitalWrite(latchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
  digitalWrite(latchPin, LOW);//chân OE = 0, cho phép IC hđ
  delay(200);
}
