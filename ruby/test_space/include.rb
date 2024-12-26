module Ap
  def hello
    puts 'hello'
  end
end

module Bp
  include Ap
end

class Tp
  include Bp
end

Tp.new.hello
