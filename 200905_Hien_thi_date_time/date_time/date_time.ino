#include<thNumber.h>
#include<Wire.h>
#include<TimeLib.h>
#include<DS1307RTC.h>

tmElements_t tm;

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void my_shiftOut(byte val) { //shiftOut
  byte i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void display_currentTime(int hour, int min, int sec, int date, int month, int year) { //Hiển thị thời gian lên thNumber
  byte bNum[12] = {FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0, FONT7_0};
  byte nam = 11, thang = 9, ngay = 7, giay = 5, phut = 3, gio = 1;
  
  // giờ
  while (hour > 0) {              
    bNum[gio] = DigitFont[hour % 10];
    hour /= 10;
    gio--;
  }
  
  // phút
  while (min > 0) {              
    bNum[phut] = DigitFont[min % 10];
    min /= 10;
    phut--;
  }
  
  //giây
  while (sec > 0) {              
    bNum[giay] = DigitFont[sec % 10];
    sec /= 10;
    giay--;
  }
  
  //ngày
  while (date > 0) {
    bNum[ngay] = DigitFont[date % 10];
    date /= 10;
    ngay--;
  }
  
  //tháng
  while (month > 0) {
    bNum[thang] = DigitFont[month % 10];
    month /= 10;
    thang--;
  }

  //năm
  while (year > 0) {
    bNum[nam] = DigitFont[year % 10];
    year /= 10;
    nam--;
  }
  
  bNum[1] |= _BV(6);
  bNum[3] |= _BV(6);
  bNum[5] |= _BV(6);
  bNum[7] |= _BV(6);
  bNum[9] |= _BV(6);
  bNum[11] |= _BV(6);
  
  for (int i = 0; i < 12; i++) {
    my_shiftOut(bNum[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

tmElements_t getTime(const char *str) {
  int Hour, Min, Sec;
  sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec);
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec + 9; 
  return tm;
}

tmElements_t getDate(const char *str) {
  char Month[12];
  int Day, Year;
  int index;
  uint8_t monthIndex;

  sscanf(str, "%s %d %d", Month, &Day, &Year);
  
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) {
      index = monthIndex;
      break;
    }
  }
  tm.Day = Day;
  tm.Month = index + 1;
  tm.Year = CalendarYrToTm(Year);
  return tm;
}

void print_serial(tmElements_t Time) { // hiển thị thời gian lên Serial monitor
  
  // hiển thị: giờ : phút : giây
  print2digits(Time.Hour);
  Serial.print(":");
  print2digits(Time.Minute);
  Serial.print(":");
  print2digits(Time.Second);
  Serial.println();
}

void print2digits(int number) { //
  if (number >= 0 && number < 10)
    Serial.print('0');
  Serial.print(number);
}

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  getTime(__TIME__);
  getDate(__DATE__);
  RTC.write(tm);
}

void loop() {
  RTC.read(tm);  // đọc dữ liệu từ RTC
  print_serial(tm);
  int Hour = tm.Hour;
  int Min = tm.Minute;
  int Sec = tm.Second;
  display_currentTime();
  delay(1000);
}
