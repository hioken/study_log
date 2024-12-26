#include <stdio.h>

void main(void) {
  // 宣言と入力
  int score;
  printf("scoreを入力してください。\n");
  scanf("%d", &score);

  // 修正
  if (score > 100) score = 100; printf("scoreが100より大きいので修正しました。\n");

  // 出力
  printf("score : %d\n", score);
}

/*
〇ブロック文
{ブロック}を使う文をブロック文という、そのまんま
複文ともいう
*/
