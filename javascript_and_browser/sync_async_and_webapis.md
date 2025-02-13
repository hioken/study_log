# 非同期(async)
## 基礎
### Jsにおける非同期処理とその他基礎知識
- 非同期処理: ある処理をジョブシステムに入れておいて、先にコールスタック内の他の処理終らせてからコールスタックに入れる仕組み
- ブラウザ上では、メインスレッド内で上記の処理が行われている
- ジョブシステム
  - マクロタスク: タスクキュー
  - マイクロタスク: ジョブキュー
- イベントループが、コールスタックとジョブシステムの間で動作して、コールスタックが空の場合にジョブシステムから処理を取り出してコールスタックに積む
  - コールスタック → ジョブキュー → タスクキューの順で巡回
  - 1回のイベントループで、ジョブキューは全て実行され、タスクキューは1つだけ実行する

### 関数
| **提供API**        | **コンストラクタ名**  | **タスク**  | **関数名**                  | **説明** |
|--------------------|------------------|------------|-------------------------|--------------------------------------------|
| **ECMAScript**    | `Generator`      | -          | `function*` `.next()`    | 非同期イテレーターと組み合わせ可能 |
| **ECMAScript**    | `Promise`        | Micro      | `.then()` `.catch()`     | 非同期処理を管理する基本オブジェクト |
| **ECMAScript**    | `AsyncFunction`  | Micro      | `async/await`           | 非同期処理を同期処理のように書ける |
| **WebAPI / Node** | `Function`          | Micro      | `fetch()` (レスポンス処理) | HTTP リクエストを送信（Promise ベース） |
| **WebAPI / Node** | -                | Macro      | `setTimeout`            | 指定時間後に 1 回だけ関数を実行 |
| **WebAPI / Node** | -                | Macro      | `setInterval`           | 指定時間ごとに繰り返し関数を実行 |
| **WebAPI / Node** | `WebSocket`      | Macro      | `.send()` `.onmessage`  | WebSocket 通信を行う |
| **WebAPI / Node** | `Worker`         | Macro      | `.postMessage()`        | Web Worker を使って並列処理 |
| **WebAPI**        | `XMLHttpRequest` | Macro      | `.open()` `.send()`     | HTTP リクエストを送信（古い方式） |
| **WebAPI**        | `EventSource`    | Macro      | `.onmessage`            | サーバーからのリアルタイムデータを受信 |
| **WebAPI**        | `Notification`   | Macro      | `new Notification()`    | デスクトップ通知を表示 |
| **WebAPI**        | -                | Macro      | `requestIdleCallback()` | ブラウザがアイドル状態のときに処理を実行 |
| **WebAPI**        | -                | Macro      | `requestAnimationFrame()` | 次の描画フレームのタイミングで処理を実行 |
| **Node**         | `Process`        | Micro      | `process.nextTick()`    | 次のイベントループの直前に実行 |


## Promise
### 基本
#### 構成
- `Promise`は`Function`のインスタンス

```js
new Promise(function(resolve, reject){
  resolve(data) || reject(rejectData);
}).then(function(data) {
  // return new Promise ({
    // resolveの引数を受け取ってする処理
  // }); 
}).then( 
  // 並列処理
  // Promise.all([
    // new Promise({}),
    // new Promise({})
  // ])
).catch(function(rejectData) {
  // rejectの処理
}).finally(function(){
  // then または reject終了時
})
```
| **名称** | **役割** |
|----------|----------|
| `[[PromiseState]]` | `pending` / `fulfilled` / `rejected` を管理 |
| `[[PromiseResult]]` | `resolve()` や `reject()` の値を保持 |
| `[[PromiseIsHandled]]` | `catch()` で処理されたかのフラグ |
| `[[PromiseFulfillReactions]]` / `[[PromiseRejectReactions]]` | `.then()` / `.catch()` のコールバックリスト |

