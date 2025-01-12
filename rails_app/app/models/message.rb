class Message
  attr_accessor :id, :content

  def initialize(id, content)
    @id = id
    @content = content
  end

  # def self.all(redis)
  #   redis.keys("message:*").map do |key|
  #     id = key.split(":").last
  #     Message.new(id, redis.get(key))
  #   end
  # end

  # def save(redis)
  #   redis.set("message:#{id}", content)
  # end

  def save_to_shard
    shard = self.class.shard_for(id)
    shard.set("message:#{id}", content)
  end

  def self.all_from_shards
    messages = []
    $redis_shards.each do |shard|
      shard.keys("message:*").each do |key|
        id = key.split(":").last
        messages << Message.new(id, shard.get(key))
      end
    end
    messages
  end

  def self.generate_id
    "#{SecureRandom.uuid}-#{rand(0..9)}"
  end

  private

  def self.shard_for(key)
    last_digit = key.to_s[-1].to_i
    if last_digit.odd?
      $redis_shards[0]
    else
      $redis_shards[1]
    end
  end
end