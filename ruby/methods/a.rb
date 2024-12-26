def check(map, y, x, limit_check, results)
  if limit_check && map[y][x] == '.'
    results << [y, x]
    true
  else
    results << ['Stop', '']
    false
  end
end

row, column, y, x, move_cnt = gets.split.map(&:to_i)
map = []; row.times { map << gets.chomp.chars }
moves = []; move_cnt.times { moves << (gets.chomp == 'R' ? 1 : 3) }
dir = 0
results = []

moves.each do |move_dir|
  case move_dir + dir
  when 0
    y += 1
    break unless check(map, y, x, y < row, results)
  when 1
    x += 1
    break unless check(map, y, x, x < column, results)
  when 2
    y -= 1
    break unless check(map, y, x, y >= 0, results)
  when 3
    x -= 1
    break unless check(map, y, x, x >= 0, results)
  end
end

results.each do |result|
  puts result.join(' ')
end
