以下の機能で、それぞれhotwireのどの技術を使うか案を出して
意外と全部streamsでいいのか？って俺は思っている

- 純粋通知: 全ページ, 通知チャネル
  - 前ページの右下に、通知のcontainerの役割を持つ要素を配備
  - ブロードキャスト受信時、以下の様な要素を上記のcontainer要素に追加(例はstimulusだが、実装で採用するかは別)
```html
<div class="notification-container" data-controller="message-notification">
  <template data-message-notification-target="template">
    <div class="notification">
      <a class="notification-link">
        <div class="notification-content">
          <span class="notification-sender"></span>
          <span class="notification-message"></span>
        </div>
      </a>
      <button class="notification-close" data-action="click->message-notification#close">✖</button>
    </div>
  </template>
</div>
``` 
- DM一覧のソート: DMの部屋一覧画面のみ, 通知チャネル
  - ブロードキャスト受信時、一覧画面から対象のメッセージが送信されたチャネルに対応する部屋を上にソート
  - その他未読マークを加えたりもする

- メッセージ一覧のソート: DM部屋詳細ページ, メッセージチャネル
  - 既読した旨がチャネルに伝わるデータを送り返す
  - ブロードキャスト受信時、以下の様な要素を一覧コンテナに追加
```html
<div class="message-box <%= 'self' if message.user_id == current_user.id %>">
  <% if message.user_id == current_user.id %>
    <span class="read-count" data-message-id="<%= message.id %>" data-read-count="0"></span>
  <% end %>

  <div class="message-content">
    <p class="sended_user">発言者: <%= message.user.name_with_id %></p>
    <span><%= message.content %></span>
  </div>

  <div class="message-timestamp">
    <%= l(message.updated_at, format: :short) %>
  </div>
</div>
```