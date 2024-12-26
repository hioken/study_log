a = [1, 2, 3]

# a.each do |x|
#   p x
#   return 0
# end

lmd2 = -> (x, a3) do
  x.call(a3)
  p 'lmd2'
end

lmd = ->(a2) do
  a2.each do |x|
    p x
    return 0
  end
  p 'lmd1'
end

lmd2.call(lmd, a)

p 'end'