def fizz_buzz(number)
  if number % 15 == 0
    "Fizz Buzz"
  elsif number % 5 == 0
    "Buzz"
  elsif number % 3 == 0
    "Fizz"
  else
    number.to_s
  end
end

begin
  puts "数値を入力してください、終了する場合は fin を入力してください。"
  number = gets
  if number == "fin\n"
    number = false
  else
    puts "結果 : #{fizz_buzz(number.to_i)}\n\n"
  end
end while number
