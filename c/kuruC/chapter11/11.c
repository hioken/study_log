/*
〇プロトタイプ宣言
・先頭で関数の形を宣言することで、すべての関数から対象の関数を使えるようにする
・前後関係を気にせず関数を書ける
データ型 関数名(引数);
int nishinsu(nishin);
・これをするために #include <>を先に書いてる
*/

void sigma(int max, int min);
void avg(int max, int min);
void randam_number(int max, int min, int count);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(void) {
  // 計算を選択
  int max, min, method;
  int count;
  printf("計算方式はどちらですか？\nシグマ算: 1\n平均値の算出: 2\n範囲内のランダムな整数をn個生成: 3\n");
  scanf("%d", &method);

  // 数値の入力
  printf("最小値を入力してください(1 ~ 1000)。\n");
  scanf("%d", &min);
  printf("最大値を入力してください(最小値 ~ 1000)。\n");
  scanf("%d", &max);

  //計算処理を分岐
  switch(method) {
    case 1:
      sigma(max, min);
      break;
    case 2:
      avg(max, min);
      break;
    case 3:
      printf("生成する数を入力してください(50個まで)。\n");
      scanf("%d", &count);
      randam_number(max, min, count);
      break;
    default:
      printf("入力が無効です。");
  }
}


void sigma(int max, int min) {
  printf("結果 : %d\n", (max + min) * (max - min + 1) / 2);
}


void avg(int max, int min) {
  printf("結果 : %g\n", (max + min) / 2.0);
}


void randam_number(int max, int min, int count) {
  srand((unsigned int)time(NULL));
  printf("乱数を生成しました\n");
  for (int i = 0; i < count; i++) {
    printf("%4d\n", rand() % (max - min) + min);
  }
}
