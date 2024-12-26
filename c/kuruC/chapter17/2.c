// 〇テキストファイルとバイナリファイル
// ・テキストファイルが文字列の普通のファイル
// ・に対してバイナリファイルは2進数で書かれたもの
// バイナリファイルは数値を直接書き込むため、サイズが少なく高速

// 〇バイナリファイルの扱い
// ・基本的にはテキストファイルと一緒だが、モード文字列の末尾にbを付ける
//
// #include <stdio.h>
//
// void main(void) {
  // int buf[] = {10,100,1000,10000};
  // FILE *file;
  // file = fopen("test.dat", "wb");
  // fwrite(buf, sizeof(buf), 1, file);
  // fclose(file);
//
// }
//

#include <stdio.h>

void main(void) {
  int buf;
  FILE *file;
  file = fopen("test.dat", "rb");
  fread(&buf, sizeof(buf), 1, file);
  fclose(file);

  printf("%d\n", buf);

}

〇ファイル操作まとめ
1.FILE型のポインタ宣言
2.ファイルを開く"file = fopen("バス/ファイル名","モード");"
3-1.書き込みをする"fprintf(file, "内容");"
3-2.読み込みをする"fscanf(file, "%", &);"
4.ファイルを閉じる"fclose(file);"
5.読み込みの場合は、読み込んだ情報を利用する

〇モード
・一覧
r : 読み込み、ファイルがないと失敗(read)
w : 書き込み、ファイルが存在しても空のファイルを作成(write)
a : 追記、ファイルが無い場合のみ作成(access?)
・それぞれ後ろに+を付けると読み書き両方できるようになる
・さらに後ろにbを付けると、バイナリファイルを操作できる
