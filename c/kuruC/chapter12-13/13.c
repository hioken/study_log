〇配列の初期化
・配列の初期値を代入する時、入力しなかったインデックス番号には、0(もしくはnull文字？)が代入される
・この代入方法は、宣言時にしか出来ない

〇sizeof
・sizeof(引数)で、引数のサイズを求められる
・sizeof(配列) / sizeof(配列[0])、配列全体のsizeを、配列1つのsizeで割ると、要素数が求められる

#include <stdio.h>

void main(void) {
  int array[] = {1,9};
  printf("%d\n", sizeof(array) / sizeof(array[0]));
}

// ただし、ループの中の条件に式を使ってしまうと、1ループごとに計算が行われてしまうため、変数に入れるのがbest!
#include <stdio.h>

void main(void) {
  int array[] = {1,2,3,4,5};
  int array_count = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < array_count; i++) {
    printf("%d個目 : %d\n", i + 1, array[i]);
  }
}

〇配列のコピー
・配列のコピーには、forで一つずつ移す、又はmomcpyを使う

〇memocpy
#include <memory.h>

memcpy(コピー先, コピー元, 配列全体のサイズ)

#include <stdio.h>
#include <memory.h>

void main(void) {
  int array1[] = {1,2,3,4,5};
  int array2[5];

  memcpy(array2, array1, sizeof(array1));

  for (int i = 0; i < 5; i++) {
    printf("%d\n", array1[i]);
  }
}
