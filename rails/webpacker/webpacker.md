# js側基礎
## アプリ
### パッケージマネージャー
- rubyのgem
- npm
- yarn: npmより新しい


# rails + js
## システム
- 従来は、gemをinstallして、application.jsでrequire
- rails6だとyarnで行う
- rails assets:precompileを実行すると、assets/とjavascript/を両方コンパイル

## Sporcketsの場合
```javascript:app/assets/javascripts/hello.js
function hello(name) {
  console.log("Hello " + name)
}
```

```javascript:app/assets/javascripts/user_greeting.js
function greet_user(name) {
  hello(name)
}
```

```html:app/views/my_controller/test.html.erb
<%= javascript_link_tag 'hello' %>
<%= javascript_link_tag 'user_greeting' %>

<button onclick="greet_user('Dire')"></button>
```

## Webpackの場合
- viewからpackにアクセス出来ない
- Webpackがコンパイルするのは、モジュール
  - Sporcketsと同じやり方は出来ない
- アクション等も全部packでセットアップする
```javascript:app/javascript/packs/user_greeting.js
import $ from 'jquery';
import { hello } from './hello';
function greet_user(last_name, first_name) {
  hello(last_name + " " + first_name);
}
$(document).ready(function() {
  $('button#greet-user-button').on(
    'click',
    function() {
      greet_user('Dire', 'Strait');
    }
  );
});

/* ES6の場合はこうやれる: */
$(() =>
  $('button#greet-user-button').on('click', () => greet_user('Dire', 'Strait'))
);
```

```html:app/views/my_controller/test.html.erb
<%= javascript_pack_tag 'user_greeting' %>
<button id="greet-user-button"></button>
```

# 用語
#### ES6
- 新しいjsの規格

#### Babel
- ES6と5の変換ツール

#### Webpack
- jsのアセットパイプライン
- ES6のコードを取り出す
- babel-loaderでBabelにES6をコンパイルさせる
- 出来上がったパックを、HTML DOMにインクルードできる形のファイルにまとめる

#### Webpacker
- RailsにWebpackerを取り込めるgem
- デフォルト設定
- application.jsはapp/javascript/packs/に置かれる
- <%= javascript_pack_tag ‘pack名’ %>でapp/javascript/packs/pack名をインクルード

#### Sprockets(3 => 4)
- アセットパイプライン
- jsがWebpack標準になったのに対して、CSSはまだSprocketsが使われている
