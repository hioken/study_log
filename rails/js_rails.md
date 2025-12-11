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


# ファイル管理
## Sprokets
### システム
- 複数のjsファイルを一つにまとめる
- jsファイルの圧縮
- ファイルにハッシュ値を付けてブラウザキャッシュを管理
- すべてのスクリプトが1つのグローバルスコープで実行される。
- 順番に読み込まれる

### 読み込み例
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


## Webpacker
### 概要
- Webpackをrailsで使いやすくするためのgem
### 導入
- 従来はgemをinstallしてapplication.jsでrequire
- rails6だとyarnで行う
- rails assets:precompileを実行すると、assets/とjavascript/を両方コンパイル

### システム
- ES6+サポート: import/export を使用できる。
- 依存管理: npmでJavaScriptライブラリを管理。
- ホットリロード: 開発中にブラウザを自動更新。
- ES6のコードを取り出す
- babel-loaderでBabelにES6をコンパイルさせる
- 出来上がったパックを、HTML DOMにインクルードできる形のファイルにまとめる

### 読み込み
#### ファイル管理
- application.jsはapp/javascript/packs/に置かれる
- <%= javascript_pack_tag ‘pack名’ %>でapp/javascript/packs/pack名をインクルード
#### 読み込み
- viewからpackにアクセス出来ない
- Webpackがコンパイルするのは、モジュール
  - Sporcketsと同じやり方は出来ない
- アクション等も全部packでセットアップする
#### 例
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

## RailsのImportmap管理システム(jsの標準仕様と同じImportmapと呼ぶことが多い)
### 概要・仕様
- importmapを管理するためのgem(importmap-rails)

### 読み込み
#### ファイル管理
- importmap.rbで以下を管理
  - モジュールの定義・パス管理
    - 参照先はRailsのアセットパイプラインかCDN
    - ブラウザ
  - モジュールの事前ロード
  - 依存関係の明確か
  - バージョン
  - キャッシュバスティング
#### 処理順
1. `importmap.rb`の内容をimportmap(`<script type="importmap">`)内にjsonとして埋め込んだリクエストを返す
2. HTMLパサーがHTML解析
3. jsエンジンがimport文を見つけるとimportmapを参照して、CDNかrailsのアセットパイプラインにリクエスト
4. 3が実行される都度、モジュールとして3のレスポンスを定義
5. 他は通常のHTML+jsの処理

#### 記述例
##### importmap版

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

# viewでの仕様等
- railsのlink_toのHTTPmethodの変更は、リンクが作動した時にイベントでキャッチしてjs側で無理やり変更しているだけ

# Hotwire
**概要**
- Railsに組み込まれた「高速でインタラクティブなユーザーインターフェースを構築するためのツールキット」。
- アーキテクチャが「ルール」ならば、Hotwireは「提案」に近い。
- Reactなどを用いたSPAではバックエンドとフロントエンドでデータ処理が二重になり、無駄が発生する。
- HotwireではHTMLをレスポンスとして返し、状態管理をサーバーサイドのみで行う。
- **Turbo**、**Stimulus**、**Strada**の3つの技術から構成される。
- **Turbo**はさらに以下の4つに分かれる：
  - **Drive**
  - **Frames**
  - **Streams**
  - **Native**: アプリケーション用

## Turbo
### Turbo概要
- JavaScriptライブラリ。
- 追加でJSを書くことなく、SPAのようなインタラクティブなアプリケーションを構築できる。
- **SPA (Single Page Application)**
  - インタラクティブ（双方向的）な動作。
  - 例: Gmail。
- HTTPメソッド**GET**では動作しない。
- 現在のページのCSS/JavaScriptをそのまま使用することで、高速な画面切り替えを実現。
- Driveは旧turbo-links
- frameとstreamは似ているが、使う場合の思想に違いがある
  - streamは画面全体に大きな影響を及ぼすため、他のフォーマットにも対応するアクションに使う
  - frameは基本このリクエストしか来ないものとして使う(respond_toがいらない設計にしたい)

