// #include <stdio.h>

// FILE create_file(char file_name[]);
// FILE add_text_file(char file_name[]);

// void main(void) {
//   int method;
//   printf("モードを選んで下さい。\n1 : CSVファイルの作成\n2 : 作成済みのCSVファイルにデータを追記\n")
//   scanf("%d", &method);
//   do {
//     if (method == 1) {

//     } else if (method == 2) {

//     } else {
//       printf("無効な数値です、もう一度入力してください(Ctrl + cでプログラムを終了します。\n");
//     }
//   } while (method < 0 || method > 2);
// }

// commandのオプション版も作る


#include <stdio.h>
#include <string.h>

int column_add(FILE *file, int column_number);
void value_add(FILE *file, int column_number);

void main(void) {
  // 宣言
  static int column_number = 0;  // カラム数
  char file_name[100];  // ファイル名
  FILE *file; // ファイルポインタ

  // ファイル名の入力、オープン
  printf("ファイル名を入力してください。\n");
  scanf("%s", file_name);
  file = fopen(file_name, "w");

  column_number = column_add(file, column_number);

  for (int i = 0; i < 50; i++) {
    // 終了処理
    char buf;
    if (i != 0) {
      printf("続けて入力しますか？ y/n\n")
      scanf("%c", &buf);
    }
    if (buf = 'n') break;

    // カラム追加の関数呼び出し
  }

  fclose(file);
}


int column_add(FILE *file, int column_number) {
  // 入力データ保存用の配列を用意
  char columns[800] = {'\0'};

  // カラムの入力
  while (column_number < 20) {
    // バッファの初期化
    char buf[100] = {'\0'};

    // 入力
    printf("%d番目のカラム名を入力してください。\nendと入力するとレコードの入力に映ります。\nカラムは最大20個まで登録できます。\n", column_number + 1);
    scanf("%s", buf);
    if (strcmp(buf, "end") != 0) break; // endと入力されたら終了

    // 文字列の結合
    if (column_number != 0) {
      strcat(columns, ",");  // 先頭では無かった場合、,で区切る
    }
    sprintf(columns, "%s\"%s\"", columns, buf);  // columnsと入力された値を結合

    // カラム数をカウント
    column_number++;
  }

  // カラムの書き込み
  fprintf(file, "%s\n", columns);

  //アドレスを開放
  // free

  // カラム数を返して終了
  return column_number;
}

void value_add(FILE *file, int column_number) {
  char buf[100]
  scanf("%s", &buf);
}

// 1 ,区切りでデータを入力して、それを一つの文字列として受け取る
// 2 それを1つずつ、ループ処理でvalue[i]に代入する
// 3 value[i]を一つずつvalues[][]に連結していく
