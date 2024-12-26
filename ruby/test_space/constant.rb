module Dark
  def method_1
    p CONSTANT
  end
end

class Hory
  CONSTANT = {a: 1}
end

class Light < Hory
  extend Dark
  attr_accessor :data
  def initialize
    @data = :a
  end

  def method_2
    p CONSTANT
  end
end


Light.new.method_2
# Light.method_1 #=> error
