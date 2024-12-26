class Foo

  protected

  def tm
    puts 'tm'
  end

  private

  def pm
    puts 'pm'
  end
end

class Baz < Foo

  def tm2
    tm
  end

  def pm2
    pm
  end
end


a = Baz.new
b = Foo.new
a.tm2
# b.tm

a.pm2







class Foo


  @a = 1
  @b = 2

  def self.a
    @a
  end
end

class Object
  attr_accessor :b
end

p Foo.a
p Object.b

@b = 2
p Object.b

p self.b



module M1
  class C1
    attr_accessor :a

    def initialize(a)
      @a = a
    end

    def c1m1
      puts 'c1m1'
    end

  end
end

class C1
  def c1m2
    puts 'c1m2'
  end
end

c1 = M1::C1.new(1)
p c1.a

c2 = C1.new
c2.c1m2
c2.c1m1