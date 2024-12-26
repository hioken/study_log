=begin
p [1,2,3].each
puts "success"


def greeting
  puts 'Start.'
  if block_given?
    puts yield 'テスト'
  end
  puts 'End.'
end

greeting
greeting {|b1, b2| "一つ目のブロック引数: #{b1}\n二つ目のブロック引数: #{b2.class}"}


def relay(&block)
  greeting(block)
end

def greeting(block)
  puts 'Start.'
  p block.class
  if block_given?
    p block.call('a')
  end
  puts 'End.'
end

relay { |text| text }


def relay(name, &block)
  puts block.arity #=> ブロックの数を確認
  greeting(name, &block) #=> ブロックをgreetingに渡す
end

def greeting(name)
   puts yield("こんにちは, ", name)
end

relay("Alice") { |hello, name| "#{hello} #{name}"}


def relay_1(&block)
  puts "\n1の結果"
  block_check(&block)
  puts "End."
end

def relay_2(&block)
  puts "\n2の結果"
  block_check(block)
  puts "End."
end

def block_check(arg = "none")
  p block_given?
  p arg
  puts arg.call if arg.class == Proc
end

relay_1 { |block| block.class }
#=> true, "none"
relay_2 { |block| block.class }
#=> false, #<Prock:~省略~>, NilClass


def block_research(arg = 'none')
  puts "\nStart."
  yield("success") if block_given?
  receiver(&arg) if arg.class != String
  puts "End."
end

def receiver
  yield("success")
end

block_research(&Proc.new { |text| puts text })
block_research(Proc.new { |text| puts text })


def relay
  arg = Proc.new {yield}
  receiver(&arg)
end

def receiver(arg)
  yield 'success'
end

relay{ |text| puts text } #=> error、yieldはcallと同じ


def lambda_research
  p yield 1, 2
  p yield 1, 2, 3
end

data1 = lambda { |a, b| a.to_i + b.to_i }
data2 = Proc.new { |a, b| a.to_i + b.to_i }
p data1
p data2

#lambda_research &data2 #=> lambdaだとerror


def relay(&block)
  #p &block.class #=> error
  p &block #=> 表示なし
  p block.class
  p block
end

relay { |text| text }


class String
  def success
    puts 'success'
  end
end

['a', 'b', 'c'].map(&:success)


class Object
def success(data)
  puts 'success'
end
end

data1 = Proc.new { |a| a.upcase }
data2 = :split.to_proc
data3 = :success.to_proc

p data1
p data2
p data3

puts "\n"

p data1.call("a")
p data2.call('a b c,d', ',', 2)
data3.call(Object.new, 'a')

p lambda { |a| a}
=end
