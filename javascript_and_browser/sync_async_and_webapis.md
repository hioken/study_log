# 同期(sync)と非同期(async)
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

#### jsonの取得例
```js
async function fetchFn() {
  const response = await fetch('接続先')
  const json = await response.json()
}
```