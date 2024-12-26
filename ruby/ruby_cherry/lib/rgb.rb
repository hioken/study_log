def to_hex(r, g, b)
=begin
  '#' +
  r.to_s(16).rjust(2, '0') +
  g.to_s(16).rjust(2, '0') +
  b.to_s(16).rjust(2, '0')

  hex = '#'
  [r, g, b].each do |int|
    hex += int.to_s(16).rjust(2, '0')
  end
  hex
=end

  [r, g, b].inject('#') do |hex, int|
    hex + int.to_s(16).rjust(2, '0')
  end
end


def to_ints(hex)
  hex.scan(/\w\w/).map(&:hex)
end
