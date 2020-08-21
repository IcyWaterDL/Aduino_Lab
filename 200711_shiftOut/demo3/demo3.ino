int latchPin = 11;  // ST_CP / RCK (  12) của 74HC595
int clockPin = 10;  // SH_CP / SCK (pin 11) của 74HC595
int dataPin = 12;   // DS    / SDI (pin 14) của 74HC595
void shift_out_1_byte(int ledStatus)
{
  //digitalWrite(latchPin, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);  
  digitalWrite(latchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
  digitalWrite(latchPin, LOW);
}
void shift_out_2_byte(int byte1, int byte2)
{
  shiftOut(dataPin, clockPin, MSBFIRST, byte2);  
  shiftOut(dataPin, clockPin, MSBFIRST, byte1); 
  digitalWrite(latchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
  digitalWrite(latchPin, LOW);
}
byte led1[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, };
byte led2[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, };
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop()
{
//  shift_out_2_byte(led1[1],led2[1]);
//  delay(500);
//  shift_out_2_byte(led1[2],led2[2]);
//  delay(500);
//  shift_out_2_byte(led1[3],led2[3]);
//  delay(500);
//  shift_out_2_byte(led1[4],led2[4]);
//  delay(500);
  for ( int i=0; i<8; i++)
  {
    shift_out_1_byte(led1[i]);
    delay(500);
  }
//  shift_out_2_byte(led1[5],led2[4]);
//  delay(500);
//  shift_out_2_byte(led1[6],led2[4]);
//  delay(500);
//  shift_out_2_byte(led1[7],led2[4]);
//  delay(500);
//  shift_out_2_byte(led1[8],led2[4]);
//  delay(500);
//  for ( int i=5; i<9;i++)
//  {
//    shift_out_2_byte(led1[i],led2[4]);
//    delay(500);
//  }
//  delay(500);
}
