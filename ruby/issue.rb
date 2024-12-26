class Data2
  attr_accessor :num, :num2
  def initialize
    @num = 0
    @num2 = 0
  end

  def make_data(n)
    @num = n[0]
    @num2 = n[1]
    return self
  end
end

a = [[1,2],[3,4],[5,6]]
obj = Data2.new

b = a.map do |data|
  ret = obj.make_data(data)
  puts ret.num
  ret
end

p b