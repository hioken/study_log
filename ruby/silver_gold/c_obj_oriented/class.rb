p '----クラス基礎----'
class Parent
  attr_accessor :a

  def initialize(a)
    @a = a
  end

  def test(arg1, arg2)
    p (arg1 + arg2 + @a)
  end

  def test2(arg1, arg2)
    p arg1 + arg2
  end
end

class Child < Parent

  def test(arg1)
    p 'start'
    super(arg1, 100)
    p 'end'
  end

  def test2(arg1, arg2)
    p arg1 + arg2
    super
    p (arg1 + arg2) * 1000
  end

  def test3_1(arg)
    p "test3_1 #{arg}"
  end

  def test3_2
    p "test3_2"
  end

  alias :alias_1 :test3_1
  # これは不可 alias :test3_1 :alias_1, :test3_2 :alias_2

end

a = Child.new(10)
b = Child.superclass.new(1)

p 'インスタンス確認'
p a
p b

p 'test'
a.test(1000)
p 'test2'
a.test2(2, 3)

a.test3_1('abc')
a.alias_1('def')

p "--------\n\n"


p '----クラスの再オープン----'

class Foo
  def m1
    p 'm1'
  end
end

class Foo
  def m2
    p 'm2'
  end
end

a = Foo.new
a.m1
a.m2

p "--------\n\n"