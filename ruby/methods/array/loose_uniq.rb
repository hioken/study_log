class Array
  def loose_uniq!(n)
    flg = {}
    self.delete_if do |v|
      flg[v] ? flg[v] += 1 : flg[v] = 1
      flg[v] > n
    end
    self
  end

  def loose_uniq(n)
    a = self.dup
    flg = {}
    a.delete_if do |v|
      flg[v] ? flg[v] += 1 : flg[v] = 1
      flg[v] > n
    end
    a
  end
end
