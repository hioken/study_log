
#include <stdio.h>

int janken(int p1, int p2) {
  // あいこ, 勝ち, 負け
  if (p1 == p2) return 0;
  if (p1 == 3) return 1;
  if ((p1 + 1) % 3 == p2) return 1;
  return 2;
}

void main(void) {
  // 宣言、データ格納
  int taro, hanako, result[4][4];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i][j] = janken(i, j);
    }
  }

  //入力
  for (int i = 0; i < 3; i++) {
    int taro_used_ok = 0, hanako_used_ok = 1;

    printf("太郎の手、その次に花子の手を入力してください\nグー : 0\n, チョキ : 1\nパー : 2\nOK : 3\n");
    scanf("%d", &taro);
    scanf("%d", &hanako);

    // 結果の表示
    switch(result[taro][hanako]) {
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

}
