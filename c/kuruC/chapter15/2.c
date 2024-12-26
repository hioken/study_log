// 〇変数の仕組み
// ・変数はメモリ上に保存されているアドレスに名前を付けたもの
// ・コンパイルされるとき、この名前がアドレスに変換される

// 〇アドレスを調べる
// - コード
// #include <stdio.h>

// void main(void) {
//   int i1, i2, i3, i4, i5;
//   printf("%p\n", &i1);
//   printf("%p\n", &i2);
//   printf("%p\n", &i3);
//   printf("%p\n", &i4);
//   printf("%p\n", &i5);
// }

// - 結果
// 0x7ffc383c125c
// 0x7ffc383c1258
// 0x7ffc383c1254
// 0x7ffc383c1250
// 0x7ffc383c124c
// ・int型は4byte、+-を考慮しないで、約43億までの数字を記憶できる
// ・アドレスも4ずつ数値がずれてる、つまりアドレスは1byteごとに番号がある

// 〇データ型のサイズ
// ・数値型のデータ型は、コンパイラ毎にサイズが異なるが、charは必ず1byteと決まっている
// ・そのためにascii文字しか入らない

#include <stdio.h>

void main(void) {
  char array[6] = "hello";
  int i = sizeof(array) / sizeof(array[0]);
  printf("%p\n", array);
  for (int j = 0; j < i; j++) {
    printf("%p\n", &array[j]);
  }
}

// 〇配列の仕組み
// array[i] = array[0]のアドレス + (i + 1) * sizeof(array[0])のアドレスを参照するということ
