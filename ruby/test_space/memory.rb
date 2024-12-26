require 'objspace'
a = [[1, 3], [1, 2], [1, 3], [2, 3], [2, 2], [2, 3], [3, 4], [3, 2], [3, 3], [4, 2], [4, 3], [4, 3]]

10000.times do
b = 0
i = 0
array = []
a.each do |data|
  if i == 0
    b = data[0]
  elsif b != data[0]
    b = data[0]
    p array
    array = []
    i = 0
  end
  array[i] = data
  i += 1;
end

end

puts "#{ObjectSpace.memsize_of_all * 0.001 * 0.001} MB"
