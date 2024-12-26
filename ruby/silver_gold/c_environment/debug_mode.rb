p 'raise前'
begin
  raise
rescue
  p $stderr
end
p 'raise後'