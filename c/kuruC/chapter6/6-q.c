// #include <stdio.h>

// void main(void) {
//   // 宣言
//   // int price, dis1, dis3, dis5, dis8;
//   int price, count[4];
//   double discount[4] = {1.0, 3.0, 5.0, 8.0};
//   // 入力
//   scanf("%d", &price);
//   // 計算
//   for (int i = 0; i < 4; i++) {
//     count[i] = (int)(price * (1 - discount[i] / 10));
//   }

//   // 出力
//   // printf("1割引 : %6d円\n3割引 : %6d円\n5割引 : %6d円\n8割引 : %6d円\n");
//   for (int i = 0; i < 4; i++) {
//     printf("%d割引 : %d円\n", (int)discount[i], count[i]);
//   }

//   int price;
//   scanf("%d", &price);
//   for(int i = 0;i<3;i++)
//     printf("%d,%d",discount[i],price*(1-(discount[i]/10));
// }
// if (hensu)

#include <stdio.h>

void main(void) {
  int hensu = 0;
  int i = 1;
  switch(hensu) {
    case 0:
      printf("%d\n", i);
      break;
  }
}
