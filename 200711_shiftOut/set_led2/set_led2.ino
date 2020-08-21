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

void my_shiftOut(uint8_t val)
{
  uint8_t i;
  for (i = 0; i < 8; i++)  {
    digitalWrite(dataPin, !!(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);    
  }
}

int output = 0x00;

void set_led2(int index, int state) {
  // put your setup code here, to run once:
  output = output & ~_BV(index) | (state << index); // (y|0)   ~(1 << index)
  my_shiftOut(output);
  digitalWrite( latchPin, HIGH);
  digitalWrite( latchPin, LOW);
}

void shift_out_2_byte(int byte1, int byte2)
{
  digitalWrite(latchPin, LOW); //các đèn LED sẽ không sáng 
  shiftOut(dataPin, clockPin, MSBFIRST, byte2);  
  shiftOut(dataPin, clockPin, MSBFIRST, byte1); 
  digitalWrite(latchPin, HIGH);//các đèn LED sáng với trạng thái vừa được cập nhập
  digitalWrite(latchPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++){
    set_led2(i, Led_on);
    delay(500);
    set_led2(i, Led_off);
    delay(500);
  }
  delay(500);
}
