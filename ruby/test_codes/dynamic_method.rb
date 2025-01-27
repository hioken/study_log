def make_varidator(roles)
  return Proc.new do |data|
    roles.each do |key, role|
      if (!role.call(data[key]))
        raise "Validation failed for #{key}"
      end
    end
  end
end


validator = make_varidator({
  name: Proc.new { |value| value.class == String && value.length > 2}
})

user_data = {name: 'A' }

p validator.call(user_data)