#### 説明
**※以下の情報は不確実！！！！！**
##### 基礎
- タスクの実行
  - 実行後、無事完了した場合は`resolve`、エラーが発生した場合は`reject`を実行(明示可能かは不明)
  - 自身の戻り値が`Promise`インスタンスかそうでないかで、`resolve`タイミングが変わる
    - `Promise`インスタンス: 遅延処理を含む、全ての処理が終わるまで待機してから`resolve`
    - `Promise`インスタンス以外: 戻り値が確定した時点で即`resolve`
    - 遅延処理がない場合はどちらも同様の結果を返す
  - エラー発生時に`[[PromiseRejectReactions]]`が見つからない場合、`[[PromiseFulfillReactions]]`のチェーンを調べて、最初に見つかった`[[PromiseRejectReactions]]`を実行
  - 実行終了時、自身の`[[PromiseState]]`に応じて`[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]` の参照先をジョブキューに渡す
    - この時、`rejected`かつ`[[PromiseRejectReactions]]`が存在しない場合はエラーになる
- `resolve(data)` | `reject(data)`
  - 厳密には`new Promise`のコールバック関数の 第一|第二 引数
  - 自身の`[[PromiseState]]`を `fulfilled`|`rejected` に変更し、固定する(後でエラーが起きても変更されない)
  - 自身(`this`)を返す
- `then(data)`メソッド
  - 呼び出し元の`[[PromiseState]]`を確認
    - `fulfilled`|`rejected` だった場合: 第一引数 | 第二引数のコールバック関数をジョブキューに渡す
    - `pending`だった場合: 呼び出し元のコールバックの戻り値の`Promise`の`[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]` に自身の 第一引数|第二引数 と次の処理の参照先(これより後の`then`等)の参照先を格納した、自身(`Promiseインスタンス`)を格納(どの様な形式で格納しているかは調べるの諦めた)
  - 上記の処理後即座にPromiseインスタンスを返す
  - コールバックの戻り値による`resolve`のタイミングの違い
    - `Promiseインスタンス`: コード内の`resolve`を実行
      - `resolve`が定義されていない場合、以降の`then`は実行されない
    - それ以外: `return`のタイミングで`resolve(戻り値)`を実行
      - `return`がなければコールバックが終わった後に`resolve(undefined)`
- `catch(data)`メソッド
  - `then`の第二引数だけバージョン
- `finally(data)`メソッド
  - 呼び出し元の`[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]`両方に格納
- `Promise.withResolvers()`メソッド
  - `new Promise`, `resolve`, `reject`を返し、外部から呼び出せるようにする
#### 並列処理
- `Promise.all([PromiseA, PromiseB])`
  - 起点やthenの引数に記述すると、引数の`Promise`が全て解決されるまで、次のPromiseチェーンを待機させる
  - この時次の引数には`Promise.all`の引数の配列順に、それぞれの戻り値が格納された配列が渡る
  - どれか一つでもエラーが起きた場合、`catch`を実行、引数には最初の`reject`の引数が入る
- `Promise.race([PromiseA, romiseB])`
  - `all`のどれか一つでも処理が終わったら次が実行されるバージョン
- `Promise.any([PromiseA, romiseB])`
  - `all`のどれか一つでも成功したら次が実行されるバージョン
- `Promise.allsettled([PromiseA, romiseB])`
  - 全ての処理を待ち、`reject`が起きてもエラー扱いせず次の処理を実行(`catch`を実行しない)
  - 引数には、前回の処理の戻り値と状態を格納したオブジェクト`{reason: 戻り値, status: [[PromiseState]]の値}`が格納された配列が入る

### AsyncFunction
#### 構成
```js
async function asyncFn() {
  let val = await fn1(0);
  val = await fn1(val);
  return val;
}

asyncFn()
```

| 内部スロット名           | 説明 |
|---------------------|------------------------------------------------|
| `[[AsyncContext]]` | `async function` の **現在の実行コンテキスト（await の状態を含む）** |
| `[[Promise]]`      | `async function` の **実行結果を保持する `Promise`** |
| `[[AwaitedValue]]` | `await` した **Promise の解決結果（or エラー）** |

#### 説明
- `Promise`の準シンタックスシュガー
- `async function~`で`AsyncFunction`のインスタンス関数を定義できる
  - `AsyncFunction`のコンストラクタは`Function`
