# Model
## 遅延評価(Lazy Loading)
- クエリを発行するメソッドは、即座にクエリを発行せず、代わりに`ActiveRecord::Associations::CollectionProxy`等のproxyオブジェクトが返る
- このオブジェクトからループ系やデータ取得系のメソッドを呼び出すと、初めてクエリを発行する
```ruby
user = User.find(1)
microposts_proxy = user.microposts # まだクエリは発行されない
first_date = microposts_proxy.first # この時点でクエリが発行される

user.microposts.build(content: 'Draft') # データベースには反映されない
user.microposts.create(content: 'Published') # 即座にINSERTが実行
```
## cache
- selectメソッドは指定したカラムだけcacheに保存する
- cacheの組み方
  - cacheしたいクエリを発行するアソシエーションメソッドをモデルで定義
  - それをincludes(:method)で呼び出す

# Cookie API
## 概要
### type
| クッキータイプ       | 説明                          | 用途                                |
|------------------|-----------------------------|-----------------------------------|
| cookies          | プレーンテキスト                  | 機密情報以外の保存                        |
| cookies.encrypted | 自動で暗号化される                | ユーザーIDや機密情報                       |
| cookies.signed    | 署名のみされる                   | 改ざん防止                            |

### 基本操作
```ruby
# 値を取得
cookies[:key]
# 有効期限設定
cookies[:key] = {value: value, expires: expiration}
# 永続化
cookies.permanent[:key] = value
# 削除
cookies.delete(:key)
# 全クッキーの削除
reset_session
# 設定
cookies[:key] = { options }
```
| オプション名    | 説明                              | デフォルト値            | 例                                  |
|-------------|---------------------------------|-------------------|-----------------------------------|
| value      | Cookieに保存する値                    | nil               | value: 123                        |
| expires    | Cookieの有効期限                       | nil               | expires: 1.hour.from_now          |
| path       | Cookieが有効なパス                     | /                 | path: '/admin'                    |
| domain     | Cookieが有効なドメイン                   | 現在のドメイン           | domain: '.example.com'            |
| secure     | HTTPS通信時のみ送信                    | false             | secure: true                      |
| httponly   | JavaScriptからアクセス不可               | false             | httponly: true                    |
| samesite   | クロスサイトリクエスト制御                | nil               | samesite: :strict                 |
| signed     | 署名付きで保存（改ざん防止）              | false             | signed: true                      |
| encrypted  | 暗号化して保存                        | false             | encrypted: true                   |
| same_site  | samesiteの別名（同じ機能）               | nil               | same_site: :lax                   |

### JavaScript経由
```javascript
document.cookie = "temp_data=temporary_value; max-age=300; path=/";

const tempData = document.cookie
  .split('; ')
  .find(row => row.startsWith('temp_data='))
  ?.split('=')[1];
```


# Development
## Console
- サンドボックスモードでコンソールを起動(全ての変更がロールバックされる)
  - `rails console --sandbox`

# Action Cable

## 概要
- Action Cableは、WebSocketとRailsを結びつけるフルスタックのフレームワークです。  
  - フルスタック: データベース、サーバ、フロントエンド、APIなどすべてのレイヤーを担当可能  
- クライアント側のJavaScriptフレームワークとサーバー側のRubyフレームワークの両方を提供

## websocket用語
- **コネクション**: クライアント・サーバーの関係  
- **コネクションインスタンス**: 一つのコネクション  
- **コンシューマ**: クライアント側のJavaScriptフレームワークによって作成されたWebSocketコネクションのクライアント  
- **チャネル**: 機能単位をカプセル化したもの  
  - コンシューマはチャネルに参加（サブスクライブ）することで、その情報を受け取る  
  - 同一のクライアントであっても別ウィンドウ等を使い、複数のコンシューマとして振る舞うことが可能  
- **サブスクライバ**: チャネルにサブスクライブしているコンシューマ

## 接続フロー
1. クライアント側のJavaScriptでWebSocketハンドシェイクのリクエストを送信
  - クライアント側のjs: `createConsumer()`
  - リクエストは`/cable`
2. Action Cableの`Connection`オブジェクトが作成され、`connect`メソッドが呼ばれてハンドシェイクレスポンスを返す
3. クライアント側のJavascriptがチャネルにサブスクライブ`consumer.subscriptions.create`(複数回可能)
4. Action Cableの`Channel`オブジェクトが生成され、`subscribed`メソッドが呼ばれる

## 送受信フロー
### クライアント側の送信
1. コンシューマ側のjs`perform`でフレームを送る
2. `perform`の引数で指定した`Channel`オブジェクトのメソッドが発火
### ブロードキャスト
1. `Channel`オブジェクトの`ActionCable.server.broadcast`メソッドでブロードキャスト
2. コンシューマ側のjs`recived`メソッドが発火

## 必要な設定
- **環境ファイル** (`config/environments/`):  
  `config.action_cable.allowed_request_origins = [許可するurl]`
- **config/cable.yml**:  
  Redisなどの設定ファイル
