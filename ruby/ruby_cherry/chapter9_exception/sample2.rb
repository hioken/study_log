def method_1
  puts '1-s'
  begin
    method_2
  rescue
    puts '例外処理実行'
    method_4
  end
  puts '1-e'
end

def method_2
  puts '2-s'
  begin
    method_3
  rescue
    puts '2-e'
  end
end

def method_3
  puts '3-s'
  1 / 0
  puts '3-e'
end

def method_4
  puts 'メソッド4が実行されました'
end

method_1
