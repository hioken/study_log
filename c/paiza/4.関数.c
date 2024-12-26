〇main関数を最下行に書かない場合
int sum(一つ目の関数のデータ型, 二つ目の関数のデータ型)

〇関数基本
・値渡しの場合は、引数に変数を使う
・参照受け渡しの場合は、引数にポインタを使う

テータ型 関数名(引数1, 引数2)
{
  処理;
  return 結果;
}

char kansu(hikisu1[10], hikisu2[10])
{
  printf("%s : %s", hikisu1, hikisu2);
  return;
}


〇return
・voidの関数は、return を指定すると、そこで関数の処理が終了する


〇グローバル変数の定義
・関数の外側で定義する


〇構造体と関数
・以下の場合、返り値は{引数, 200, 20}が返る
・それを実現するためか、関数のデータ型がvoidではなくKousou(データ構造型)になっている
typedef struct {
  char name[20];
  int hp;
} Kouzou

Kouzou init(char *name)
{
  Kouzou kouzou

  strcpy(kouzou.name, *name);
  kouzou.hp = 100;
  kouzou.mp = 20;

  return kouzou;
}
