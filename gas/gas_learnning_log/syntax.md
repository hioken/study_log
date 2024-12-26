# 文法
```js
  //メソッド
  function name(argument) {
    //処理
  }
  //宣言
  let a = 1, b = 2;

  //代入
  [a, b, c] = [1, 2, 3]
  {a, b, c} = {a: 1, b: 2, c: 3}

  //配列展開
  ...[1, 2]

  //式展開
  `aaa${variable}`

  //オブジェクトの参照
  object['property']
  object.property

  //条件分岐
  if (expression) {
    //処理
  } else if {
  }

  switch (expression) {
    case value:
      //処理
      break;
    default:
      //処理
  }

  //ループ
    //forはcと一緒
  for (const b of array) {
    //処理
  }

  //例外処理
  try {
    //例外が起こりうる処理
  } catch(variable) { //例外クラスを受け取る変数
    //例外処理
  } finally {
    //例外の有無に関わらず行う処理
  }

  throw object; //raiseと一緒

  // 共通ルール
    // ステートメントが一つの時は、省略可能
    if (true) break;
```

# 変数
|宣言|説明|
|---|---|
|const|定数|
|let|変数|
|ver|関数変数|

# 真偽
## 比較演算
- '1' == 1 はtrue
- '1' === 1 はfalse
## falseの値
- 0, NaN
- ''
- false
- null, undefined

# 条件分岐
- 書き方はcと一緒、switchにbreakは必須

# ループ
## 構文
|構文|説明|
|---|---|
|while||
|for||
|for a of b | bは反復可能な値、aはブロック変数のeach|
|for a in b | bはオブジェクト、aはブロック変数、ブロック変数にはプロパティが入る|
|b.forEach(a => statement)| bは配列、aはブロック変数になる|
|continue, break||

## ラベル
- 多重ループの際、ループの前に level: を付けると、break levelで、そのループまで抜け出せる
