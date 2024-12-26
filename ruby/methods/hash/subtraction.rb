class Hash
  def subtract!(rob, all_key_string: false)
    if all_key_string
      h_2 = self.map { |k, v| [k.to_s, v] }.to_h
      self.delete_if { |k, v| k.class != String }
      self.merge!(h_2)
      rob.each { |k, v| self[k.to_s] = self[k.to_s].to_i - v }
    else
      rob.each { |k, v| self[k] = self[k].to_i - v }
    end
    self
  end

  def subtract(rob, all_key_string: false)
    self_dup = self.dup
    if all_key_string
      h_2 = self_dup.map { |k, v| [k.to_s, v] }.to_h
      self_dup.delete_if { |k, v| k.class != String }
      self_dup.merge!(h_2)
      rob.each { |k, v| self_dup[k.to_s] = self_dup[k.to_s].to_i - v }
    else
      rob.each { |k, v| self_dup[k] = self_dup[k].to_i - v }
    end
    self_dup
  end
end

# テスト
a = {a: 1, b: 2, c: 20}
b = {a: 1, b: 1, d: 100}

p a.subtract(b)
p a
p a.subtract!(b)
p a
