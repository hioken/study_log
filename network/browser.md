# Cookie
## 概要
### Session
- cookie内に保存されている
- サーバー側でデータを管理する意図の領域
- ブラウザを閉じるか一定時間で削除
- websocket通信に引き継がれない
### Cookie
- 指定期限までブラウザに保存される
- websocket通信に引き継がれる
## フローと構造
### フロー
1. サーバーサイドからCookieを送信
  - HTTPレスポンスにSet-Cookieヘッダを追加
2. ブラウザがCookieを保存
3. 次回以降の同じドメインへのHTTPリクエスト時にCookieを含める
```mathematica
Set-Cookie: user_id=123; Path=/; HttpOnly; Secure; SameSite=Strict
```
### 構造
- key-value
- Path: 適用パス
- HttpOnly: JavaScriptからのアクセス禁止
- Secure: HTTPSのみ
- SameSite: クロスサイトリクエストを制御