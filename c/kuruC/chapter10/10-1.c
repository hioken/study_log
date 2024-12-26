// #include <stdio.h>

/* void main(void) {
//   int month = 1;
//   double money = 1;
//   for (; money < 1000000; money *= 2) {
//     printf("%02d ヶ月目 : %7.0f 円\n", month, money);
//     month++;
//   }
//   printf("%02d ヶ月目 : %7.0f 円 1,000,000円を超えました。\n", month, money);
// }
*/

#include <stdio.h>

void main(void) {
  int month = 1;
  double money = 1;
  while (money < 1000000) {
    printf("%02d ヶ月目 : %7.0f 円\n", month, money);
    money *= 2;
    month++;
  }
  printf("%02d ヶ月目 : %7.0f 円 1,000,000円を超えました。\n", month, money);
}

/*
〇for, whileの使い分け
・ループ回数が決まっている場合はfor、決まっていない場合はwhileを使うのが分かりやすいらしい
*/
