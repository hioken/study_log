5.times do |i|
  if false
    begin
      raise StandardError
    rescue => e
      raise unless i < 3
      puts i
    end
  else
    p i
  end
end
