module ClassMethods
  class Integer
    def plus(n)
      self + n
    end
  end
end

class Tc
  include ClassMethods
  attr_reader :num

  def initialize(num)
    @num = num.plus(4)
  end

  class Integer
    def plus(n)
      self + n
    end
  end

end

p Tc.new(2).num
