#include <stdio.h>

int janken(int p1, int p2) {
  // あいこ
  if (p1 == p2) return 0;

  if (p1 == 4) {
    return 1;
  } else if (p2 == 4) {
    return 2;
  }

  // 通常の勝ち, 負け
  if ((p1 + 1) % 3 == p2) return 1;
  return 2;
}

void main(void) {
  // 宣言
  int taro, hanako, result;
  result = janken(taro, hanako);

  //入力
  printf("太郎の手、その次に花子の手を入力してください\nグー : 0\n, チョキ : 1\nパー : 2\n", );
  scanf("%d", &taro);
  scanf("%d", &hanako);

  // 結果の表示
  switch(result) {
    case 0:
      printf("あいこです\n");
      break;
    case 1:
      printf("太郎の勝ちです\n");
      break;
    case 2:
      printf("太郎の負けです\n");
  }
}
