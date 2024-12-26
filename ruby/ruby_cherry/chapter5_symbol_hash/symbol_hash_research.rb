=begin
p :ruby
puts :ruby
a = :ruby
p a
puts a

hash1 = { key1: 1, key2: 2}
hash2 = {**hash1, key3: 3}
p hash2

h = Hash.new('miss')
p h
p h[:key] = 1
p h
p h[:a]

h = Hash.new{ |hash, key| hash[key] = 'default' }
h[:key1]
p h #=> {:key1 => 'default'}

p :a.object_id
p :'a'.object_id
=end
