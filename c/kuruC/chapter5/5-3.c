#include <stdio.h>

void main(void)
{
  int x, y, z;
  x = 10;
  y = 200;
  z = 3000;
  printf("1行目: %-4dです\n", x);
  printf("2行目: %-4dです\n", y);
  printf("3行目: %-4dです\n", z);
}

// フォーマット指定子の空白３パターン
// %5d, %-5d, %05d
