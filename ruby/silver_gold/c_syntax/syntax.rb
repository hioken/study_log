puts '----リテラル----'
p "?r #{?r}"
print '?\C-v '
p (?\C-v)
puts "--------\n\n"

puts '----引数----'
def test_method(a, b, c = 0, *d, e, f, **g)
  puts "a, b, c: #{a}, #{b}, #{c}"
  print 'd: '; p d
  puts "e, f: #{e}, #{f}"
  print g; p g
end

test_method(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, h: 'a', i: 'b')
puts "--------\n\n"

puts '----擬似変数----'
p "__FILE__, __LINE__: #{__FILE__}, #{__LINE__}"
puts "--------\n\n"

puts '----その他----'
abc ||= 'data'
efg &&= 'data'
print "abc ||= 'data':"; p abc
print "efg &&= 'data': "; p efg
puts "--------\n\n"

puts '----ヒアドキュメント----'
text = <<~TEXT
  koreha
  test
TEXT
p text
puts "--------\n\n"

puts '----%記法----'
print '%Q!ab#{1 + 3}!: '; p %Q!ab#{1 + 3}!
puts "--------\n\n"