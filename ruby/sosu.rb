def gets_num
  puts '0より大きいの整数を入力してください'
  check = gets.to_i
  if check <= 0
    puts '数値が0以下です'
    gets_num
  else
    return check
  end
end

search_range = gets_num
flg = true
prime_nums = []

(1..search_range).each do |i|
  (1..i).each do |y|
    if y != 1 && i != y && i % y == 0
      flg = false
      break
    end
  end
  if flg
    prime_nums.push(i)
    flg = false
  end
end

puts 'result ' + prime_nums.join(', ')