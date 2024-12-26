def command_make(command)
  while [' ', "\n", "\t"].include?(command[-1])
    command.slice!(-1)
  end

  puts command.split("\n").join(' && ')
end

text = File.read("command.txt")

ret =  text.gsub(/\$(.+\n)/) { $1 }.split("\n").delete_if { |str| [str[0], str[1]].include?('#') || str.length < 2 || str.include?("SHELL -l") }.join("\n")

command_make(ret)
