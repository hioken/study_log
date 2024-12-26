class MatchData
  def each(&block)
    if block.arity == 2
      for i in 1..self.size
        yield self[0], self[i]
      end
    elsif block.arity == 1
      for i in 1..(self.size - 1)
        yield self[i]
      end
    else
      raise "ブロック引数の個数は2つまでです"
    end
  end

  include Enumerable
end


text = "a, b, c"
data = /(\w), (\w), (\w)/.match(text)

data.each { |value| puts value }
puts "\n"
p data.map { |value| value }
puts "\n"
data.each { |value, v2, v3| p v3 }
