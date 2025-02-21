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

## methods
### has_many
```ruby
has_many :メソッド名, 
         -> { 条件 },                # スコープを指定（任意）
         class_name: "クラス名",     # 関連先のモデル名を指定（デフォルト以外のクラス名を使う場合）
         foreign_key: "外部キー名",  # 外部キーを指定（デフォルト以外のキーを使う場合）
         primary_key: "主キー名",    # 主キーを指定（デフォルト以外のキーを使う場合）
         through: :中間テーブル名,   # 中間テーブルを経由する場合（has_many :through）
         source: :関連元,            # 中間テーブル経由の関連名
         dependent: :destroy,       # 関連先が削除されたときの動作 (:destroy, :nullify, :restrict_with_error など)
         inverse_of: :関連先メソッド名, # 双方向の関連付けを明示
         validate: true             # 関連付けを保存時に検証するかどうか（デフォルト: true）
```

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

# Action Job
## 説明
### 基礎
-- 一つのジョブごとに一つの`Job`クラスを作る
- `perform`メソッド内に処理内容を定義
- クラスから対応したメソッドを呼び出す事で、同期及び非同期定期に`perform`[メソッドを実行](#実行系メソッド)
  - `perform_later`:
    - デフォルト: ジョブキューに登録、レスポンスを返す等の同期処理が完了した後に実行
    - `Sidekiq`: 並列処理 サーバー側の処理をバックグラウンドで非同期で行えるようにする
- クラス内部でキャンセル処理等を[事前設定できる](#クラス内部の制御定義)

### メソッド
#### 実行系メソッド
| メソッド | 説明 |
|----------|----------------------------------------------|
| `perform_now` | **即時実行（シングルスレッド処理）** |
| `perform_later` | **非同期実行（キューに登録）** |
| `set(wait: 10.minutes)` | **指定時間後に実行** |
| `set(wait_until: Time.new(2025,1,1))` | **指定日時に実行** |
| `cancel` | **ジョブをキャンセル（実行前のみ）** |
| `cancel_all` | **同じジョブのすべてのインスタンスをキャンセル** |

#### その他メソッド
| メソッド | 説明 |
|----------|----------------------------------------------|
| `queue_as :high_priority` | **ジョブのキューを指定（優先度変更）** |
| `self.queue_name` | **現在のジョブのキュー名を取得** |
| `self.queue_adapter` | **現在のキューアダプターを取得** |
| `arguments` | **ジョブに渡された引数を取得** |
| `executions` | **ジョブが何回実行されたかを取得** |
| `enqueue` | **ジョブを手動でキューに登録** |

#### クラス内部の制御定義
| メソッド | 説明 |
|----------|----------------------------------------------|
| `retry_on エラー, wait: 5.seconds, attempts: 3` | **指定エラー発生時にリトライ**（最大3回、5秒待機） |
| `discard_on エラー` | **指定エラーが発生してもリトライせずスルー** |
| `before_enqueue :メソッド名` | **ジョブがキューに入る前に実行** |
| `around_perform :メソッド名` | **ジョブの前後で処理を挟む** |
| `after_perform :メソッド名` | **ジョブ実行後に実行** |


## 導入/設定
### 導入
- `rails g job job_name`

### 設定
#### 設定(config.active_job)
| 設定項目 | 説明 | デフォルト |
|----------|----------------------------------------------|------------|
| `queue_adapter` | **使用するキューアダプターを設定**  | `:async` |
| `queue_name_prefix` | **ジョブのキュー名にプレフィックスを追加** (`"app_name_"` など) | `nil` |
| `queue_name_delimiter` | **キュー名の区切り文字**（デフォルトは `_`） | `_` |
| `disable_job_execution` | **`true` にするとジョブの実行を無効化**（テスト時に使う） | `false` |
| `maintain_test_schema` | **テスト環境でDBスキーマを維持する** | `true` |
| `custom_serializers` | **カスタムシリアライザを追加**（独自オブジェクトをジョブで使う場合） | `[]` |

#### アダプター
| アダプター | 説明 | 処理 |
|------------|--------------------------|------|
| `:async`  | **スレッドを使って即実行**（Railsサーバー内） | シングルスレッド処理 |
| `:inline`  | **`perform_now` と同じ（同期処理）** | 同期処理 |
| `:sidekiq` | **Sidekiq（Redisを使った本格的なジョブキュー）** | 並列 |
| `:delayed_job` | **DBを使ったジョブキュー（遅い）** | 非同期 |
| `:resque` | **Redisベースのジョブキュー** | 並列 |
| `:que` | **PostgreSQLベースのジョブキュー** | 非同期 |

