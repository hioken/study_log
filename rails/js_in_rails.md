# js側基礎
## 用語
- **ES6**: 新しいjsの規格
- **Babel**: ES6と5の変換ツール
- **Webpack**:
  - jsのアセットパイプライン
- **Sprockets(3 => 4)**:
  - アセットパイプライン
  - jsがWebpack標準になったのに対して、CSSはまだSprocketsが使われている
- **アセットパイプライン(rails)**: `app/asset`or`app/javascript`
- **importmap**:
  - ESモジュールを管理するためのjs標準仕様のシステム
  - ESモジュール自体はimportmapに依存してはいない

## パッケージマネージャー
- rubyのgem
- npm
- yarn: npmより新しい

## モジュールとして管理
- jsファイルをモジュールとして管理する仕組み
  - それぞれが独立したスコープを持つ
- ESモジュールとはES6で使用されている方式


| **特徴**       | **ESモジュール (ES6)** | **CommonJS (Node.jsの標準)** |
|---------------|-----------------------|---------------------------|
| **構文**      | `import` / `export`   | `require` / `module.exports` |
| **読み込み**   | 静的解析              | 実行時に動的解析           |
| **非同期対応** | 対応                 | 非対応                    |
| **ブラウザサポート** | 対応                 | 非対応（Node.js専用）        |



# Sprokets
## システム
- 複数のjsファイルを一つにまとめる
- jsファイルの圧縮
- ファイルにハッシュ値を付けてブラウザキャッシュを管理
- すべてのスクリプトが1つのグローバルスコープで実行される。
- 順番に読み込まれる

## 読み込み例
`app/assets/javascripts/library.js`
```javascript
//= require library
//= require file
```

`app/assets/javascripts/hello.js`
```javascript
function hello(name) {
  console.log("Hello " + name)
}
```

`app/assets/javascripts/user_greeting.js`
```javascript
function greet_user(name) {
  hello(name)
}
```

`app/views/my_controller/test.html.erb`
```html
<%= javascript_link_tag 'library' %>
<%= javascript_link_tag 'hello' %>
<%= javascript_link_tag 'user_greeting' %>

<!--
<script src="/assets/library-abc123.js"></script>
<script src="/assets/hello-def456.js"></script>
<script src="/assets/user_greeting-ghi789.js"></script>
-->


<button onclick="greet_user('Dire')"></button>
```


# Webpacker
## 概要
- Webpackをrailsで使いやすくするためのgem
## 導入
- 従来はgemをinstallしてapplication.jsでrequire
- rails6だとyarnで行う
- rails assets:precompileを実行すると、assets/とjavascript/を両方コンパイル

## システム
- ES6+サポート: import/export を使用できる。
- 依存管理: npmでJavaScriptライブラリを管理。
- ホットリロード: 開発中にブラウザを自動更新。
- ES6のコードを取り出す
- babel-loaderでBabelにES6をコンパイルさせる
- 出来上がったパックを、HTML DOMにインクルードできる形のファイルにまとめる

## 読み込み
### ファイル管理
- application.jsはapp/javascript/packs/に置かれる
- <%= javascript_pack_tag ‘pack名’ %>でapp/javascript/packs/pack名をインクルード
### 読み込み
- viewからpackにアクセス出来ない
- Webpackがコンパイルするのは、モジュール
  - Sporcketsと同じやり方は出来ない
- アクション等も全部packでセットアップする
### 例
`app/javascript/packs/library.js`
```javascript
import 'library';
import 'file';
```

`app/javascript/packs/hello.js`
```javascript
export function hello(name) {
  console.log("Hello " + name);
}
```

`app/javascript/packs/user_greeting.js`
```javascript
import { hello } from './hello';

export function greet_user(name) {
  hello(name);
}
```

`app/javascript/packs/application.js`
```javascript
import { greet_user } from './user_greeting';

window.greet_user = greet_user;
```

`app/views/my_controller/test.html.erb`
```erb
<%= javascript_pack_tag 'application' %>

<!--
<script src="/packs/js/application-abc123.js"></script>
-->
<button onclick="greet_user('Dire')"></button>
```

# RailsのImportmap管理システム(jsの標準仕様と同じImportmapと呼ぶことが多い)
## 概要・仕様
- importmapを管理するためのgem(importmap-rails)

## 読み込み
### ファイル管理
- importmap.rbで以下を管理
  - モジュールの定義・パス管理
    - 参照先はRailsのアセットパイプラインかCDN
    - ブラウザ
  - モジュールの事前ロード
  - 依存関係の明確か
  - バージョン
  - キャッシュバスティング
### 処理順
1. `importmap.rb`の内容をimportmap(`<script type="importmap">`)内にjsonとして埋め込んだリクエストを返す
2. HTMLパサーがHTML解析
3. jsエンジンがimport文を見つけるとimportmapを参照して、CDNかrailsのアセットパイプラインにリクエスト
4. 3が実行される都度、モジュールとして3のレスポンスを定義
5. 他は通常のHTML+jsの処理

### 記述例
# importmap版

`config/importmap.rb`
```ruby
pin "application"
pin "library"
pin "hello"
pin "user_greeting"
```

`app/javascript/library.js`
```javascript
// ライブラリのコード
console.log("Library loaded");
```

`app/javascript/hello.js`
```javascript
export function hello(name) {
  console.log("Hello " + name);
}
```

`app/javascript/user_greeting.js`
```javascript
import { hello } from './hello';

export function greet_user(name) {
  hello(name);
}
```

`app/javascript/application.js`
```javascript
import { greet_user } from './user_greeting';

window.greet_user = greet_user;
```

`app/views/my_controller/test.html.erb`
```erb
<%= javascript_importmap_tags %>
<!--
<script type="importmap">
{
  "imports": {
    "application": "/assets/application-abc123.js",
    "library": "/assets/library-def456.js",
    "hello": "/assets/hello-ghi789.js",
    "user_greeting": "/assets/user_greeting-jkl012.js"
  }
}
</script>
<script src="/assets/es-module-shims.min.js" async="async" data-turbo-track="reload"></script>
<script type="module">import "application"</script>

<script src="/assets/application-abc123.js"></script>
-->
<button onclick="greet_user('Dire')"></button>
```