### 簡易表
| 機能         | 特徴       | 詳細                                         |
|--------------|------------|----------------------------------------------|
| **Turbo Drive** | **全体置換** | レスポンスされたHTMLの`<body>`要素を抜き出して置換する（`<head>`はマージされる）。 |
| **Turbo Frames**| **部分置換** | `<turbo-frame>`タグにのみレスポンスを適用する。          |
| **Turbo Streams**| **複数箇所の更新** | 追加、更新、削除が可能。指定の`<turbo-stream>`タグにレスポンスを適用する。 |

### 詳細表
| 項目 | Turbo Drive（ページ全体） | Turbo Frames（部分ナビゲーション） | Turbo Streams（差分更新） |
|------|---------------------------|--------------------------------------|----------------------------|
| **リクエスト送信時の JS の動作** | `a` / `form` を Turbo がフックして、`fetch` 相当でリクエスト送信。`turbo:click`, `turbo:before-visit`, `turbo:submit-start` などのイベントが飛ぶ。 | `<turbo-frame>` 内の `a` / `form` を Turbo がフックし、その frame 用に `fetch`。`Turbo-Frame` ヘッダ付きで送る。 | 通常のフォーム送信や XHR / ActionCable などから発火。**ナビゲーション用の JS 介入は基本なし**（Drive/Frames みたいにクリック横取りはしない）。 |
| **リクエストの送信形式** | ほぼ通常の HTTP リクエスト（GET/POST 等）。ヘッダに `Accept: text/html`（＋必要に応じて Turbo 独自の Accept）が付く程度。 | 同じく通常の HTTP リクエストだが、ヘッダに `Turbo-Frame: <frame-id>` が付くのが特徴。 | 多くは `Accept: text/vnd.turbo-stream.html` を付けて送るフォーム / XHR、もしくは WebSocket 経由のメッセージ。形式よりも「**返り値が turbo-stream かどうか**」がポイント。 |
| **レスポンスの形式** | **普通の HTML 全ページ**（`<html>〜</html>`）を想定。Turbo が `<body>` と `<title>` を抜き出して使う。 | 通常は **その frame 部分の HTML**（`<turbo-frame id="...">...</turbo-frame>`）を返す。全ページ返ってきた場合も、同じ `id` の `<turbo-frame>` 部分だけ抜き出して差し替える。 | `text/vnd.turbo-stream.html` な **`<turbo-stream>` タグ群**。`<turbo-stream action="append" target="...">...</turbo-stream>` など、「DOM に対する操作命令付き HTML」。 |
| **レスポンス後の URL の変更** | **基本的に変わる**（`pushState` / `replaceState` で履歴を更新）。通常のページ遷移と同じように URL が変化。 | **通常は変わらない。** frame 内だけのナビゲーションなので、ページ全体の URL には影響しない。<br>※ `_top` への遷移やリダイレクトなど特殊ケースでは Drive 相当の遷移になることもある。 | **変わらない。** DOM の一部を書き換えるだけで、ナビゲーションは発生しない。 |
| **レスポンス後の `<title>` の変更** | レスポンス HTML の `<title>` を読んで **書き換える**。 | **基本的に変わらない。** frame 内の更新ではページ全体の `<title>` は触らない。 | **変わらない。** stream はタイトルに手を出さない（変えたければ別途 stream や JS で変更する）。 |
| **レスポンス後のスクロール位置** | 通常は **トップへスクロール**。戻る操作など「復元 visit」の場合は、前のスクロール位置を復元することもある。 | ページ全体のスクロール位置は **基本そのまま**。frame 内でスクロールがある場合は、その要素の中だけ動く。 | ページナビゲーションを行わないので、**スクロール位置はそのまま**。DOM操作の結果でレイアウトが変わったぶんだけ、多少ずれることはあり得る。 |
| **レスポンス受け取り後の JS の動作** | Turbo が `turbo:before-render`, `turbo:render`, `turbo:load` などを発火し、`<body>` を置き換え。既存の JS コンテキストは維持されつつ、新しい DOM に対して Stimulus controller が `disconnect` → `connect` し直される。 | 対象 `<turbo-frame>` の中身だけを差し替え。frame 内の Stimulus controller は `disconnect` → `connect`。ページ全体の JS は基本そのまま。 | Turbo が `<turbo-stream>` タグを1つずつ読み込み、指定された DOM 操作（append / replace / remove 等）を実行。`turbo:before-stream-render` などのイベントが飛ぶこともあるが、ナビゲーション系イベントは発火しない。 |

