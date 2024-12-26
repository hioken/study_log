# メソッド
## 概要
- オブジェクトの値として、関数式を定義すること
- オブジェクト.メソッド(　== 関数式のプロパティ)で実行可能
- メンバー: オブジェクトが所有しているメソッドのプロパティと関数式をまとめた呼称
- メソッドも、通常の値同様, object.new_method_name = 関数式 で追加できる

## メソッド構文
```js
const object = {
  methodName(arg) {
   //statements; 
  }
}
```

# class
## 概要
- Rubyと違って、クラスというオブジェクトや概念は本質的には存在しない
- ただし、class構文でobjectの型を定義することで、実質classみたいなものを作れる

## 定義
### 基礎
- constructor: initializeと一緒
- this: クラスから生成されるインスタンスを指す
- インスタンスもただのオブジェクトなので、メンバーの追加が可能
- 調べた感じ、classに定数を定義する方法は、静的メンバ以外余りなさそう。。。
### プロトタイプメンバ
- constructor外に定義
- クラスから生成されたインスタンスが共通で参照できるメンバ
- 基本メソッドを定義する
### 静的メンバ
- クラスに定義されたメンバ(classメソッドのようなもの)
- メソッドとプロパティで記述場所が違うので注意
- これを利用して、シングルトンみたいなことが出来る
### 構文
```js
class ClassName {
  ...

//静的メソッド  
  static method_name(arg) {
    //statement
  }
}

//静的プロパティ
ClassName.property = value;

//プロトタイプメンバ(メソッド)の上書き
ClassName.prototype.method_name = ...
```

## 構文
```js
// クラスの定義
class ClassName {
  // メンバ(値)の定義
  constructor(arg1, arg2) {
    this.property1 = arg1;
    this.property2 = arg2;
  }

  // プロトタイプの定義
  method_name(arg) {
    //statements;
  }
}

// インスタンスの生成
new ClassName(arg);
```
