## データ型
|種類|説明|
|---|---|
|undefined|値が未定義|
|Number|数値型は整数と浮動小数の区切りがなく、/演算は整数同士でも小数点以下まで出す|
|String||
|null|空|

### Array, Object
- 存在しないindexやpropertyを指定するとundifindが返る
- 変数に紐づけたArray, Objectの値を書き換えると、メモリの値も変わる(Rubyと一緒)
```js
// entriesの使い方
for (const [i, v] of array.entries()) {
  // iにindex, vにvalueが入る
}
```

## 組み込みオブジェクト
|種類|説明|
|---|---|
|jsのデータ型に対応||
|Number||
|String||
|Boolean||
|Array||
|Object|オブジェクト|
|Function|関数、関数リテラル|
|jsのデータ型以外に対応||
|Date||
|RegExp||
|Error||
|機能を提供する||
|Math|数学的な定数、関数を提供する|
|JSON|Json型のデータを操作するための関数等を提供する|

### Date
- newの引数
  - 基礎: 年, 月, 日[, 時, 分, 秒, ミリ秒]
  - 文字列
  - タイムスタンプ値
  - Dateオブジェクト
- オブジェクトなので、参照渡しになる点に注意
- Rubyと違って直接演算ができない
```js
// 日付の演算方法(日付の場合)
dateObj.setDay(dateObj.getDay + 1);
```

### Error
- 種類
|種類|説明|
|---|---|
|Error|スタンダード|
|RangeError|値が配列内に存在しない等|
|ReferenceError|存在しない変数を参照|
|SyntaxError||
|TypeError|期待される型ではない|

- 内容
|種類|説明|
|---|---|
|message||
|name|例外名|
|stack|トレース|

### JSON
- jsで扱う場合はオブジェクトに、受け渡す場合は文字列に変換する
- プロパティと文字列はダブルクォーテーションで囲む
```js
[
  {"name": "value"}
]
```


## 主要メソッド
### Number
|メソッド名|説明|
|---|---|
|toString||
### Stirng
|メソッド名|説明|
|---|---|
|toLower / toUpper, match, replace||
|includes|第二引数で検索スコープの開始位置を指定できる|
### Array
|メソッド名|説明|
|---|---|
|indexOf / includes, join, push / pop, sort / reverse||
|concat|非破壊で、引数の配列を強制で展開するpush|
|flat|引数の次元配列以下に配列を平滑化する|
|forEach|配列の各要素に引数を実行|
|filter|selectと一緒|
|map|mapと一緒|
|entries|with_indexみたいな使い方が出来る|
### Function
|メソッド名|説明|
|---|---|
|length|引数の数を取得|
### Date
|メソッド名|説明|
|---|---|
|toString||
|get~|Yearなら年等、~を取得する|
|set~|~を引数に設定する|
### Math
|メソッド名|説明|
|---|---|
|全て静的に呼び出して引数に対して行う||
|ceil / floor / round|切り上げ、切り捨て、四捨五入|
|max / min|スプレッドで展開することで、配列の最大等を求められる|
|random||
### Math
|メソッド名|説明|
|---|---|
|全て静的に呼び出して引数に対して行う||
|freeze / seal / isFrozen||
