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
