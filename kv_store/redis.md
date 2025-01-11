# 基礎
## 構成
| 要素         | 役割                                                       |
|--------------|------------------------------------------------------------|
| Client       | Redisサーバーにリクエストを送るアプリケーションやCLI。     |
| Server       | Redisのコア部分。リクエストを処理し、データを管理。       |
| Data Store   | データをメモリ上に格納。永続化が有効ならディスクにも保存。 |
| Replication  | マスタースレーブ構成によるデータ複製。                     |
| Persistence  | RDBやAOFを使ったデータ永続化。                            |

## DBの管理
- デフォルトで16個のdbを所持
- 0~15で指定する
- 2はセッション管理、みたいに暗黙の風潮がある？

## データフロー

- シングルスレッドモデル

1. リクエスト(redisコマンド)
2. リクエストをキューに格納
3. 順次コマンド処理
4. 応答
5. 有れば永続化など後処理

## コマンド
### プロセス
```bash
service redis-server start
service redis-server stop
service redis-server restart

ps aux | grep redis
```

### 動作確認
```bash
INFO | grep "used_cpu"

# -n: リクエスト, -c: 同時接続数, -q: サマリーのみ表示
redis-benchmark -n 100000 -c 50 -q
```

### redis内
```bash
SELECT 1 # 1番目を使用
```

## 設定
- `/etc/redis/redis.conf`

| 項目               | 説明                              | 設定例                |
|--------------------|-----------------------------------|-----------------------|
| port               | Redisの待ち受けポート             | port 6379             |
| bind               | 接続を許可するIPアドレス          | bind 127.0.0.1        |
| maxmemory          | 使用するメモリの上限              | maxmemory 2gb         |
| maxmemory-policy   | メモリ不足時の削除ポリシー        | allkeys-lru           |
| appendonly         | AOFによる永続化を有効にする       | appendonly yes        |
| save               | RDBスナップショットの保存頻度     | save 60 1000          |

## 永続化
### RDB(Redis Database File)
- 指定秒数内に指定回数の変更が合ったら全データのスナップショットをディスクに保存
- デフォルトでは`/var/lib/redis/dump.rdb`
```bash
save 秒毎 変更数
```

### AOF(Append Only File)
- 書き込み総裁(コマンド)をログとして記録
- デフォルトでは`/var/lib/redis/appendonly.aof`
```bash
appendonly yes
appendsync 秒数
```

# Failover
- SentinelサーバーがMasterサーバーに定期的にPINGを送信して、指定時間応答がない場合、Slaveに昇格指示を送る

# 設定ファイル
## redis.conf
| 設定項目              | 説明                                                              | 例                           |
|----------------------|------------------------------------------------------------------|------------------------------|
| **port**             | Redisサーバーのリスンポートを指定。                                  | `port 6379`                  |
| **bind**             | 接続を許可するホストを指定。                                        | `bind 127.0.0.1 ::1`         |
| **timeout**          | クライアントのアイドルタイムアウト（秒）。                         | `timeout 300`                |
| **save**             | データを保存するスナップショットのトリガー条件。                    | `save 900 1`                 |
| **appendonly**       | AOF（Append-Only File）モードを有効化するか。                      | `appendonly yes`             |
| **maxmemory**        | Redisが使用できる最大メモリ量。                                    | `maxmemory 2gb`              |
| **maxmemory-policy** | メモリ不足時のデータ削除ポリシー。                                  | `maxmemory-policy allkeys-lru` |
| **requirepass**      | クライアント接続時の認証パスワード。                                | `requirepass mysecretpass`   |
| **tls-cert-file**    | TLS証明書ファイルの設定。                                          | `tls-cert-file /etc/ssl/certs/redis.crt` |
| **tls-key-file**     | TLS秘密鍵ファイルの設定。                                          | `tls-key-file /etc/ssl/private/redis.key` |
| **replicaof**        | マスターサーバーの指定（スレーブ専用）。                           | `replicaof redis-master 6379` |
| **masterauth**       | マスター接続時の認証情報。                                         | `masterauth masterpassword` |

## sentinel.conf
| 設定項目                        | 説明                                                              | 例                                           |
|--------------------------------|------------------------------------------------------------------|----------------------------------------------|
| **port**                       | Sentinelのリスンポートを指定。                                      | `port 26379`                                |
| **bind**                       | Sentinelがバインドするアドレス。                                    | `bind 127.0.0.1`                            |
| **sentinel monitor**           | 監視するマスターサーバーを設定。                                    | `sentinel monitor mymaster redis-master 6379 2` |
| **sentinel auth-pass**         | マスター認証のパスワード。                                          | `sentinel auth-pass mymaster mysecretpass`   |
| **sentinel down-after-milliseconds** | マスターがダウンとみなされるまでの時間（ms）。                   | `sentinel down-after-milliseconds mymaster 5000` |
| **sentinel failover-timeout**  | フェイルオーバープロセス全体のタイムアウト（ms）。                   | `sentinel failover-timeout mymaster 10000`  |
| **sentinel parallel-syncs**    | フェイルオーバー時のスレーブ並行同期数。                           | `sentinel parallel-syncs mymaster 1`         |
| **sentinel client-reconfig-script** | マスター変更後に呼び出すスクリプト。                             | `sentinel client-reconfig-script mymaster /path/to/script.sh` |

## その他
- nodes.conf（Clusterモード用）
- redis-aof-rewrite.conf（AOFモード用）
- cluster-config-file（クラスタ構成ファイル）