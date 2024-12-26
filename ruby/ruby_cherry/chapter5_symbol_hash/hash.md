# hash
## hash基礎
### 仕様
- {}.class #=> Hash
### hashの定義
- 基本
  - {'key1' => value1, 'key2' => value2}
  - {}で囲む
  - keyとvalueの組合わせで保存する、,で区切る
  - keyを文字列で指定する場合、'key' => valueの形で記述する
  - keyをシンボルで指定する場合 key: value(:key => value)と記述可能
- 多重hash
  ```
  hash = {a: 'a', b: {c: 'c'}}
  puts [:b][:c] #=> "c"
  ```
- Hash.new(){}でも生成可能、引数を指定すると、存在しないキーを選択した時の戻り値を定義出来る
  - 普通の引数だと初期値の参照が同じ、ブロック引数だと、戻り値を返すたびに違うオブジェクトが生成される
  - 見つからなかった時に、デフォルト値で自動保存
    ```
    h = Hash.new{ |hash, key| hash[key] = 'default' }
    h[:key1]
    p h #=> {:key1 => 'default'}
    ```
### 使い方
- hashのCRUD
  ```
  hash = {japan: 'yen', 'us' => 'dollar'}
  取得
  hash[:japan] #=> 'yen'; hash[:india] #=> nil
  追加/更新
  hash[:india] = 'rupee' #=> {japan: 'yen', 'us' => 'dollar', india: 'rupee'}
  hash[:japan] = '円' #=> {japan: '円', 'us' => 'dollar', india: 'rupee'}
  削除
  hash.delete(:japan)
  ```
- hashの中に他のhashの内容を混ぜたい場合、**を付ける
  ```
  hash1 = {key1: 1, key2: 2}
  hash2 = {**hash1, key3: 3} #=> {key1: 1, key2: 2, key3: 3}
  ```
- hashは比較可能
- ブロックに渡す場合、引数1つの場合は[key, value], 2つの場合はkey, valueの形で渡る
- 普通の引数にhashとしてhashを渡したい場合
  ```
  def method(**引数); end; method({key1: 1, key2: 2}) #=> 引数 == {key1: 1, key2: 2}
  ```
- キーワード引数として渡す事が出来る
  ```
  def method(main: , drink: true)
  end

  params = {main: "fish", drink: true}
  method(params)
  ```
- hashを配列に変換するには、普通にto_aを使えばいい、[[key, value]]の形の2次元配列となる
- 配列をhashに変換するにはto_hを使う、対象が↑の形になっていないとerror
- **引数に使う際は、()の中に書かないとブロックの{}として扱われてしまうため注意**

# symbol
## 仕様
- classはSymbol
- :symbol 又は %s!symbol!
- %iでシンボルの配列を作成可能
- to_s, to_symメソッドで、文字列とシンボルをお互いに変換可能
- 同じシンボルなら同じオブジェクト、参照先が一緒
- 識別子として有効なものを設定できる(123等は設定できない)
  - ''で囲うと、本来使用できない数値等もsymbolも使用できる
  - ""で囲うと、symbolを式展開可能
  - :a と :'a'のobject_idは一緒
- イミュータブル(非破壊的)
- 整数として処理されてるので、メモリ効率が良く処理が高速