### 関数, オブジェクト当
#### view
| 名前                          | 種類                  | 簡易説明 |
|-------------------------------|-----------------------|----------|
| turbo_frame_tag               | Railsヘルパーメソッド | `<turbo-frame>` 要素を生成するためのヘルパ。idやsrcなどをRails側から指定して書きやすくする。 |
| <turbo-frame>                 | HTMLタグ              | ページ内の一部分を「ミニ画面」として扱うための枠。中身だけを別URLで読み込んだり差し替えたりできる。 |
| <turbo-stream>                | HTMLタグ              | DOMに対する操作命令（append/replace/removeなど）を表すタグ。クライアント側で解釈され、対象要素に変更が適用される。 |
| turbo_stream.append           | Railsヘルパーメソッド | 指定したターゲット要素に対して、HTMLを末尾に追加する `<turbo-stream>` を生成する。 |
| turbo_stream.prepend          | Railsヘルパーメソッド | 指定したターゲット要素に対して、HTMLを先頭に追加する `<turbo-stream>` を生成する。 |
| turbo_stream.replace          | Railsヘルパーメソッド | ターゲット要素全体を別のHTMLに置き換える `<turbo-stream>` を生成する。 |
| turbo_stream.update           | Railsヘルパーメソッド | ターゲット要素の中身だけを更新する `<turbo-stream>` を生成する（wrapされた要素はそのまま）。 |
| turbo_stream.remove           | Railsヘルパーメソッド | ターゲット要素をDOMから削除する `<turbo-stream>` を生成する。 |
| turbo_stream_from             | Railsヘルパーメソッド | 指定したストリーム名/モデルに対して、Turbo Streamsの購読を行うためのタグ（Action Cable購読のセットアップ）。 |

#### broadcast
| 名前                 | 種類            | 簡易説明 |
|----------------------|-----------------|----------|
| broadcast_append_to  | クラスメソッド  | モデルの変更をトリガーに、指定ストリームへ「append」操作の `<turbo-stream>` をブロードキャストする。 |
| broadcast_prepend_to | クラスメソッド  | モデルの変更をトリガーに、指定ストリームへ「prepend」操作の `<turbo-stream>` をブロードキャストする。 |
| broadcast_replace_to | クラスメソッド  | モデルの変更をトリガーに、指定ストリームへ「replace」操作の `<turbo-stream>` をブロードキャストする。 |
| broadcast_remove_to  | クラスメソッド  | モデルの削除などをトリガーに、指定ストリームへ「remove」操作の `<turbo-stream>` をブロードキャストする。 |

#### js側のイベント
| 名前                          | 種類     | 簡易説明 |
|-------------------------------|----------|----------|
| turbo:click                   | イベント | Turbo Drive がリンククリックを処理するタイミングで発火。ナビゲーション前に処理を差し込むことができる。 |
| turbo:before-visit            | イベント | 新しいURLへの visit が始まる直前に発火。ナビゲーションをキャンセルしたり前処理を実行したりできる。 |
| turbo:visit                   | イベント | visit が開始されたときに発火。ナビゲーション進行中のフックとして使える。 |
| turbo:before-fetch-request    | イベント | fetchでリクエストを投げる直前に発火。ヘッダの追加やログ出力などに使える。 |
| turbo:before-fetch-response   | イベント | レスポンス受信直後、DOM へ反映される前に発火。レスポンスを書き換えたり、処理を差し込んだりできる。 |
| turbo:before-render           | イベント | 新しいHTMLをDOMに適用する直前に発火。差し替えをカスタマイズしたいときに使う。 |
| turbo:render                  | イベント | 新しいHTMLがDOMにレンダリングされたときに発火。後処理やログ、UI初期化などに使える。 |
| turbo:load                    | イベント | Turboによるページ読み込み／遷移が完了したときに発火。従来の `DOMContentLoaded` 的な役割で使われることが多い。 |
| turbo:submit-start            | イベント | Turboがフォーム送信を処理し始めたときに発火。ローディング表示などの開始に使える。 |
| turbo:submit-end              | イベント | フォーム送信の処理が完了したときに発火。ローディング解除や結果に応じたUI更新に使う。 |
| turbo:before-frame-render     | イベント | `<turbo-frame>` の中身を書き換える直前に発火。frameの差し替えをカスタマイズしたいときに使える。 |
| turbo:frame-load              | イベント | `<turbo-frame>` の内容が読み込み完了したときに発火。frame内のUI初期化などに使う。 |
| turbo:before-stream-render    | イベント | `<turbo-stream>` によるDOM操作を適用する直前に発火。streamの適用をカスタマイズ・キャンセルしたいときに使える。 |