- `async関数`内では、内部スロットに常に最後に実行された`resolve`または`reject(エラー含む)`の結果を保持する
- `return val`: `resolve(val)`を実行した時と同じ動作をする
- `await fn(val)`:
  - `内部スロットの保持Promise.then(fn)`と同じほぼ動作
  - 戻り値は、`fn`内の`resolve`の引数

### 補足
```js
function sleep(val) {
  return new Promise(function(resolve) {
    setTimeout(function() {
      console.log(val++);
      resolve(val);
    }, 1000);
  });
}

// async
async function asyncFn1() {
  let val = await sleep(0);
  val = await sleep(val);
  const result = await asyncFn2(val);
}

async function asyncFn2(val) {
  val = await sleep(val);
  val = await sleep(val);
}

asyncFn1();

// async無し
new Promise((resolve) => { resolve() }).then(function() {
  return sleep(0)
}).then(function(val) {
  return sleep(val);
}).then(function(val) {
  return new Promise(function(resolve){
    resolve(val);
  })
}).then(function(val) {
  return new Promise((resolve) => { resolve() }).then(function() {
    return sleep(val);
  }).then(function(val) {
    return sleep(val);
  }).then(function(val) {
    return new Promise(function(resolve){
      resolve(val)
    });
  });
});


```

### Fetch
#### 説明
- `fetch(url, options = null)`は`Web APIs`に定義されている、通常の`Function`コンストラクタのインスタンス
  - 取得情報を`resolve`の引数として返す`Promise`を返す。
  - `resolve`の引数には`Response`インスタンスのオブジェクトが返る

#### options
| プロパティ       | 値                                       | デフォルト       | 説明                                   |
|--------------|-------------------------------------|--------------|--------------------------------------|
| `method`    | `"GET"`, `"POST"`, `"PUT"`, `"DELETE"` など | `"GET"`       | HTTP メソッドを指定                  |
| `headers`   | `{ "Content-Type": "application/json" }` など | `{}`          | リクエストヘッダーを指定              |
| `body`      | `JSON.stringify({ key: "value" })` など   | `null`        | `POST` / `PUT` 時の送信データ        |
| `mode`      | `"cors"`, `"no-cors"`, `"same-origin"`  | `"cors"`      | クロスオリジンリクエストの許可範囲     |
| `credentials` | `"omit"`, `"same-origin"`, `"include"` | `"same-origin"` | Cookie などの認証情報の送信設定       |
| `cache`     | `"default"`, `"no-store"`, `"reload"`  | `"default"`   | キャッシュの利用方法                  |
| `redirect`  | `"follow"`, `"manual"`, `"error"`     | `"follow"`    | リダイレクトの処理方法                |
| `referrer`  | `""`, `"no-referrer"`, `"client"`    | `"client"`    | 送信する `Referer` ヘッダーの値       |
| `keepalive` | `true`, `false`                      | `false`       | ページ移動後もリクエストを継続するか    |
| `signal`    | `AbortSignal`                        | `undefined`   | リクエストの中断に使う `AbortController` |


#### Responseインスタンス
| プロパティ / メソッド | 説明 |
|----------------|----------------------------------------------|
| **`status`**  | HTTP ステータスコード（例: `200`, `404`） |
| **`ok`**  | ステータスコードが `200-299` のとき `true` |
| **`headers`**  | `Headers` オブジェクト（レスポンスヘッダーを管理） |
| **`body`**  | **`ReadableStream`（レスポンスのボディデータ）** |
| **`json()`**  | **`body` をすべて取得して JSON に変換（`Promise` を返す）** |
| **`text()`**  | `body` をテキストとして取得（`Promise<string>`） |
| **`blob()`**  | `body` を `Blob`（バイナリデータ）として取得（`Promise<Blob>`） |
| **`arrayBuffer()`**  | `body` を `ArrayBuffer` として取得（`Promise<ArrayBuffer>`） |
| **`clone()`**  | `Response` を複製（`body` は再利用不可なのでコピーする必要あり） |

#### jsonの取得例とテストコード
```js
// jsonの取得例
async function fetchFn() {
  const response = await fetch('接続先')
  const json = await response.json()
}

// テストコード
fetch("https://jsonplaceholder.typicode.com/posts/1")
  .then(response => response.json())
  .then(data => console.log(data))
  .catch(error => console.error("Error:", error));
```

