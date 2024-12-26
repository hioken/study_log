def find_currency(country)
  currencies = {japan: 'yen'}
  currencies[:"#{country}"]
end

def show_currency(country)
  find_currency(country)&.upcase
end

p show_currency('japan')
p show_currency('us')
