shard1_sentinels = [
  { host: "redis-shard1-sentinel1", port: 26379 },
  { host: "redis-shard1-sentinel2", port: 26379 },
  { host: "redis-shard1-sentinel3", port: 26379 }
]

shard2_sentinels = [
  { host: "redis-shard2-sentinel1", port: 26379 },
  { host: "redis-shard2-sentinel2", port: 26379 },
  { host: "redis-shard2-sentinel3", port: 26379 }
]

$redis_shards = [
  Redis.new(
    url: "redis://mymaster",
    sentinels: shard1_sentinels,
    role: :master
  ),
  Redis.new(
    url: "redis://mymaster",
    sentinels: shard2_sentinels,
    role: :master
  )
]

=begin
改善コード、動作未確認
sentinels = [[], []]

3.times do |i|
  sentinels[0] << { host: "redis-shard1-sentinel#{i + 1}", port: 26379 }
  sentinels[1] << { host: "redis-shard2-sentinel#{i + 1}", port: 26379 }
end

$redis_shards = sentinels.map { |ss| Redis.new(url: "redis://mymaster", sentinels: ss, role: :master) }
=end