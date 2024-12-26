// 〇無限ループの活用
// ・メモ帳：キーがあったら入力、それを表示、これを無限ループ

#include <stdio.h>

int main(void) {
  char x[4];
  for (;;) {
    scanf("%s\n", &x);
    if (x == "end") break;
  }
}

// ・break;はその処理を強制終了させられる
