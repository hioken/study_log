## 文字列関係のライブラリ
- 目次
・数値変換　atoi/stdlib : "a to integer"
・コピー strcpy/string : "string copy"
・2つの連結 strcat/string : "string concatenation"
・合成 sprintf/stdlib : "string print"
・文字数の取得 strlen/string : "string length"
・比較 strcmp/string : "string compare"
・出力 printf/stdio : "print format"
・入力 scanf/stdil : "string scan format"

〇文字列の数値への変換
#include <stdlib.h>

atoi(対象);

〇文字列のコピー
#include <string.h>

strcpy(コピー先, コピー元); // 文字列全てをコピー

strncpy(コピー先, コピー元, コピーする文字数); // 文字数指定
コピー元[文字数] = '\0'; //strincpyでは、null文字を入れてくれないため

〇文字列の連結
#include <string.h>

strcat(元の文字列, 追加する文字列);


〇自由な文字列の合成
#include <stdlib.h>

sprintf(記憶変数, "保存する文字列(フォーマット指定子を使える)", 必要な数の引数);

例：
#include <stdio.h>

void main(void) {
	char str[100];
	char str1[] = "time";
	char str2[] = "money";
	int i = 3;
	sprintf(str, "%s is %s\nint型も変換可能 : %d\n", str1, str2, i);
	printf(str);
}

〇文字列を数える('\0'を除く)
#include <string.h>

strlen(配列);

〇文字列の比較
#include <string.h>

strcmp(配列1, 配列2) == 0; // strcmpの比較結果が同じなら、0が返る


〇文字列の出力
いつものprintf
地味に知らなったけど、printf(文字列型の配列)で、文字列を表示できる(ただし、%が入っている場合、フォーマット指定子と勘違いされる為注意)

例:
#include <stdio.h>

void main(void) {
	char str[] = "hello %s\n";
	printf(str, "world");
}



〇入力された文字の受け取り
いつものscanf
ただし、最初の引数のフォーマット指定子は %配列の大きさs にしないと、配列より大きい文字が入力された時に暴走する
