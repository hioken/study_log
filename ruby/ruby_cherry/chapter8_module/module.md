## moduleとは、用語
- `モジュール`
  - is-aの関係ではないけど、class同士で共通のメソッドが存在する際、そのメソッドをまとめておくもの
  - 名前空間として利用
  - 唯一のオブジェクトとして利用
- `ミックスイン` モジュールのメソッドを特定のクラス、オブジェクトで使えるようにすること

## 記述
- 定義
  ```ruby
  module Module名
  end
  ```
- ミックスイン
  - `include` インスタンスメソッドとして呼び出し
    ```ruby
    class TestClass
      include Module名
    end
    ```
  - `extend` クラスメソッド(特異メソッド)として呼び出し
     - オブジェクトに対して、特異メソッドとしてミックスインもできる
    ```ruby
    class TestClass
      extend Module名
    end

    オブジェクト.extend(Module名)
    ```
  - `prepend` モジュールのメソッド優先でミックスイン
    - メソッドの置き換えが容易

## 仕様
- 特異メソッド、定数はクラス同様に作成出来る
- moduleにmoduleをincludeする事が可能
- `module_function` 指定したメソッドを、特異メソッドとしてもミックスインとしても使用できるようにするメソッド
  - ミックスインした際、自動でprivateになる
  - 記述方法はprivateとかと一緒
- privateはモジュール側に書く
- モジュール内で定義してあるインスタンス変数を読み書きすると、include先のインスタンス変数を読み書きしたことになる
  - ミックスイン先で特定のインスタンス変数がある前提で、設計をするのは良くない
  - やるならメソッドがある前提
  ```ruby
  module NameChanger
    def change_name
      # 良い例、ミックスイン先にアクセサメソッド(def name=)が定義されていないとエラーになる
      self.name = 'Alice'
      # 良くない例、ミックスイン先に@nameが定義されていなくてもエラーにならない
      @name = 'Alice'
    end
  end
  ```

## 既存module
- Enumerable
  - ループ処理
  - include条件: eachが定義されている事
- Comparable
  - 比較演算子
  - include条件: <=>が定義されている事
- Kernel
  - puts等
  - Objectクラスがデフォルトでincludeしている
- Singleton
  - シングルトンパターンを実現する
  - newが出来なくなる

## 名前空間
- クラスより先にmoduleが定義されている前提
- module内にクラスをネストする
- module::クラス名と記述する
- トップレベルのクラスと明記する際は、::クラス名と記述する
```ruby
# ::での記述
module Public
end

class Public::User
end

# ネストでの記述
module Admin
  class User
  end
end

# トップレベル(名前空間に属していない)クラスの指定
class ::User
end
```

## 唯一のオブジェクトとして
- モジュールのクラスメソッドを定義して、そこにインスタンスメソッドを定義する
```ruby
module UrlApi
  @url = ''

  class << self
    attr_accessor :url
  end
end

UrlApi.url #=> この中身は共通で、書き換えた際も保存される
```

## 有効範囲を決める
- `refinements` refineとusingを使って、モジュールのメソッドのスコープを限定する
  - `refine`　引数にクラス、ブロック内に対象のメソッドを記述
  - `using` 使用可能なクラス(またはファイル)に記述する
  ```ruby
  # refinementsのSrringのメソッドを追加
  module StringShuffle
    refine String {
      def shuffle
        chars.shuffle.join
      end
    }
  end

  # Userクラスでモジュールを有効にする
  class User
    using StringShuffle
  end
  ```
