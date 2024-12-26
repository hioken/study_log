#include <stdio.h>

int olympic(int year) {
  // オリンピックが行われたか判別
  // コロナの例外処理
  if (year == 2020) {
    printf("コロナウイルスの影響により、オリンピックは開催されていません\n");
    return 0;
  } else if (year == 2021) {
    printf("夏季オリンピックが開催されました\n");
    return 0;
  }
  // 通常の処理
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
  int error = olympic(year);
  if (error == 1) {
    printf("プログラムに異常を発見しました\n");
  } else {
    printf("プログラムは正常に終了しました\n");
  }
}
