=begin
array = [1, 'aa', true, nil, false]
id = 0

array.each do |data|
  print "#{id} : "
  if data
    puts "true"
  else
    puts "false"
  end
  id += 1
end

array = [[1, 2, 3], [4, 5, 6]]
puts array[1][2]

array = [0]
for i in 1..9 do
  array << i
end
p array

array = [1, 2, 3, 4]
array.delete_at(0, 2)
p array => error

array = [0, 1, nil, false, 2]
array.delete(false)
p array => [0, 1, nil, 2]

array = [0, 1, 2, false]
array.delete_if do |data|
  false
  true
end
p array

array = [0, 1, nil, false, 2]
array = array.map! {|data| data * 2 if data }
p array => [0, 2, nil, false, 4]

array = [0, 1, nil, false, 2]
count = 0
array.delete_if do |data|
  count += 1
  count > 2
end
p array => [0, 1]

array = [0, 1, nil, false, 2]
a =
array.find do |data|
  data > 0
end
p a

a = (1..5).inject(0) {|result, n| result + n }
p a

a =  Array.new(7){|n| n }
a.each_with_index{|data, i| puts i}

i = 0
a = Array.new(3) do |n|
  [[i+=1, i+=1, i+=1], [i+=1, i+=1, i+=1]]
end
p a
a.each { |n, m, l| puts "n: #{n}, m: #{m}, l: #{l}"}
'lはnilになる、恐らく、ブロック変数は2次元配列までしか対応してない'

c1, c2, c3 = 0, 0, 0
a = Array.new(5) {|n| n}
b = Array.new(5) {|n| n}

a.each do |num|
  catch :done do
    b.each do |num2|
      throw(:done) if num2 == 3
      c2 += 1
    end
  end
  c1 += 1
end

p c1
p c2

"abcd"[1..2].each { |s| puts s }

def method(*values, hikisu2, *test)
  p values
  p hikisu2
  p test
end
method([1, 2, 3] 'a', ['b']) #=> error
=end
