#include <stdio.h>

typedef enum {
  none,
  summer,
  winter,
} SEASON;

SEASON olympic(int year) {
  // オリンピックが行われたか判別
  // コロナの例外処理
  if (year == 2020) {
    printf("コロナウイルスの影響により、オリンピックは開催されていません\n");
    return none;
  } else if (year == 2021) {
    printf("夏季オリンピックが開催されました\n");
    return summer;
  }
  // 通常の処理
  switch(year % 4) {
    case 0:
      printf("夏季オリンピックが開催されました\n");
      return summer;
    case 2:
      printf("冬季オリンピックが開催されました\n");
      return winter;
    case 1:
    case 3:
      printf("オリンピックは開催されていません\n");
      return none;
  }
}

void main(void) {
  // 宣言、入力
  int safety = 0;
  int year;
  printf("2000年 ~ 3000年の年を、半角数字で入力してください\n");

  // 入力
  // do { // 無効な年の場合再入力
  scanf("%d", &year);
  // if (year < 2000 || year > 3000) printf("無効な年です、もう一度入力してください\n");
  // safety++;
  // } while (year < 2000 || year > 3000 || safety < 5);
  // 上のプログラムが暴走する

  // プログラムを実行/終了
  SEASON oly = olympic(year);
  printf("%d\n", oly);
}
