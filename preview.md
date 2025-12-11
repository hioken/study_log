今回はrailsで実行してますが、おそらくjsの問題なのでフレームワーク等は関係ないと予想しています。
初歩的な質問で恐縮ですが、教えていただけると幸いです。

## 説明
### 環境
- rails7(turbo, action cable)
- google chrome
- 開発環境

### したい事、しようとした事
- 特定のページでのみ購読したいチャネルの購読を、ページ退出時にキャンセルさせたい
  - 今回はDMページにいるときのみ、DMチャネル(`"channel_#{params[:channel_id]}"`)を購読させたい
- `pagehide`や`visibilitychange`時に購読切断させようとしたが、bfcache環境下でブラウザバックで動作しない
  - `subscriptions.remove()`

### 確認済みの動作
- pagehideの発火(pagehide内に記述した同期処理は動作する)
- click等のイベント内での購読切断

### 起こっている問題やご教示いただきたい事、自分の考え等
- ブラウザバックやタブ閉じを行った際に、`subscriptions.remove()`等の非同期処理を実行する設計が分からないため知りたい
- 現在起こっている現象についての自分の理解が正しいのか教えていただきたい

### コード
```js
import consumer from "channels/consumer"
import { channelId } from "./channel_id";

const dmChannel = consumer.subscriptions.create(
  {channel: "MessageShowChannel", channel_id: channelId },
  // 省略 
);

document.addEventListener("visibilitychange", () => {
  consumer.subscriptions.remove(dmChannel);  // 動作しない
  sessionStorage.setItem(`${channelId}:draft`, messageInput.value); // これは動作する
});
window.addEventListener("pagehide", () => {
  consumer.subscriptions.remove(dmChannel);  // 動作しない
  sessionStorage.setItem(`${channelId}:draft`, messageInput.value); // これは動作する
});

// 接続遮断テスト、これは動作する
document.getElementById('test-button').addEventListener("click",() => {
  consumer.subscriptions.remove(dmChannel);
});
```

## 質問
### 質問1
現在起こっていることは、以下であっているか知りたい

bfcache時に`pagehide`や`visibilitychange`内に記述した非同期処理が動作しないは、動作の順番が
1. pagehide等のイベント検知
2. pagehide内の同期処理を実行、非同期処理があればjobキューへ
3. bfcacheのスナップ(この時、待機キューはスナップされない)
4. 遷移
5. 遷移先のスクリプト
となり、遷移前にjobキューに入れられた非同期処理は実行されないから

### 質問2
bfcache環境下で、ブラウザバックに`subscriptions.remove()`含む非同期処理を実行する方法や設計を知りたい
