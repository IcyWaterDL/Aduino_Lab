/* _BV(bit): Chức năng của nó là chuyển giá trị của tham số bit thành dạng số BYTE có giá trị là là 2^bit(2 mũ bit), thực hiện việc dịch trái bit lần số 1.
  vd: bit = 0      --> 1
    bit = 1      --> 2
    bit = 2      --> 4
    bit = 3      --> 8
    ...
    bit = n      --> 2^n
    Hàm này thường được sử dụng để thực hiện thao tác với 1 bit thứ n nào đó trên một chuỗi bit.
    Giả sử muốn set 1 bit thứ 5 của số: (Number | _BV(5)), xóa bit thứ 5: (Number | (~_BV(5)))
*/

#include <thNumber.h>

int chu_L = SEG7_D | SEG7_E | SEG7_F;
int chu_O = SEG7_A | SEG7_B | SEG7_C | SEG7_D | SEG7_E | SEG7_F;
int chu_N = SEG7_A | SEG7_B | SEG7_C | SEG7_E | SEG7_F;
int chu_G = SEG7_A | SEG7_C | SEG7_D | SEG7_E | SEG7_F | SEG7_G;

int SDI_pin = 10;
int SCK_pin = 11;
int RCK_pin = 12;

void setup()
{
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

void loop()
{
  thNumber.setBitmap(3, chu_L);
  thNumber.setBitmap(2, chu_O);
  thNumber.setBitmap(1, chu_N);
  thNumber.setBitmap(0, chu_G);
  delay(500);
}
