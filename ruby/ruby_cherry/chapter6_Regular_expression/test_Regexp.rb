=begin
text1 = <<TEXT
I love Ruby.
Python is a great language.
Java and Javascript ard different.
English
japanese
TEXT

puts "text1 : #{text1.scan(/[A-Z][A-Za-z]+/)}"


text2 = <<TEXT
私の郵便番号は2395020です。
私の住所は6330201 兵庫県西脇市伊多波町だよ。
TEXT

puts "text2 : #{text2.gsub(/(\d{3})(\d{4})/, '\1-\2')}"


text = <<-TEXT
名前：伊藤淳一
電話：03-1234-5678
住所：兵庫県西脇市板波町1-2-3
TEXT

puts text.scan(/\d-\d/)


text = <<TEXT
<select name="game_console">
<option value="none"></option>
<option value="wii_u">Wii U</option>
<option value="ps4">プレステ4</option>
<option value="gb">ゲームボーイ</option>
</select>
TEXT

p text.scan(/<option value="\w+">[^<>]*<\/option>/).join("\n").gsub(/<option value="([a-z0-9_]+)">([^<>]*)<\/option>/, '\1, \2')


text = <<TEXT
{
  japan:	'yen',
  america:'dollar',
  italy:     'euro'
}
TEXT

puts text.gsub(/:\s*/, ': ')

text = <<TEXT
name,email
alice,alice@example.com
bob,bob@example.com
TEXT

puts text.gsub(/,/, "\t")


text = <<TEXT
Feb 14 07:33:02 app/web.1:  Completed 302 Found ...
Feb 14 07:36:46 heroku/api:  Starting process ...
Feb 14 07:36:50 heroku/scheduler.7625:  Starting ...
Feb 14 07:36:50 heroku/scheduler.7625:  State ...
Feb 14 07:36:54 heroku/router:  at=info method=...
Feb 14 07:36:54 app/web.1:  Started HEAD "/" ...
Feb 14 07:36:54 app/web.1:  Completed 200 ...
TEXT

puts '結果1'
puts text.scan(/^.+(app|router).+$/).join("\n")
puts "\n結果2"
puts text.gsub(/^.+heroku\/(api|scheduler).+\n/, '')


text = <<TEXT
Feb 14 07:33:02 app/web.1:  Completed 302 Found ...
Feb 14 07:36:46 heroku/api:  Starting process ...
Feb 14 07:36:50 heroku/scheduler.7625:  Starting ...
Feb 14 07:36:50 heroku/scheduler.7625:  State ...
Feb 14 07:36:54 heroku/router:  at=info method=...
Feb 14 07:36:54 app/web.1:  Started HEAD "/" ...
Feb 14 07:36:54 app/web.1:  Completed 200 ...
TEXT

puts '結果1'
puts text.scan(/^.+(?:app|router).+$/).join("\n")
puts "\n結果2"
puts text.gsub(/^.+heroku\/(api|scheduler).+\n/, '')


text = <<-TEXT
type=zip; filename=users.zip; size=1024;
type=xml; filename=posts.xml; size=2048;
TEXT
p text.scan(/filename=([^;]+)/).map{|s| s.last}


text = "私の誕生日は1997年7月17日です"
data = text.match(/(\d+)年(\d+)月(\d+)日/)
p data.class
p data[1..3].class

data2 = /(\d+)年(\d+)月(\d+)日/.match(text)
p data2


text = "私の誕生日は1997年7月17日です"
/(?<year>\d+)年(?<month>\d+)月(?<day>\d+)日/ =~ text
p year #=> "1997"


p 'ab,cd-ef'.split(/,|\-/)
=end

a = /\d{3}/ =~ '111'
b = 1 == 1
p a
p b