### 記述方法
#### Stream(レスポンスが全体)
1. `respond_to { |f| f.turbo_steam }`またはデフォルトで`app/views/controllers/action.turbo_stream.erb`が読み込まれる
2. レスポンス用のviewの`<turbo-stream>`タグのtarget属性の要素をaction属性に従って操作する
- 変数はlocalsで明示する
- 応用
```ruby
# 直接内容を記述
turbo_stream.アクション属性名("target", partial: "partial", locals: (variable: variable))

# 違うテンプレート
render :template
respond_to { |f| f.turbo_stream {render: :template}}
```
#### Frame(レスポンスがパーシャル)
0. 予め置換したい位置を`<turbo-frame id="">`で囲う
1. `render パーシャル内容`で指定した`<turbo-frame>`月のパーシャルを返す
2. `<turbo-frame>`の内容がレスポンスに置き換わる

- 変数はインスタンス変数とlocalsでの明示両対応

### Gem turbo-rails
- Turbo用のGem。
- Turbo自体はRailsから直接使用することも可能。

#### **メリット**
- 記述量の短縮。


## Stimulus

### 概要
- データ属性を使用して、DOM要素に直接アクションを関連付ける。
- 上記のスクリプトをコントローラ単位で管理する。

### 使い方
1. controllerの定義とマッピング(railsの場合はマッピング不要)
2. controller内に使用したいtargetやmethodを定義
3. view側でdata-action="\<actionName\>>-.\<ctrlName>#\<methodName>"等でメソッドを呼び出したりする
- railsの例
```js:app/javascript/controllers/xxx_controller.js
import { Controller } from "@hotwired/stimulus"

export default class extends Controller {
  static targets = ["name"]

  method() {
    console.log('test')
    console.log(`input=${this.nameTraget.value}`)
  }
}

```

```html
<div data-controller="hello">
  <input data-hello-target="name" type="text">
  <button data-action="click->hello#method">挨拶</button>
</div>
```

- マッピング例
```js
// js/main.js
import { Application } from "https://unpkg.com/@hotwired/stimulus@3.2.2/dist/stimulus.js"
import XxxController from "./controllers/xxx_controller.js"

// Stimulusアプリケーション起動
const application = Application.start()

// "xxx" という名前で controller を登録
application.register("xxx", XxxController)
```

### 仕様
#### HTML
| 名前                                      | 種類     | 説明 |
|-------------------------------------------|----------|------|
| data-controller                           | HTML属性 | 要素に紐づける Stimulus controller の名前 `<ctrlName>` を指定する。対応する JS 側の controller 定義と結び付けるトリガーになる。 |
| data-<ctrlName>-target="<tgtName>"        | HTML属性 | `<ctrlName>` controller にとってのターゲット要素をマークする。JS 側の `static targets = ["<tgtName>"]` と組み合わせることで、`this.<tgtName>Target` / `this.<tgtName>Targets` / `this.has<TgtName>Target` が生成される対象になる。 |
| data-action                               | HTML属性 | 任意のDOMイベントと controller メソッドを紐付ける。`<eventName>-><ctrlName>#<methodName>` という形式で、イベント発火時にどの controller のどのメソッドを呼ぶかを宣言する。 |
| data-<ctrlName>-<valName>-value           | HTML属性 | `<ctrlName>` controller の `<valName>` value に初期値や設定値を渡すための属性。JS 側の `static values = { <valName>: Type }` と組み合わせることで、`this.<valName>Value` の値がここから読み込まれる。 |
| data-<ctrlName>-<classKey>-class          | HTML属性 | `<ctrlName>` controller の `<classKey>` class に CSS クラス名を渡すための属性。JS 側の `static classes = ["<classKey>"]` と組み合わせることで、`this.<classKey>Class` の値がここから決定される。 |

