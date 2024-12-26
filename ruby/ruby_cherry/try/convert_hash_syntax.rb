def convert_hash_syntax(hash)
  ret = hash.gsub(/:(\w+) *=> */, '\1: ')
  ret.gsub(/(['"].+['"]) *=> */, '\1 => ')
end

data = <<TEXT
TEXT
