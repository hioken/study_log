array = [0, 1, 2, 3, 4]
p "test1"
p array[1, 3]
p array[-2]

printf "\n\ntest2\n"
array[1, 4] = "change"
p array
array = [0, 1, 2, 3, 4]

printf "\n\ntest3\n"
array2 = ["a", 3, "b", 0, 6]
p array | array2

printf "\n\ntest4\n"
a, b, *c = array
p a
p b
p c

data =
  if 1 == 1
    '成功'
  else
    '失敗'
  end
puts data
