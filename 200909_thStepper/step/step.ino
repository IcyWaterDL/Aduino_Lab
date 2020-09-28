// Kết nối Arduino với thStepper:
//    Arduino pin       thStepper pin
//       10        ---    I3
//       11        ---    I2
//       12        ---    I1
//       13        ---    I0
//       VCC      ---     V+
//       GND      ---     GND

int knob = A3;
int I0_pin = 13;
int I1_pin = 12;
int I2_pin = 11;
int I3_pin = 10;

#include <Stepper.h>
Stepper myStepper(64, I0_pin, I2_pin, I1_pin, I3_pin);

int stepsPerRevolution = 2048;  // số bước để động cơ quay đủ 1 vòng


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);
  pinMode(knob, INPUT);
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int val = analogRead(knob) + 5; 
  int mySpeed = (float)val * 500.0 / 1030.0;
//  Serial.print(val);
//  Serial.print("\t");
//  Serial.print(mySpeed, 3);
//  Serial.print("\t");
//  Serial.println((int)mySpeed);
  myStepper.setSpeed(mySpeed);              // đặt tốc độ = 300
  myStepper.step(-1);       // quay thuận 1 vòng
//  delay(1);
 
}
