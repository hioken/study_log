〇構造体の宣言
struct 構造体名(
  データ型1 変数1;
  データ型2 変換2;
)

struct kouzou{
  int id;
  int number;
};


〇構造体への代入
・SQLのinsertを名前を付けて(変数を指定して)実行するみたいな感じ
struct 構造体名 変数名 = {値1, 値2};

struct kouzou testdate = {1, 777};


〇構造体から値を取り出す
printf("id : %d, number : %d", testdate.id, testdate.number);


〇構造体の文字列の変更
# include <string.h>

struct kouzou test;
strcpy(test.moziretu = "data");


〇typedef
・構造体やデータ型に名前をつけられる
～基本～
typedef データ型 名前;

～構造体～
typedef struct 構造体名(省略可能) {
  データ型 変数;
} 名前;
