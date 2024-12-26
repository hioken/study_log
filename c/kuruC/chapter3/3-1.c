/*
〇疑似命令
・コードではない命令の事
・機械語に翻訳されず、その前段階で処理される
・#include がそれ <stdio.h>は渡すファイル名
*/

// 〇文字列を出力する
#include <stdio.h> // printfが使えるようになるライブラリ
/*
ちなみに以下がライブラリなしのprintf
extern int printf(__const char * __restrict __format, ...);
*/

void main(void)
{
  printf("Hello\tWorld\n");
  printf("Test\tTextseccond\n");
}


/*
〇エスケープシーケンス
・画面に表示できない制御を行うための特殊文字
\n 改行
\t スペース揃え
・エスケープシーケンスや、文字列制御に使われる\や"を文字列として出力したい場合、\の後のその文字を入れると出力できる
*/
