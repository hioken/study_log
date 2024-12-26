class Foo
  def initialize(a = nil)
    @a = a
  end
end

a = Foo.new

p a.to_s
p a.inspect