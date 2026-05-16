# 前提知識
## マクロ
- `#define`: 定義自由の置き換え
- `__FILE__`: 今のファイル名
- `__LINE__`: 今の行番号

# assert.h
## 概要
- 実質`assert`というマクロのみ
### assertマクロ
- 式の評価が偽(`0`)の場合、`abort`
- 出力内容
  - `__FILE__`
  - `__LINE__`
  - `__func__`
### NDEBUGマクロ
- `assert`の有効・無効を切り替えるスイッチ
- `#include <assert.h>`より前に`#define NDEBUG`が記述されているか、コンパイラ引数で指定されている場合、`assert(式)`は空行に置換される

## 説明
### 流れ
- `assert`はPreProcess, Compile, RunTimeで動作
- Compile以降は、`NDEBUG`未定義時
###### PreProcess: 
- `NDEBUG`未定義: `assert(expr)`は条件分岐コードに置換される
- `NDEBUG`定義: `assert(expr)`は`((void)0)`に置換される
###### Compile
- `assert`の条件が偽だった時に呼び出す標準ライブラリの内部関数へのジャンプ命令が生成される
- `__FILE__`や`__LINE__`から生成された文字列データが、バイナリのデータ領域に埋め込まれる
###### RunTime

- assert.h の中身のイメージ
```c
#undef assert  /* 念のため以前の定義を消す */
#ifdef NDEBUG
    /* NDEBUGがあるなら、assert(ignore) を「空っぽ」に置き換えるルール */
    #define assert(expression) ((void)0)
#else
    /* NDEBUGがないなら、判定コードに置き換えるルール */
    #define assert(expression) \
      ((expression)          \
        ? (void)0          \
        : __assert_fail(#expression, __FILE__, __LINE__, __func__))
#endif
```

# Makefile
## 概要
- c言語系専用のものではない
- コードの依存関係を自動追跡して、変更があった個所だけ再コンパイル

```Makefile
target: file
  shell_command
```

- target: 生成したいファイル名、または実行したいラベル
- file: ソースファイル等
- shell_command: ターゲットを生成するためのシェルコマンド
- 構文: shell_command部分にタブ文字が必須

## アルゴリズム
### 概要
- `make`コマンドの実行時、ツール内部で、依存グラフの構築, タイムスタンプの比較が自動で行われる

## リファレンス
### 代入
| 識別子 | 評価タイミング | 説明 |
| :--- | :--- | :--- |
| `:=` | 定義実行時 | 単純展開。定義した時点で値が確定する。 |
| `=` | 変数参照時 | 再帰展開。変数が実際に使用されるたびに評価する。 |
| `?=` | 定義実行時 | 条件付き代入。変数が未定義の場合のみ代入する。 |
| `+=` | 元の変数に依存 | 追加代入。既存の値の末尾に文字列を追加する。 |

### 自動変数
| 識別子 | 説明 |
| :--- | :--- |
| `$@` | 現在処理しているターゲット名。 |
| `$<` | 必須項目のうち最初のファイル名。 |
| `$^` | すべての必須項目のファイル名。重複は排除する。 |
| `$?` | ターゲットよりタイムスタンプが新しいすべての必須項目名。 |
| `$*` | パターンルール（`%`）に一致した部分の文字列。 |
| `$+` | すべての必須項目のファイル名。重複を排除せず保持する。 |

### 特殊ターゲット
| ターゲット名 | 説明 |
| :--- | :--- |
| `.PHONY` | ターゲットをファイル名ではなく、コマンドのラベルとして扱う。 |
| `.DEFAULT_GOAL` | コマンド引数でターゲットを指定しない場合の既定ターゲットを定義する。 |
| `.SUFFIXES` | サフィックスルールで用いる拡張子を定義する。空にすると旧ルールを無効化する。 |
| `.DELETE_ON_ERROR` | レシピがエラーで終了した場合に作成途中のターゲットファイルを削除する。 |

