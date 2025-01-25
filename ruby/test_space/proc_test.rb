# a = 1

# 3.times do |a|
#   puts a
# end

# puts a


# def variable_factory
#   a = 1
#   b = 2
# end
# variable_factory
# puts a

# a = 1
# def variable_reader
#   puts a
# end
# variable_reader

# count = 0
# increment = Proc.new do
#   count += 1
# end
# puts increment.call
# puts increment.call


# count = 1
# increment = Proc.new do
#   defined?(count) ? count += 1 : count = 1 
# end
# puts increment.call
# puts increment.call
# count = 100
# puts increment.call


# increment = Proc.new do
#   defined?(count) ? count += 1 : count = 1 
# end
# count = 1
# puts increment.call
# puts increment.call
# count = 100
# puts increment.call




# def m 
#   a = 1
#   a.object_id
# end
# object_id_check = Proc.new do
#   p "Defined?: #{!!defined?(a)}" # 明示的に出力を確認
#   a = 1
#   p "Object ID: #{a.object_id}" # Object IDも分かりやすく
# end
# object_id_check.call
# object_id_check.call
# p m
# p m
# a = 1
# p a.object_id


# increment = Proc.new do
#   defined?(count) ? count[0] = count[0] + 1 : count = [1] 
#   count.object_id
# end
# count = [1]
# puts increment.call
# puts increment.call
# count = [100]
# puts increment.call


# count = [1]
# increment = Proc.new do
#   defined?(count) ? count[0] = count[0] + 1 : count = [1] 
#   count.object_id
# end
# puts increment.call
# puts increment.call
# count = [100]
# puts increment.call


# ar = [0]
# p ar.object_id
# ar[0] = 1
# p ar.object_id




# a = 2
# update_a = Proc.new do
#   a = 1
# end
# update_b = Proc.new do
#   b = 1
# end
# b = 2

# p a
# p b
# update_a.call
# update_b.call
# p a
# p b
# a = 100
# update_a.call
# b = 100
# update_b.call
# p a
# p b



# class Abc
#   def call_proc(proc)
#     result = proc.call
#     p result
#   end
# end


# a = 1
# update_a = Proc.new do
#   a += 1
# end

# Abc.new.call_proc(update_a)
# Abc.new.call_proc(update_a)
