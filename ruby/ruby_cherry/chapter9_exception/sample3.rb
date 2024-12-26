def method_1
  begin
    1.join
  rescue ZeroDivisionError => exception
    puts '例外処理1'
  rescue NameError => e
    puts '例外処理2'
    p e.class
  end
  puts 'End.'
end

method_1
