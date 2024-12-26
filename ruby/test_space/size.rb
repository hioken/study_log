require 'objspace'
rvalue_size = GC::INTERNAL_CONSTANTS[:RVALUE_SIZE]

hash = {}
100.times do
  a = 0
  i = 0
  loop do
    a = rand(500...6999)
    break if !(hash.keys.include?(a)) || i > 100
    i += 1
  end
  hash[a] = [a, a, 'aaaaaaa', 'adbあa']
end

p hash
p ObjectSpace.memsize_of(hash)
