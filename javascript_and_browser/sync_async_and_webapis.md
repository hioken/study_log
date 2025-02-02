# 同期(sync)と非同期(async)
## 基礎
### Jsにおける非同期処理とその他基礎知識
- 非同期処理: ある処理をタスクキューに入れておいて、先にコールスタック内の他の処理終らせてからコールスタックに入れる仕組み
- ブラウザ上では、メインスレッド内で上記の処理が行われている
- イベントループが、コールスタックとタスクキューの間で動作して、コールスタックが空の場合にタスクキューから処理を取り出してコールスタックに積む

### 関数
| **提供API**         | **コンストラクタ名**  | **関数名**                  | **説明** |
|--------------------|------------------|-------------------------|--------------------------------------------|
| **ECMAScript**    | `Promise`        | `.then()` `.catch()`     | 非同期処理を管理する基本オブジェクト |
| **ECMAScript**    | `AsyncFunction`  | `async/await`           | 非同期処理を同期処理のように書ける |
| **ECMAScript**    | `Generator`      | `function*` `.next()`    | 非同期イテレーターと組み合わせ可能 |
| **WebAPI / Node** | -                | `setTimeout`            | 指定時間後に 1 回だけ関数を実行 |
| **WebAPI / Node** | -                | `setInterval`           | 指定時間ごとに繰り返し関数を実行 |
| **WebAPI / Node** | `Fetch`          | `fetch()`               | HTTP リクエストを送信（Promise ベース） |
| **WebAPI / Node** | `WebSocket`      | `.send()` `.onmessage`  | WebSocket 通信を行う |
| **WebAPI / Node** | `Worker`         | `.postMessage()`        | Web Worker を使って並列処理 |
| **WebAPI**        | `XMLHttpRequest` | `.open()` `.send()`     | HTTP リクエストを送信（古い方式） |
| **WebAPI**        | `EventSource`    | `.onmessage`            | サーバーからのリアルタイムデータを受信 |
| **WebAPI**        | `Notification`   | `new Notification()`    | デスクトップ通知を表示 |
| **WebAPI**        | -                | `requestIdleCallback()` | ブラウザがアイドル状態のときに処理を実行 |
| **WebAPI**        | -                | `requestAnimationFrame()` | 次の描画フレームのタイミングで処理を実行 |
| **Node**         | `Process`        | `process.nextTick()`    | 次のイベントループの直前に実行 |
| **Node**         | `fs`             | `fs.readFile()`        | 非同期でファイルを読み込む |


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
- タスクの実行
  - 実行後、無事完了した場合は`resolve`、エラーが発生した場合は`reject`を実行(明示可能かは不明)
  - 自身の戻り値が`Promise`インスタンスかそうでないかで、`resolve`タイミングが変わる
    - `Promise`インスタンス: 遅延処理を含む、全ての処理が終わるまで待機してから`resolve`
    - `Promise`インスタンス以外: 戻り値が確定した時点で即`resolve`
    - 遅延処理がない場合はどちらも同様の結果を返す
  - エラー発生時に`[[PromiseRejectReactions]]`が見つからない場合、`[[PromiseFulfillReactions]]`のチェーンを調べて、最初に見つかった`[[PromiseRejectReactions]]`を実行
- `resolve(data)` | `reject(data)`
  - 厳密には`new Promise`のコールバック関数の 第一|第二 引数
  - `[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]` の参照先を即実行
  - 自身`[[PromiseState]]`を `fulfilled`|`rejected` に変更
- `then(data)`メソッド
  - 呼び出し元の`[[PromiseState]]`を確認
    - `fulfilled`|`rejected` だった場合、第一引数のコールバック関数を実行
    - `pending`だった場合、呼び出し元の`[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]` に自身の第一引数, 第二引数の内容を格納(どの様な形式で格納しているかは調べるの諦めた)
    - タスクキューに引数の処理を追加
- `catch(data)`メソッド
  - `then`の第二引数だけバージョン
- `finally(data)`メソッド
  - 呼び出し元の`[[PromiseFulfillReactions]]`|`[[PromiseRejectReactions]]`両方に格納
- `Promise.all([Promise, Promise])`
  - 起点やthenの引数に記述すると、引数の`Promise`が全て解決されるまで、次のPromiseチェーンを待機させる
