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

# Action Job | sidekiq
## action job
### 説明
- 非同期処理をするための機能、基本は`gem sidekiq`と組合わせて並列処理を可能にする用途で使われる
- 一つのジョブごとに一つの`Job`クラスを作る
- `perform`メソッド内に処理内容を定義
- クラスから対応したメソッドを呼び出す事で、同期及び非同期定期に`perform`[メソッドを実行](#実行系メソッド)
  - `perform_later`:
    - デフォルト: ジョブキューに登録、レスポンスを返す等の同期処理が完了した後に実行
    - `Sidekiq`: 並列処理 サーバー側の処理をバックグラウンドで非同期で行えるようにする
- クラス内部でキャンセル処理等を[事前設定できる](#クラス内部の制御定義)
- **ジョブの成否を判断する機能は提供**されていないため、キャッシュ等で自前での管理が必要
- エラーの伝播についてはrubyの基礎仕様と一緒

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
| `retry_on エラー, wait: time, attempts: max` | **指定エラー発生時にリトライ** |
| `discard_on エラー` | **指定エラーが発生してもリトライせずスルー** |
| `before_enqueue :メソッド名` | **ジョブがキューに入る前に実行** |
| `around_perform :メソッド名` | **ジョブの前後で処理を挟む** |
| `after_perform :メソッド名` | **ジョブ実行後に実行** |

### インスタンス
| インスタンス変数          | 説明 |
|-----------------|--------------------------------------------------|
| `@arguments` | `perform` に渡された引数 |
| `@exception_executions` | どのエラーで何回リトライされたかを記録するハッシュ |
| `@executions` | このジョブが実行された回数（リトライも含む） |
| `@job_id` | ジョブごとに一意な ID（UUID 形式） |
| `@priority` | キューの優先度（`nil` の場合はデフォルト） |
| `@provider_job_id` | Sidekiq などのバックエンドがジョブを識別するための ID |
| `@queue_name` | このジョブが入ったキュー名（`default` など） |
| `@successfully_enqueued` | `perform_later` でキューに入れるのに成功したか（`true/false`） |
| `@timezone` | ジョブのタイムゾーン（デフォルトは `UTC`） |


### 導入/設定
#### 導入
- `rails g job job_name`

#### 設定
##### 設定(config.active_job)
| 設定項目 | 説明 | デフォルト |
|----------|----------------------------------------------|------------|
| `queue_adapter` | **使用するキューアダプターを設定**  | `:async` |
| `queue_name_prefix` | **ジョブのキュー名にプレフィックスを追加** (`"app_name_"` など) | `nil` |
| `queue_name_delimiter` | **キュー名の区切り文字**（デフォルトは `_`） | `_` |
| `disable_job_execution` | **`true` にするとジョブの実行を無効化**（テスト時に使う） | `false` |
| `maintain_test_schema` | **テスト環境でDBスキーマを維持する** | `true` |
| `custom_serializers` | **カスタムシリアライザを追加**（独自オブジェクトをジョブで使う場合） | `[]` |

##### アダプター
| アダプター | 説明 | 処理 |
|------------|--------------------------|------|
| `:async`  | **スレッドを使って即実行**（Railsサーバー内） | シングルスレッド処理 |
| `:inline`  | **`perform_now` と同じ（同期処理）** | 同期処理 |
| `:sidekiq` | **Sidekiq（Redisを使った本格的なジョブキュー）** | 並列 |
| `:delayed_job` | **DBを使ったジョブキュー（遅い）** | 非同期 |
| `:resque` | **Redisベースのジョブキュー** | 並列 |
| `:que` | **PostgreSQLベースのジョブキュー** | 非同期 |


## sidekiq
### 説明
- `Thread`と`Process`をラップした並列処理をするためのrubyライブラリ
- railsとは独立しているが、railsの設定ファイルに対応する機能は提供されている
- ワーカーを立ち上げ、ジョブキューの管理と、railsやrubyのプロセス, スレッドを実行する領域を提供
- `sidekiq`は上記の機能を外付け的に提供しているだけだから、ダウンしたとしても並列処理できなくなるだけ、並列処理前提のシステムを組んでいない限りサービスは止まらない
- ジョブキューには外部のキャッシュシステムを使う(通常はredis)

### ジョブ毎の設定
- `Sidekiq::Job`を`include`したActionJobクラス内に、`sidekiq_options`メソッドの引数としてキーワード引数で指定
- 一覧

| 設定項目       | 説明 |
|--------------|------------------------------------------------|
| `retry`      | リトライ回数 (`false` にするとリトライなし) |
| `queue`      | キューの指定（`default` や `mailers` など） |
| `backtrace`  | エラー時にバックトレースをログに出す (`true` なら全出力) |
| `dead`       | `false` にすると、失敗したジョブを Dead Set に入れない |
| `unique`     | ジョブの重複を防ぐ（Gem: `sidekiq-unique-jobs` が必要） |
| `expires_in` | Redis に保存されるジョブの有効期限（秒） |
| `tags`       | Sidekiq Web UI でジョブにタグをつける |


### 設定ファイル
#### yml
| 設定項目            | 説明 |
|---------------------|--------------------------------|
| `:concurrency`     | 1ワーカーあたりの最大スレッド数 |
| `:queues`          | 処理するキューのリスト（優先度順） |
| `:timeout`         | ジョブのタイムアウト時間（秒） |
| `:logfile`         | ログの出力先 |
| `:pidfile`         | PID ファイルの保存場所 |
| `:daemon`         | デーモンモードで実行するか（true/false） |
| `:verbose`        | 詳細なログを出力するか（true/false） |
| `:redis`          | Redis の接続先 |
| `:strict`         | 未定義のキューを許可するか（true: 許可しない, false: 許可する） |
| `:require`        | Sidekiq 起動時に読み込むファイル |

#### initilizer
| 設定項目                     | 説明 |
|------------------------------|------------------------------|
| `Sidekiq.configure_server`   | Sidekiq サーバー側の設定 |
| `Sidekiq.configure_client`   | Rails 側（クライアント）の設定 |
| `Sidekiq.default_worker_options` | 全ワーカー共通のオプション |
| `Sidekiq.logger.level`       | ログのレベル（`Logger::WARN` など） |
| `config.redis`               | Redis の接続先 |
| `config.server_middleware`   | サーバー側のミドルウェア追加 |
| `config.client_middleware`   | クライアント側のミドルウェア追加 |
| `config.error_handlers`      | ジョブ失敗時のエラーハンドラー |

#### その他
- `routes.rb`: ダッシュボードの追加
```ruby
require 'sidekiq/web'

Rails.application.routes.draw do
  mount Sidekiq::Web => "/sidekiq"  # http://localhost:3000/sidekiq
end
```
