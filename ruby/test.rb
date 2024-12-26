class Person
  attr_accessor :name, :age
  def initialize(name)
    @name = name
  end
end

per = Person.new('taro')
per.age = 2
p per
