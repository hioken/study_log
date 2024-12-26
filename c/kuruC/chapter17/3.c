// 〇コマンドライン引数
// ・アプリケーション起動時に渡される文字列
// ・処理するファイル名や動作オプションを指定する目的で使われる事が多い
// ・コマンドラインは配列で指定する？
#include <stdio.h>

int main(int argc,char *argv[])
{
  for (int i = 0; argv[1][i] != '\0'; i++) {
    printf("%d文字目 : %c\n", i + 1, argv[1][i]);
    // if (argv[1][i] == '\\') {
    //   argv[1][i] == '/';
    // }
  }

    if (argc > 1) {
      FILE *file;
      file = fopen(argv[1], "a");
      fprintf(file, "%s\n", argv[2]);
      fclose(file);
    }

    fflush(stdin);
    getchar();

    return 0;
}
