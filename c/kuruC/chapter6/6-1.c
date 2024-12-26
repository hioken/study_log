// #include <stdio.h>

// void main(void) {
//   int x, y;
//   scanf("%d%d", &x, &y);
//   printf("%d\n", x + y);
// }

/*
〇入力
・scanfを使う
・複数指定子を記述すれば、その分入力できる
・なぜか変換指定子のfにはlをつけて%lfにしなければいけない
・以下のコードはどっちも実行可能
*/

// #include <stdio.h>

// void main(void) {
//   char hero[30];
//   int hp;
//   scanf("%s %d", &hero, &hp);
//   printf("%sのHPは%dです", hero, hp);
// }

// void main(void) {
//   char hero[30];
//   int hp;
//   char buf[N];
//   fgets(buf, sizeof(buf), stdin);
//   sscanf(buf, "%s %d", &hero, &hp);
//   printf("%sのHPは%dです", hero, hp);
// }

/*
〇scanfのフォーマット指定子
指定子の間に区切り文字を入れると、その文字で区切る
*/


// これでは,がstringになってしまって上手くいかない
// #include <stdio.h>
// //
// void main(void) {
//   char hero[30];
//   int hp;
//   scanf("%s,%d", &hero, &hp);
//   printf("%sのHPは%dです", hero, hp);
// }

// シグマ算のプログラム
#include <stdio.h>

void main(void) {
  // 宣言
  int max, min, sum;
  // 入力
  scanf("%d %d", &max, &min);
  // 計算
  sum = (max + min) * (min - max + 1) / 2;
  // 出力
  printf("シグマ算の答えは%d\n", sum);
}

// 上のように、コメントアウトを大切にする