#### Controllerのプロパティ定義
| 名前                 | 種類            | 説明 |
|----------------------|-----------------|------|
| static targets = []  | 静的プロパティ  | controller が使用するターゲット名 `<tgtName>` の配列を宣言する。宣言された各 `<tgtName>` について、インスタンス側に `this.<tgtName>Target`（単一要素）、`this.<tgtName>Targets`（要素配列）、`this.has<TgtName>Target`（存在判定の真偽値）が自動生成される。 |
| static values = {}   | 静的プロパティ  | controller が使用する値 `<valName>` とその型情報をオブジェクトで宣言する。宣言された各 `<valName>` について、インスタンス側に `this.<valName>Value`（getter/setter 可能なプロパティ）が生成され、任意で `<valName>ValueChanged(previous, current)` メソッドを定義しておくと、値の変化時にそのメソッドが自動的に呼び出される。 |
| static classes = []  | 静的プロパティ  | controller が使用する CSS クラスキー `<classKey>` の配列を宣言する。宣言された各 `<classKey>` について、インスタンス側に `this.<classKey>Class`（文字列としてのクラス名）と `this.has<ClassKey>Class`（対応するクラス名が設定されているかどうかの真偽値）が自動生成される。(クラス属性のセットを名前付きで保管できる) |

#### Controllerのライフサイクル管理
| 名前         | 種類     | 説明 |
|--------------|----------|------|
| initialize() | メソッド | controller インスタンス生成直後に一度だけ呼び出される。まだDOMへの接続前のタイミングで、インスタンス変数の初期化やメソッドのbindなど、DOM依存性の低い準備処理を行うのに用いる。 |
| connect()    | メソッド | controller が紐づく要素がDOMツリーに接続されたときに呼び出される。Turboによるページ遷移や `<turbo-frame>` 差し替えで要素が画面に現れたタイミングでも呼ばれ、イベントリスナーの登録・タイマー開始・非同期処理の開始など、表示を前提とする初期化処理を担当する。 |
| disconnect() | メソッド | controller が紐づく要素がDOMツリーから取り除かれたときに呼び出される。Turboのページ遷移や部分更新で該当要素が消える際にも呼ばれ、イベントリスナーの解除・タイマー停止・購読解除など、リソース解放やクリーンアップ処理を担当する。 |

#### Controllerのメソッド/プロパティ
| 名前                                    | 種類           | 説明 |
|-----------------------------------------|----------------|------|
| this.element                            | プロパティ     | 該当 controller が紐づいているルート要素。`data-controller="<ctrlName>"` を持つDOM要素そのものが入る。 |
| this.<tgtName>Target                    | プロパティ     | `static targets` に宣言された `<tgtName>` に対応する単一ターゲット要素。`data-<ctrlName>-target="<tgtName>"` が複数ある場合は最初の1つが入る。 |
| this.<tgtName>Targets                   | プロパティ     | `<tgtName>` ターゲットに該当する全ての要素を配列（Array）として保持するプロパティ。各要素は DOM Element オブジェクトになる。 |
| this.has<TgtName>Target                 | プロパティ     | `<tgtName>` ターゲットが1つ以上存在するかどうかを示す真偽値。ターゲットが1つ以上あれば true、0個なら false となる。 |
| this.<valName>Value                     | プロパティ     | `static values` に宣言された `<valName>` の現在値を読み書きする getter/setter。型は宣言時に指定した型情報に基づいて変換される。 |
| <valName>ValueChanged(previous, current)| メソッド       | `<valName>` value が変化した直後に自動的に呼び出されるフックメソッド。引数として変更前の値と変更後の値を受け取る。`static values` で `<valName>` を宣言している場合に任意で定義する。 |
| this.<classKey>Class                    | プロパティ     | `static classes` に宣言された `<classKey>` に対応する単一のCSSクラス名。`data-<ctrlName>-<classKey>-class` から取得されたクラス名が文字列として格納される。 |
| this.has<ClassKey>Class                 | プロパティ     | `<classKey>` に対応するクラス名が設定されているかどうかを示す真偽値。対応する `data-<ctrlName>-<classKey>-class` が存在しない場合などには false になる。 |
