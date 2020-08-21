int clockPin = 10; //SCK
int latchPin = 11; //RCK
int dataPin = 12;  //SDI

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

int led[] = {0x00, 0x80,0xC0, 0xE0, 0xF0, 0xF8, 0xFE, 0xFF};

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(latchPin, LOW);
  for(int i = 0; i < 8; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, led[i]);
    digitalWrite(latchPin, HIGH);
//    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, led[i]);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, LOW);
    delay(100);
  }
  delay(100);
}
