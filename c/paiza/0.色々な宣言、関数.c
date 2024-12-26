〇フォーマット指定子のスペース統一
～種類(ポインタ, 文字列, 文字, 整数, float)～
%p, %s, %c, %d, %f

～その文字数になるようにスペースを空ける～
%文字数d



〇マクロ
・文字列の長さを変数のように指定できる
#define N 10

char buf[N];



〇変数の宣言と代入
～通常～
データ型 hensu;

～複数～
データ型 hensu1, hensu2;

～配列～
データ型 array[サイズ];

～ポインタ～
データ型 *pointer;

～２配列の宣言と代入～
データ型 array2[縦のサイズ][横のサイズ] = { {1行目の配列}, {2行目の配列}, ... {n行目の配列}};



〇配列のコピー
#include <string.h>

memcpy(コピー先, コピー元, サイズ);



〇乱数
#include <stdlib.h>
#include <time.h>

srand((unsigned int)time(NULL));
int x = rand(範囲、指定なしも可);

〇void
・引数が何もない
