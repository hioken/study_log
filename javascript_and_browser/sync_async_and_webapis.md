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
| **ECMAScript**    | `Promise`        | Micro      | `.then()` `.catch()`     | 非同期処理を管理する基本オブジェクト |
| **ECMAScript**    | `AsyncFunction`  | Micro      | `async/await`           | 非同期処理を同期処理のように書ける |
| **ECMAScript**    | `Generator`      | -          | `function*` `.next()`    | 非同期イテレーターと組み合わせ可能 |
| **WebAPI / Node** | -                | Macro      | `setTimeout`            | 指定時間後に 1 回だけ関数を実行 |
| **WebAPI / Node** | -                | Macro      | `setInterval`           | 指定時間ごとに繰り返し関数を実行 |
| **WebAPI / Node** | `Fetch`          | Micro      | `fetch()` (レスポンス処理) | HTTP リクエストを送信（Promise ベース） |
| **WebAPI / Node** | `WebSocket`      | Macro      | `.send()` `.onmessage`  | WebSocket 通信を行う |
| **WebAPI / Node** | `Worker`         | Macro      | `.postMessage()`        | Web Worker を使って並列処理 |
| **WebAPI**        | `XMLHttpRequest` | Macro      | `.open()` `.send()`     | HTTP リクエストを送信（古い方式） |
| **WebAPI**        | `EventSource`    | Macro      | `.onmessage`            | サーバーからのリアルタイムデータを受信 |
| **WebAPI**        | `Notification`   | Macro      | `new Notification()`    | デスクトップ通知を表示 |
| **WebAPI**        | -                | Macro      | `requestIdleCallback()` | ブラウザがアイドル状態のときに処理を実行 |
| **WebAPI**        | -                | Macro      | `requestAnimationFrame()` | 次の描画フレームのタイミングで処理を実行 |
| **Node**         | `Process`        | Micro      | `process.nextTick()`    | 次のイベントループの直前に実行 |


## Promise
### 構成
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

### 説明
**※以下の情報は不確実！！！！！**
#### 基礎
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
#### 並列処理
- `Promise.all([PromiseA, PromiseB])`
  - 起点やthenの引数に記述すると、引数の`Promise`が全て解決されるまで、次のPromiseチェーンを待機させる
  - この時次の引数には`Promise.all`の引数の配列順に、それぞれの戻り値が格納された配列が渡る
  - どれか一つでもエラーが起きた場合、`catch`を実行、引数には最初の`reject`の引数が入る
- `Promise.race([PromiseA, romiseB])`
  - `all`のどれか一つでも処理が終わったら次が実行されるバージョン
- `Promise.allsettled([PromiseA, romiseB])`
  - 全ての処理を待ち、`reject`が起きてもエラー扱いせず次の処理を実行(`catch`を実行しない)
  - 引数には、前回の処理の戻り値と状態を格納したオブジェクト`{reason: 戻り値, status: [[PromiseState]]の値}`が格納された配列が入る
