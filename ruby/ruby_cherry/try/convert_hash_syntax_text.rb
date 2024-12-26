require 'minitest/autorun'
require_relative './convert_hash_syntax.rb'

class ConvertHashSyntaxTest < Minitest::Test
  def test_convert_hash_syntax
test_data = <<TEXT
  {
    :name => 'Anice',
    'age'=>20,
    :gender  =>  :female
  }
TEXT

expect_data = <<TEXT
  {
    name: 'Anice',
    'age' => 20,
    gender: :female
  }
TEXT

    assert_equal expect_data, convert_hash_syntax(test_data)
  end
end
