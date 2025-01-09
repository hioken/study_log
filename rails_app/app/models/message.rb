class Message
  attr_accessor :id, :content

  def initialize(id, content)
    @id = id
    @content = content
  end

  def self.all(redis)
    redis.keys("message:*").map do |key|
      id = key.split(":").last
      Message.new(id, redis.get(key))
    end
  end

  def save(redis)
    redis.set("message:#{id}", content)
  end
end
