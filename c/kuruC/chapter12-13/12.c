/*
〇グローバル変数の初期化
・グローバル変数はプログラム開始時に「自動で初期化」される
・グローバル変数が宣言され直す事はそうそうないため

〇ローカル変数の独立性
・同名であっても、変数はスコープが違うと、違う変数として扱われる
・参照する際は、狭いスコープの変数が優先される

〇static変数
・変数の宣言の前にstaticをつけると、静的な変数を宣言できる
・static変数は、使用できる範囲は自信のスコープ、値が保持される範囲はグローバル変数になる
・また、グローバル変数同様、プログラム開始時に自動で初期化される
・関数の呼び出し回数を数えたり、検索で前回見つけた文字位置を記憶する場合に使われる
*/

#include <stdio.h>

int count(void);

void main(void) {
  count();
  count();
  count();
}

int count(void) {
  static int number;
  number++;

  if (number == 1)  {
    printf("1回目の表示 : %d\n", number);
  } else if (number == 2) {
    printf("2回目の表示 : %d\n", number);
  } else {
    printf("3回目の表示 : %d\n", number);
  }

  return 0;
}
