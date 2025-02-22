# HTTP比較
## 基礎
- リクエスト/レスポンス形式
- 基本、どのリクエストが来ても、要求を無視して自由なレスポンスを返す
- レスポンスをどう扱うかはデバイスが決める
  - 例えばブラウザなら、通常のaタグ等でリクエストを送ったらレスポンスを画面に表示させるし、fetchでリクエストを送ったらJavaScriptエンジン内でコードとして解釈される
  - これによってエラーになるかどうかが決まるだけで、レスポンスの返し方にルールがあるわけではない
- そもそもレスポンスというのはheader+bodyをそれぞれ文字列として送っているだけであって、それをクライアントが解釈しているだけ
- チャンク転送(Transfer-Encoding: chunked)という分割送信機能がある
  - 先にヘッダを返して、分割でbodyだけ送る

## 表
| 技術         | 通信の方向                           | 接続維持          | リクエスト形式                     | 接続の切り替え               |
|--------------|---------------------------------|----------------|---------------------------------|----------------------------|
| 通常のHTTP   | クライアント → サーバー（リクエスト）<br> サーバー → クライアント（レスポンス） | 1回ごとに接続    | **HTTPリクエスト**（GET, POSTなど） | 毎回新しい接続を確立        |
| SSE         | **サーバー → クライアントのみ**（一方向通信） | 継続的に接続    | **HTTPリクエスト（GET）** + `text/event-stream` | 再接続はブラウザが自動処理   |
| WebSocket   | **双方向通信**（リアルタイム）     | 継続的に接続    | **WebSocket ハンドシェイク（Upgradeリクエスト）** | **ハンドシェイク** によるプロトコル切り替え |

## パケット
```http
<!-- 通常 GET -->
GET /sample/path?query=value HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8
Accept-Encoding: gzip, deflate, br
Accept-Language: ja,en-US;q=0.9,en;q=0.8
Connection: keep-alive
Cookie: session_id=abcdef123456
Referer: https://www.google.com/


<!-- 通常 POST -->
POST /submit-form HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Content-Length: 27
Connection: keep-alive
Cookie: session_id=abcdef123456
Referer: https://example.com/form
Origin: https://example.com

name=kai&email=cat@example.com


<!-- 通常 HTTP レスポンス -->
HTTP/1.1 200 OK
Date: Sat, 24 Feb 2024 12:00:00 GMT
Content-Type: application/json
Content-Length: 27
Connection: close

{"message": "Hello, World!"}



<!-- SSE -->
GET /events HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Accept: text/event-stream
Cache-Control: no-cache
Connection: keep-alive
Referer: https://example.com/


<!-- SSE レスポンス -->
HTTP/1.1 200 OK
Date: Sat, 24 Feb 2024 12:00:00 GMT
Content-Type: text/event-stream
Cache-Control: no-cache
Connection: keep-alive
Transfer-Encoding: chunked

data: メッセージ1

data: メッセージ2




<!-- HTTP Upgrade (WebSockets) -->
GET /ws HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: x3JJHMbDL1EzLkh9YZrdg==
Sec-WebSocket-Version: 13
Origin: https://example.com


```

# Server-Sent Events(SSE)
## 概要
- サーバーからクライアントへの一方向通信
- チャンク転送を応用した技術で、クライアント側がそれぞれを独立したレスポンスとして解釈することが可能
- チャンク転送を流用しているため、bodyのみ送る

## 接続フロー
1. クライアントが`text/event-stream`リクエストを送る
2. クライアント側がレスポンスを受け入れ続ける状態になるため、レスポンスを適時返す

# WebSockets
## 概要
- 双方向通信を可能にするプロトコル
- 一つのTCPで実現
- HTTPから切り替わる

## 用語
- HTTPハンドシェイク: `101 Switching Protocols`Websocketプロトコルに切り替えるためのHTTPリクエスト/レスポンスのやり取りの事
- フレーム: 送受信されるデータ単位

## 接続フロー
1. クライアントがサーバーにWebsocketハンドシェイクのリクエストをHTTPで送る
2. クライアントにWebsocketハンドシェイクのレスポンスを返す
3. クライアントがレスポンスを受け取ると接続が確立され、双方向通信が可能になる

- 補足: 多くの場合、2の段階でサーバーがCookie等のヘッダ情報を保存する