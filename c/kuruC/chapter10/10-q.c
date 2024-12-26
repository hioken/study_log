#include <stdio.h>

void main(void) {
  int score;
  printf("テストの点数を入力してください\n");
  do {
    scanf("%d", &score);
    if (score < 0 || score > 100) printf("正しい値を入力してください\n");
  } while (score < 0 || score > 100);
  printf("テストの点数は%d点でした\n", score);
}
