# $redis_master = Redis.new(
#   url: "redis://redis-sentinel:26379",
#   role: :master
# )
# $redis_slave = Redis.new(
#   url: "redis://redis-sentinel:26379",
#   role: :slave
# )

# sentinels = [
#   { host: "redis-sentinel", port: 26379 },
# ]

# # マスターへの接続
# $redis_master = Redis.new(
#   url: "redis://mymaster",
#   sentinels: sentinels,
#   role: :master
# )

# # スレーブへの接続（コメントアウト部分も有効化可能）
# $redis_slave = Redis.new(
#   url: "redis://mymaster",
#   sentinels: sentinels,
#   role: :slave
# )

$redis_shards = [
  Redis.new(host: "172.23.0.201", port: 6379),
  Redis.new(host: "172.23.0.202", port: 6379),
]