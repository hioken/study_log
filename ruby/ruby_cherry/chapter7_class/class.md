## オブジェクト思考
- ある物事に関して扱うデータ(構造体)と、それに対して仕様するメソッドをひとまとめにしておこう
- それがclass

## メモ
- `private` そのclass ~ end のコード内からでしか呼び出せないメソッド
  - classのインスタンス.privateメソッドが行えない
- `@インスタンス変数` そのclassが所持している変数、データ
  - まだ定義していないインスタンスを呼ぼうとするとnilが返る(**errorにならない**)
- `initialize` そのクラスで扱うインスタンスを定義
  - そのclassに所属している構造体を定義するようなもの
  - Class.newの引数が、値として格納される
  - そのデータは、class内で自由に呼び出せる
  ```ruby
  class User
    def initialize(name)
      @name = name
    end

    def hello
      puts "Hello, #{@name}"
      @aa #=> nil
    end
  end
  ```
- classのインスタンスをnewで複数生成した場合、Class[n]で配列のようにデータを取得できる
- `定数の定義` 大文字の変数で、上の方に定義しておく、c言語のマクロに似てる
  ```ruby
  class Product
    DEFAULT_PRICE = 100

    def initialize(name, price = DEFALUT_PRICE)
      @name = name
      @price = price
    end

    def self.default_price
      DEFAULT_PRICE
    end
  end
  ```

## クラスのインスタンスの読み書き
- クラスのインスタンスは通常、外部から読み書きできない
- `アクセサメソッド` classのインスタンスの値を外部から変更出来るメソッド
  - 以下書き取りを定義するアクセサメソッドの例
  - =で終わるメソッドを書くと、**メソッド名 = 引数**の形で呼び出せるため、代入したように見える
  ```ruby
  class User
    def initialize(name)
      @name = name
    end

    def hello
      puts "Hello, #{@name}"
    end

    def name=(name)
      @name = name
    end
  end
  a = User.new("Alice")
  a.name = "Lily"
  ```
- `attr_accessor` `attr_reader` `attr_writer` アクセサメソッドを省略出来る
  - それぞれ、読み書き、読み取り、書き込み
  ``` ruby
  class User
  attr_accessor :name
    def initialize(name)
      @name = name
    end

    def hello
      puts "Hello, #{@name}"
    end
  end

  a = User.new("Alice")
  a.name = "Lily" #=> 可能
  puts a.name #=> 可能
  ```

## クラスメソッド
- 定義
  - `def self.メソッド名`
  - `class << self; end` の中にネストして書く
- `Class.クラスメソッド名` クラスメソッドの呼び出し

## self
- 基本selfを記述しなくても、selfが記述されている事になる
  - ただし、メソッド内に、代入する形でself無しのインスタンス変数の記述を書くと、ローカル変数として処理される為注意
  ```ruby
  class TestClass
    def initialize(name)
      @name = name
    end

    # 以下はどれも正解
    def hello(name)
      "Hello #{@name}"
    end

    def hello(name)
      "Hello #{self.name}"
    end

    def hello(name)
      "Hello #{name}"
    end

    def name=(new_name)
      # 以下の場合、nameはself.nameにならず、nameというローカル変数として扱われる
      name = new_name
    end

  end
  ```
- selfの意味は場所によって異なる
  - クラス定義の直下、及びクラスメソッドの内 : クラス名
  - インスタンスメソッド内 : レシーバー

## 継承
### 概要、仕様
- is-aの関係であるのが適切な継承
  - サブクラスは、スーパークラスの一部である、と言って違和感がないようにする
  - DVDクラスが商品クラスを継承している時、「DVDは商品の一部」と言って違和感がない
- superでinitialize等も継承出来る
  - initialize等、特別なクラスも、スーパークラスで処理が済むならサブクラスにわざわざ記述しなくていい
- `オーバーライド` スーパークラスで定義したメソッドをサブクラスで上書きすること
  - `super` スーパークラスの同名メソッドの処理を読み込む
    - superの処理が1行の文字列だった場合、"#{super}, ~~~"と文字列を続ける事も可能

### 注意点
- スーパークラスのprivateは、サブクラスでも呼び出せる
- メソッド名とインスタンス変数は、上書きする意図がない限り、名前の被りがないようにする

## メソッドの公開レベル
### レベル
- `public` 外部から呼び出せる
- `protected` クラス内部からのみ呼び出せる : レシーバー付きで呼び出せる
- `private` レシーバー付きでは呼び出せない(=外部から呼び出せない)

### レベルの記述
- 以下、privateと書いたところは、protectedでも可
- privateを書くと、その下のメソッドが全てprivateになる
- private :メソッド名 とメソッドを記述していくと、そこで指定したメソッドのみがprivateになる
- 他にも、privateと書いた後にpublicを指定するなど、書き方は様々

## 定数
- クラス名::定数、で定数を参照可能
- 定数は、破壊的なメソッドや代入によって変更可能
- 定数を変更しないようにするにはfreezeメソッドを使用する
  - 配列やハッシュに対しては、中身までfreezeする必要がある
  - 例 TEISU = ["a", "b", "c"].map(&:freeze).freeze

## 変数の種類
- `ブロック変数`
- `ローカル変数`
- `インスタンスの変数` @を付けて定義する
  - `インスタンス変数`
    - インスタンスメソッド以下で定義されているインスタンス変数
    - インスタンス事に管理される
  - `クラスインスタンス変数`
    - クラス直下、またはクラス変数で定義されている変数
    - つまり定数
  - これらは、スーパークラスとサブクラスでも別々に扱われる
  - 同じ名前のインスタンス変数でも、呼び出し方によって、上記のどれに当てはまるかが変わる
- `クラス変数` @@を付けて定義する
  - スーパークラス、サブクラスで共通の変数
  - どこで定義しようと、同じ扱い(=上書きが可能)
- `グローバル変数` $を付けて定義する
- `組み込み変数` $から始まる用意されていいる変数

## ネスト
- classはネスト出来る
- `外側のClass::内側のClass` ネストした場合、このように参照する
  ```ruby
  class Public
    class User
    end
  end

  user = Public::User.new
  ```

## メソッドの追加
- Rubyのクラスはオープンクラスであるため、メソッドを追加、上書きできる
  - railsではこの機能によりメソッドが多く追加されている
  ```ruby
  # Stringクラスに、文字列をシャッフルするメソッドを追加する
  class String
    def shuffle
      chars.shuffle.join
    end
  end
  ```
  - `モンキーパッチ` 既にあるメソッドを指定した場合、上書きされる
    - モンキーパッチを当てる前に、既存のメソッドを他の名前でaliasとして残して置くことも出来る

## その他
- `alias 新しい名前 元のメソッド` エイリアスメソッドの定義
- `特異メソッド` `def レシーバーの指定.メソッド名` 特異メソッドの定義
  - クラスメソッドは特異メソッドの一部
