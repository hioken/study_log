〇define
・簡易関数を設定
#include <stdio.h>
#define PRINT_TEMP printf("temp = %d\n", temp)

void main(void) {
  int temp = 1;
  PRINT_TEMP;
}

・引数も設定可能
#define PRINT(X) printf("%s", X)
ただし、通常の引数と違って、計算せずに直接置き換わる
#define SANSU(X) printf("%d", X * 2)
...
SANSU(2 + 3);
これをすると
5 * 2、ではなく、2 + 3 * 2 = 2 + 6になる
そのため、マクロ側にかっこを付けておくのが無難
#define SANSU(X) printf("%d", (X) * 2)
これなら問題がおきない

〇マクロ関数の特徴
・常に読み込まれている
そのため呼び出しが高速
アプリ自体の処理が少し重くなる
・この特徴から、何度も使用される数式などを設定するのに便利