# WebAPIs
## レンダリング処理時に作成される要素

| データ構造               | 作成タイミング                        | 説明                                      | 影響するJS操作 |
|------------------------|---------------------------------|---------------------------------|------------------------------|
| **IDハッシュマップ**     | HTMLパース時                     | `id` をキーに要素を管理            | `id` 指定で要素を検索する時 |
| **Class ハッシュマップ** | DOM構築時（動的変更あり）         | `class` ごとに要素をリスト管理       | `class` 指定で要素を検索する時 |
| **Name ハッシュマップ**  | `name` 属性を持つ要素が追加された時 | `name` ごとに要素をリスト管理        | `name` 指定で要素を検索する時 |
| **スタイルキャッシュ**   | CSS適用時 & `getComputedStyle()` 実行時 | 計算済みのスタイル情報を保存          | スタイルを取得する時 |
| **レイアウトキャッシュ** | レイアウト計算後                   | 要素の `offsetWidth` などの情報を保存 | 要素のサイズや位置を取得する時 |
| **イベントリスナーリスト** | `addEventListener()` 実行時         | 要素ごとに登録されたイベントを管理      | イベントリスナーを追加・削除する時 |
| **アニメーションキャッシュ** | `transform` や `opacity` 変更時   | GPU最適化のためのデータを管理         | アニメーションや変形を適用する時 |

## DOM
### オブジェクト
#### 一覧
| オブジェクトの種類       | 特徴 |
|------------------|-------------------------------------------|
| `Element`       | **HTMLタグを表すオブジェクト** |
| `Text`          | **テキストノード（タグなしの文字）** |
| `Comment`       | **HTML内のコメントノード** |
| `Document`      | **HTML全体（ルート）を表すオブジェクト** |
| `DocumentFragment` | **軽量な仮想DOMコンテナ（DOMに直接表示されない）** |
| `Attr`          | **属性ノード（HTMLの属性を表す）※通常は使わない** |
| `HTMLCollection` | **動的な要素リスト（`Element` のみを含む）** |
| `NodeList`      | **`Element` や `Text` などを含むリスト（静的 or 動的）** |
| `StyleSheetList` | **ページ内のスタイルシートのリスト** |

#### 原子型
- メモリ上の一意のデータの参照を保存している
- DOM上に存在する要素に変更を加えた場合、DOMを実際に操作する
- DeepCopyやCreateを行った際は、DOM上にはない要素がメモリに展開される
- Node追加系のメソッド等の追加動作の追加要素に、既にDOM上にあるElementを指定すると移動する

#### 列挙型
| 型名               | 動的 or 静的 | ループ処理の可否               | Arrayとの違い |
|------------------|------------|------------------------------|----------------------|
| `HTMLCollection` | **動的**    | `for in`, `for of`            | 配列メソッドが使えない / `querySelectorAll` とは異なる |
| `NodeList`（動的） | **動的**    | `for in`, `for of`            | `childNodes` で取得するとテキストノードも含む |
| `NodeList`（静的） | **静的**    | `for in`, `for of`, `forEach` | `querySelectorAll` の結果は固定 |
| `StyleSheetList` | **動的**    | `for in`, `for of`            | CSSルールのリスト、配列メソッド不可 |
| `Array`          | **静的**    | `for in`, `for of`, `forEach`, `map/filter` | メソッドが豊富で `map` / `filter` などが使える |


