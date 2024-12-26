#include <stdio.h>

int janken(int p1, int p2) {
  int buf;
  // あいこ
  if (p1 == p2) return 0;

  // p1の勝ち
  buf = p1 + 1;
  if (buf > 3) buf = 1;
  if (buf == p2) return 1;

  // p1の負け
  return 2;
}

void main(void) {
  // 宣言
  int taro, hanako, result;
  result = janken(taro, hanako);

  //入力
  printf("太郎の手、その次に花子の手を入力してください\nパー : 1\n, チョキ : 2\nグー : 3\n", );
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
