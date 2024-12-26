# ブロック
## 概要
- {} で囲んだ処理の固まりのオブジェクト
- ブロックの事

## 記述方法(基礎)
### Proc、ブロック
- `{}` `do end` で囲う、処理がまとめられたもの
- **&を付けるとブロックとして、&を付けないとProcオブジェクトとして扱われる**
- ブロックはメソッドに何も定義されていなくても渡す事が出来る
- `ブロック引数`
  - `||` を{の直後に書いて、中にブロック引数を定義できる(任意)
  - 呼び出す際のyield, callの引数が、ブロック引数に渡される
  - 呼び出し時の引数とブロック引数を比べて、yieldの引数の過分は無視され、不足分はnilで置き換えられる
  - デフォルト値の設定が可能
- 呼び出しの順番
  1. ブロックがメソッドに渡る
  2. yieldでブロックが呼ばれる、yieldの引数がブロック引数に渡る
  3. ブロックが実行される
  4. yieldの後ろの行に戻る

### メソッド側
#### ブロックとして渡された場合
- ブロックは一つしか受け取れない
  - Procオブジェクトは何個でも受け取り可能
- `yield` 渡されたブロックを実行して、その戻り値を返す**構文**(メソッドではない)
- `.block_given?` ブロックの有無を確認するメソッド
```ruby
def greeting
  puts 'Start.'
  if block_given?
    puts yield 'テスト'
  end
  puts 'End.'
end
greeting
#=> ifは実行されない
greeting {|b1, b2| "一つ目: #{b1}\n二つ目: #{b2.class}"}
#=> "一つ目: テスト\n二つ目: NilClass
```
- `&block引数` 引数に&を付けた引数を記述すると、その引数にブロックが格納される
  - メリット
    1. 他のメソッドにブロックを渡せる
    2. ブロックをレシーバーにして、Proc等のメソッドを呼び出せる
  - 記述ルール通り、&を付けないとProcオブジェクトとして扱われる
``` ruby
def relay(name, &block)
  puts block.arity #=> ブロックの数を確認
  greeting(name, &block) #=> 引数とブロックをgreetingに渡す
end

def greeting(name)
   puts yield("こんにちは, ", name)
end

relay("Alice") { |hello, name| "#{hello} #{name}"}
```
#### Procオブジェクトの扱い
- `.call` Procオブジェクトを実行するメソッド
  - Procオブジェクト.call と block_given?がtrueの時のyieldは一緒
- 他のメソッドへ渡す時も、&を付けるとブロックとして、&を付けないとProcオブジェクトを普通の引数として渡される
  - ブロックとして渡っていないと、block_given?はfalseになる
```ruby
def relay_1(&block)
  puts "\n1の結果"
  block_check(&block) # ブロックとして渡す
  puts "End."
end

def relay_2(&block)
  puts "\n2の結果"
  block_check(block) # Procオブジェクトとして渡す
  puts "End."
end

def block_check(arg = "none")
  p block_given?
  p arg
  puts arg.call if arg.class == Proc # 引数がProcならcallを実行
end

relay_1 { |block| block.class }
#=> true, "none"
relay_2 { |block| block.class }
#=> false, #<Prock:~省略~>, NilClass
```

# Procオブジェクト
## 通常のProcの生成
- `Proc.new ブロック`
- `proc ブロック` Kernelモジュールのprocメソッド

## 仕様
### 仕様
- オプション的なのが付く(後述、正式名称が分からない)
- 例えメソッド内で参照されたローカル変数でも、ブロック内で参照されたものはそのまま残る
  - ただしブロック外では使えない
  ```ruby
  def proc_generater
    counter = 10
    Proc.new { counter += 10; p counter }
  end

  a = proc_generater
  a.call
  a.call
  a.call #=> 40が表示される
  p counter #=> error
  ```
- `クロージャ` こういうローカル変数を保持する的なメソッドの事
  - つまりProcはクロージャ

### ラムダ(lambda)
- lambdaというオプションがついたようなProcオブジェクト
- 記述
  - `-> (ブロック引数) ブロック`
  - `lambda ブロック` Kernelモジュールのlambdaメソッド
- 通常との違い
  - 引数に厳格になる(nilの補強等がされない)
  - ラムダ内でreturnを仕様した時、ラムダのブロックを使用しているメソッドから抜けるのではなく、ラムダの処理だけから抜ける
    - つまりそのブロックの戻り値になる
    ```ruby
    def proc_return
      f = Proc.new { |n| return n * 10 }
      ret = [1, 2, 3].map(&f)
      "ret: #{ret}"
    end
    
    def lambda_return
      f = ->(n) { return n * 10 }
      ret = [1, 2, 3].map(&f)
      "ret: #{ret}"
    end
    
    p proc_return #=> 10
    # proc_returnの最終的な戻り値が最初のreturnのn * 10になる
    p lambda_return #=> "ret: [10, 20, 30]"
    # mapの1ループの戻り値がreturnのn * 10として処理される
    ```

### &の詳細
- している事
  1. 右辺をレシーバーにto_procを呼び出す
      - シンボルにto_procは有効
  2. 1の戻り値をブロックに利用する

### シンボル産Proc
- `&:method名` オブジェクトに、ラムダのようにこのオプションが付く
- 通常との違い
  - 呼び出し時の第一引数をレシーバーとする
  - それ以降の第n引数を、メソッドの第n-1引数として受け取る

# 補足
### array.map{ |s| s.upcase} と array.map(&:upcase) が同じ理由
1. &:により、upcaseがシンボル産のProcとなる
2. 1のProcは呼び出し時の第一引数をレシーバーとする
3. mapメソッドは、レシーバーの要素を1つずつ第一引数として、ブロックをyieldする
4. つまり、本来のブロック引数をレシーバーとして、1のProcの元のメソッドの処理を実行する
5. よって、&:メソッドを引数として渡す事が、ブロック引数からそのメソッドを呼び出すブロックを渡す事と一緒になる
