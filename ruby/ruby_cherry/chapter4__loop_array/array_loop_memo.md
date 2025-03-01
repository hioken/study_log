# 配列
## 配列の仕様
- 存在しない添え字を指定してもerrorにはならず、nilが返る
- データが宣言されてない添え字には全てnilが入る、以下例
  - array = [0, 1]; array[3] = 3; p array => [0, 1, nil, 3]
- 配列 << 値 で、配列の末尾にデータを追加できる
- 多重代入の値に使用すると、左の変数から順に、配列の値が代入されていく、配列の値の数が足りない場合はnilが代入される
  - a, b, c, d = [0, 1, 2] => a==0, b==1, c==2, d==nil
- 添え字を範囲選択して、そこに値を代入すると、先頭の値のみ代入され、他は削除される
  - a = [0, 1, 2, 3]; a[1, 2] = 100 => a == [0, 100, 3]
- 比較可能(array == array2)
- 文字列は文字の配列として扱える a = 'abcd'
  - a << 'e' => 'abcde'
  - a[1] = 'c' => a == 'accd'
  - a[1..3] => 'bcd'

## ポインタ
- *はc言語のポインタとほぼ一緒 a = [0], b = [1, 2] 
  - a.push(b) => a == [0, [1, 2]]
  - a.push(*b) => a == [0, 1, 2]

## 記述ルール
### 要素の追加
- array << value
  - 配列の最後に値を追加
### 添え字
- 添え字の負の値 arrya[-n]
  - 最後からn番目の要素を取ってくる
- array[n, m]
  - 添え字nからm個分のデータを取り出す、nは負の値も可能
### 連結、集合 a1 = [0, 1, 2, 3]; a2 = [2, 3, 4]
- 連結 a1 + a2 => [0, 1, 2, 3, 2, 3, 4]
- 和集合 a1 | a2 => [0, 1, 2, 3, 4]
  - a2の中から、a1にないもののみをa1の後ろに連結させる
- 差集合a1 - a2 => [0, 1]
  - a2に含まれる数を、a1から除外する
- 積集合 a1 & a2 => [2, 3]
  - a1の中から、a2に含まれている物のみを抽出
### 代入
- *付きの変数で配列を受け取れる
  - *a = [0, 1] => a == [0, 1]
  - a, *b = [0, 1, 2] => a==0, b==[1, 2]


## 配列の基礎メソッド
- 配列の先頭/最後を取り出す
  - array.first
  - array.last
  - 引数を入れると、その数値分のデータを先頭/最後から取り出す
- 配列から値を取り出す
  - array.values_at(添え字1, 添え字2...) 添え字の部分を取り出して配列とする
- 配列からある値を削除
  - array.delete(削除する値)
- 引数を順番に追加
  - array.push(n, m, ...)

## テクニック
### 基礎
- 配列で返る戻り値を別々の変数で受けとる時は、多重代入が便利
  - quotient, remainder = 14.divmod(3) => quotient == 4, remainder == 2
- ポインタを利用して配列を作る a = [0, 1]
  - ['a', 'b', *a, 'c'] => ['a', 'b', 0, 1, 'c']
  - これと一緒 ['a', 'b'] + a + ['c', 'd']

### Arrayクラスのnewメソッド
- 引数
  - a = Array.new == a = []
  - a = Array.new(2) => a == [nil, nil]
  - a = Array.new(3, 0) => a == [0, 0, 0]
  - ※第2引数で初期値を設定した場合、参照先が同じになる(upcaseなどを使用した場合、配列が全て変更される)
  - 上記はブロックを仕様することで回避可能
- ブロック引数
  - a = Array.new(5) { |n| n % 3 + 1} => a == [1, 2, 3, 1, 2]


# ループ
## 仕様
- do end と { } は一緒
- 以下の条件の時のみ { |block| block.メソッド } を (&:メソッド) に書き換えられる
  - ブロックが一つ
  - 処理が1つ
  - メソッドに引数がない
  - 例: array.select { |data| data.odd? } => array.select(&:odd?)

## 文法
### 制御
- `break` 内側のループを抜ける、引数を渡すとそれが戻り値となる
- `catch` throwを行うとcatchの内側のループ処理を全て脱出する、引数は戻り値
  - catch(:シンボル) do ; throw(:シンボル, 引数); end
- `next` このループを中断して次のループに進む
- `redo` このループをやり直す


## テクニック
- 1行でループ処理とその内容を書きたい時は{}を使うと見やすく書ける
  - 配列の合計を出す処理の例 array.each { |number| sum += number}
