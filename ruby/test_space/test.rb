a = false
b = nil
b ? p(b) : p(a) if a

=begin
hash = {a: 1, b: 6}
range = (1..4)
hash.select!{|key, value| range.include?(value) }
p hash

a = [{a: 'a', b: 'b'}, {a: 1, b: 2}]
p a[1]

hash = {value_1: {key1: 1, key2: 2}, value_2: {key1: 3, key2: 4}}
ret = {}
hash.each do |a, b|
  ret[b[:key1]] = b[:key2]
end
p ret

nil && (p 'a')
(p 'a') && nil

module Dammy
  def method_1
    p self.amount
  end
end

class Amount
  include Dammy
  attr_accessor :amount
  def initialize
    @amount = 1
  end
end

a = Amount.new
a.method_1

def printer(a)
  a.each do |key, value|
    p key
  end
end

a = {'a' => 'a', :b => 'a'}

printer(a)

class Tester

  def initialize
    @data = 'abc'
  end


end

=end
