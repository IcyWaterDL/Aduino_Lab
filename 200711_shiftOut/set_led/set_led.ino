int clockPin = 11; // sck
int latchPin = 12; // rck
int dataPin  = 10; // sdi

#define Led_on HIGH
#define Led_off LOW

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

byte phep_or = 0x01;
byte output = 0x00;

void set_led(int index, int state) {
  if ( state == Led_on) {
    output = output | ( phep_or << index);
    shiftOut(dataPin, clockPin, MSBFIRST, output);
    digitalWrite(latchPin, HIGH); // bật trang thái vừa update
    digitalWrite(latchPin, LOW); // chân OE = low
    phep_or = 0x01;
  }
  else {
    output = output & ~(phep_or << index);
    shiftOut( dataPin, clockPin, MSBFIRST, output);
    digitalWrite( latchPin, HIGH);
    digitalWrite( latchPin, LOW);
    phep_or = 0x01;
  }
}

void loop() {
  set_led(7, Led_on);
  delay(2000);
  set_led(2, Led_on);
  delay(200);

}
