## クラス/モジュール

|メソッド|説明|
|---|---|
|**Objectクラス**|-----------------|
|object_id / __id__||
|class, superclass||
|ancestors|継承チェーンの配列を取得|
|instance_methods|引数にfalseを指定すると、superクラスを辿らない|
|extend|引数のモジュールを、対象の特異クラスにincludeする|
|equal? / eql?|オブジェクト同士の id/ハッシュ値 が同一かを調べる|
|(private等_)method?|全てのメソッドや、private等の特定のメソッド一覧|
|dub / clone|オブジェクトを複製(cloneは凍結状態と特異メソッドも含め複製)、どちらもシャローコピー|
|freeze|対象を破壊的メソッドの対象にできなくする|
|taint / untaint / tainted?|汚染関係(Ruby2.7~3.2で廃止)|
|instance_variable _set/_get/s|インスタンス変数、引数には@付きのシンボルか文字列を渡す|
|constants|定数名のシンボルの配列|
|method_missing(name, args*), const_missing|継承チェーン上にメソッド/定数が見つからない時に呼び出されるメソッド、BasicObject/Moduleに定義されている|
|to_s / inspect|文字列表現を取得、inspectはインスタンス変数の内容など、デバッグに向いた情報も文字列化する|
|||
|**Numericクラス**|-----------------|
|ceil / floor(ndigits = 0)|小数点を 切り上げ/切り捨て する|
|round(ndigits = 0, half: :up)|四捨五入、halfで0.5をどうするか指定、:evenの場合、偶数側にする|
|truncate|0から自身の間で近い整数に変換|
|abs|絶対値|
|step(upper, step){ |x| }|upperまでstep分ブロック引数を+=していく|
|divmod||
|||
|**Integerクラス**|-----------------|
|upto / downto, times|upperまでstep分ブロック引数を+=していく|
|||
|**Integerクラス**|-----------------|
|