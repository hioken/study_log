/*
〇キャスト変換
(データ型)(式);
(int)(x * 1.2);って事も可能
*/

// #include <stdio.h>

// void main(void)
// {
//   int x = 2;
//   printf("%f", (double)(x * 1.2));
// }


#include <stdio.h>

void main(void)
{
  char x = '1';
  //printf("%d", x);
  printf("%d", (int)x);
  char c = (int)'a' + 2;
  printf("%c", c);
  printf("\n");
}
