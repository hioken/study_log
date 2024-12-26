=begin
class User
  def initialize(name)
    @name = name
  end

  def hello
    puts "Hello, #{@name}"
    private_test
  end

  private
  def private_test
    puts "プライベートメソッドの呼び出し"
  end
end

a = User.new("Alice")
a.hello
=end

class User
  def initialize(name)
    @name = name
  end

  def hello
    puts "Hello, #{@name}"
  end

  def name=(name)
    @name = name
  end


end

a = User.new("Alice")
a.name = "Lily"
p a
