$redis_master = Redis.new(url: "redis://redis-master:6379/0")
$redis_slave = Redis.new(url: "redis://redis-slave1:6379/0")