### メソッド
#### 取得系
| メソッド / プロパティ               | 取得対象                                        | 返り値の型         | 特徴 |
|--------------------------------|--------------------------------|----------------|------------------------------|
| `document.getElementById(id)`          | `id` が一致する最初の要素                  | `Element`      | **最速**（IDハッシュマップを参照） |
| `document.getElementsByClassName(class)` | `class` が一致するすべての要素              | `HTMLCollection` | **動的**（要素の増減をリアルタイムで反映） |
| `document.getElementsByTagName(tag)`    | 指定したタグ名のすべての要素                 | `HTMLCollection` | **ページ全体 or 親要素から検索** |
| `document.getElementsByName(name)`      | `name` 属性が一致するすべての要素           | `NodeList`     | **主にフォーム要素で利用** |
| `document.querySelector(selector)`      | **CSSセレクタで指定した最初の要素**          | `Element`      | **柔軟だが `getElementById()` より遅い** |
| `document.querySelectorAll(selector)`   | **CSSセレクタで指定したすべての要素**        | `NodeList`     | **静的リスト（動的変更を反映しない）** |
| `element.closest(selector)`            | 指定したセレクタに**最も近い親要素**         | `Element`      | **親方向に探索する（子要素には使えない）** |
| `element.matches(selector)`            | **要素が指定したセレクタに一致するかを判定** | `boolean`      | **`if` 条件での要素判定に便利** |
| `document.body`                         | `<body>` 要素                              | `Element`      | **ページの本体に直接アクセス** |
| `document.documentElement`              | `<html>` 要素                             | `Element`      | **ページ全体のルート要素** |
| `document.head`                         | `<head>` 要素                             | `Element`      | **メタ情報やスタイルシートを管理** |
| `document.activeElement`                | **現在フォーカスされている要素を取得**      | `Element`      | **`input` や `textarea` で便利** |
| `document.scrollingElement`             | **スクロール可能な要素を取得**              | `Element`      | **`document.documentElement` または `document.body` を返す** |
| `document.forms`                        | **ページ内のすべてのフォーム要素**         | `HTMLCollection` | **`document.forms[0]` で1つ目のフォームを取得** |
| `document.links`                        | **ページ内のすべての `<a>`（リンク）要素** | `HTMLCollection` | **`href` を持つリンクのみ取得** |
| `document.images`                       | **ページ内のすべての `<img>` 要素**        | `HTMLCollection` | **画像の管理に便利** |
| `document.scripts`                      | **ページ内のすべての `<script>` 要素**     | `HTMLCollection` | **動的にスクリプトを操作する時に使う** |
| `document.styleSheets`                  | **ページ内のすべてのスタイルシート**       | `StyleSheetList` | **CSSの動的変更に利用** |
| `element.children`                      | **要素の直下の子要素（要素ノードのみ）**    | `HTMLCollection` | **テキストノードは含まれない** |
| `element.childNodes`                    | **要素の直下の全ノード（テキスト含む）**    | `NodeList`     | **改行や空白もノードとしてカウント** |
| `element.firstElementChild`             | **最初の子要素を取得**                     | `Element`      | **テキストノードは無視** |
| `element.lastElementChild`              | **最後の子要素を取得**                     | `Element`      | **テキストノードは無視** |
| `element.previousElementSibling`        | **直前の兄弟要素を取得**                   | `Element`      | **`null` になることもある** |
| `element.nextElementSibling`            | **直後の兄弟要素を取得**                   | `Element`      | **`null` になることもある** |

