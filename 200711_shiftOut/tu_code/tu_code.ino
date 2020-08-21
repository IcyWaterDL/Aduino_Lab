int clockPin = 10; // SCK
int latchPin = 11; // RCK
int dataPin = 12; // SDI
void setup() {
  // put your setup code here, to run once:
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

byte led[] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, led[i]);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    delay(100);
  }
  
}