### 組み込み関数
| 関数名 | 引数 | 説明 |
| :--- | :--- | :--- |
| `subst` | `from,to,text` | 文字列text内のfromをすべてtoに置換する。 |
| | | 使用例: `$(subst a,A,banana)` |
| `patsubst` | `pattern,replacement,text` | text内でpatternに一致する単語をreplacementに置換する。 |
| | | 使用例: `$(patsubst %.c,%.o,main.c test.c)` |
| `strip` | `string` | 文字列の先頭と末尾の空白を削除し、途中の連続した空白を1つにする。 |
| | | 使用例: `$(strip a b c )` |
| `findstring` | `find,in` | 文字列inの中に文字列findが含まれるか検索する。あればfindを返す。 |
| | | 使用例: `$(findstring a,banana)` |
| `filter` | `pattern...,text` | text内の単語のうち、patternのいずれかに一致するものだけを残す。 |
| | | 使用例: `$(filter %.c %.h,main.c main.o main.h)` |
| `filter-out` | `pattern...,text` | text内の単語のうち、patternのいずれかに一致するものを除外する。 |
| | | 使用例: `$(filter-out %.o,main.c main.o)` |
| `sort` | `list` | list内の単語をアルファベット順にソートし、重複を排除する。 |
| | | 使用例: `$(sort b a b)` |
| `word` | `n,text` | text内のn番目の単語を取り出す。1から開始する。 |
| | | 使用例: `$(word 2,a b c)` |
| `words` | `text` | text内の単語の総数を数える。 |
| | | 使用例: `$(words a b c)` |
| `dir` | `names...` | パス名の一覧からディレクトリ部分（最後のスラッシュまで）を抽出する。 |
| | | 使用例: `$(dir src/main.c)` |
| `notdir` | `names...` | パス名の一覧からファイル名部分（最後のスラッシュ以降）を抽出する。 |
| | | 使用例: `$(notdir src/main.c)` |
| `suffix` | `names...` | パス名の一覧から拡張子（ドット含む）のみを抽出する。 |
| | | 使用例: `$(suffix src/main.c)` |
| `basename` | `names...` | パス名の一覧から拡張子を除いた部分を抽出する。 |
| | | 使用例: `$(basename src/main.c)` |
| `addsuffix` | `suffix,names...` | ファイル名一覧の各単語の末尾に指定した拡張子を付与する。 |
| | | 使用例: `$(addsuffix .c,main test)` |
| `addprefix` | `prefix,names...` | ファイル名一覧の各単語の先頭に指定した文字列を付与する。 |
| | | 使用例: `$(addprefix src/,main.c test.c)` |
| `join` | `list1,list2` | 2つのリストの単語を同じ位置同士で結合する。 |
| | | 使用例: `$(join a b,.c .o)` |
| `wildcard` | `pattern` | 指定したパターンに一致する、実際に存在するファイル名の一覧を返す。 |
| | | 使用例: `$(wildcard src/*.c)` |
| `realpath` | `names...` | 指定したファイルの絶対パスを返す。存在しないファイルは無視する。 |
| | | 使用例: `$(realpath main.c)` |
| `abspath` | `names...` | ファイルの存在に関わらず、指定したパスの絶対パスを計算して返す。 |
| | | 使用例: `$(abspath ./main.c)` |
| `if` | `condition,then-part[,else-part]` | conditionが真（空文字以外）ならthen-partを、偽ならelse-partを評価する。 |
| | | 使用例: `$(if $(DEBUG),-g,-O2)` |
| `and` | `condition...` | すべての条件を順に評価し、すべて真なら最後の値を返す。偽があれば空を返す。 |
| | | 使用例: `$(and $(A),$(B))` |
| `or` | `condition...` | 条件を順に評価し、最初に真となった値を返す。すべて偽なら空を返す。 |
| | | 使用例: `$(or $(A),$(B))` |
| `foreach` | `var,list,text` | list内の各単語に変数varに代入しながら、textの評価を繰り返す。 |
| | | 使用例: `$(foreach dir,src include,$(wildcard $(dir)/*))` |
| `file` | `op filename[,text]` | ファイルへの書き込み（`>`、`>>`）や読み込み（`<`）を行う。 |
| | | 使用例: `$(file >out.txt,$(LIST))` |
| `call` | `variable,param...` | 定義済みの多重展開変数を関数として呼び出し、引数を`$1`、`$2`に渡す。 |
| | | 使用例: `$(call my-func,arg1,arg2)` |
| `eval` | `text` | textをMakefileの構文として評価し、その場でパース・実行する。 |
| | | 使用例: `$(eval $(call define-rule,main))` |
| `value` | `variable` | 変数を展開せず、定義されているそのままの文字列を返す。 |
| | | 使用例: `$(value CC)` |
| `origin` | `variable` | 指定した変数がどこで定義されたか（環境変数、コマンドライン等）を返す。 |
| | | 使用例: `$(origin CC)` |
| `flavor` | `variable` | 指定した変数の種類（再帰展開型か単純展開型か）を返す。 |
| | | 使用例: `$(flavor CC)` |
| `shell` | `command` | シェルコマンドを実行し、その標準出力を返す。改行はスペースに置換される。 |
| | | 使用例: `$(shell date)` |
| `error` | `text` | 致命的エラーとして文字列textを出力し、makeの処理を即座に停止する。 |
| | | 使用例: `$(error CC is not defined)` |
| `warning` | `text` | 警告メッセージとして文字列textを出力する。makeの処理は継続する。 |
| | | 使用例: `$(warning Optimization turned off)` |
| `info` | `text` | 情報メッセージとして文字列textを出力する。 |
| | | 使用例: `$(info Building project...)` |