#### 変更系
| メソッド / プロパティ       | アクション | 戻り値 | 特徴 |
|----------------------------|----------|------------------------|-------------------------------------------|
| `document.createElement(tag)` | ノード作成 | `Element` | 新しい要素ノードを作成 |
| `document.createTextNode(text)` | テキスト作成 | `Text` | テキストノードのみを作成（HTMLタグは解釈しない） |
| `document.createComment(text)` | コメント作成 | `Comment` | コメントノードを作成 |
| `element.appendChild(node)` | ノード追加 | 追加した `Node` | 指定要素の最後に子ノードを追加 |
| `element.prepend(node)` | ノード追加 | `undefined` | 指定要素の最初に子ノードを追加 |
| `element.insertBefore(newNode, referenceNode)` | ノード追加 | 追加した `Node` | 指定した要素の前に新しい要素を挿入 |
| `element.before(node)` | ノード追加 | `undefined` | 指定要素の前にノードを追加（自身の兄弟要素として） |
| `element.after(node)` | ノード追加 | `undefined` | 指定要素の後にノードを追加（自身の兄弟要素として） |
| `element.removeChild(node)` | ノード削除 | 削除した `Node` | 親要素から指定の子要素を削除 |
| `element.remove()` | ノード削除 | `undefined` | 自分自身を削除（親要素を指定せずに実行可能） |
| `element.replaceChild(newNode, oldNode)` | ノード置換 | 置き換えられた `Node` | 既存のノードを新しいノードで置き換える |
| `element.cloneNode(deep)` | ノード複製 | `Element`（または `Node`） | `true` で子要素も含めて複製 |
| `element.textContent` | テキスト編集 | `string`（取得時） | HTMLタグを無視してテキストを変更できる |
| `element.innerHTML` | HTML編集 | `string`（取得時） | HTMLタグを含めて変更できるが、セキュリティリスクがある |
| `element.outerHTML` | HTML編集 | `string`（取得時） | 要素自身を含むHTMLを取得・変更 |
| `element.setAttribute(name, value)` | 属性追加・変更 | `undefined` | 指定した属性を追加または変更 |
| `element.getAttribute(name)` | 属性取得 | `string` または `null` | 指定した属性の値を取得 |
| `element.removeAttribute(name)` | 属性削除 | `undefined` | 指定した属性を削除 |
| `element.classList.add(className)` | クラス追加 | `undefined` | クラスを追加 |
| `element.classList.remove(className)` | クラス削除 | `undefined` | クラスを削除 |
| `element.classList.toggle(className)` | クラス切り替え | `boolean`（追加後の状態） | クラスの追加・削除をトグル |
| `element.classList.contains(className)` | クラス判定 | `boolean` | 指定したクラスが含まれているか判定 |
| `element.style.property = value` | インラインスタイル変更 | `string`（取得時） | `style="..."` を直接変更 |
| `element.getBoundingClientRect()` | 位置・サイズ取得 | `DOMRect` | 要素の位置やサイズを取得 |
| `element.scrollIntoView()` | スクロール | `undefined` | 指定要素を画面内にスクロール |

## イベントリスナー
### 説明
- `addEventLisner(event, callback(event), options))`でイベントリスナーを追加削除する
- コールバック
  - 引数は`Event`オブジェクト
  - `this`はイベントを起こしたElement
- `options`

| **オプション** | **型** | **意味** |
|-----------------|------|---------------------------|
| `capture` | `boolean` | `true` にするとキャプチャリング（親 → 子）になる |
| `once` | `boolean` | `true` にするとイベントを1回だけ実行して自動削除 |
| `passive` | `boolean` | `true` にすると `preventDefault()` を無視（スクロール時に最適） |

### イベント一覧
#### DOM
| イベント名                 | レシーバーの制限       | 発火条件 |
|--------------------------|------------------|--------------------------------|
| `click`\|`dblclick`   | なし             | クリック\|ダブルクリック された時 |
| `mousedown`\|`mouseup` | なし             | マウスが 押された\|離された 時 |
| `mousemove`              | なし             | マウスが移動した時 |
| `mouseover`\|`mouseout` | なし             | マウスが要素の上に 乗った\|外に出た 時（子要素でも発火） |
| `mouseenter`\|`mouseleave` | なし        | マウスが要素の 上に乗った\|外に出た 時（子要素では発火しない） |
| `contextmenu`            | なし             | 右クリックメニューが開かれた時 |
| `wheel`\|`scroll`      | スクロール可能要素 | マウスホイール回転\|スクロール された時 |
| `keydown`\|`keypress`\|`keyup` | グローバルオブジェクト+入力可能タグ | キーが 押された\|押され続けた（非推奨）\| 離された 時 |
| `focus`\|`blur`       | 入力可能タグ     | 要素が フォーカスされた\|フォーカスが外れた 時 |
| `input`\|`change`      | 入力可能タグ     | ユーザーが 入力\|値を確定 した時 |
| `submit`\|`reset`      | `<form>`        | フォームが 送信\|リセット された時 |
| `dragstart`\|`drag`\|`dragend` | `draggable="true"` | 要素の ドラッグ開始\|ドラッグ中\|ドラッグ終了 時 |
| `dragover`\|`drop`     | なし             | ドラッグされた要素が 上に来た\|ドロップされた 時 |
| `touchstart`\|`touchmove`\|`touchend` | モバイル端末 | 画面に 指が触れた\|指を動かした\|指が離れた 時 |
| `animationstart`\|`animationend`\|`animationiteration` | `animation` 設定要素 | CSSアニメーションが 開始\|終了\|繰り返された 時 |
| `transitionstart`\|`transitionend` | `transition` 設定要素 | CSSトランジションが 開始\|終了 した時 |
| `fullscreenchange`       | `document`       | フルスクリーン ON/OFF 切り替え時 |
| `visibilitychange`       | `document`       | タブの表示/非表示 切り替え時 |
| `volumechange`           | `<video>` `<audio>` | メディアの音量が変更された時 |
| `play`\|`pause`       | `<video>` `<audio>` | メディアが 再生\|一時停止 された時 |

