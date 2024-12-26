puts "ruby test.rb file_1.txt file_2.txt\n\n"

puts '----再代入の警告----'
A = 1
p A
A = 2
p A
puts "--------\n\n"

puts '----組み込み定数----'
p "STDIN #{STDIN}"
p "ENV #{ENV["TEST"]}"
p "ARGV #{ARGV}"
p "ARGV.class #{ARGV.class}"
p "DATA.gets #{DATA.gets}"
p "RUBY_PLATFORM #{RUBY_PLATFORM}"
puts "--------\n\n"

puts '----ARGF----'
puts 'file_1.txtとfile_2.txtのテキスト出力'
l = 0
while line = ARGF.gets
  puts ("#{l+=1}: #{line}")
end

puts "--------\n\n"

puts '----$LOAD_PATH----'
p $LOAD_PATH
puts "--------\n\n"


__END__
__END__以下の落書き