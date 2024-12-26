〇ファイルの操作
・ファイルの操作には、構造体から成るFILE型のポインタ変数が必要
・ファイルを開く : ポインタ = fopne("ファイル名", "モード");
・ファイルを閉じる : fclose(ポインタ)
・fcloseをしないと、共有ロックがかかったままになる
・書き込み(echo) : fprintf(ポインタ, "内容", フォーマット指定子の内容);
・読み込み : fscanf(ポインタ, "フォーマット指定子", 保存変数のポインタ);



#include <stdio.h>

void main(void) {
  FILE *file;
  int i, j;

  file = fopen("data.txt", "r");
  fscanf(file, "%d, %d", &i, &j);
  fclose(file);
  printf("%d\n", i + j);
}
