/*
〇文字列型のメモリ確保
1.メモリを固定的に確保(文字巣制限とメモリの無駄が生じる)
2.メモリを可変的に確保(速度が遅い)
大体の言語はどちらかに固定されている
c言語はこの二つの中から選択できる

〇char型の仕組み
・文字コードの仕組みを利用している整数型
・文字一つ一つに番号が付けられていて、その番号を格納している
・Aをchar dataに代入する場合
1.Aをコンパイラが65と解釈、それをdataに代入
2.取り出すときは、char dataの中身65を、文字コードの番号から探して、Aに変換して出力する

〇文字に対する計算
・char型は整数型なので、計算が行える
・A + 9 なら、その番号65に9を足した番号74のJが出力される
・番号は基本順番に設定されているので、この方法で、Aから9つ後のアルファベットはJだということが分かる

#include <stdio.h>

void main(void) {
  char mozi = 'A';
  mozi = mozi + 9;
  printf("%c\n", mozi);
}
*/

/*
〇char型の文字を整数に変換
・この仕組みを利用して、数字のchar型の番号から、'0'(番号48)を引くと、char型の文字をint型に変換できる

#include <stdio.h>

void main(void) {
  char mozi = '8';
  int suuti;
  suuti = mozi - '0';
  printf("%d\n", suuti);
}

これに、文字以外が入力されたら0に変換する条件式を加えたのが、rubyのto_iの仕組み

#include <stdio.h>

void main(void) {
  char c;
  int suuti;

  scanf("%c", &c);

  if (c >= '0' && c <= '9') {
    suuti = c - '0';
  } else {
    suuti = 0;
  }

  printf("変換した数に1を足した物 : %d\n", suuti + 1);
}
*/

/*
〇文字の種類判別関数
・上のプログラムのifの条件を、文字の種類ごとに関数としてまとめてくれているライブラリがある
ライブラリ : #include <ctype.h>
使い方 : if (関数名(対象))
・よく使われそうなのまとめ
10進数 : isdigit
16進数 : isxdigit
大文字 : isupper
小文字 : islower
*/
#include <stdio.h>
#include <ctype.h>

void main(void) {
  char c;
  int suuti;

  scanf("%c", &c);

  if (isdigit(c)) {
    suuti = c - '0';
  } else {
    suuti = 0;
  }

  printf("変換した数に1を足した物 : %d\n", suuti + 1);
}
