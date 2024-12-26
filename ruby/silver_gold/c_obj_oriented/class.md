# 定義
## スコープ
- クラスにもスコープがある
- 同じ名前でもモジュール内で定義したクラスと、トップで定義したクラスは別物
```ruby
class C1
end

module M
  class C1
  end
end

# これは別物1
c1 = C1.new
m_c1 = M::C1.new
```

# メソッド
## 基礎
- superはsuperクラスの同名メソッドを呼び出す
  - 引数未指定の場合、superを記述したメソッドが受け取った引数をそのまま渡す
  - 引数を指定することも可能
- メソッドが見つからない場合、BasicObjectのメソッドmethod_missingが呼ばれ、その中でNoMethodErrorが起こる
  - method_missingをオーバーライドすれば、メソッドが見つからなかった時の処理をフック出来る

## 別名
- alias式、又はalias_methodメソッドを使う

```ruby
class Foo
  alias method_1 alias_1
  alias_method method_2, alias_2

  def method_1
  end

  def method_2
  end
end
```

## 定義の取り消し
- undef式で、継承チェーンに存在するメソッドの定義を取り消せる
- aliasは取り消されない

```ruby
class Parent
  def method_1
  end

  def method_2
  end
end

class Child < Parent
  undef :method_1, :method_2
end
```

## ネスト
- メソッド内でメソッドが定義されている場合(ネストされている場合)、内側のメソッドは、外側のメソッドが定義されているクラスの所属になる

## 可視性

|可視性|説明|
|---|---|
|public|デフォルト|
|private|レシーバーを省略した形でしか呼び出せない|
|protected|クラス内で記述した場合のみ呼び出せる(クラス外でインスタンスから直接呼び出せない?)|

## 組み込み関数
- Rubyの組み込み関数のようなものは、全部Kernelモジュールのprivateメソッド
  - Kernelモジュールは、Objectクラスがincludeしている
  - トップレベルのselfはObjectだから、ObjectにincludeされているKernelのメソッドが呼び出せる

# 継承関係
## 基礎
- ChildClass < ParentClass で継承関係の是非を確認できる(true, false)
- Object < Kernel < BasicObject
- BasicObject.superclassはnil

## 無名クラス
- モジュールをincludeでMixInすると、継承チェーンのincludeしたクラスの直前に、モジュールに対応した無名クラスが割り込む
  - この無名クラスはancestors等で参照出来ない(代わりにモジュールが入る)
- prependでMixInすると、継承チェーンのprependしたクラスの直後(つまり一番浅い階層)に無名クラスが割り込む

## 特異クラス
### 特異メソッド
- インスタンス毎にメソッドを定義できる
```ruby
foo1 = Foo.new

def foo1.method
end
```

### 特異クラス
- 特異メソッドを定義する、または以下の記述で得意クラスの定義が可能
```ruby
foo1 = Foo.new

class << foo1
end
```

- 特異クラスが定義されると、継承チェーンの一番浅い階層に、特異クラスが割り込む
  - 無名クラスと同じく、ancestors等で参照できず、インスタンスのクラスも特異クラスを定義する前のクラスを指す
- 特異クラスにモジュールをincludeしたい時、オブジェクト.extend(モジュール)と書く事が出来る
- クラスオブジェクトの特異クラスは、そのクラスオブジェクトが継承したクラス(オブジェクト)の特異クラスを継承する

## Refinements
- ある記述以降だけモジュールをextendさせる方法
- クラス内ではなくモジュール内に、extendさせるクラスを書く
  - refine クラス do; end
- using モジュール を記述した以降の行から、ファイル(クラス、モジュール内で記述した場合は定義の終わりまで)の末尾まで、モジュールが有効になる
- using前に定義したメソッドから、モジュールでオーバーライドしたメソッドを呼びだす場合、オーバーライド前のメソッドが呼び出される
```ruby
class Foo
  def method
    'a'
  end

  def mtd
  end
end

module Baz
  refine Foo do
    def method
      'b'
    end
  end
end

using Baz

a = Foo.new
a.method #=> 'b'
a.mtd #=> 'a'
```

# Classクラス
- Class.newでもClassを定義可能
  - 引数にスーパークラス, ブロックに定義内容
- Classクラスにメソッドを定義すると、全クラスから.~で呼びさせる
  - Classのインスタンスであるクラスに対して.~で呼び出すから
  - ClassもObjectを継承しているため、Objectに定義したメソッドはクラスメソッドとしても、インスタンスメソッドとしても使える
- クラスメソッド == Classのインスタンスであるクラスの特異クラスに定義したインスタンスメソッド
  - クラス名.メソッド名で定義するため
```ruby
class Foo
  # self == Foo、def インスタンス.メソッド名で、特異メソッドを定義出来る
  def self.method 
  end

  # class << インスタンス でで特異クラスを定義出来るため、この中に特異メソッドを定義出来る
  class << self 
    def method
    end
  end
end
```