#### ナビゲーション
| イベント名       | レシーバーの制限 | 発火条件 |
|----------------|--------------|--------------------------------|
| `popstate`     | `window`     | `history.back()` / `history.forward()` で遷移時 |
| `beforeunload` | `window`     | ページを閉じる / リロードする時 |
| `hashchange`   | `window`     | `#` の変更（例：`index.html#section1`） |
| `load`        | `window`     | ページが完全に読み込まれた時 |
| `DOMContentLoaded` | `document` | DOMツリーが構築された時（画像やCSSは未完了でも発火） |
| `unload`      | `window`     | ユーザーがページを離れる時（最近は非推奨） |
| `online` \| `offline` | `window` | ネットワークが接続 \| 切断 された時 |

#### Eventオブジェクト
| **イベント名** | **派生オブジェクト** |
|--------------|----------------|
| `click` / `mousedown` / `mouseup` | `MouseEvent` |
| `keydown` / `keyup` | `KeyboardEvent` |
| `touchstart` / `touchmove` | `TouchEvent` |
| `scroll` | `UIEvent` |
| `focus` / `blur` | `FocusEvent` |
| `input` / `change` | `InputEvent` |
| `submit` | `SubmitEvent` |

| **prop/method**         | **意味** |
|------------------|--------------------------------|
| **prop** |-----------------------|
| `event.type`     | イベントの種類（`"click"` など） |
| `event.target`   | イベントが発生した要素 |
| `event.currentTarget` | `addEventListener()` が設定された要素 |
| `event.timeStamp` | イベント発生時刻（ms単位） |
| `event.defaultPrevented` | `preventDefault()` が実行されたか（`true` / `false`） |
| **Method** |-----------------------|
| `event.preventDefault()` | **デフォルトの動作を無効化**（例：フォーム送信やリンクの遷移を防ぐ） |
| `event.stopPropagation()` | **親要素への伝播（バブリング）を止める** |
| `event.stopImmediatePropagation()` | **他のリスナーの実行も含めて止める** |
| `event.composedPath()` | **イベントの伝播経路を配列で取得** |

### 補足
#### イベントデリゲーション
- イベントリスナーの重複定義を防ぐアプローチ
- 同じイベントはなるべく親要素にまとめる
```js
// 条件分岐を工夫
document.addEventListener("click", event => {
  if (event.target.matches(".delete-btn")) {
    console.log("削除ボタンが押された！");
  } else if (event.target.matches(".edit-btn")) {
    console.log("編集ボタンが押された！");
  }
});

// closestで親要素を絞る
document.addEventListener("click", event => {
  const button = event.target.closest(".delete-btn");
  if (button) {
    console.log("削除ボタンが押された！");
  }
});
```



# DevTools(ブラウザのデバッガ)
## 機能
| タブ名          | 用途 |
|--------------|-----------------------------|
| **Elements** | DOMツリーとCSSの確認・編集 |
| **Console**  | JavaScriptの実行＆デバッグ |
| **Sources**  | スクリプトのデバッグ＆ブレークポイント設定 |
| **Network**  | ネットワーク通信（APIリクエスト・WebSocket）の確認 |
| **Performance** | ページのレンダリングや処理速度を分析 |
| **Application** | localStorage, sessionStorage, Cookie, IndexedDB などの管理 |
| **Security** | HTTPS証明書やセキュリティ情報の確認 |
