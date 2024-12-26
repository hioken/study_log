#include <stdio.h>

int olympic(void) {
  // 宣言、入力
  int year;
  printf("2000年 ~ 2018年の年を、半角数字で入力してください\n");
  scanf("%d", &year);
  // 無効な年の場合プログラムを終了
  if (year < 2000 || year > 2018) {
    printf("無効な年です\n");
    return 1;
  }
  // オリンピックが行われたか判別
  switch(year % 4) {
    case 0:
      printf("夏季オリンピックが開催されました\n");
      return 0;
    case 2:
      printf("冬季オリンピックが開催されました\n");
      return 0;
    case 1:
    case 3:
      printf("オリンピックは開催されていません\n");
      return 0;
    default:
      printf("予期せぬerror\n");
      return 1;
  }
}

void main(void) {
  olympic();
}
