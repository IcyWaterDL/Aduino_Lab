int knob_sensor_pin = A3;
int Led = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(knob_sensor_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int knob_value = analogRead(knob_sensor_pin);
//  Serial.println(knob_value);
  int bright = (int)((float)knob_value * 255.0 / 1023.0);
  Serial.println(bright);
  analogWrite(Led, bright);
  delay(200);
}
