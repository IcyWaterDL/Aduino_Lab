//#include"wiring_private.h"
//#include"pins_arduino.h"

int buzzer_pin = 10;
int knob_pin = A3;

//void my_tone(int pin, int fre) {
//    ICR1 = 250000 / fre; //xung răng cưa tràn sau 250000 / fre p_clock
//    OCR1B = 250000 / fre / 2; //khi TTCN1 == OCR1B thì compare match
//    TCCR1B |= (1 << CS10) | (1 << CS11); // f_clock1 = 16Mhz / 64 
//}

void Tone(int buzzer_pin, int fre) {
  int t_on = 1000000.0 * (1.0 / (float)fre) / 2.0;
  if (fre < 100) {
    int dem = 10;
    while (dem--) {
      digitalWrite(buzzer_pin, HIGH);
      delayMicroseconds(t_on);
      digitalWrite(buzzer_pin, LOW);
      delayMicroseconds(t_on);
    }
  }
  else if (fre < 1000 && fre >= 100) {
    int dem = 100;
    while (dem--) {
      digitalWrite(buzzer_pin, HIGH);
      delayMicroseconds(t_on);
      digitalWrite(buzzer_pin, LOW);
      delayMicroseconds(t_on);
    }
  }
  else {
    int dem = 1000;
    while (dem--) {
      digitalWrite(buzzer_pin, HIGH);
      delayMicroseconds(t_on);
      digitalWrite(buzzer_pin, LOW);
      delayMicroseconds(t_on);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(knob_pin, INPUT);
//  TCCR1A = 0; TCCR1B = 0;// reset 2 thanh ghi
//  TCCR1A |= (1 << WGM11);                 //chọn mode fast pwm(mode 
//  TCCR1B |= (1 << WGM12) | (1 << WGM13);  //top value tự do ICR1)
//  TCCR1A |= (1 << COM1B1); // chế đô so sánh thường non-inverted
}

void loop() {
  // put your main code here, to run repeatedly:
  int knob_value = analogRead(knob_pin);
  int fre = (int)((float)knob_value * 10000.0 / 1023.0);
  Serial.println(fre);
  Tone(buzzer_pin, fre);
//  Tone(buzzer_pin, 524);
//  Tone(buzzer_pin, 588);
//  Tone(buzzer_pin, 660);
//  Tone(buzzer_pin, 698);
//  Tone(buzzer_pin, 784);
//  Tone(buzzer_pin, 880);
//  Tone(buzzer_pin, 988);
//  delay(1000);
}
