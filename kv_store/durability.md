## 耐障害性 High Availability
###### レプリケーション (Replication)
- 概要: データを複数のサーバーに複製して保存。
- 目的: 1台のサーバーがダウンしても他のサーバーからデータを取得できる。
###### フェイルオーバー (Failover)
- 概要: マスターサーバーがダウンした際に、自動的にスレーブがマスターに昇格する仕組み。
- 目的: サービスの停止時間を最小化。
###### シャーディング (Sharding)
- 概要: データを複数のサーバーに分割して保存することで、負荷を分散。
- 目的: 大量データを効率的に管理し、パフォーマンスを向上。

## 永続化 Persistence
### 概要
- インメモリ型のKVストアが、物理層にデータを保存する仕組み
- RDB（Redis Database File）
  - 定期的にデータを**スナップショット（瞬間的な状態）**としてディスクに保存。
- AOF（Append Only File）
  - 全ての書き込み操作をログファイルとして記録。

### 比較
| 項目         | RDB                                | AOF                              |
|--------------|------------------------------------|----------------------------------|
| 保存タイミング | 定期的にスナップショットを保存        | すべての書き込みをログに記録      |
| パフォーマンス | 高速                                | 書き込み時にオーバーヘッドあり    |
| データ損失     | 直近のデータは失われる可能性あり      | ほぼ完全にデータを復元可能        |
| 用途           | バックアップ、読み取り中心のシステム   | 書き込みが多いシステム            |
