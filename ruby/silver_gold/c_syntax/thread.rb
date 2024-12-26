t1 = Thread.new do
  10.times do |i|
    p 'aaaaaaa'
  end
end

1000.times do |s|
  p s
end