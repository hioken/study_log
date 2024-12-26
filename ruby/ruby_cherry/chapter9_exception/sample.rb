puts 'Start.'
module Greeter
  def hello
    'hello'
  end
end

begin
  puts Greeter.new.hello
rescue
  puts "例外処理"
end
puts 'End.'
