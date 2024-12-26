def hash(int)
  str = int.to_s
  (str.chars.inject(0) { |hash, i| hash + i.to_i }) % 10
end


array = []
[938, 2983, 13, 149].each do |i|
  place = hash(i)
  unless array[place]
    array[place] = i
  else
    while(array[place] != nil)
      place += 1
    end
    array[place] = i
  end
end


p array





=begin
a = [1, 2, 3, 4, 5]
a.shuffle!
p a
1.upto(a.size - 1) do |i|
  i.downto(1) do |j|
    if a[j - 1] > a[j]
      tmp = a[j]
      a[j] = a[j - 1]
      a[j - 1] = tmp
    end
  end
end
p a



def to_num(str)
  p str
  case str
  when 'gu' then 0
  when 'tyoki' then 1
  when 'pa' then 2
  else
    p 'retry gu tyoki pa-'
    to_num(gets.chomp)
  end
end


while true
  puts ''
  p 'START'
  p 'taro gu tyoki pa'
  taro = to_num(gets.chomp)
  p 'hanako gu tyoki pa'
  hanako = to_num(gets.chomp)

    p '---------------'
  if taro == hanako
    p 'RESULT draw'
  elsif (taro + 1) % 3 == hanako
    p 'RESULT win taro'
  else
    p 'RESULT win hanako'
  end
    p '---------------'

end
=end
