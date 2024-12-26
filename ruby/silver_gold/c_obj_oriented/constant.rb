module M1
end

module M2
  C = 2
end

M1::A = M2

M1::A::B = 1


p M1::A
p M1::A::B
p M1::A::C


puts '----class----'

class C1
  A = 1
end

p C1::A


puts '----定数----'

TOP = 100

class C10
  p TOP
end