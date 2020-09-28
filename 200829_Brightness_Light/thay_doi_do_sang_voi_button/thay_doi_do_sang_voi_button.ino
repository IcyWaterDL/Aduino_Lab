#include<thButton.h>
#include"wiring_private.h"
#include"pins_arduino.h"

int button4_pin = 8;
int button0_pin = 9;
int button1_pin = 11;
int button2_pin = 12;

int Led4 = 10;

thButton b0(button0_pin);
thButton b1(button1_pin);
thButton b2(button2_pin);
thButton b4(button4_pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(Led4, OUTPUT);
}

void my_analogWrite(int pin, int val) {
  if ( val == 0) digitalWrite(pin, LOW);
  else if (val == 255) digitalWrite(pin, HIGH);
  else {
    TCCR1A = 0; TCCR1B = 0;// reset 2 thanh ghi
    DDRB |= (1 << PB2); // chọn đầu ra PB2 là output(pin 10)
    TCCR1A |= (1 << WGM11);                 //chọn mode fast pwm(mode 
    TCCR1B |= (1 << WGM12) | (1 << WGM13);  //top value tự do ICR1)
    TCCR1A |= (1 << COM1B1); // chế đô so sánh thường non-inverted
    ICR1 = 256; //xung răng cưa tràn sau 255 p_clock
    OCR1B = val; //khi TTCN1 == OCR1B thì compare match
    TCCR1B |= (1 << CS10); // f_clock1 = 16Mhz 
  }
  
}

bool run = false, blink = false;
int dir = -1;
int do_sang = 0;

void check() {
  if (b0.onPress()) {
    run = !run;
  }
  if (b1.onPress()) {
    run = true;
    blink = true; // nháy led
    dir = -1;
  }
  if (b2.onPress()) {
    run = true;
    dir = 1; // tang do sang
  }
  if (b4.onPress()) {
    run = true;
    dir = 0; // giam do sang
  }
}

void giam(){
  if(do_sang < 0) do_sang = 255;
    do_sang--;
}

void tang() {
  if(do_sang > 255) do_sang = 0;
    do_sang++;
}

void loop() {
  check();
  if (run == false) my_analogWrite(Led4, do_sang);
  else {
    if (dir == 1) {
      tang();
      my_analogWrite(Led4, do_sang);
      delay(20);
      my_analogWrite(Led4, 0);
      delay(20);
    }
    else if (dir == 0) {
      giam();
      my_analogWrite(Led4, do_sang);
      delay(20);
    }
    else if(blink == true) {
      my_analogWrite(Led4, 255);
      delay(50);
      my_analogWrite(Led4, 0);
      delay(50);
    }
  }
}
