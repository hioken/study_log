/*
〇if (変数)
この場合、変数の中身が0以外だったらif文を実行する
*/

// この場合、valueに1以上が入っていたらtrue, valueが未定義、もしくは0が入っていたらfalse
/*
#include <stdio.h>

void main(void) {
  int value;
  // scanf("%d", &value);
  if (value) {
    printf("hello\n");
  } else {
    printf("good bye\n");
  }
}

初期化の概念をもっと大切にしよう、プログラムの性質を決める重要な概念だから、不要じゃない時は書くようにしよう
*/

/*
応用：以下の場合だと、10を入力した時だけfalseを返す、それ以外はtrue
これだけパスワード作れそう
いやそもそも == で作れるやんｗ、でも==の仕組みは分かった、確かにこの理論使えば、足し算だけで==が出来る
*/
#include <stdio.h>

void main(void) {
  int value;
  scanf("%d", &value);
  if (value - 10) {
    printf("hello\n");
  } else {
    printf("good bye\n");
  }
}
