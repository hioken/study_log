=begin
def henkan
  self.to_i + 2
end

a = '1'.to_i + 2
a = 'hello'
puts a

a = [2, 5]
puts
print a

name = 'Alice'
puts "Hello, #{name}"

if !(1 == 3)
  puts 'hello'
end

a =
  1
puts a

data = 2
a =
  if data == 1
    'hello'
  else
    'good bye'
  end
puts a

p 'オラ' * 10


def name1(int)
  'Alice' if int < 2
end

def name2(int)
  'Lily' if int < 2
end

def name3(int)
  'Mea' if int < 2
end

a = name1(2) || name2(1) || name3(2)
p a # => "Lily"

message = "Hello"
message =
  if message
    message
  else
    "メッセージが空です"
  end
p message

a = 'test'
b = a
p a.object_id
p b.object_id
p "\n"
a.upcase!
p a
p b

require 'date'
p Date.today
=end

a, b, c = 1, 2, 3

puts a
puts b
puts c
