class Grand
  def grand_method
    puts 'Hello'
  end

  def inheritence(n)
    puts 'inherritence'
    n += 20
  end
end

class Parent < Grand
end

class Child < Parent
  def inheritence(n)
    n = 200 + super
    p n
  end
end

a = Child.new
a.grand_method
a.inheritence(1)
